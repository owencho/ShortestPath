#include "GraphCompare.h"

int graphCompareForAvlAdd (GraphPath *node, GraphPath * valuePtr){
    if(node->sPath->pathCost < valuePtr->sPath->pathCost)
        return -1;
    else if (node->sPath->pathCost >  valuePtr->sPath->pathCost)
        return 1;
    return 0;
}

int graphCompareForAvlDelete (GraphPath *node, ShortestPath * sPath){
    if(node->sPath->pathCost < sPath->pathCost)
        return -1;
    else if (node->sPath->pathCost >  sPath->pathCost)
        return 1;
    return 0;
}
