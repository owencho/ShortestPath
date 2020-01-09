#ifndef _FINDSHORTESTPATH_H
#define _FINDSHORTESTPATH_H
#include "GraphPath.h"
#include "Node.h"
#include "GraphCompare.h"
List * generateShortestPath(NetworkNode * nNode);
void compareAndAddShortestPathIntoWorkingAVL(ShortestPathNode * sPathToAdd);
void addNeighbouringNode(GraphPath* graphPath);
void findShortestPath(NetworkNode * nNode , char * name);
void printShortestPathDetails(NetworkNode *nNode,ShortestPathNode * sPath);
#endif // _FINDSHORTESTPATH_H
