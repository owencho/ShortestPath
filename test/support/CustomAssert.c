#include "CustomAssert.h"
#include "unity.h"
#include "Exception.h"
#include <stdio.h>
#include <stdint.h>
#include <malloc.h>
#include <stdarg.h>
#include <string.h>
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
