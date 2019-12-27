#include "GraphCompare.h"

int graphCompare (GraphPath *node, ShortestPath * valuePtr){
    ShortestPath shortest = *valuePtr;
    if(node->value->pathCost < shortest.pathCost)
        return -1;
    else if (node->value->pathCost >  shortest.pathCost)
        return 1;
    return 0;
}
