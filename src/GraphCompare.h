#ifndef _GRAPHCOMPARE_H
#define _GRAPHCOMPARE_H
#include "GraphPath.h"
//(Compare) for Avl
int graphCompareForPathCostAvlAdd (GraphPath *node, GraphPath * valuePtr);
int graphCompareForNameAvlAdd (GraphPath *node, GraphPath * valuePtr);
int graphCompareForPathCost (GraphPath *node, int* pathCost);
int graphCompareForName (GraphPath *node, char * name);
//(LinkedListCompare)
int listCompareForListWithSameCostGraph (ListItem *listItem, GraphPath * pathPtr);
#endif // _GRAPHCOMPARE_H
