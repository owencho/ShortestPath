#include "GraphCompare.h"

int graphCompare (GraphPath *node, void * valuePtr){
    ShortestPath * shortestPath = (ShortestPath*)valuePtr;
    if(node->shortestPath->pathCost < shortestPath->pathCost)
        return -1;
    else if (node->shortestPath->pathCost >  shortestPath->pathCost)
        return 1;
    return 0;
}
