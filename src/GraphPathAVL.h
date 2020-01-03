#ifndef _GRAPHPATHAVL_H
#define _GRAPHPATHAVL_H
#include "GraphPath.h"
#include "Compare.h"
GraphPath *createGraphPath(ShortestPath * sPath);
ShortestPath* createShortestPath(Link * linkItemData, List * pathLinks);
Link* createLinkFromShortestPath(ShortestPath * sPath);
void * addGraphPathIntoPathCostAVL(ShortestPath * sPath);
void * addGraphPathIntoPathNameAVL(ShortestPath * sPath);
void * deleteGraphPathFromPathCostAVL(double pathCost);
void * deleteGraphPathFromPathNameAVL(char * name);
GraphPath * getGraphPathFromNodeName(char * nodeName);
GraphPath * getGraphPathFromPathCost(double pathCost);
GraphPath * _getGraphPath(void * valuePtr,GraphPath * root,Compare compare);
void * resetPathCostAVL(void);
void * resetNodeNameAVL(void);
#endif // _GRAPHPATHAVL_H
