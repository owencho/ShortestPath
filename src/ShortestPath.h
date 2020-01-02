#ifndef _SHORTESTPATH_H
#define _SHORTESTPATH_H
#include "NetworkNode.h"
#include "List.h"
#include "ListItem.h"
typedef struct ShortestPath ShortestPath ;

struct ShortestPath{
    NetworkNode * dst ;
    NetworkNode * src ;
    double pathCost ;
    List * pathLinks ;
};
#endif // _SHORTESTPATH_H
