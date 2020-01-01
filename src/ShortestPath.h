#ifndef _SHORTESTPATH_H
#define _SHORTESTPATH_H
#include "GraphPath.h"
#include "Node.h"
#include "GraphCompare.h"
//Node * shortestPath(Node* root,Compare compare);
GraphPath* findNearestNode(GraphPath* graphRoot,NetworkNode * node);
GraphPath* compareAndAddShortestPath(GraphPath * rootTree,GraphPath * currentPointingNode);
GraphPath* modifyGraphNodeWithShorterPath(Link*ListItemData,GraphPath * rootTree,GraphPath * nodeOut,GraphPath * currentPointingNode);
GraphPath* findGraphPath(GraphPath * root,NetworkNode * dstNode);
#endif // _SHORTESTPATH_H
