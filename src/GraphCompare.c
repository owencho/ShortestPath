#include "GraphCompare.h"
#include <stdio.h>
#include <string.h>


int graphCompareForPathCostAvlAdd (GraphPath *node, GraphPath * valuePtr){
    if(node->sPath->pathCost < valuePtr->sPath->pathCost)
        return -1;
    else if (node->sPath->pathCost >  valuePtr->sPath->pathCost)
        return 1;
    return 0;
}

int graphCompareForPathCost (GraphPath *node, double *pathCost){
    if(node->sPath->pathCost < *pathCost)
        return -1;
    else if (node->sPath->pathCost > *pathCost)
        return 1;
    return 0;
}

int graphCompareForNameAvlAdd (GraphPath *node, GraphPath * valuePtr){
  if(strcmp(node->sPath->dst->name ,valuePtr->sPath->dst->name)<0)
      return -1;
  else if (strcmp(node->sPath->dst->name ,valuePtr->sPath->dst->name)>0)
      return 1;
  return 0;
}

int graphCompareForName (GraphPath *node, char * name){
    if(strcmp(node->sPath->dst->name ,name)<0)
        return -1;
    else if (strcmp(node->sPath->dst->name ,name)>0)
        return 1;
    return 0;
}
