//==================
// AnalogHelper.cpp
//==================

#include "pch.h"


//=======
// Using
//=======

#include <driver/adc.h>
#include "AnalogHelper.h"
#include "System.h"


//===========
// Namespace
//===========

namespace Devices {
	namespace Gpio {


//=========
// Globals
//=========

BOOL bAdcInitalized=false;


//========
// Common
//========

FLOAT AnalogRead(BYTE upin)
{
if(upin!=17)
	return 0.f;
if(!bAdcInitalized)
	{
	adc_config_t cfg;
	cfg.mode=ADC_READ_TOUT_MODE;
	cfg.clk_div=1;
	if(adc_init(&cfg)!=ESP_OK)
		{
		DebugPrint("adc_init() failed\r\n");
		return 0.f;
		}
	bAdcInitalized=true;
	}
WORD uvalue=0;
if(adc_read(&uvalue)!=ESP_OK)
	{
	DebugPrint("adc_read() failed\r\n");
	return 0.f;
	}
if(uvalue>=1023)
	uvalue=0;
FLOAT fvalue=(FLOAT)uvalue/1000.f;
fvalue=fvalue/3.3f*System::Voltage;
return fvalue;
}

}}