#include "GraphPath.h"

void createGraphPath(GraphPath * node,  ShortestPath * value ){
    node->left = NULL;
    node->right = NULL;
    node->bFactor = 0;
    node->value = value;
}

void createShortestPath(ShortestPath * sPath,  Link * linkItemData ){
    sPath->dst = linkItemData->head;
    sPath->right = linkItemData->tail;
    sPath->pathCost = linkItemData.cost;
    //path link
}
