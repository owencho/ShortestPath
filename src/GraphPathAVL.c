#include "GraphPathAVL.h"
#include "GraphCompare.h"
#include "AvlAdd.h"
#include "AvlDelete.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Exception.h"
#include "AvlError.h"
#include "ShortestPathError.h"
#include "List.h"
#include "CException.h"

GraphPath * rootTreePathCost = NULL;
GraphPath * rootTreeNodeName = NULL;
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

//main function
// add the node into both working tree
void addGraphPathIntoWorkingAVL(ShortestPathNode * sPath){
    if(sPath == NULL)
        return;
    addGraphPathIntoPathCostAVL(sPath);
    addGraphPathIntoPathNameAVL(sPath);
}

void deleteGraphPathFromWorkingAVL(ShortestPathNode * sPath){
    if(sPath == NULL)
        return;
    deleteGraphPathFromPathCostAVL(sPath->pathCost,sPath->id->name);
    deleteGraphPathFromPathNameAVL(sPath->id->name);
}

void resetWorkingAVL(void){
    resetPathCostAVL();
    resetNodeNameAVL();
}
///Working Tree for PATH cost//////////////////////////////////////////////////////////////////
void addGraphPathIntoPathCostAVL(ShortestPathNode * sPath){
    GraphPath * gNode;
    GraphPath * newGPath;
    if(sPath==NULL)
        return;
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
            freeException(ex);
            gNode= getGraphPathFromPathCost(sPath->pathCost);
            gNode->listWithSameCost = listAddItemToHead(gNode->listWithSameCost,(void*)newGPath);
            resetCurrentListItem(gNode->listWithSameCost);
        }
    }
}

void deleteGraphPathFromPathCostAVL(int pathCost,char * name){
    GraphPath * gPath;
    if(name == NULL)
        return;
    gPath = getGraphPathFromPathCost(pathCost);

    if(gPath == NULL)
        throwException(ERR_NODE_NOT_FOUND," %s with pathCost of %d cant found inside the tree",name,pathCost);
    else if(strcmp(gPath->sPath->id->name ,name)==0)
        deleteAndOverrideGraphPathWithSameCost(gPath,pathCost);
    else if(gPath->listWithSameCost->count !=0)
        gPath = deleteSameCostGraphPathListItem(gPath,name);
}

void deleteAndOverrideGraphPathWithSameCost(GraphPath * graphPath,int pathCost){
    GraphPath * overridePath;
    GraphPath * deletedGraphPath;
    ListItem * overrideListItem;
    GraphPath * searchPath;
    ListItem * overrideList;
    if(graphPath == NULL)
        return;
    deletedGraphPath = (GraphPath*)avlDelete((Node**)&rootTreePathCost,(void*)&pathCost,(Compare)graphCompareForPathCost);
    if(graphPath->listWithSameCost->count !=0){
       overrideListItem =  (ListItem*)graphPath->listWithSameCost->head;
       overridePath =  (GraphPath*)overrideListItem->data;
       deleteHeadListItem(graphPath->listWithSameCost);
       addGraphPathIntoPathCostAVL(overridePath->sPath);
       searchPath = getGraphPathFromPathCost(overridePath->sPath->pathCost);
       searchPath -> listWithSameCost = graphPath->listWithSameCost;
       resetCurrentListItem(searchPath->listWithSameCost);
    }
    freeGraphPath(deletedGraphPath);
}

GraphPath * deleteSameCostGraphPathListItem(GraphPath * gPath,char * name){
    ListItem * sameCostItem;
    GraphPath * sameCostGPath;
    if(gPath == NULL || name == NULL)
        return gPath;
    resetCurrentListItem(gPath->listWithSameCost);
    sameCostItem = getCurrentListItem(gPath->listWithSameCost);
    while(sameCostItem != NULL){
        sameCostGPath = (GraphPath*)sameCostItem->data;
        if(strcmp(sameCostGPath->sPath->id->name ,name)==0){
            deleteSelectedListItem(gPath->listWithSameCost,sameCostGPath,(LinkedListCompare)listCompareForListWithSameCostGraph);
            break;
        }
        sameCostItem = getNextListItem(gPath->listWithSameCost);
    }
    if(sameCostItem == NULL){
        throwException(ERR_NODE_NOT_FOUND,"couldn't delete %s on graphPath cost tree",name);
    }
    resetCurrentListItem(gPath->listWithSameCost);
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
    if(rootTreePathCost == NULL)
        return NULL;
    smallestNode = (GraphPath*)findSmallestNode((Node*)rootTreePathCost);
    if(smallestNode->listWithSameCost->count != 0){
        smallestNode = smallestNode->listWithSameCost->head->data;
    }
    return smallestNode;
}

void resetPathCostAVL(void){
    freeGraphPath(rootTreePathCost);
    rootTreePathCost = NULL;
}

///Working Tree for PATH NAME//////////////////////////////////////////////////////////////////
void addGraphPathIntoPathNameAVL(ShortestPathNode * sPath){
    GraphPath * gNode;
    ListItem * newItem;
    if(sPath==NULL)
        return;
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
}


void deleteGraphPathFromPathNameAVL(char * name){
    GraphPath * deletedGraphPath;
    if(name == NULL)
        return;
    Try{
        deletedGraphPath = (GraphPath*)avlDelete((Node**)&rootTreeNodeName,name,(Compare)graphCompareForName);
        freeGraphPath(deletedGraphPath);
    }Catch(ex) {
        throwException(ERR_NODE_NOT_FOUND,"%s does not exist inside the working tree and couldn't remove the node ",name);
    }
}

GraphPath * getGraphPathFromNodeName(char * nodeName){
    if(rootTreeNodeName == NULL || nodeName == NULL){
        return NULL;
    }
    return _getGraphPath((void*)nodeName,rootTreeNodeName,(Compare)graphCompareForName);
}

void resetNodeNameAVL(void){
    freeGraphPath(rootTreeNodeName);
    rootTreeNodeName = NULL;
}
//Shared Function
GraphPath * _getGraphPath(void * valuePtr,GraphPath * root,Compare compare){
    int size = compare((void*)root,valuePtr);
    GraphPath * foundNode = NULL;
    if(!size){
        foundNode = root;
        return root;
    }
    else if(size == -1){
        if(root->right != NULL)
            foundNode = _getGraphPath(valuePtr,root->right,compare);
    }
    else{
        if(root->left != NULL)
            foundNode = _getGraphPath(valuePtr,root->left,compare);
    }
    return foundNode;
}
