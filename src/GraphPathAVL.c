#include "GraphPathAVL.h"
#include "GraphCompare.h"
#include "AvlAdd.h"
#include "AvlDelete.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Exception.h"
#include "Error.h"
#include "CException.h"

GraphPath * rootTreePathCost = NULL;
GraphPath * rootTreeNodeName = NULL;
CEXCEPTION_T ex;

GraphPath *createGraphPath(ShortestPath * sPath){
    GraphPath*graphPath= (GraphPath *)malloc(sizeof(GraphPath));
    graphPath->left = NULL;
    graphPath->right = NULL;
    graphPath->bFactor = 0;
    graphPath->listWithSameCost = sPath->pathLinks; // note: this might fail
    graphPath->sPath = sPath; // can change to shortestPath
    return graphPath;
}
Link* createLinkFromShortestPath(ShortestPath * sPath){
    Link* linkItemData = (Link *)malloc(sizeof(Link));
    linkItemData->head= sPath->dst ;
    linkItemData->tail= sPath->src ;
    linkItemData->cost= sPath->pathCost ;
    return linkItemData;
}

void * addGraphPathIntoPathCostAVL(ShortestPath * sPath){
    GraphPath * gNode;
    ListItem * newItem;
    if(rootTreePathCost == NULL){
        rootTreePathCost = createGraphPath(sPath);
    }
    else{
        Try{
            rootTreePathCost = (GraphPath*)avlAdd((Node*)rootTreePathCost,
                               (Node*)createGraphPath(sPath),
                               (Compare)graphCompareForPathCostAvlAdd);
        }Catch(ex){
           //gNode= getGraphPathFromPathCost(sPath->pathCost);
           //newItem=createLinkFromShortestPath(sPath);
          // gNode->list = listAddItemToHead(gNode->list, ListItem * item );
        }
    }
    return rootTreePathCost;
}
void * addGraphPathIntoPathNameAVL(ShortestPath * sPath){
    GraphPath * gNode;
    ListItem * newItem;
    if(rootTreeNodeName == NULL){
        rootTreeNodeName = createGraphPath(sPath);
    }
    else{
        Try{
            rootTreeNodeName = (GraphPath*)avlAdd((Node*)rootTreeNodeName,
                               (Node*)createGraphPath(sPath),
                               (Compare)graphCompareForNameAvlAdd);
        }Catch(ex){
           //gNode= getGraphPathFromPathCost(sPath->pathCost);
           //newItem=createLinkFromShortestPath(sPath);
          // gNode->list = listAddItemToHead(gNode->list, newItem );
        }
    }
    return rootTreeNodeName;
}

void * deleteGraphPathFromPathNameAVL(ShortestPath * sPath){
    rootTreeNodeName = (GraphPath*)avlDelete((Node*)rootTreeNodeName,
                       (void*)&sPath->pathCost,(Compare)graphCompareForPathCost);
    return rootTreeNodeName;
}

void * deleteGraphPathFromPathCostAVL(ShortestPath * sPath){
    rootTreePathCost = (GraphPath*)avlDelete((Node*)rootTreePathCost,
                       sPath->dst->name,(Compare)graphCompareForName);
    return rootTreePathCost;
}


GraphPath * getGraphPathFromNodeName(char * nodeName){
    GraphPath node = *rootTreeNodeName;
    return _getGraphPath((void*)nodeName,&node,(Compare)graphCompareForName);
}
GraphPath * getGraphPathFromPathCost(double pathCost){
    GraphPath node = *rootTreePathCost;
    return _getGraphPath((void*)&pathCost,&node,(Compare)graphCompareForPathCost);
}

GraphPath * _getGraphPath(void * valuePtr,GraphPath * root,Compare compare){
    int size = compare((void*)root,valuePtr);
    if(!size)
        return root;
    else if(size == -1)
        root = _getGraphPath(valuePtr,root->right,compare);
    else
        root = _getGraphPath(valuePtr,root->left,compare);
    return root;
}
