#pragma once
#include <afxmt.h>
#include <queue>
using namespace std;

template <typename T>
class QueueManager {
protected:
	int			m_maxsize;

	CCriticalSection				m_cs_queue;
	queue<T*>						m_queue;

public:
	QueueManager(int _maxsize)		{ m_maxsize = _maxsize; }
	virtual ~QueueManager()			{ Clear(); }

	virtual void Clear() {
		while (GetSize() > 0) {
			T* pNode = Pop();
			delete pNode;
		}
	}

	bool	Push(T* _pNode) {

		bool bFull = false;

		if (GetSize() >= m_maxsize) {
			bFull = true;
		}

		if (bFull)
			return false;

		m_cs_queue.Lock();
		{
			m_queue.push(_pNode);
		}
		m_cs_queue.Unlock();

		return true;
	}

	T*		Pop() {

		T* pRlt = NULL;

		m_cs_queue.Lock();
		{
			pRlt = m_queue.front();
			m_queue.pop();
		}
		m_cs_queue.Unlock();

		return pRlt;
	}

	int GetSize() {
		int size = 0;

		m_cs_queue.Lock();
		{
			size = m_queue.size();
		}
		m_cs_queue.Unlock();

		return size;
	}

};


