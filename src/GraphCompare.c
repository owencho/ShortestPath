#include "GraphCompare.h"

int graphCompare (GraphPath *node, GraphPath * valuePtr){
    if(node->value->pathCost < valuePtr->value->pathCost)
        return -1;
    else if (node->value->pathCost >  valuePtr->value->pathCost)
        return 1;
    return 0;
}
