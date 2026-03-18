#ifndef BST_USING_WHILE_TEMPLATE_H
#define BST_USING_WHILE_TEMPLATE_H

#include "../0.공통/debug_print.h"	//로그, 경고, 에러 등의 콘솔 출력을 위한 매크로를 사용함
#include "../0.공통/stack.h"		//스택을 통해 일부 함수 상태를 저장하여 재귀 호출을 대체하도록 함
using namespace std;				//생성자 리스트, 이동 생성자, 할당자, 삽입 메소드에서 std::move(..)를 사용함

template <class NodeType>
class BST_Template
{
public:
	BST_Template() : m_pHead(NULL)
	{
		LogPrint("empty constructor");
	}

	~BST_Template() noexcept
	{
		LogPrint("destructor");

		RemoveTree();
	}

	BST_Template(const BST_Template<NodeType>& sourceBST)
	{
		LogPrint("copy constructor");

		CopyTree(sourceBST);
	}

	BST_Template(BST_Template<NodeType>&& sourceBST) noexcept
	{
		LogPrint("move constructor");

		m_pHead = sourceBST.m_pHead;
		sourceBST.m_pHead = NULL;
	}

	//TODO : CopyTree(..)가 매개변수를 const로 받지 않아서 이 메소드가 인스턴스화되면 오류가 발생할 것이다. 이 오류를 해결하자.
	BST_Template<NodeType>& operator = (const BST_Template<NodeType>& sourceBST)
	{
		LogPrint("copy assignment");

		if (this == &sourceBST)
		{
			return *this;
		}

		CopyTree(sourceBST);

		return *this;
	}

	BST_Template<NodeType>& operator = (BST_Template<NodeType>&& sourceBST) noexcept
	{
		LogPrint("move assignment");

		if (this == &sourceBST)
		{
			return *this;
		}

		RemoveTree();

		m_pHead = sourceBST.m_pHead;
		sourceBST.m_pHead = NULL;

		return *this;
	}

public:
	bool Insert(int newKey,int newData)
	{
		LogPrint("insert");

		NodeType* pDummyNode = NULL;
		bool isDummySet = Search(newKey, pDummyNode, &BST_Template::SetDummyChild);
		
		if (isDummySet == true)
		{
			pDummyNode->m_key = newKey;
			pDummyNode->m_data = newData;

			return true;
		}
		else
		{
			return false;
		}
	}

	bool Retrieve(int targetKey, int& outData)
	{
		LogPrint("retrieve");

		return Search(targetKey, outData, &BST_Template::GetNodeData);
	}

	bool Remove(int targetKey)
	{
		LogPrint("remove one item");

		char dummy = 'd';

		return Search(targetKey, dummy, &BST_Template::RemoveTarget);
	}

public:
	void RemoveTree() noexcept
	{
		LogPrint("remove tree");

		PostorderTraverse(&BST_Template::RemoveTwoChilds, this);
		delete m_pHead;
		m_pHead = NULL;
	}

	//트리의 값전달로 인해 복사생성자가 실행되는 것을 막기 위해 레퍼런스 인자를 사용함.
	//복사 생성자가 호출되는 것은 성능에도 안 좋으나, 무엇보다 복사 생성자가 CopyTree(..)를 이용해 구현되어있으므로, CopyTree가 복사 생성자를 이용하면 순환 오류가 난다.
	void CopyTree(BST_Template& sourceBST)
	{
		LogPrint("copy tree");

		sourceBST.PreorderTraverse(&BST_Template::CopyNode, this);
	}

	void PreorderPrint()
	{
		LogPrint("preorder print");

		PreorderTraverse(&BST_Template::PrintTargetNode, this);
	}

	void InorderPrint()
	{
		LogPrint("inorder print");

		InorderTraverse(&BST_Template::PrintTargetNode, this);
	}

	void PostorderPrint()
	{
		LogPrint("postorder print");

		PostorderTraverse(&BST_Template::PrintTargetNode, this);
	}

protected:
	//"pToDoWithTargetNode" 메소드 포인터는 특정 target_key를 가진 노드의 위치에 대해 수행할 작업을 넘겨주는 인터페이스임.
	//삽입과 삭제 메소드가 기능하려면 부모가 자식을 가리키는 포인터 변수를 직접 수정할 수 있어야 하기에, NodeType*&과 같이 레퍼런스 인자를 사용함.
	template <typename OutType>
	bool Search(int targetKey, OutType& out, bool (BST_Template::* pToDoWithTargetNode)(NodeType*&, OutType&))
	{
		if (m_pHead == NULL)
		{
			return (this->*pToDoWithTargetNode)(m_pHead, out);
		}
		else if (targetKey == m_pHead->m_key) 
		{
			return (this->*pToDoWithTargetNode)(m_pHead, out);
		}
		else
		{
			NodeType* pSearch = m_pHead;
			while (true)
			{
				if (targetKey < pSearch->m_key)
				{
					if (pSearch->m_pLeftChild != NULL && pSearch->m_pLeftChild->m_key != targetKey)
					{
						pSearch = pSearch->m_pLeftChild;
					}
					else
					{
						return (this->*pToDoWithTargetNode)(pSearch->m_pLeftChild, out);
					}
				}
				else
				{
					if (pSearch->m_pRightChild != NULL && pSearch->m_pRightChild->m_key != targetKey)
					{
						pSearch = pSearch->m_pRightChild;
					}
					else
					{
						return (this->*pToDoWithTargetNode)(pSearch->m_pRightChild, out);
					}
				}
			}
		}
	}

	bool SetDummyChild(NodeType*& pDummyNode, NodeType*& pOutNode)
	{
		pOutNode = pDummyNode = new NodeType(0, 0);

		return true;
	}

	bool GetNodeData(NodeType*& pTargetNode, int& outData)
	{
		outData = pTargetNode->m_data;

		return true;
	}

	bool RemoveTarget(NodeType*& pTargetNode, char& dummyParmeter)
	{
		if (pTargetNode->m_pLeftChild != NULL && pTargetNode->m_pRightChild != NULL)		//중위선행자와 중위후속자 둘 다 있으면 그냥 중위후속자를 없애기로함
		{
			return ReplaceWithInorderSuccessor(pTargetNode);
		}
		else if (pTargetNode->m_pLeftChild == NULL && pTargetNode->m_pRightChild != NULL)
		{
			return ReplaceWithInorderSuccessor(pTargetNode);
		}
		else if (pTargetNode->m_pLeftChild != NULL && pTargetNode->m_pRightChild == NULL)
		{
			return ReplaceWithInorderPredecessor(pTargetNode);
		}
		else
		{
			delete pTargetNode;
			pTargetNode = NULL;

			return true;
		}
	}

	bool ReplaceWithInorderPredecessor(NodeType*& pTargetNode)
	{
		NodeType* pPrevious = NULL;
		NodeType* pTraverse = pTargetNode->m_pLeftChild;
		while (pTraverse->m_pRightChild != NULL)
		{
			pPrevious = pTraverse;
			pTraverse = pTraverse->m_pRightChild;
		}

		if (pPrevious != NULL)
		{
			pPrevious->m_pRightChild = pTraverse->m_pLeftChild;
		}
		else
		{
			pTargetNode->m_pLeftChild = pTraverse->m_pLeftChild;
		}

		pTargetNode->m_key = pTraverse->m_key;
		pTargetNode->m_data = pTraverse->m_data;
		delete pTraverse;

		return true;
	}

	bool ReplaceWithInorderSuccessor(NodeType*& pTargetNode)
	{
		NodeType* pPrevious = NULL;
		NodeType* pTraverse = pTargetNode->m_pRightChild;
		while (pTraverse->m_pLeftChild != NULL)
		{
			pPrevious = pTraverse;
			pTraverse = pTraverse->m_pLeftChild;
		}

		if (pPrevious != NULL)
		{
			pPrevious->m_pLeftChild = pTraverse->m_pRightChild;
		}
		else
		{
			pTargetNode->m_pRightChild = pTraverse->m_pRightChild;
		}

		pTargetNode->m_key = pTraverse->m_key;
		pTargetNode->m_data = pTraverse->m_data;
		delete pTraverse;

		return true;
	}

protected:
	//"pToDoWhileTraverse" 함수 포인터는 전위순회로 돌면서 각 노드에 수행할 작업을 위한 인터페이스임
	//"optional_target_BST" BST 포인터는 앞선 "to_do_while_traverse" 작업에서 대상 BST 포인터가 필요한 경우를 위한 인수임.
	void PreorderTraverse(void (BST_Template::* pToDoWhileTraverse)(NodeType*, BST_Template<NodeType>*), BST_Template<NodeType>* pOptionalTargetTreeParameter)
	{
		if (m_pHead == NULL) return;

		Stack<NodeType*> DepthFirstSearchStack;
		NodeType* pTraverse = NULL;
		DepthFirstSearchStack.Push(this->m_pHead);
		while (DepthFirstSearchStack.Pop(pTraverse) == true)
		{
			(this->*pToDoWhileTraverse)(pTraverse, pOptionalTargetTreeParameter);

			if (pTraverse->m_pRightChild != NULL) DepthFirstSearchStack.Push(pTraverse->m_pRightChild);
			if (pTraverse->m_pLeftChild != NULL) DepthFirstSearchStack.Push(pTraverse->m_pLeftChild);
		}
	}

	template<typename OptionalType>
	void InorderTraverse(void (BST_Template::* pToDoWhileTraverse)(NodeType*, BST_Template<NodeType>*), BST_Template<NodeType>* pOptionalTargetTreeParameter)
	{
		if (m_pHead == NULL) return;

		Stack<NodeType*> DepthFirstSearchStack;
		DepthFirstSearchStack.Push(m_pHead);
		bool newLeftSpine = true;
		while (!DepthFirstSearchStack.IsEmpty())
		{
			NodeType* headNode = DepthFirstSearchStack.GetTop();

			while (newLeftSpine && headNode->m_pLeftChild)
			{
				DepthFirstSearchStack.Push(headNode->m_pLeftChild);
			}

			NodeType* pTraverse = NULL;
			DepthFirstSearchStack.Pop(pTraverse);
			(this->*pToDoWhileTraverse)(pTraverse, pOptionalTargetTreeParameter);

			if (pTraverse->m_pRightChild != NULL)
			{
				DepthFirstSearchStack.Push(pTraverse->m_pRightChild);
				newLeftSpine = true;
			}
			else
			{
				newLeftSpine = false;
			}
		}
	}

	void PostorderTraverse(void (BST_Template::* pToDoWhileTraverse)(NodeType*, BST_Template<NodeType>*), BST_Template<NodeType>* pOptionalTargetTreeParameter)
	{
		if (m_pHead == NULL) return;

		Stack<NodeType*> DepthFirstSearchStack;
		DepthFirstSearchStack.Push(m_pHead);
		bool newLeftSpine = true;
		bool newRightSpine = true;
		while (!DepthFirstSearchStack.IsEmpty())
		{
			NodeType* headNode = NULL;
			DepthFirstSearchStack.GetTop(headNode);

			while (newLeftSpine && headNode->m_pLeftChild)
			{
				DepthFirstSearchStack.GetTop(headNode);
				DepthFirstSearchStack.Push(headNode->m_pLeftChild);
			}

			if (newRightSpine && headNode->m_pRightChild)
			{
				DepthFirstSearchStack.Push(headNode->m_pRightChild);
				newLeftSpine = true;
			}
			else
			{
				(this->*pToDoWhileTraverse)(headNode, pOptionalTargetTreeParameter);

				newLeftSpine = false;
				NodeType* pPrevNode = NULL;
				DepthFirstSearchStack.Pop(pPrevNode);
				NodeType* pCurrNode = NULL;
				DepthFirstSearchStack.GetTop(pCurrNode);

				if (pCurrNode && pCurrNode->m_pRightChild && (pCurrNode->m_pRightChild == pPrevNode)) newRightSpine = false;
				else newRightSpine = true;
			}
		}
	}

	void RemoveTwoChilds(NodeType* pTargetNode, BST_Template<NodeType>* nullParameter)
	{
		if (pTargetNode->m_pLeftChild != NULL)
		{
			delete pTargetNode->m_pLeftChild;
			pTargetNode->m_pLeftChild = NULL;
		}
		if (pTargetNode->m_pRightChild != NULL)
		{
			delete pTargetNode->m_pRightChild;
			pTargetNode->m_pRightChild = NULL;
		}
	}

	void CopyNode(NodeType* pSourceNode, BST_Template<NodeType>* pDestTree)
	{
		NodeType* pInsertedNode = NULL;
		
		bool ret = pDestTree->Search(pSourceNode->m_key, pInsertedNode, &BST_Template::SetDummyChild);

		*pInsertedNode = *pSourceNode;
	}

	void PrintTargetNode(NodeType* pTargetNode, BST_Template<NodeType>* nullParameter)
	{
		cout << "node m_key : " << pTargetNode->m_key << " / node m_data : " << pTargetNode->m_data << endl;
	}

protected:
	NodeType* m_pHead;
};

#endif //BST_USING_WHILE_TEMPLATE_H
