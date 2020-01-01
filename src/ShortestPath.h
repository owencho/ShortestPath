#ifndef _SHORTESTPATH_H
#define _SHORTESTPATH_H
#include "GraphPath.h"
#include "Node.h"
#include "GraphCompare.h"
//Node * shortestPath(Node* root,Compare compare);
GraphPath* findNearestNode(GraphPath* graphRoot,NetworkNode * node);
GraphPath* findGraphPath(GraphPath * root,NetworkNode * dstNode);
GraphPath* modifyGraphNodeWithShorterPath(Link*ListItemData,GraphPath * rootTree,GraphPath * nodeOut,GraphPath * currentPointingNode);
GraphPath * avlRemoveSmallestGraphPath(GraphPath*root);
#endif // _SHORTESTPATH_H
