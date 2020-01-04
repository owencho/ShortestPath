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

ShortestPathNode* createShortestPath(ShortestPathNode * parent, Link * linkItemData);
#endif // _SHORTESTPATHNODE_H
