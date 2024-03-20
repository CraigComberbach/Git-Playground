#include <errno.h>
#include <stddef.h>
#include "ButtonControl.h"
#include "Types.h"
#include "UnityHelper.h"
#include "unity.h"

ErrorCode_t ReturnedValue;

/**********Happy Path Definitions**********/
ErrorCode_t (*Happy_ReadButtonFunction)(ButtonObjects_t) = NULL;
uint8_t Happy_ButtonToReference = 3;
ButtonObjects_t Happy_ButtonID = 0;
uint16_t Happy_ThresholdForPress_mS = 5;
uint16_t Happy_ThresholdForLongPress_mS = 7;
void (*Happy_NotificationFunction)(ButtonObjects_t, ButtonStatus_t) = NO_NOTIFICATION;
ButtonDefaultState_t Happy_DefaultState = NORMALLY_LOW;

/*************Fake Functions************/
ErrorCode_t Fake_ReadButtonFunction(ButtonObjects_t dummy);
void Fake_NotificationFunction(ButtonObjects_t Object, ButtonStatus_t Status);

ErrorCode_t Fake_ReadButtonFunction(ButtonObjects_t dummy)
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
	Happy_ButtonToReference = 3;
	ButtonObjects_t Happy_ButtonID = 0;
	Happy_ThresholdForPress_mS = 5;
	Happy_ThresholdForLongPress_mS = 7;
	Happy_DefaultState = NORMALLY_LOW;
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

	TEST_ASSERT_TRUE(ReturnedValue == SUCCESS);
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

	TEST_ASSERT_TRUE(ReturnedValue == SUCCESS);
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

void test_Initialize_Button_InvalidDefaultState(void)
{
	ReturnedValue = Initialize_Button(Happy_ReadButtonFunction,
									  Happy_ButtonToReference,
									  Happy_ButtonID,
									  Happy_ThresholdForPress_mS,
									  Happy_ThresholdForLongPress_mS,
									  Happy_NotificationFunction,
									  3);

	TEST_ASSERT_TRUE(ReturnedValue == ERANGE);
}

void test_Initialize_Button_LongpressThresholdIsGreaterThanPressThreshold(void)
{
	ReturnedValue = Initialize_Button(Happy_ReadButtonFunction,
									  Happy_ButtonToReference,
									  Happy_ButtonID,
									  5,
									  5,
									  Happy_NotificationFunction,
									  Happy_DefaultState);

	TEST_ASSERT_TRUE(ReturnedValue == EINVAL);
}
