//=======
// Cpu.h
//=======

#pragma once


//===========
// Namespace
//===========

namespace Devices {


//=====
// Cpu
//=====

class Cpu
{
public:
	// Common
	static VOID DisableInterrupts();
	static VOID EnableInterrupts();
	static const UINT Frequency=80000000;
	static inline UINT GetCycleCount() __attribute__((always_inline))
		{
		UINT ccount;
		__asm __volatile("rsr %0,ccount":"=a" (ccount));
		return ccount;
		}
	static inline VOID Sleep(UINT MicroSeconds)
		{
		UINT ustart=GetCycleCount();
		UINT uend=ustart+MicroSeconds*80;
		if(uend<ustart)
			while(GetCycleCount()>ustart);
		while(GetCycleCount()<uend);
		}

protected:
	// Con-/Destructors
	Cpu() {}
};

}
