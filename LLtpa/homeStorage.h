#pragma once
#include "pch.h"
extern std::unique_ptr<KVDB> db;
struct Vec4 {
	Vec3 vc;
	char dimid;
	string toStr()const {
		return "(" + std::to_string(vc.x) + " , " + std::to_string(vc.y) + " , " + std::to_string(vc.z) + " , " + std::to_string(dimid) + " , " + ")";
	}
	template<typename _TP>
	void pack(WBStreamImpl<_TP>& ws) const {
		ws.apply(vc, dimid);
	}
	void unpack(RBStream& rs) {
		rs.apply(vc, dimid);
	}
	void teleport(ServerPlayer* wp) {
		wp->teleport(vc, dimid);
	}
	Vec4(ServerPlayer* wp) {
		vc = wp->getPos();
		vc.y -= 1.5;
		dimid = wp->getDimensionId();
	}
	Vec4(Vec3 x, int dim) :vc(x), dimid(dim) {}
	Vec4() {}
};
struct Homes {
	struct Home {
		Vec4 pos;
		string name;
		Home() {}
		Home(string const& b, ServerPlayer ac) :name(b), pos(&ac) {
		}
		Home(string const& b, Vec4 const& ac) :name(b), pos(ac) {
		}
		template<typename _TP>
		void pack(WBStreamImpl<_TP>& ws) const {
			ws.apply(pos, name);
		}
		void unpack(RBStream& rs) {
			rs.apply(pos, name);
		}
	};
	unsigned long long owner = 0;
	std::list<Home> data;
	Homes() {}
	Homes(unsigned long long xid) {
		string val;
		if (db->get(to_view(xid), val)) {
			RBStream rs{ val };
			rs.apply(data);
		}
		owner = xid;
	}
	Homes(string_view own) {
		string val;
		auto x = std::stoull(PlayerDB::getXuid((std::string)own));
		if (x != 0) {
			if (db->get(to_view(x), val)) {
				RBStream rs{ val };
				rs.apply(data);
			}
			owner = x;
		}
	}
	template<typename _TP>
	void pack(WBStreamImpl<_TP>& ws) const {
		ws.apply(data);
	}
	void unpack(RBStream& rs) {
		rs.apply(data);
	}
	void save() {
		WBStream ws;
		ws.apply(*this);
		if (owner != 0)
			db->put(to_view(owner), ws);
	}
};
Homes& getHomeInCache(unsigned long long xid);