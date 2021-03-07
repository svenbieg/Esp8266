//===============
// PwmHelper.cpp
//===============

#include "pch.h"


//=======
// Using
//=======

#include <driver/pwm.h>
#include "Devices/Gpio/GpioHelper.h"
#include "PwmHelper.h"


//===========
// Namespace
//===========

namespace Devices {
	namespace Gpio {


//=========
// Globals
//=========

BOOL pPwmInitalized[4]={ false, false, false, false };


//========
// Common
//========

VOID PwmInit(BYTE upin, UINT uperiod)
{
if(upin<12||upin>15)
	return;
BYTE uch=upin-12;
if(pPwmInitalized[uch])
	return;
UINT up=upin;
UINT uduty=0;
if(pwm_init(uperiod, &uduty, 1, &up)!=ESP_OK)
	{
	DebugPrint("pwm_init() failed\r\n");
	return;
	}
if(pwm_start()!=ESP_OK)
	{
	DebugPrint("pwm_start() failed\r\n");
	return;
	}
pPwmInitalized[uch]=true;
}

VOID PwmSetDuty(BYTE upin, UINT uduty)
{
if(upin<12||upin>15)
	return;
BYTE uch=upin-12;
if(!pPwmInitalized[uch])
	PwmInit(upin, 1000);
if(pwm_set_duty(uch, uduty)!=ESP_OK)
	{
	DebugPrint("pwm_set_duty() failed\r\n");
	return;
	}
if(pwm_start()!=ESP_OK)
	{
	DebugPrint("pwm_start() failed\r\n");
	return;
	}
}

VOID PwmSetPhase(BYTE upin, SHORT ideg)
{
if(upin<12||upin>15)
	return;
BYTE uch=upin-12;
if(!pPwmInitalized[uch])
	PwmInit(upin, 1000);
if(pwm_set_phase(uch, ideg)!=ESP_OK)
	{
	DebugPrint("pwm_set_phase() failed\r\n");
	return;
	}
if(pwm_start()!=ESP_OK)
	{
	DebugPrint("pwm_start() failed\r\n");
	return;
	}
}

}}
