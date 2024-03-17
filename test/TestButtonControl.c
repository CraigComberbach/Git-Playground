#include <stddef.h>
#include "ButtonControl.h"
#include "Types.h"
#include "UnityHelper.h"
#include "unity.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_PushButton(void)
{
	Initialize_Button(NULL, 3, BUTTON_, 5, 7, NULL, 11);
	TEST_ASSERT_TRUE(1);
}
