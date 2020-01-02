#ifndef _GRAPHPATH_H
#define _GRAPHPATH_H
#include "NetworkNode.h"
#include "List.h"
#include "ListItem.h"
#include "ShortestPath.h"
typedef struct GraphPath GraphPath ;

struct GraphPath{
    GraphPath * left ;
    GraphPath * right ;
    int bFactor ;
    List * listWithSameCost ;
    ShortestPath * sPath ;
};
#endif // _GRAPHPATH_H
