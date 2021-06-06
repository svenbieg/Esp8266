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


//==========
// Callback
//==========

BOOL bClockSet=false;

VOID ClockCallback(timeval* pt)
{
if(sntp_get_sync_status()!=SNTP_SYNC_STATUS_COMPLETED)
	return;
bClockSet=true;
}


//========
// Common
//========

BOOL ClockIsSet()
{
return bClockSet;
}

VOID ClockStartSync()
{
ClockStopSync();
sntp_set_sync_mode(SNTP_SYNC_MODE_IMMED);
sntp_setoperatingmode(SNTP_OPMODE_POLL);
sntp_setservername(0, "pool.ntp.org");
sntp_set_time_sync_notification_cb(ClockCallback);
sntp_init();
}

VOID ClockStopSync()
{
if(sntp_enabled())
	sntp_stop();
}

}