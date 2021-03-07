//==========
// I2CBus.h
//==========

#pragma once


//=======
// Using
//=======

#include "Storage/Streams/OutputStream.h"


//===========
// Namespace
//===========

namespace Devices {
	namespace I2C {


//=========
// I2C-Bus
//=========

class I2CBus: public Storage::Streams::OutputStream
{
public:
	// Con-/Destructors
	I2CBus(BYTE PinSDA=21, BYTE PinSCL=22);
	~I2CBus();

	// Ouput-Stream
	VOID Flush()override;
	SIZE_T Write(BYTE Value);
	SIZE_T Write(VOID const* Buffer, SIZE_T Size)override;

	// Common
	VOID BeginRead(BYTE Address);
	VOID BeginWrite(BYTE Address);
	static Handle<I2CBus> Current;
	VOID EndTransmission(BOOL SendStop);
};

}}
