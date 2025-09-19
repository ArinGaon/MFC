
#pragma once

#include <windows.h>

class AFX_EXT_CLASS CStopWatch
{

public:
	CStopWatch();
	virtual ~CStopWatch();

public:
	void Start();
	void Stop();

	FLOAT GetDurationSecond() {
		return m_fTimeforDuration;
	}
	FLOAT GetDurationMilliSecond() {
		return (m_fTimeforDuration * 1000.0F);
	}

protected:
	LARGE_INTEGER m_swFreq;
	LARGE_INTEGER m_swStart;
	LARGE_INTEGER m_swEnd;
	FLOAT m_fTimeforDuration;
};