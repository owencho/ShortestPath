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
GraphPath * rootTreeNodeName = NULL; //to store gPath but sorted by destination of that gPath
CEXCEPTION_T ex;

ShortestPath* createShortestPath(Link * linkItemData, List * pathLinks){
    ShortestPath* sPath = (ShortestPath *)malloc(sizeof(ShortestPath));
    sPath->dst = linkItemData->head;
    sPath->src = linkItemData->tail;
    sPath->pathCost = linkItemData->cost;
    sPath->pathLinks = pathLinks;
    return sPath;
}
GraphPath *createGraphPath(ShortestPath * sPath){
    GraphPath*graphPath= (GraphPath *)malloc(sizeof(GraphPath));
    graphPath->left = NULL;
    graphPath->right = NULL;
    graphPath->bFactor = 0;
    graphPath->listWithSameCost = NULL;
    graphPath->sPath = sPath;
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
    GraphPath * newGPath;
    ListItem * newlistItem;
    if(rootTreePathCost == NULL){
        rootTreePathCost = createGraphPath(sPath);
    }
    else{
        Try{
            newGPath = createGraphPath(sPath);
            rootTreePathCost = (GraphPath*)avlAdd((Node*)rootTreePathCost,
                               (Node*)newGPath,
                               (Compare)graphCompareForPathCostAvlAdd);
        }Catch(ex){
            gNode= getGraphPathFromPathCost(sPath->pathCost);
            newlistItem->data = (void*)newGPath;
            gNode->listWithSameCost = listAddItemToHead(gNode->listWithSameCost, newlistItem );
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
            throwException(ERR_SAME_NODE,"same node of %s detected",sPath->dst->name);
        }
    }
    return rootTreeNodeName;
}

void * deleteGraphPathFromPathCostAVL(double pathCost,char * name){
    GraphPath * gPath;
    ListItem * sameCostItem;
    GraphPath * sameCostGPath;
    gPath = getGraphPathFromPathCost(pathCost);
    if(gPath->listWithSameCost->count !=0){
        resetCurrentListItem(gPath->listWithSameCost);
        while(sameCostItem != NULL){
            sameCostItem = getNextListItem(gPath->listWithSameCost);
            sameCostGPath = (GraphPath*)sameCostItem->data;
            if(strcmp(sameCostGPath->sPath->dst->name ,name)==0){

            }
        }
    }else{
        rootTreePathCost = (GraphPath*)avlDelete((Node*)rootTreePathCost,
                           (void*)&pathCost,(Compare)graphCompareForPathCost);
    }

    return rootTreePathCost;
}

void * deleteGraphPathFromPathNameAVL(char * name){
    Try{
        rootTreeNodeName = (GraphPath*)avlDelete((Node*)rootTreeNodeName,
                           name,(Compare)graphCompareForName);
    }Catch(ex) {
        throwException(ERR_NODE_NOT_FOUND,"%s does not exist inside the working tree and couldnt remove the node ",name);
    }
    return rootTreeNodeName;
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
    GraphPath * foundNode = NULL;
    if(!size){
        foundNode = root;
        return root;
    }
    else if(size == -1){
        if(root->right != NULL){
            foundNode = _getGraphPath(valuePtr,root->right,compare);
        }
    }
    else{
        if(root->left != NULL){
            foundNode = _getGraphPath(valuePtr,root->left,compare);
        }
    }
    return foundNode;
}

void * resetPathCostAVL(void){
    rootTreePathCost = NULL;
    return rootTreePathCost;
}

void * resetNodeNameAVL(void){
    rootTreeNodeName = NULL;
    return rootTreeNodeName;
}
