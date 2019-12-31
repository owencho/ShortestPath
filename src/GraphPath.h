#ifndef _GRAPHPATH_H
#define _GRAPHPATH_H
#include "NetworkNode.h"
#include "List.h"
typedef struct ShortestPath ShortestPath ;

struct ShortestPath{
    NetworkNode * dst ;
    NetworkNode * src ;
    double pathCost ;
    List * pathLinks ;
};
typedef struct GraphPath GraphPath ;

struct GraphPath{
    GraphPath * left ;
    GraphPath * right ;
    int bFactor ;
    ShortestPath * sPath ;
};

GraphPath *createGraphPath(ShortestPath * sPath);
ShortestPath *createShortestPath(Link * linkItemData, List * pathLinks);
Link* createLinkFromShortestPath(ShortestPath * sPath);
#endif // _GRAPHPATH_H
