#pragma once
#include <iostream>
#include<lua.hpp>
#include<string>
#include<string_view>
#include<type_traits>
#include<algorithm>
#include<vector>
#include<unordered_map>
using std::string, std::string_view;
using namespace std::string_literals;

class xstring:public string{
public:
    using string::operator=;
    using string::operator std::basic_string_view<char, std::char_traits<char>>;
    using string::operator+=;

};

struct LuaFly {
    lua_State* L;
    inline LuaFly(lua_State* L_) {
        L = L_;
    }
    inline bool pCall(const char* name,size_t in,int out,int EHIDX) {
        if (lua_pcall(L, (int)in, out, EHIDX) != 0) {
            printf("[LUA] pcall %s error %s\n",name,lua_tostring(L,-1));
            return false;
        }
        return true;
    }
    void stack(int sz) {
        lua_checkstack(L, sz);
    }
    template<typename T,typename T2>
    void push(std::unordered_map<T, T2>const& x) {
        lua_newtable(L);
        for (auto& [k,v] : x) {
            push(k);
            push(v);
            lua_rawset(L, -3);
        }
    }
    template<typename T>
    void push(std::vector<T>const& x) {
        lua_newtable(L);
        int idx = 0;
        for (auto& i : x) {
            push(i);
            lua_rawseti(L, -2, ++idx);
        }
    }
    template<typename T,typename std::enable_if_t<std::is_same_v<std::decay_t<T>, string>|| std::is_same_v<std::decay_t<T>, string_view>,int> X=0>
    void push(T&& x) {
        lua_pushlstring(L, x.data(), x.size());
    }
    template<typename T, typename std::enable_if_t<std::is_same_v<std::decay_t<T>, const char*>, int> X = 0>
    void push(T&& x) {
        lua_pushstring(L, x);
    }
    template<typename T, typename std::enable_if_t<std::is_integral_v<std::decay_t<T>>, int> X = 0>
    void push(T&& x) {
        lua_pushinteger(L,x);
    }
    template<typename T, typename std::enable_if_t<std::is_floating_point_v<std::decay_t<T>>, int> X = 0>
    void push(T&& x) {
        lua_pushnumber(L, x);
    }
    template<typename... T>
    void pushs(T&&... a) {
        (push(std::forward<T>(a)), ...);
    }
    void readx(xstring& x,int pos=-1) {
        if (lua_gettop(L) == 0) throw "stack overflow"s;
        switch (lua_type(L, pos)) {
        case LUA_TBOOLEAN:
            x = lua_toboolean(L, pos)?"true":"false";
            break;
        case LUA_TNUMBER:
            if (lua_isinteger(L, pos))
                x = std::to_string(lua_tointeger(L, pos));
            else
                x = std::to_string(lua_tonumber(L, pos));
            break;
        case LUA_TSTRING:
        {
            size_t sz;
            x = string_view{ lua_tolstring(L,pos,&sz),sz };
        }
            break;
        case LUA_TTABLE:
        {
            int ppos = pos < 0 ? (pos - 1) : pos;
            x = "[";
            std::vector<std::pair<int, string>> mp;
            lua_pushnil(L);
            while (lua_next(L, ppos)) {
                //val
                //string dat{ luaL_tolstring(L,-1,&Ldat),Ldat };
                xstring dat;
                pop(dat);
                int IDX = (int)lua_tointeger(L, ppos+1);
                mp.emplace_back(IDX, std::move(dat));
            }
            //lua_pop(L, 1); //pop key
            std::sort(mp.begin(), mp.end());
            for (auto& [K, V] : mp) {
                x += '"';
                x += V;
                x += "\",";
            }
            if (x.back() == ',') x.pop_back();
            x.push_back(']');
        }
            break;
        default:
            throw "x-str required, but "s + luaL_typename(L, pos) + " found";
        };
    }
    void pop(xstring& x) {
        readx(x);
        lua_pop(L, 1);
    }
    template<typename T, typename std::enable_if_t < std::is_same_v<std::decay_t<T>, string>, int> X = 0>
    void pop(T&& x) {
        if (lua_gettop(L) == 0) throw "stack overflow"s;
        if (!lua_isstring(L, -1))
            throw "str required, but "s + luaL_typename(L, -1) + " found";
        size_t sz;
        auto str = lua_tolstring(L, -1, &sz);
        x = string(str, sz);
        lua_pop(L, 1);
    }
    template<typename T, typename std::enable_if_t < std::is_integral_v<std::decay_t<T>>, int> X = 0>
    void pop(T&& x) {
        if(lua_gettop(L)==0) throw "stack overflow"s;
        if (!lua_isinteger(L, -1))
            throw "int required, but "s + luaL_typename(L, -1) + " found";
        x = (std::decay_t<T>)lua_tointeger(L, -1);
        lua_pop(L, 1);
    }
    template<typename T, typename std::enable_if_t <std::is_floating_point_v<std::decay_t<T>>, int> X = 0>
    void pop(T&& x) {
        if (lua_gettop(L) == 0) throw "stack overflow"s;
        if (!lua_isnumber(L, -1))
            throw "num required, but "s + luaL_typename(L, -1) + " found";
        x = (std::decay_t<T>)lua_tonumber(L, -1);
        lua_pop(L, 1);
    }
    template<typename TP>
    void pop(std::vector<TP>& x) {
        if (lua_gettop(L) == 0) throw "stack overflow"s;
        if (!lua_istable(L, -1))
            throw "table required, but "s + luaL_typename(L, -1) + " found";
        lua_pushnil(L);
        while (lua_next(L, -2)) {
            //-2 index
            TP v;
            pop(v);
            x.emplace_back(std::move(v));
        }
        lua_pop(L, 1); //pop key&table
    }
    template<typename TP>
    void pop(std::unordered_map<string, TP>& x) {
        if (lua_gettop(L) == 0) throw "stack overflow"s;
        if (!lua_istable(L, -1))
            throw "table required, but "s + luaL_typename(L, -1) + " found";
        lua_pushnil(L);
        while (lua_next(L, -2)) {
            //-2 index
            xstring k;
            TP v;
            pop(v);
            readx(k);
            x[k] = v;
        }
        lua_pop(L, 1); //pop key&table
    }
    template<typename... T>
    void pops(T&&... args) {
        (pop(std::forward<T>(args)), ...);
    }
    template<typename... T>
    bool Calll(const char* name,int out, T&&... args) {
        lua_getglobal(L, "EXCEPTION");
        auto EHIDX = lua_gettop(L);
        if (lua_getglobal(L, name) == 0) return false;
        (push(std::forward<T>(args)), ...);
        return pCall(name, sizeof...(T), out, EHIDX);
    }
    auto top() {
        return lua_gettop(L);
    }
};