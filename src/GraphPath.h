#ifndef _GRAPHPATH_H
#define _GRAPHPATH_H
#include "NetworkNode.h"
#include "GraphPath.h"
#include "List.h"
#include "ListItem.h"
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
List* createLinkListForShortestPath(NetworkNode * head,NetworkNode * tail,int cost);
#endif // _GRAPHPATH_H
