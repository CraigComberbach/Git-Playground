#include "PWM.h"

void Setup_PWM(gpt_instance_ctrl_t *GPT_To_Use, uint32_t pin, double TargetDutyCycle, double TargetFrequency)
{
	timer_info_t p_info;
	uint32_t DutyCycle;
	uint32_t Frequency;

	R_GPT_InfoGet(GPT_To_Use, &p_info);

	Frequency = (uint32_t)((double)p_info.clock_frequency / TargetFrequency);
	DutyCycle = (uint32_t)((double)Frequency * TargetDutyCycle);

	R_GPT_Stop(GPT_To_Use);
	R_GPT_PeriodSet(GPT_To_Use, Frequency);
	R_GPT_DutyCycleSet(GPT_To_Use, DutyCycle, pin);
	R_GPT_Start(GPT_To_Use);
	return;
}

uint32_t period_us
	UNUSED(period_us);
