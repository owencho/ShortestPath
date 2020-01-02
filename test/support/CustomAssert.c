#include "CustomAssert.h"
#include "unity.h"
#include "Exception.h"
#include <stdio.h>
#include <stdint.h>
#include <malloc.h>
#include <stdarg.h>

void assertEqualGraphPath(const GraphPath * actualGraphPath,
                          const GraphPath * left,
                          const GraphPath * right,
                          const int bFactor,
                          const ShortestPath * sPath,
                          const UNITY_LINE_TYPE lineNumber){

    char msg[1024];
    int length;
    int i;

    if(actualGraphPath == NULL){
        UNITY_TEST_FAIL(lineNumber,"The actual GraphPath is NULL");
    }
    if(actualGraphPath->left != left){
        if(left == NULL){
            sprintf(msg,"the actual left GraphPath is (dst=%s,src=%s) and not NULL"
                    ,actualGraphPath->left->sPath->dst->name,actualGraphPath->left->sPath->src->name);
        }
        else if (actualGraphPath->left == NULL){
            sprintf(msg,"the actual left GraphPath is NULL and not (dst=%s,src=%s) "
                    ,left->sPath->dst->name,left->sPath->src->name);
        }
        else{
            sprintf(msg,"Expected (dst=%s,src=%s)  but encountered (dst=%s,src=%s) in actualGraphPath , the left GraphPath is not the same"
                    ,left->sPath->dst->name,left->sPath->src->name,actualGraphPath->left->sPath->dst->name,actualGraphPath->left->sPath->src->name);
        }
        UNITY_TEST_FAIL(lineNumber,msg);
    }

    if(actualGraphPath->right != right){
        if(right == NULL){
            sprintf(msg,"the actual right GraphPath is (dst=%s,src=%s) and not NULL"
                    ,actualGraphPath->right->sPath->dst->name,actualGraphPath->right->sPath->src->name);
        }
        else if (actualGraphPath->right == NULL){
            sprintf(msg,"the actual right GraphPath is NULL and not (dst=%s,src=%s) "
                        ,right->sPath->dst->name,right->sPath->src->name);
        }
        else{
            sprintf(msg,"Expected (dst=%s,src=%s)  but encountered (dst=%s,src=%s) in actualGraphPath , the right GraphPath is not the same"
                    ,right->sPath->dst->name,right->sPath->src->name,actualGraphPath->right->sPath->dst->name,actualGraphPath->right->sPath->src->name);
        }
        UNITY_TEST_FAIL(lineNumber,msg);
    }

    if(actualGraphPath->bFactor != bFactor){
        sprintf(msg,"Expected %d but encountered %d in actualGraphPath, the balanceFactor on graphPath (dst=%s,src=%s)  is not the same"
                ,bFactor,actualGraphPath->bFactor,actualGraphPath->sPath->dst->name,actualGraphPath->sPath->src->name);
        UNITY_TEST_FAIL(lineNumber,msg);
    }
    assertEqualShortestPath(actualGraphPath->sPath,sPath->dst,sPath->src,sPath->pathCost,sPath->pathLinks,lineNumber);
}

void assertEqualShortestPath(const ShortestPath * actualShortestPath,
                          const NetworkNode * dst,
                          const NetworkNode * src,
                          const double pathCost,
                          const List * pathLinks,
                          const UNITY_LINE_TYPE lineNumber){

    char msg[1024];
    int length;
    int i;

    if(actualShortestPath == NULL){
        UNITY_TEST_FAIL(lineNumber,"The actual ShortestPath is NULL");
    }
    if(actualShortestPath->dst != dst){
        if(dst == NULL){
            sprintf(msg,"the actual destination ShortestPath is %s and not NULL",actualShortestPath->dst->name);
        }
        else{
            sprintf(msg,"Expected %s but encountered %s in actualShortestPath , the destination node is not the same",dst->name,actualShortestPath->dst->name);
        }
        UNITY_TEST_FAIL(lineNumber,msg);
    }

    if(actualShortestPath->src != src){
        if(src == NULL){
            sprintf(msg,"the actual source node is %s and not NULL",actualShortestPath->src->name);
        }
        else{
            sprintf(msg,"Expected node %s but encountered node %s in actualShortestPath , the source node is not the same",src->name,actualShortestPath->src->name);
        }
        UNITY_TEST_FAIL(lineNumber,msg);
    }

    if(actualShortestPath->pathCost != pathCost){
        sprintf(msg,"Expected %.0f but encountered %.0f in actualShortestPath, the cost on from  %s to %s is not the same",
                pathCost,actualShortestPath->pathCost,actualShortestPath->src->name,actualShortestPath->dst->name);
        UNITY_TEST_FAIL(lineNumber,msg);
    }

    if(actualShortestPath->pathLinks != pathLinks){
        sprintf(msg,"Expected pathlink are different from the actual pathLinks");
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
            sprintf(msg,"Expected node %s but encountered node %s in actualLinkItemData , the head node is not the same",head->name,actualLinkItemData->head->name);
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
