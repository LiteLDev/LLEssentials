#include "pch.h"
#include "homeStorage.h"
#include <LRUMap.h>

U64LRUmap<Homes, 17> HomeCache(48);
Homes& getHomeInCache(xuid_t xid) {
	Homes* rv = HomeCache.find(std::stoull(xid));
	if (!rv) {
		rv = HomeCache.insert(std::stoull(xid), std::stoull(xid));
	}
	return *rv;
}
