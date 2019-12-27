#ifndef _GRAPHPATH_H
#define _GRAPHPATH_H
#include "NetworkNode.h"
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
    ShortestPath * value ;
};

void createGraphPath(GraphPath * node,  ShortestPath * value );
void createShortestPath(ShortestPath * sPath,  Link * linkItemData );
#endif // _GRAPHPATH_H
