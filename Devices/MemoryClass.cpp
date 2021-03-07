//=================
// MemoryClass.cpp
//=================

#include "pch.h"


//=======
// Using
//=======

#include <esp_heap_caps.h>
#include "Runtime/Application.h"
#include "MemoryClass.h"

using namespace Runtime;


//===========
// Namespace
//===========

namespace Devices {


//==================
// Con-/Destructors
//==================

Memory::Memory()
{
Available=new Int32("MemoryAvailable", 0);
Total=new Int32("MemoryTotal", 72*1024);
}


//========
// Common
//========

VOID Memory::Update()
{
Available=heap_caps_get_free_size(MALLOC_CAP_32BIT);
}

}
