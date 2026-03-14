#ifndef STACK_H
#define STACK_H

#include "../0.공통/debug_print.h"	//로그, 경고, 에러 등의 콘솔 출력을 위한 매크로를 추후 도입할 예정
using namespace std;				//생성자 리스트, 이동 생성자, 할당자, 삽입 메소드에서 std::move(..)를 사용함

template <class DataType>
class Stack;

template <class DataType>
class StackNode
{
private:
	friend class Stack<DataType>;

	DataType m_data;
	StackNode* m_pChild;

	StackNode(const DataType& newData)
		: m_data(newData), m_pChild(NULL)
	{

	}

	StackNode(DataType&& newData)
		: m_data(move(newData)), m_pChild(NULL)
	{

	}

	//이 노드를 사용하는 Stack에서는 순회를 이용한 소멸자가 정의되어있으므로,
	//일단 노드 소멸자에서 m_pChild와 그 자식들의 해제를 하는 코드를 작성할 필요는 없음
	~StackNode() noexcept
	{

	}

	//노드에 저장될 데이터를 인자로 명시해주는 경우에만 생성할 수 있도록 하며, 할당 또한 금지함
	StackNode() = delete;

	StackNode(const StackNode& sourceNode) = delete;

	StackNode(StackNode&& sourceNode) = delete;

	StackNode& operator = (const StackNode& sourceNode) = delete;

	StackNode& operator = (StackNode&& sourceNode) = delete;
};

template <class DataType>
class Stack
{
private:
	StackNode<DataType>* m_pHead;

public:
	Stack()
		: m_pHead(NULL)
	{
	
	}

	~Stack() noexcept
	{
		RemoveStack();
	}

	Stack(const Stack& sourceStack)
	{
		CopyStack(sourceStack);
	}

	Stack(Stack&& sourceStack)
	{
		m_pHead = sourceStack.m_pHead;
		sourceStack.m_pHead = NULL;
	}

	Stack& operator = (const Stack& sourceStack)
	{
		CopyStack(sourceStack);

		return *this;
	}

	Stack& operator = (Stack&& sourceStack)
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
};

#endif //STACK_H