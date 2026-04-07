#ifndef STACK_H
#define STACK_H

#include <memory>					//유니크 포인터를 사용함
#include <utility>					//이동 시맨틱을 사용함
using namespace std;				//..

template <class DataType>
class Stack;

template <class DataType>
class StackNode
{
	friend class Stack<DataType>;

private:
	StackNode(const DataType& newData)
		: m_data(newData), m_pChild(NULL)
	{

	}

	StackNode(DataType&& newData)
		: m_data(move(newData)), m_pChild(NULL)
	{

	}

	//스택 클래스에 순회를 이용한 소멸자가 정의되어있으므로 노드의 소멸자 정의는 필요 없음
	~StackNode() noexcept
	{

	}

	//쓰이지 않는 노드 생성 방식들
	StackNode() = delete;

	StackNode(const StackNode& sourceNode) = delete;

	StackNode(StackNode&& sourceNode) = delete;

	StackNode& operator = (const StackNode& sourceNode) = delete;

	StackNode& operator = (StackNode&& sourceNode) = delete;

private:
	DataType m_data;
	StackNode* m_pChild;
};

template <class DataType>
class Stack
{
public:
	Stack()
		: m_pHead(NULL)
	{
	
	}

	Stack(const Stack& sourceStack)
	{
		CopyStack(sourceStack);
	}

	Stack(Stack&& sourceStack) noexcept
	{
		m_pHead = sourceStack.m_pHead;
		sourceStack.m_pHead = NULL;
	}

	Stack& operator = (const Stack& sourceStack)
	{
		CopyStack(sourceStack);

		return *this;
	}

	Stack& operator = (Stack&& sourceStack) noexcept
	{
		if (this == &sourceStack)
		{
			return *this;
		}

		RemoveStack();

		m_pHead = sourceStack.m_pHead;
		sourceStack.m_pHead = NULL;

		return *this;
	}

	~Stack() noexcept
	{
		RemoveStack();
	}

	bool Push(const DataType& data)
	{
		if (m_pHead == NULL)
		{
			m_pHead = new StackNode<DataType>(data);
		}
		else
		{
			StackNode<DataType>* pTraverse = m_pHead;
			while (pTraverse->m_pChild)
			{
				pTraverse = pTraverse->m_pChild;
			}

			pTraverse->m_pChild = new StackNode<DataType>(data);
		}

		return true;
	}

	bool Push(DataType&& data)
	{
		if (m_pHead == NULL)
		{
			m_pHead = new StackNode<DataType>(move(data));
		}
		else
		{
			StackNode<DataType>* pTraverse = m_pHead;
			while (pTraverse->m_pChild)
			{
				pTraverse = pTraverse->m_pChild;
			}

			pTraverse->m_pChild = new StackNode<DataType>(move(data));
		}

		return true;
	}

	bool Pop(DataType& outData)
	{
		if (m_pHead == NULL)
		{
			return false;
		}

		if (m_pHead->m_pChild == NULL)
		{
			outData = m_pHead->m_data;
			delete m_pHead;
			m_pHead = NULL;

			return true;
		}
		else
		{
			StackNode<DataType>* pTraverse = m_pHead;
			while (pTraverse->m_pChild->m_pChild != NULL)
			{
				pTraverse = pTraverse->m_pChild;
			}

			outData = pTraverse->m_pChild->m_data;
			delete pTraverse->m_pChild;
			pTraverse->m_pChild = NULL;

			return true;
		}
	}

	bool GetTop(DataType& outData)
	{
		if (m_pHead == NULL)
		{
			return false;
		}

		if (m_pHead->m_pChild == NULL)
		{
			outData = m_pHead->m_data;
			return true;
		}
		else
		{
			StackNode<DataType>* pTraverse = m_pHead;
			while (pTraverse->m_pChild->m_pChild)
			{
				pTraverse = pTraverse->m_pChild;
			}

			outData = pTraverse->m_pChild->m_data;
			return true;
		}
	}

	bool IsEmpty()
	{
		if (m_pHead == NULL) return true;
		else return false;
	}

	bool RemoveStack()
	{
		if (m_pHead == NULL)
		{
			return true;
		}

		StackNode<DataType>* pTraversePrev = m_pHead;
		StackNode<DataType>* pTraverseCurr = m_pHead->m_pChild;
		delete pTraversePrev;
		while (pTraverseCurr)
		{
			pTraversePrev = pTraverseCurr;
			pTraverseCurr = pTraverseCurr->m_pChild;
			delete pTraversePrev;
		}
		
		return true;
	}

	bool CopyStack(const Stack<DataType>& sourceStack)
	{
		if (sourceStack.m_pHead == NULL)
		{
			return false;
		}

		RemoveStack();

		StackNode<DataType>* pSourceStackTraverse = sourceStack.m_pHead;
		m_pHead = new StackNode<DataType>(pSourceStackTraverse->m_data);
		StackNode<DataType>* pDestStackTraverse = m_pHead;
		while (pSourceStackTraverse->m_pChild != NULL)
		{
			pSourceStackTraverse = pSourceStackTraverse->m_pChild;
			pDestStackTraverse->m_pChild = new StackNode<DataType>(pSourceStackTraverse->m_data);
			pDestStackTraverse = pDestStackTraverse->m_pChild;
		}

		return true;
	}

private:
	StackNode<DataType>* m_pHead;
};

#endif //STACK_H