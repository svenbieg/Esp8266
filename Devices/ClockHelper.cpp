//=================
// ClockHelper.cpp
//=================

#include "pch.h"


//=======
// Using
//=======

#include <lwip/apps/sntp.h>
#include "Devices/Clock.h"
#include "Devices/ClockHelper.h"


//===========
// Namespace
//===========

namespace Devices {


//========
// Common
//========

VOID ClockStartSync()
{
ClockStopSync();
sntp_setoperatingmode(SNTP_OPMODE_POLL);
CHAR pserver[13];
StringCopy(pserver, 8, "pool.ntp.org");
sntp_setservername(0, pserver);
sntp_init();
}

VOID ClockStopSync()
{
if(sntp_enabled())
	sntp_stop();
}

}