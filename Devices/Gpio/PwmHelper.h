//=============
// PwmHelper.h
//=============

#pragma once


//===========
// Namespace
//===========

namespace Devices {
	namespace Gpio {


//========
// Common
//========

VOID PwmInit(BYTE Pin, UINT PeriodUs);
VOID PwmSetDuty(BYTE Pin, UINT Duty);
VOID PwmSetPhase(BYTE Pin, SHORT Degrees);

}}
