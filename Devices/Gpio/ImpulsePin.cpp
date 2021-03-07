//================
// ImpulsePin.cpp
//================

#include "pch.h"


//=======
// Using
//=======

#include <esp_attr.h>
#include <esp_timer.h>
#include "Devices/Gpio/GpioHelper.h"
#include "ImpulsePin.h"


//===========
// Namespace
//===========

namespace Devices {
	namespace Gpio {


//============
// Interrupts
//============

UINT IRAM_ATTR pEdgeCount[16];

VOID IRAM_ATTR InterruptProc(VOID* parg)
{
UINT upin=(UINT)parg;
pEdgeCount[upin]++;
}


//==================
// Con-/Destructors
//==================

ImpulsePin::ImpulsePin(BYTE upin, BYTE uunit):
uCount(0),
uPin(upin)
{
pEdgeCount[uPin]=0;
AttachInterrupt(uPin, InterruptProc, (VOID*)(UINT)uPin);
hTimer=new Timer();
hTimer->Triggered.Add(this, &ImpulsePin::OnTimerTriggered);
hTimer->StartPeriodic(1000000);
}


//================
// Common Private
//================

VOID ImpulsePin::OnTimerTriggered(Handle<Timer> htimer)
{
uCount=pEdgeCount[uPin]/2;
pEdgeCount[uPin]=0;
}

}}