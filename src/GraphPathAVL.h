#ifndef _GRAPHPATHAVL_H
#define _GRAPHPATHAVL_H
#include "GraphPath.h"
#include "Compare.h"
GraphPath *createGraphPath(ShortestPathNode * sPath);
void * addGraphPathIntoPathCostAVL(ShortestPathNode * sPath);
void * addGraphPathIntoPathNameAVL(ShortestPathNode * sPath);
void * deleteGraphPathFromPathCostAVL(int pathCost,char * name);
void * deleteGraphPathFromPathNameAVL(char * name);
GraphPath * getGraphPathFromNodeName(char * nodeName);
GraphPath * getGraphPathFromPathCost(int pathCost);
GraphPath * _getGraphPath(void * valuePtr,GraphPath * root,Compare compare);
void * resetPathCostAVL(void);
void * resetNodeNameAVL(void);
List *createList(void); //move to LinkList pls
#endif // _GRAPHPATHAVL_H
