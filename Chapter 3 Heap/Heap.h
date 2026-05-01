#ifndef HEAP_H
#define HEAP_H

#include "../Common/Debug.h"	//정의한 로그 출력 매크로를 사용함
#include <utility>				//이동 시맨틱을 사용함
using namespace std;

class Heap
{
public:

	Heap()
	{
		LogPrint("empty constructor");

		m_pData = DBG_NEW int[50];
		m_size = 0;
		m_capacity = 50;
	}

	Heap(const Heap& sourceHeap)
	{
		LogPrint("copy constructor");

		m_pData = DBG_NEW int[sourceHeap.m_capacity];
		m_capacity = sourceHeap.m_capacity;
		m_size = sourceHeap.m_size;

		for (int i = 0; i < m_size; i++)
		{
			m_pData[i] = sourceHeap.m_pData[i];
		}
	}

	Heap(Heap&& sourceHeap) noexcept
	{
		LogPrint("move constructor");

		m_pData = sourceHeap.m_pData;
		sourceHeap.m_pData = nullptr;

		m_capacity = sourceHeap.m_capacity;
		m_size = sourceHeap.m_size;
	}

	Heap& operator = (const Heap& sourceHeap)
	{
		LogPrint("copy assignment");

		if (this == &sourceHeap)
		{
			return *this;
		}

		RemoveAll();

		m_pData = DBG_NEW int[sourceHeap.m_capacity];
		m_capacity = sourceHeap.m_capacity;
		m_size = sourceHeap.m_size;

		for (int i = 0; i < m_size; i++)
		{
			m_pData[i] = sourceHeap.m_pData[i];
		}
	}

	Heap& operator = (Heap&& sourceHeap) noexcept
	{
		LogPrint("move assignment");

		if (this == &sourceHeap)
		{
			return *this;
		}

		RemoveAll();

		m_pData = sourceHeap.m_pData;
		sourceHeap.m_pData = nullptr;

		m_capacity = sourceHeap.m_capacity;
		m_size = sourceHeap.m_size;
	}

	~Heap() noexcept
	{
		LogPrint("destructor");

		delete[] m_pData;
		m_pData = nullptr;
		m_size = 0;
		m_capacity = 0;
	}

	void Push(int newData)
	{
		LogPrint("push");

		if (m_size >= m_capacity)
		{
			GiveLargerMemorySpace();
		}

		m_pData[m_size] = newData;
		m_size++;
		ReorderByPromoting();
	}

	int GetTop()
	{
		LogPrint("get top");

		if (m_size <= 0)
		{
			WarningPrint("can't get item from heap because heap is empty.");
			return 0;
		}

		return m_pData[0];
	}

	int Pop()
	{
		LogPrint("pop");

		if (m_size <= 0)
		{
			WarningPrint("cannot pop item from heap because heap is empty.");
			return 0;
		}

		int poppedData = m_pData[0];

		m_size--;
		m_pData[0] = m_pData[m_size];
		ReorderByDemoting();

		return poppedData;
	}

	void RemoveAll()
	{
		LogPrint("remove all");

		delete[] m_pData;
		m_size = 0;
		m_capacity = 0;
	}

protected:

	int GetLeftChildIndex(int dataIndex)
	{
		return (dataIndex * 2 + 1);
	}

	int GetRightChildIndex(int dataIndex)
	{
		return (dataIndex * 2 + 2);
	}

	int GetParentIndex(int dataIndex)
	{
		return ((dataIndex - 1) / 2);
	}

	void Swap(int& dataA, int& dataB)
	{
		int temp = move(dataA);
		dataA = move(dataB);
		dataB = move(temp);
	}

	virtual bool IsNotOrdered(int parentIndex, int childIndex) = 0;					//상속된 최소힙 or 최대힙에서 각기 방식으로 구체화함

	virtual bool IsLeftChildTarget(int leftChildIndex, int rightChildIndex) = 0;	//상속된 최소힙 or 최대힙에서 각기 방식으로 구체화함

	void ReorderByPromoting();

	void ReorderByDemoting();

	void GiveLargerMemorySpace()
	{
		int newCapacity = (m_capacity == 0) ? (50) : (2 * m_capacity);
		int* newData = DBG_NEW int[newCapacity];

		for (int i = 0; i < m_size; i++)
		{
			newData[i] = m_pData[i];
		}

		delete[] m_pData;
		m_pData = newData;
		m_capacity = newCapacity;
	}

protected:

	int* m_pData;
	int m_size;
	int m_capacity;
};

void Heap::ReorderByPromoting()
{
	int targetIndex = m_size - 1;
	int parentIndex = GetParentIndex(targetIndex);

	while (targetIndex != parentIndex && IsNotOrdered(parentIndex, targetIndex))
	{
		Swap(m_pData[targetIndex], m_pData[parentIndex]);
		targetIndex = parentIndex;
		parentIndex = GetParentIndex(targetIndex);
	}
}

void Heap::ReorderByDemoting()
{
	int targetIndex = 0;
	int leftChildIndex = GetLeftChildIndex(targetIndex);
	int rightChildIndex = GetRightChildIndex(targetIndex);
	int targetChildIndex;

	while (leftChildIndex < m_size)
	{
		if (rightChildIndex < m_size)
		{
			if (IsLeftChildTarget(leftChildIndex, rightChildIndex))
			{
				targetChildIndex = leftChildIndex;
			}
			else
			{
				targetChildIndex = rightChildIndex;
			}
		}
		else
		{
			targetChildIndex = leftChildIndex;
		}

		if (IsNotOrdered(targetIndex, targetChildIndex))
		{
			Swap(m_pData[targetIndex], m_pData[targetChildIndex]);

			targetIndex = targetChildIndex;
			leftChildIndex = GetLeftChildIndex(targetIndex);
			rightChildIndex = GetRightChildIndex(targetIndex);
		}
		else
		{
			break;
		}
	}
}

class MinHeap : public Heap
{
public:

	MinHeap() : Heap() {}

private:

	bool IsNotOrdered(int parentIndex, int childIndex)
	{
		if (m_pData[parentIndex] > m_pData[childIndex])
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool IsLeftChildTarget(int leftChildIndex, int rightChildIndex)
	{
		if (m_pData[leftChildIndex] < m_pData[rightChildIndex])
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

class MaxHeap : public Heap
{
public:

	MaxHeap() : Heap() {}

private:

	bool IsNotOrdered(int parentIndex, int childIndex)
	{
		if (m_pData[parentIndex] < m_pData[childIndex])
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool IsLeftChildTarget(int leftChildIndex, int rightChildIndex)
	{
		if (m_pData[leftChildIndex] > m_pData[rightChildIndex])
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

#endif //HEAP_H