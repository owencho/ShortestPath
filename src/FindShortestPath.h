#ifndef _FINDSHORTESTPATH_H
#define _FINDSHORTESTPATH_H
#include "GraphPath.h"
#include "Node.h"
#include "GraphCompare.h"

//main function
void findShortestPath(NetworkNode * nNode , char * name);
void findAllShortestPathCost(NetworkNode * nNode);  
void findAllShortestPathLink(NetworkNode * nNode);

// function that made find shortestPath work
List * generateShortestPath(NetworkNode * nNode);
void compareAndAddShortestPathIntoWorkingAVL(ShortestPathNode * sPathToAdd);
void addNeighbouringNode(GraphPath* graphPath);

//function for printing
void printShortestPathDetails(NetworkNode *nNode,ShortestPathNode * sPath);
void printSinglePath(ShortestPathNode * sPath);
void printPathCostFromShortestPath(ListItem * item);
void printPathLinkFromShortestPath(ListItem * item);
#endif // _FINDSHORTESTPATH_H
