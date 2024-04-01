
#pragma once

class cslock
{
public:
	CRITICAL_SECTION cs;				///< 임계영역

	cslock()
	{ 
		InitializeCriticalSectionAndSpinCount(&cs,4096);
	}

	~cslock()
	{ 
		DeleteCriticalSection(&cs); 
	}

	
	void lock()
	{ 
		EnterCriticalSection(&cs); 
	}

	void unlock()
	{ 
		LeaveCriticalSection(&cs); 
	}
};

