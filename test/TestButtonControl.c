#include <errno.h>
#include <stddef.h>
#include "ButtonControl.h"
#include "Types.h"
#include "UnityHelper.h"
#include "unity.h"

ErrorCode_t ReturnedValue;

/**********Happy Path Definitions**********/
int (*Happy_ReadButtonFunction)(int) = NULL;
int Happy_ButtonToReference = 3;
ButtonObjects_t Happy_ButtonID = 0;
int Happy_ThresholdForPress_mS = 5;
int Happy_ThresholdForLongPress_mS = 7;
void (*Happy_NotificationFunction)(ButtonObjects_t, ButtonStatus_t) = NULL;
ButtonDefaultState_t Happy_DefaultState = NORMALLY_LOW;

/*************Fake Functions************/
int Fake_ReadButtonFunction(int dummy);
void Fake_NotificationFunction(ButtonObjects_t Object, ButtonStatus_t Status);

int Fake_ReadButtonFunction(int dummy)
{
	return 0;
}
void Fake_NotificationFunction(ButtonObjects_t Object, ButtonStatus_t Status)
{
	return;
}

void setUp(void)
{
	ReturnedValue = 0;
	Happy_ReadButtonFunction = &Fake_ReadButtonFunction;
	Happy_NotificationFunction = &Fake_NotificationFunction;
}

void tearDown(void)
{
}

void test_Initialize_Button_HappyPath(void)
{
	ReturnedValue = Initialize_Button(Happy_ReadButtonFunction,
									  Happy_ButtonToReference,
									  Happy_ButtonID,
									  Happy_ThresholdForPress_mS,
									  Happy_ThresholdForLongPress_mS,
									  Happy_NotificationFunction,
									  Happy_DefaultState);

	TEST_ASSERT_TRUE(ReturnedValue == 0);
}

void test_Initialize_Button_ReadButtonIsNull(void)
{
	ReturnedValue = Initialize_Button(NULL,
									  Happy_ButtonToReference,
									  Happy_ButtonID,
									  Happy_ThresholdForPress_mS,
									  Happy_ThresholdForLongPress_mS,
									  Happy_NotificationFunction,
									  Happy_DefaultState);

	TEST_ASSERT_TRUE(ReturnedValue == EINVAL);
}

void test_Initialize_Button_NotificationIsNull(void)
{
	ReturnedValue = Initialize_Button(Happy_ReadButtonFunction,
									  Happy_ButtonToReference,
									  Happy_ButtonID,
									  Happy_ThresholdForPress_mS,
									  Happy_ThresholdForLongPress_mS,
									  NULL,
									  Happy_DefaultState);

	TEST_ASSERT_TRUE(ReturnedValue == 0);
}

void test_Initialize_Button_InvalidButtonID_Low(void)
{
	ReturnedValue = Initialize_Button(Happy_ReadButtonFunction,
									  Happy_ButtonToReference,
									  -1,
									  Happy_ThresholdForPress_mS,
									  Happy_ThresholdForLongPress_mS,
									  Happy_NotificationFunction,
									  Happy_DefaultState);

	TEST_ASSERT_TRUE(ReturnedValue == ERANGE);
}

void test_Initialize_Button_InvalidButtonID_High(void)
{
	ReturnedValue = Initialize_Button(Happy_ReadButtonFunction,
									  Happy_ButtonToReference,
									  NUMBER_OF_BUTTONS,
									  Happy_ThresholdForPress_mS,
									  Happy_ThresholdForLongPress_mS,
									  Happy_NotificationFunction,
									  Happy_DefaultState);

	TEST_ASSERT_TRUE(ReturnedValue == ERANGE);
}

void test_Initialize_Button_ExtremeValidThresholds(void)
{
	TEST_IGNORE();
}

void test_Initialize_Button_ExtremeInvalidThresholds(void)
{
	TEST_IGNORE();
}

void test_Initialize_Button_InvalidDefaultState(void)
{
	TEST_IGNORE();
}
