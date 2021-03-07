//===============
// MemoryClass.h
//===============

#pragma once


//===========
// Namespace
//===========

namespace Devices {


//========
// Memory
//========

class Memory: public Object
{
public:
	// Con-/Destructors
	Memory();

	// Common
	Handle<Int32> Available;
	Handle<Int32> Total;
	VOID Update();
};

}
