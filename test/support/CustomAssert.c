#include "CustomAssert.h"
#include "unity.h"
#include "Exception.h"
#include <stdio.h>
#include <stdint.h>
#include <malloc.h>
#include <stdarg.h>

void assertEqualGraphPath(const GraphPath * actualGraphPath,
                          const NetworkNode * dst,
                          const NetworkNode * src,
                          const double pathCost,
                          const List * pathLinks,
                          const UNITY_LINE_TYPE lineNumber){

    char msg[1024];
    int length;
    int i;

    if(actualGraphPath == NULL){
        UNITY_TEST_FAIL(lineNumber,"The actual Node is NULL");
    }
    if(actualGraphPath->value->dst != dst){
        if(dst == NULL){
            sprintf(msg,"the actual destination node is %s and not NULL",actualGraphPath->value->dst->name);
        }
        else if (actualGraphPath->left == NULL){
            sprintf(msg,"the actual destination node is NULL and not %s ",dst->name);
        }
        else{
            sprintf(msg,"Expected node %s but encountered node %s in actualGraphPath , the destination node is not the same",dst->name,actualGraphPath->value->dst->name);
        }
        UNITY_TEST_FAIL(lineNumber,msg);
    }

    if(actualGraphPath->value->src != src){
        if(rightNode == NULL){
            sprintf(msg,"the actual source node is %s and not NULL",actualGraphPath->value->src->name);
        }
        else if (actualGraphPath->right == NULL){
            sprintf(msg,"the actual source node is NULL and not %s ",src->name);
        }
        else{
            sprintf(msg,"Expected node %s but encountered node %s in actualGraphPath , the source node is not the same",src->value,actualGraphPath->value->src->name);
        }
        UNITY_TEST_FAIL(lineNumber,msg);
    }

    if(actualGraphPath->value->pathCost != pathCost){
        sprintf(msg,"Expected %d but encountered %d in actualGraphPath, the balanceFactor on from node %s to node %s is not the same",
                pathCost,actualGraphPath->pathCost,actualGraphPath->value->src->name,actualGraphPath->value->dst->name);
        UNITY_TEST_FAIL(lineNumber,msg);
    }

    if(actualGraphPath->value->pathLinks != pathLinks){
        sprintf(msg,"Expected pathlink are different from the actual pathLinks");
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
