//============
// I2CBus.cpp
//============

#include "pch.h"


//=======
// Using
//=======

#include "I2CBus.h"


//===========
// Namespace
//===========

namespace Devices {
	namespace I2C {


//==================
// Con-/Destructors
//==================

I2CBus::I2CBus(BYTE sda, BYTE scl)
{
}

I2CBus::~I2CBus()
{
}


//===============
// Output-Stream
//===============

VOID I2CBus::Flush()
{
}

SIZE_T I2CBus::Write(BYTE uvalue)
{
return 0;
}

SIZE_T I2CBus::Write(VOID const* pbuf, SIZE_T usize)
{
return 0;
}


//========
// Common
//========

VOID I2CBus::BeginRead(BYTE uaddr)
{
}

VOID I2CBus::BeginWrite(BYTE uaddr)
{
}

Handle<I2CBus> I2CBus::Current=new I2CBus();

VOID I2CBus::EndTransmission(BOOL bstop)
{
}

}}
