// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 BDXLUA_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// BDXLUA_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#pragma once
#ifdef LLLUA_EXPORTS
#define LLLUA_API __declspec(dllexport)
#else
#define LLLUA_API __declspec(dllimport)
#endif

#include<variant>
#include<vector>
#include<unordered_map>
#include<stl\optional.h>
#include<stl\static_queue.h>
#include<luafly.h>

extern struct lua_State* _L;
extern bool _LIsInMain;
extern int _LEHIDX;

using std::variant,std::vector,std::unordered_map;
typedef variant<long long, string> ldata_t;
typedef ldata_t(*luacb_t)(vector<ldata_t>& arg);
LLLUA_API extern unordered_map<string, luacb_t> bindings;
struct ldata_ref_t {
	union {
		long long lv;
		string const* sp;
	} d;
	bool isLong;
	ldata_ref_t(long long x) {
		d.lv = x;
		isLong = true;
	}
	ldata_ref_t(string const* x) {
		d.sp = x;
		isLong = false;
	}
	string const& asStr() const{
		return *d.sp;
	}
	long long asLL() const {
		return d.lv;
	}
};
LLLUA_API optional<long long> call_lua(const char* name, std::initializer_list<ldata_ref_t> const& arg);
#ifdef LLLUA_EXPORTS
int lua_bind_GUI(lua_State* L);
#endif

#define CATCH() catch (string e) { \
		luaL_error(L, e.c_str()); \
		return 0; \
	} \
	catch (std::exception e) { \
		luaL_error(L, e.what()); \
		return 0; \
	} \
	catch (...) { \
		luaL_error(L, "internal error"); \
		return 0; \
	}

template<int rv = 0>
struct LuaStackBalance {
	int stk;
	lua_State* myL;
	inline LuaStackBalance(lua_State* L) {
		stk = lua_gettop(L);
		myL = L;
	}
	inline ~LuaStackBalance() {
		lua_settop(myL, stk + rv);
	}
};
struct LuaCtxSwapper {
	bool oldismain;
	lua_State* oldstate;
	LuaCtxSwapper(lua_State* L) {
		oldstate = L;
		oldismain = false;
		std::swap(_L, oldstate);
		std::swap(_LIsInMain, oldismain);
	}
	~LuaCtxSwapper() {
		std::swap(_L, oldstate);
		std::swap(_LIsInMain, oldismain);
	}
};



#include<luafly.h>
auto inline getEHIDX() {
	if (!_LIsInMain) {
		lua_rawgeti(_L, LUA_REGISTRYINDEX, _LEHIDX);
		return lua_gettop(_L);
	}
	else {
		return 1;
	}
}
template<typename... TP>
optional<long long> call_luaex(const char* name, TP&&... args) {
	LuaStackBalance B(_L);
	int EHIDX(getEHIDX());
	if (lua_getglobal(_L, name) == 0) {
		printf("[LUA] function %s not found\n", name);
		return {};
	}
	LuaFly fly{ _L };
	fly.pushs(std::forward<TP>(args)...);
	if (!fly.pCall(name, sizeof...(args), 1, EHIDX)) {
		printf("[Lua] <%s> Error: %s\n", name,lua_tostring(_L, -1));
		return {};
	}
	if (lua_isinteger(_L, -1)) {
		long long x;
		fly.pop(x);
		return { {x} };
	}
	else {
		return {};
	}
}
template<typename... TP>
void call_luaex_norv(const char* name, TP&&... args) {
	LuaStackBalance B(_L);
	int EHIDX(getEHIDX());
	if (lua_getglobal(_L, name) == 0) {
		printf("[LUA] function %s not found\n", name);
		return;
	}
	LuaFly fly{ _L };
	fly.pushs(std::forward<TP>(args)...);
	if (!fly.pCall(name, sizeof...(args), 0, EHIDX)) {
		printf("[Lua] <%s> Error: %s\n", name,lua_tostring(_L, -1));
		return;
	}
}


struct LModule {
	void(*onload)(lua_State* L);
	void(*ondefunct)(lua_State* L);
	LModule(void(*a)(lua_State* L), void(*b)(lua_State* L) = nullptr) {
		onload = a;
		ondefunct = b;
	}
	void init(lua_State* L) {
		onload(L);
	}
	void defunct(lua_State* L) {
		if (ondefunct) ondefunct(L);
	}
};
LLLUA_API void registerLuaModule(LModule x);
static inline string_view LReadStr(lua_State* L,int idx) {
	size_t len;
	auto pchr = lua_tolstring(L, idx, &len);
	return { pchr,len };
}