#ifndef _GRAPHPATHAVL_H
#define _GRAPHPATHAVL_H
#include "GraphPath.h"
#include "Compare.h"
GraphPath *createGraphPath(ShortestPath * sPath);
Link* createLinkFromShortestPath(ShortestPath * sPath);
void * addGraphPathIntoPathCostAVL(ShortestPath * sPath);
void * addGraphPathIntoPathNameAVL(ShortestPath * sPath);
void * deleteGraphPathFromPathCostAVL(ShortestPath * sPath);
GraphPath * getGraphPathFromNodeName(char * nodeName);
GraphPath * getGraphPathFromPathCost(double pathCost);
GraphPath * _getGraphPath(void * valuePtr,GraphPath * root,Compare compare);
#endif // _GRAPHPATHAVL_H
