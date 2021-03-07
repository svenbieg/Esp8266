//============
// System.cpp
//============

#include "pch.h"


//=======
// Using
//=======

#include <esp_sleep.h>
#include <esp_system.h>
#include <esp_wifi.h>
#include <rom/ets_sys.h>
#include "Devices/Storage/FlashDevice.h"
#include "System.h"

using namespace Collections;
using namespace Devices;
using namespace Devices::Storage;
using namespace Physics;


//========
// Common
//========

WakeupReason System::GetWakeupReason()
{
auto cause=esp_reset_reason();
switch(cause)
	{
	case ESP_RST_DEEPSLEEP:
		return WakeupReason::Timer;
	default:
		break;
	}
return WakeupReason::None;
}

Handle<Memory> System::Memory;

VOID System::Reset()
{
auto hflash=FlashDevice::Current;
if(hflash)
	{
	UINT usize=hflash->GetSize();
	hflash->Erase(0, usize);
	}
esp_restart();
}

VOID System::Restart()
{
DebugPrint("Restart...\n");
esp_restart();
}

VOID System::Sleep(UINT ums)
{
esp_wifi_stop();
esp_deep_sleep(ums*1000);
}

Handle<TimePoint> System::Start=new TimePoint("SystemStart");

static const FLOAT Voltage=3.3f;
