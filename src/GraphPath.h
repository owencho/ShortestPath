#ifndef _GRAPHPATH_H
#define _GRAPHPATH_H
#include "NetworkNode.h"
#include "List.h"
#include "ListItem.h"
#include "ShortestPathNode.h"
typedef struct GraphPath GraphPath ;

struct GraphPath{
    GraphPath * left ;
    GraphPath * right ;
    int bFactor ;
    List * listWithSameCost ;
    ShortestPathNode * sPath ;
};

#define freeGraphPath(graphPath)                                      \
                          do{if(graphPath) free(graphPath);}while(0)
#endif // _GRAPHPATH_H
