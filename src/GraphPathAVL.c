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
//main function
void * addGraphPathIntoWorkingAVL(ShortestPathNode * sPath){
    addGraphPathIntoPathCostAVL(sPath);
    addGraphPathIntoPathNameAVL(sPath);
    return rootTreePathCost;
}

void * deleteGraphPathFromWorkingAVL(ShortestPathNode * sPath){
    deleteGraphPathFromPathCostAVL(sPath->pathCost,sPath->id->name);
    deleteGraphPathFromPathNameAVL(sPath->id->name);
    return rootTreePathCost;
}

void resetWorkingAVL(void){
    resetPathCostAVL();
    resetNodeNameAVL();
}
///Working Tree for PATH cost//////////////////////////////////////////////////////////////////
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
    gPath = getGraphPathFromPathCost(pathCost);

    if(gPath == NULL)
        throwException(ERR_NODE_NOT_FOUND," %s with pathCost of %d cant found inside the tree",name,pathCost);
    else if(strcmp(gPath->sPath->id->name ,name)==0)
        deleteAndOverrideGraphPathWithSameCost(gPath,pathCost);
    else if(gPath->listWithSameCost->count !=0)
        gPath = deleteSameCostGraphPathListItem(gPath,name);
    return rootTreePathCost;
}

void * deleteAndOverrideGraphPathWithSameCost(GraphPath * graphPath,int pathCost){
    GraphPath * overridePath;
    ListItem * overrideListItem;
    GraphPath * searchPath;
    ListItem * overrideList;
    rootTreePathCost = (GraphPath*)avlDelete((Node*)rootTreePathCost,(void*)&pathCost,(Compare)graphCompareForPathCost);
    if(graphPath->listWithSameCost->count !=0){
       overrideListItem =  (ListItem*)graphPath->listWithSameCost->head;
       overridePath =  (GraphPath*)overrideListItem->data;
       graphPath->listWithSameCost=deleteHeadListItem(graphPath->listWithSameCost);
       addGraphPathIntoPathCostAVL(overridePath->sPath);
       searchPath = getGraphPathFromPathCost(overridePath->sPath->pathCost);
       searchPath -> listWithSameCost = graphPath->listWithSameCost;
    }
    return rootTreePathCost;
}

GraphPath * deleteSameCostGraphPathListItem(GraphPath * gPath,char * name){
    ListItem * sameCostItem;
    GraphPath * sameCostGPath;
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
    if(sameCostItem == NULL){
        throwException(ERR_NODE_NOT_FOUND,"couldnt delete %s on graphPath cost tree",name);
    }
    return gPath;
}

GraphPath * getGraphPathFromPathCost(int pathCost){
    if(rootTreePathCost == NULL){
        return NULL;
    }
    return _getGraphPath((void*)&pathCost,rootTreePathCost,(Compare)graphCompareForPathCost);
}

GraphPath * findSmallestPathCostFromAVL(void){
    GraphPath * smallestNode ;
    smallestNode = (GraphPath*)findSmallestNode((Node*)rootTreePathCost);
    if(smallestNode->listWithSameCost->count != 0){
        smallestNode = smallestNode->listWithSameCost->head->data;
    }
    return smallestNode;
}

void * resetPathCostAVL(void){
    rootTreePathCost = NULL;
    return rootTreePathCost;
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
    if(rootTreeNodeName == NULL){
        return NULL;
    }
    return _getGraphPath((void*)nodeName,rootTreeNodeName,(Compare)graphCompareForName);
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

void * resetNodeNameAVL(void){
    rootTreeNodeName = NULL;
    return rootTreeNodeName;
}
