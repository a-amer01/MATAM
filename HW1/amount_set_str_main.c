#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "amount_set_str.h"
#include  "tests/test_utilities.h"
#include  "amount_set_str_tests.h"

int main()
{
    RUN_TEST(testasCreateDestroy);
    RUN_TEST(testasRegister);
    RUN_TEST(testasDelete);
    RUN_TEST(testAmountandSize);
    RUN_TEST(testasContains);
    RUN_TEST(testasCopy);
    RUN_TEST(testIterator);
    RUN_TEST(testasClear);
    

    return 0;

}