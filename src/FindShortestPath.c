#include "FindShortestPath.h"
#include "ShortestPathNode.h"
#include <stdlib.h>
#include <stdio.h>
#include "AvlAdd.h"
#include "AvlDelete.h"
#include "Compare.h"
#include "NetworkNode.h"
#include "List.h"
#include "ListItem.h"
/*
Node * shortestPath(NetworkNode * nNode){
    List * linkList;
    GraphPath*rootWorkingTree,finalShortestPathTree;
    //first time
    //addGraphNode for the first time
    linkList=getIteratorOfLinks(&nNode);

    smallestNode=(GraphPath*)avlRemoveSmallest((Node*)root,(Compare)graphCompare);
    root = findNearestNode(Working AVLTree,root); //generate AvlTree with cost (not shortest path yet)
    //second time
    return root;


/*
GraphPath* findNearestNode(GraphPath * currentPointingNode,GraphPath* graphRoot,NetworkNode * node){
    Node * root;
    List * nearestNodelinkList;
    List * pathLinkList;
    ListItem * listItem;
    Link * linkItemData;
    Node * inputNode;
    nearestNodelinkList= getIteratorOfLinks(node);   //retreive the link list
    resetCurrentListItem(nearestNodelinkList);      // reset the linkList

    while(nearestNodelinkList->current !=NULL) {
        listItem = getNextListItem(nearestNodelinkList);
        linkItemData = (Link*)listItem->data;    //retreive the data with cost, head , tail
        linkItemData -> cost = linkItemData -> cost + currentPointingNode->value->pathCost;
        if(linkItemData->head->marked ==0 ){
            root = compareAndAddShortestPath(currentPointingNode,graphRoot,linkItemData);
            //compare inside the working AVL tree see there is any shorter path (then if yes overwrite linkItemData and input PathLink)
            //graphNode value points to shortestPath struct
        }
    }
    return (GraphPath*)root;
}


*/
// we know that the source is always at C , so we just need to find its destination
// iterate through to find on the rootTree if not marked
// return the GraphPath of destinated
GraphPath* compareAndAddShortestPath(GraphPath * rootTree,GraphPath * currentPointingNode){
    ListItem * listItem;
    Link * newItemData;
    List * nearestNodelinkList;
    List * pathLinkList;
    GraphPath *nodeOut;
    nearestNodelinkList= getIteratorOfLinks(currentPointingNode->sPath->dst); //this might fail
    resetCurrentListItem(nearestNodelinkList);
    listItem= getNextListItem(nearestNodelinkList);
    while(listItem != NULL){
        newItemData = (Link*)listItem->data;
        if(newItemData->head->marked == 0){
            nodeOut = findGraphPath(rootTree, newItemData->head);
            if(nodeOut != NULL){
                rootTree=modifyGraphNodeWithShorterPath(newItemData,rootTree,nodeOut,currentPointingNode);
            }
            else{
                newItemData -> cost = newItemData -> cost + currentPointingNode->sPath->pathCost;
                pathLinkList=createLinkListForShortestPath(newItemData->head,newItemData->tail,newItemData -> cost);
                //create pathLink (pathLinkList = createPathLinkList(newItemData->head,newItemData->tail,newItemData -> cost));
                //below function will be overwrite by addGraphPathIntoPathCostAVL
                //nodeOut =createGraphPath(createShortestPath(newItemData,pathLinkList));
                //rootTree = (GraphPath *)avlAdd((Node*)rootTree,(Node*)nodeOut,(Compare)graphCompareForAvlAdd);
            }
        }
        listItem= getNextListItem(nearestNodelinkList);
    }
    return rootTree;
}
// check is new route cost is smaller than pathCost
// if yes then override the old pathCost
// avlDelete it and add it back
GraphPath* modifyGraphNodeWithShorterPath(Link*ListItemData,GraphPath * rootTree,GraphPath * nodeOut,GraphPath * currentPointingNode){
    double newPathCost;
    ListItem *newListItem = (ListItem *)malloc(sizeof(ListItem));
    Node*root;

    newPathCost = ListItemData->cost + currentPointingNode->sPath->pathCost;
    if(nodeOut->sPath->pathCost > newPathCost){
        root = avlDelete((Node*)rootTree,(void*)nodeOut->sPath,(Compare)graphCompareForAvlDelete); //remove the old node that contain old data
        nodeOut->sPath->pathCost = newPathCost;
        nodeOut->sPath->pathLinks = NULL;
        resetCurrentListItem(currentPointingNode->sPath->pathLinks);
        nodeOut->sPath->pathLinks = currentPointingNode->sPath->pathLinks;
        newListItem->data = (void*)ListItemData;
        nodeOut->sPath->pathLinks = listAddItemToTail(nodeOut->sPath->pathLinks,newListItem);
        root = avlAdd(root,(Node*)nodeOut,(Compare)graphCompareForAvlAdd);
        return (GraphPath*)root;
    }
    else
        return rootTree;

}

GraphPath* findGraphPath(GraphPath * root,NetworkNode * dstNode){
    GraphPath * graphNode = NULL;
    if(root->sPath->dst == dstNode){
      return root;
    }
    if(root->left != NULL){
        graphNode = findGraphPath(root->left,dstNode);
        if(graphNode !=NULL)
            return graphNode;
    }
    if (root->right != NULL){
        graphNode = findGraphPath(root->right,dstNode);
        if(graphNode !=NULL)
            return graphNode;
    }
    return root;
}

GraphPath* addFirstGraphNodeIntoRootTree(NetworkNode * firstNode){
    GraphPath * rootTree=(GraphPath *)malloc(sizeof(GraphPath));
    List * firstGraphNodeList;
    rootTree->sPath->dst = firstNode;
    rootTree->sPath->src = firstNode;
    rootTree->sPath->pathCost = 0;
    firstGraphNodeList=createLinkListForShortestPath(firstNode,firstNode,0);
    rootTree->sPath->pathLinks = firstGraphNodeList;
    return rootTree;
}
