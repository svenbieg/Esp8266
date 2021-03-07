//=========
// Cpu.cpp
//=========

#include "pch.h"


//=======
// Using
//=======

#include <rom/ets_sys.h>
#include <portmacro.h>
#include "Cpu.h"


//===========
// Namespace
//===========

namespace Devices {


//========
// Common
//========

VOID Cpu::DisableInterrupts()
{
portDISABLE_INTERRUPTS();
}

VOID Cpu::EnableInterrupts()
{
portENABLE_INTERRUPTS();
}

}
