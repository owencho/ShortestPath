#ifndef _GRAPHPATHAVL_H
#define _GRAPHPATHAVL_H
#include "GraphPath.h"
#include "Compare.h"
//shared Function
GraphPath *createGraphPath(ShortestPathNode * sPath);
GraphPath * _getGraphPath(void * valuePtr,GraphPath * root,Compare compare);
void freeGraphPathNode(GraphPath * gPathNode);
//Main Function
void addGraphPathIntoWorkingAVL(ShortestPathNode * sPath);
void deleteGraphPathFromWorkingAVL(ShortestPathNode * sPath);
void resetWorkingAVL(void);
//Working Tree for PathCost
GraphPath * getGraphPathFromPathCost(int pathCost);
GraphPath * findSmallestPathCostFromAVL(void);
void  addGraphPathIntoPathCostAVL(ShortestPathNode * sPath);
void  deleteGraphPathFromPathCostAVL(int pathCost,char * name);
void  deleteAndOverrideGraphPathWithSameCost(GraphPath * graphPath,int pathCost);
GraphPath * deleteSameCostGraphPathListItem(GraphPath * gPath,char * name);
void  resetPathCostAVL(void);
//Working Tree for PathName
void  addGraphPathIntoPathNameAVL(ShortestPathNode * sPath);
void  deleteGraphPathFromPathNameAVL(char * name);
GraphPath * getGraphPathFromNodeName(char * nodeName);
void  resetNodeNameAVL(void);

#endif // _GRAPHPATHAVL_H
