#ifndef _SHORTESTPATHNODE_H
#define _SHORTESTPATHNODE_H
#include "NetworkNode.h"
#include "List.h"
#include "ListItem.h"
typedef struct ShortestPathNode ShortestPathNode ;

struct ShortestPathNode{
    NetworkNode * id ;
    ShortestPathNode * parent ;
    int linkCost ;
    int pathCost ;
};

ShortestPathNode* createShortestPathFromLinkItemData(ShortestPathNode * parent, Link * linkItemData);
ShortestPathNode* createFirstShortestPath(NetworkNode * firstNode);
#endif // _SHORTESTPATHNODE_H
