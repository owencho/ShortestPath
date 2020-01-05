#ifndef _FINDSHORTESTPATH_H
#define _FINDSHORTESTPATH_H
#include "GraphPath.h"
#include "Node.h"
#include "GraphCompare.h"
//Node * shortestPath(Node* root,Compare compare);
GraphPath* findNearestNode(GraphPath* graphRoot,NetworkNode * node);
GraphPath* compareAndAddShortestPath(GraphPath * rootTree,GraphPath * currentPointingNode);
GraphPath* modifyGraphNodeWithShorterPath(Link*ListItemData,GraphPath * rootTree,GraphPath * nodeOut,GraphPath * currentPointingNode);
#endif // _FINDSHORTESTPATH_H
