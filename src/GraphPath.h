#ifndef _GRAPHPATH_H
#define _GRAPHPATH_H

typedef struct GraphPath GraphPath ;

struct GraphPath{
    GraphPath * left ;
    GraphPath * right ;
    int balanceFactor ;
    ShortestPath * value ;
};

typedef struct ShortestPath ShortestPath ;

struct ShortestPath{
    NetworkNode * dst ;
    NetworkNode * src ;
    double pathCost ;
    List * pathLinks ;
};

#endif // _GRAPHPATH_H
