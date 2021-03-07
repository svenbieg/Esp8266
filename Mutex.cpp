//===========
// Mutex.cpp
//===========

#include "pch.h"


//=======
// Using
//=======

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "Mutex.h"


//==================
// Con-/Destructors
//==================

Mutex::Mutex()
{
portENTER_CRITICAL();
}

Mutex::~Mutex()
{
Release();
}


//========
// Common
//========

VOID Mutex::Release()
{
portEXIT_CRITICAL();
}
