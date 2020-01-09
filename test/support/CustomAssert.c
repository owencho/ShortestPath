#include "CustomAssert.h"
#include "unity.h"
#include "Exception.h"
#include <stdio.h>
#include <stdint.h>
#include <malloc.h>
#include <stdarg.h>
#include <string.h>
/*
void assertEqualGraphPath(const GraphPath * actualGraphPath,
                          const GraphPath * left,
                          const GraphPath * right,
                          const int bFactor,
                          const ShortestPathNode * sPath,
                          const UNITY_LINE_TYPE lineNumber){

    char msg[1024];
    int length;
    int i;

    if(actualGraphPath == NULL){
        UNITY_TEST_FAIL(lineNumber,"The actual GraphPath is NULL");
    }
    if(actualGraphPath->left != left){
        if(left == NULL){
            sprintf(msg,"the actual left GraphPath is %s and not NULL"
                    ,actualGraphPath->left->sPath->id->name,actualGraphPath->left->sPath->src->name);
        }
        else if (actualGraphPath->left == NULL){
            sprintf(msg,"the actual left GraphPath is NULL and not (id=%s,src=%s) "
                    ,left->sPath->id->name,left->sPath->src->name);
        }
        else{
            sprintf(msg,"Expected (id=%s,src=%s)  but encountered (id=%s,src=%s) in actualGraphPath , the left GraphPath is not the same"
                    ,left->sPath->id->name,left->sPath->src->name,actualGraphPath->left->sPath->id->name,actualGraphPath->left->sPath->src->name);
        }
        UNITY_TEST_FAIL(lineNumber,msg);
    }

    if(actualGraphPath->right != right){
        if(right == NULL){
            sprintf(msg,"the actual right GraphPath is (id=%s,src=%s) and not NULL"
                    ,actualGraphPath->right->sPath->id->name,actualGraphPath->right->sPath->src->name);
        }
        else if (actualGraphPath->right == NULL){
            sprintf(msg,"the actual right GraphPath is NULL and not (id=%s,src=%s) "
                        ,right->sPath->id->name,right->sPath->src->name);
        }
        else{
            sprintf(msg,"Expected (id=%s,src=%s)  but encountered (id=%s,src=%s) in actualGraphPath , the right GraphPath is not the same"
                    ,right->sPath->id->name,right->sPath->src->name,actualGraphPath->right->sPath->id->name,actualGraphPath->right->sPath->src->name);
        }
        UNITY_TEST_FAIL(lineNumber,msg);
    }

    if(actualGraphPath->bFactor != bFactor){
        sprintf(msg,"Expected %d but encountered %d in actualGraphPath, the balanceFactor on graphPath (id=%s,src=%s)  is not the same"
                ,bFactor,actualGraphPath->bFactor,actualGraphPath->sPath->id->name,actualGraphPath->sPath->src->name);
        UNITY_TEST_FAIL(lineNumber,msg);
    }
    assertEqualShortestPath(actualGraphPath->sPath,sPath->id,sPath->src,sPath->pathCost,sPath->pathLinks,lineNumber);
}
*/
void assertEqualShortestPath(const ShortestPathNode * actualShortestPath,
                             const NetworkNode * id,
                             const ShortestPathNode * parent,
                             const int pathCost,
                             const double linkCost,
                             const UNITY_LINE_TYPE lineNumber){

    char msg[1024];
    int length;
    int i;

    if(actualShortestPath == NULL){
        UNITY_TEST_FAIL(lineNumber,"The actual ShortestPathNode is NULL");
    }

    if(actualShortestPath->parent != NULL && parent !=NULL){
        assertEqualShortestPath(actualShortestPath->parent,parent->id,parent->parent,parent->pathCost,parent->linkCost,lineNumber);
    }
    else if(actualShortestPath->parent != NULL && parent == NULL){
        sprintf(msg,"the actual parent ShortestPathNode is %s and not NULL",actualShortestPath->parent->id->name);
        UNITY_TEST_FAIL(lineNumber,msg);
    }
    else if(actualShortestPath->parent == NULL && parent != NULL){
        sprintf(msg,"the actual parent ShortestPathNode is NULL");
        UNITY_TEST_FAIL(lineNumber,msg);
    }

    if(id != NULL){
        if(strcmp(actualShortestPath->id->name,id->name)!=0){
            sprintf(msg,"Expected %s but encountered %s in actualShortestPath , the id node is not the same",id->name,actualShortestPath->id->name);
            UNITY_TEST_FAIL(lineNumber,msg);
        }
    }
    else{
        sprintf(msg,"the actual id of ShortestPathNode is %s and not NULL",actualShortestPath->id->name);
        UNITY_TEST_FAIL(lineNumber,msg);
    }

    if(actualShortestPath->pathCost != pathCost){
        sprintf(msg,"Expected %d but encountered %d in actualShortestPath, the path cost on %s is not the same",
                pathCost,actualShortestPath->pathCost,actualShortestPath->id->name);
        UNITY_TEST_FAIL(lineNumber,msg);
    }

    if(actualShortestPath->linkCost != linkCost){
        sprintf(msg,"Expected %d but encountered %d in actualShortestPath, the link cost on %s is not the same",
                linkCost,actualShortestPath->linkCost,actualShortestPath->id->name);
        UNITY_TEST_FAIL(lineNumber,msg);
    }

}

void assertEqualLink(const Link * actualLinkItemData,
                     const NetworkNode * head,
                     const NetworkNode * tail,
                     const int cost,
                     const UNITY_LINE_TYPE lineNumber){

    char msg[1024];
    int length;
    int i;

    if(actualLinkItemData == NULL){
        UNITY_TEST_FAIL(lineNumber,"The actual linkItemData is NULL");
    }
    if(actualLinkItemData->head != head){
        if(head == NULL){
            sprintf(msg,"the actual head node is %s and not NULL",actualLinkItemData->head->name);
        }
        else{
            sprintf(msg,"Expected %s but encountered %s in actualLinkItemData , the head node is not the same",head->name,actualLinkItemData->head->name);
        }
        UNITY_TEST_FAIL(lineNumber,msg);
    }
    if(actualLinkItemData->tail != tail){
        if(tail == NULL){
            sprintf(msg,"the actual tail node is %s and not NULL",actualLinkItemData->tail->name);
        }
        else{
            sprintf(msg,"Expected tail node %s but encountered tail node %s in actualLinkItemData , the tail node is not the same",tail->name,actualLinkItemData->tail->name);
        }
        UNITY_TEST_FAIL(lineNumber,msg);
    }
    if(actualLinkItemData->cost != cost){
        sprintf(msg,"Expected %d but encountered %d in actualLinkItemData, the cost on from %s to  %s is not the same",
                cost,actualLinkItemData->cost,actualLinkItemData->tail->name,actualLinkItemData->head->name);
        UNITY_TEST_FAIL(lineNumber,msg);
    }
}


void testReportFailure (UNITY_LINE_TYPE lineNumber,char* message ,...){
    int actualLength;
    char* buffer;
    Exception *exceptionPtr;
    va_list arg;
    va_start(arg, message);
    actualLength = vsnprintf(NULL,0, message, arg);   //trick system to take actualLength
    buffer =malloc(actualLength + 1);               // allocate value to buffer
    vsnprintf(buffer,actualLength + 1, message, arg);
    va_end(arg);
    UNITY_TEST_FAIL(lineNumber, buffer);
}
