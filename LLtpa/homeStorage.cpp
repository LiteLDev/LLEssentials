#include "pch.h"
#include "homeStorage.h"
U64LRUmap<Homes, 17> HomeCache(48);
Homes& getHomeInCache(xuid_t xid) {
	Homes* rv = HomeCache.find(xid);
	if (!rv) {
		rv = HomeCache.insert(xid, xid);
	}
	return *rv;
}
