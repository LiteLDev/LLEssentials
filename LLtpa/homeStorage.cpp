#include "homeStorage.h"
#include <Dedicated/LRUMap.h>

U64LRUmap<Homes, 17> HomeCache(48);

Homes& getHomeInCache(unsigned long long xid) {
	Homes* rv = HomeCache.find(xid);
	if (!rv) {
		rv = HomeCache.insert(xid, xid);
	}
	return *rv;
}
