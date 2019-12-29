#include "GraphCompare.h"

int graphCompare (GraphPath *node, ShortestPath * valuePtr){
    if(node->value->pathCost < valuePtr->pathCost)
        return -1;
    else if (node->value->pathCost >  valuePtr->pathCost)
        return 1;
    return 0;
}
