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

GraphPath *createGraphPath(ShortestPathNode * sPath){
    GraphPath*graphPath= (GraphPath *)malloc(sizeof(GraphPath));
    graphPath->left = NULL;
    graphPath->right = NULL;
    graphPath->bFactor = 0;
    graphPath->listWithSameCost = createList();
    graphPath->sPath = sPath;
    return graphPath;
}

List *createList(void){
    List * list = (List *)malloc(sizeof(List));
    list->head = NULL;
    list->tail = NULL;
    list->current = NULL;
    list->count = 0;
    list->previous = NULL;
    return list;
}

void * addGraphPathIntoPathCostAVL(ShortestPathNode * sPath){
    GraphPath * gNode;
    GraphPath * newGPath;
    ListItem * newListItem = (ListItem *)malloc(sizeof(ListItem));
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
            newListItem->data = (void*)newGPath;
            gNode->listWithSameCost = listAddItemToHead(gNode->listWithSameCost,newListItem);
            resetCurrentListItem(gNode->listWithSameCost);
        }
    }
    return rootTreePathCost;
}

void * deleteGraphPathFromPathCostAVL(int pathCost,char * name){
    GraphPath * gPath;
    ListItem * sameCostItem;
    GraphPath * sameCostGPath;
    gPath = getGraphPathFromPathCost(pathCost);

    if(gPath == NULL){
        throwException(ERR_NODE_NOT_FOUND," %s with pathCost of %d cant found inside the tree",name,pathCost);
    }
    else if(strcmp(gPath->sPath->id->name ,name)==0){
        rootTreePathCost = (GraphPath*)avlDelete((Node*)rootTreePathCost,
                           (void*)&pathCost,(Compare)graphCompareForPathCost);
        if(gPath->listWithSameCost->count !=0){
            //call a function to check
            // GraphPath * overridePath =  gPath->listWithSameCost->head->data;
            // remove head listItem(gPath->listWithSameCost)
            // overridePath->listWithSameCost =gPath->listWithSameCost
            // add back this node into Tree
            //addGraphPathIntoPathCostAVL(overridePath);
            //
        }
    }
    else if(gPath->listWithSameCost->count !=0){
        resetCurrentListItem(gPath->listWithSameCost);
        sameCostItem = getCurrentListItem(gPath->listWithSameCost);
        while(sameCostItem != NULL){
            sameCostGPath = (GraphPath*)sameCostItem->data;
            if(strcmp(sameCostGPath->sPath->id->name ,name)==0){
                gPath->listWithSameCost = deleteSelectedListItem(gPath->listWithSameCost,sameCostGPath,(LinkListCompare)graphCompareForSameCostList);
                break;
            }
            sameCostItem = getNextListItem(gPath->listWithSameCost);
        }
    }
    return rootTreePathCost;
}



GraphPath * getGraphPathFromPathCost(int pathCost){
    GraphPath node = *rootTreePathCost;
    return _getGraphPath((void*)&pathCost,&node,(Compare)graphCompareForPathCost);
}

///Working Tree for PATH NAME//////////////////////////////////////////////////////////////////
void * addGraphPathIntoPathNameAVL(ShortestPathNode * sPath){
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
            throwException(ERR_SAME_NODE,"same node of %s detected",sPath->id->name);
        }
    }
    return rootTreeNodeName;
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
