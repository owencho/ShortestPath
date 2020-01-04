#include "ShortestPathNode.h"
#include <stdlib.h>

ShortestPathNode* createShortestPath(ShortestPathNode * parent, Link * linkItemData){
    ShortestPathNode* sPath = (ShortestPathNode *)malloc(sizeof(ShortestPathNode));
    sPath->id = linkItemData->head;
    sPath->parent = parent;
    sPath->pathCost = linkItemData->cost + parent->pathCost ;
    sPath->linkCost = linkItemData->cost;
    return sPath;
}
