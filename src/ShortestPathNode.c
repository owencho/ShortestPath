#include "ShortestPathNode.h"

ShortestPath* createShortestPath(Link * linkItemData, List * pathLinks){
    ShortestPath* sPath = (ShortestPath *)malloc(sizeof(ShortestPath));
    sPath->dst = linkItemData->head;
    sPath->src = linkItemData->tail;
    sPath->pathCost = linkItemData->cost;
    sPath->pathLinks = pathLinks;
    return sPath;
}
