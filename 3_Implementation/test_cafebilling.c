#include "unity.h"

extern void test_cafebilling();

void setup(void)
{

}

void tearDown(void)
{

}

int main(void)
{
    UnityBegin(NULL);

    RUN_TEST(test_cafebilling);

    return (UnityEnd());
}