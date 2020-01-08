#ifndef _FINDSHORTESTPATH_H
#define _FINDSHORTESTPATH_H
#include "GraphPath.h"
#include "Node.h"
#include "GraphCompare.h"
List * generateShortestPath(NetworkNode * nNode);
void* compareAndAddShortestPathIntoWorkingAVL(ShortestPathNode * sPathToAdd);
void * findAndAddNearestNode(GraphPath* graphPath);

#endif // _FINDSHORTESTPATH_H
