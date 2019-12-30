#include "unity.h"
#include "CustomAssert.h"

void setUp(void){}

void tearDown(void){}

/**
*            50(0)
*           /   \
*         30(0)  60(0)
**/

void test_CustomAssert_given_30_50_60_expected_to_pass(void){
    initIntNode(&node30,NULL,NULL,0);
    initIntNode(&node60,NULL,NULL,0);
    initIntNode(&node50,&node30,&node60,0);

    //Test
    TEST_ASSERT_EQUAL_INT_NODE(&node50,&node30,&node60,0);
    TEST_ASSERT_EQUAL_INT_NODE(&node30,NULL,NULL,0);
    TEST_ASSERT_EQUAL_INT_NODE(&node60,NULL,NULL,0);
}
