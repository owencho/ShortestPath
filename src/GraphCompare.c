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

int graphCompareForPathCost (GraphPath *node, int *pathCost){
    if(node->sPath->pathCost < *pathCost)
        return -1;
    else if (node->sPath->pathCost > *pathCost)
        return 1;
    return 0;
}

int graphCompareForNameAvlAdd (GraphPath *node, GraphPath * valuePtr){
  if(strcmp(node->sPath->id->name ,valuePtr->sPath->id->name)<0)
      return -1;
  else if (strcmp(node->sPath->id->name ,valuePtr->sPath->id->name)>0)
      return 1;
  return 0;
}

int graphCompareForName (GraphPath *node, char * name){
    if(strcmp(node->sPath->id->name ,name)<0)
        return -1;
    else if (strcmp(node->sPath->id->name ,name)>0)
        return 1;
    return 0;
}

int graphCompareForSameCostList (GraphPath *node, GraphPath * pathPtr){
    if(strcmp(node->sPath->id->name ,pathPtr->sPath->id->name)==0)
        return 1;
    return 0;
}
