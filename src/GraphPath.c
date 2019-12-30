#include "GraphPath.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

GraphPath *createGraphPath(ShortestPath * value){
    GraphPath*graphPath= (GraphPath *)malloc(sizeof(GraphPath));
    graphPath->left = NULL;
    graphPath->right = NULL;
    graphPath->bFactor = 0;
    graphPath->value = value; // can change to shortestPath
    return graphPath;
}

ShortestPath* createShortestPath(Link * linkItemData, List * pathLinks){
    ShortestPath* sPath = (ShortestPath *)malloc(sizeof(ShortestPath));
    sPath->dst = linkItemData->head;
    sPath->src = linkItemData->tail;
    sPath->pathCost = linkItemData->cost;
    sPath->pathLinks = pathLinks;
    return sPath;
}
