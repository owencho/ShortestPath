#include "ShortestPathNode.h"
#include <stdlib.h>

ShortestPathNode* createShortestPathFromLinkItemData(ShortestPathNode * parent, Link * linkItemData){
    ShortestPathNode* sPath = (ShortestPathNode *)malloc(sizeof(ShortestPathNode));
    sPath->id = linkItemData->head;
    sPath->parent = parent;
    if(parent == NULL)
        sPath->pathCost = linkItemData->cost ;
    else
        sPath->pathCost = linkItemData->cost + parent->pathCost ;
    sPath->linkCost = linkItemData->cost;
    return sPath;
}

ShortestPathNode* createFirstShortestPath(NetworkNode * firstNode){
    ShortestPathNode * sPath=(ShortestPathNode *)malloc(sizeof(ShortestPathNode));
    sPath->id = firstNode;
    sPath->parent = NULL;
    sPath->pathCost = 0;
    sPath->linkCost = 0;
    return sPath;
}
