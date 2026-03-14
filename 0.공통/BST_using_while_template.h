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

	BST_Template<NodeType>& operator = (const BST_Template<NodeType >& sourceBST)
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

	void Insert(int newKey, int newData)
	{
		LogPrint("insert");

		NodeType* pMadeChild = Search(newKey, &BST_Template::SetDummyChild);
		pMadeChild->m_key = newKey;
		pMadeChild->m_data = newData;
	}

	int Retrieve(int targetKey)
	{
		LogPrint("retrieve");

		return Search(targetKey, &BST_Template::GetT)->m_data;
	}

	void Remove(int targetKey)
	{
		LogPrint("remove one item");

		Search(targetKey, &BST_Template::RemoveTarget);
	}


	void RemoveTree()
	{
		LogPrint("remove tree");

		PostorderTraverse(&BST_Template::RemoveChilds, NULL);
		delete m_pHead;
		m_pHead = NULL;
	}

	//트리의 값전달로 인해 복사생성자가 실행되는 것을 막기 위해 레퍼런스 인자를 사용함.
	//복사 생성자가 호출되는 것은 성능에도 안 좋으나, 무엇보다 복사 생성자가 CopyTree(..)를 이용해 구현되어있으므로, CopyTree가 복사 생성자를 이용하면 순환 오류가 난다.
	void CopyTree(const BST_Template& sourceBST)
	{
		LogPrint("copy tree");

		sourceBST.PreorderTraverse(&BST_Template::CopyNode, this);
	}

	void PreorderPrint()
	{
		LogPrint("preorder print");

		PreorderTraverse(&BST_Template::PrintTargetNode, NULL);
	}

	void InorderPrint()
	{
		LogPrint("inorder print");

		InorderTraverse(&BST_Template::PrintTargetNode, NULL);
	}

	void PostorderPrint()
	{
		LogPrint("postorder print");

		PostorderTraverse(&BST_Template::PrintTargetNode, NULL);
	}

protected:
	//"to_do_with_target_ptr" 메소드 포인터는 특정 target_key를 가진 노드를 가리키는 자식 포인터에 수행할 작업이나,
	//특정 target_key 노드가 삽입될 수 있는 NULL 자식 포인터에 수행할 작업을 넘겨주는 인터페이스임.
	//응용되는 삽입-검색-삭제에서는 부모가 자식을 가리키는 포인터 변수를 직접 수정할 수 있어야 하기에, 메소드 포인터는 레퍼런스 인자를 가짐
	NodeType* Search(int targetKey, NodeType* (BST_Template::* pToDoWithTargetPtr)(NodeType*&))
	{
		if (m_pHead == NULL) return (this->*pToDoWithTargetPtr)(m_pHead);
		else if (targetKey == m_pHead->m_key) return (this->*pToDoWithTargetPtr)(m_pHead);

		NodeType* pSearch = m_pHead;
		while (true)
		{
			if (targetKey < pSearch->m_key)
			{
				if (pSearch->m_pLeftChild != NULL && pSearch->m_pLeftChild->m_key != targetKey) pSearch = pSearch->m_pLeftChild;
				else return (this->*pToDoWithTargetPtr)(pSearch->m_pLeftChild);
			}
			else
			{
				if (pSearch->m_pRightChild != NULL && pSearch->m_pRightChild->m_key != targetKey) pSearch = pSearch->m_pRightChild;
				else return (this->*pToDoWithTargetPtr)(pSearch->m_pRightChild);
			}
		}
	}

	NodeType* GetT(NodeType*& pParentSeat)
	{
		return pParentSeat;
	}

	NodeType* SetDummyChild(NodeType*& pParentSeat)
	{
		return pParentSeat = new NodeType(0, 0);
	}

	NodeType* RemoveTarget(NodeType*& pTarget)
	{
		if (pTarget->m_pLeftChild != NULL && pTarget->m_pRightChild != NULL)	//두 자식 모두 있는 경우엔, 중위선행자와 중위후속자 중에서 그냥 중위후속자(오른쪽 자식 트리에서 제일 작은 키 값의 노드)를 없애기로함
		{
			ReplaceWithInorderSuccessor(pTarget);

			return NULL;
		}
		else if (pTarget->m_pLeftChild == NULL && pTarget->m_pRightChild != NULL)
		{
			ReplaceWithInorderSuccessor(pTarget);

			return NULL;
		}
		else if (pTarget->m_pLeftChild != NULL && pTarget->m_pRightChild == NULL)
		{
			ReplaceWithInorderPredecessor(pTarget);

			return NULL;
		}
		else
		{
			delete pTarget;
			pTarget = NULL;

			return NULL;
		}
	}

	void ReplaceWithInorderPredecessor(NodeType*& pTarget)
	{
		NodeType* pPrevious = NULL;
		NodeType* pTraverse = pTarget->m_pLeftChild;
		while (pTraverse->m_pRightChild != NULL)
		{
			pPrevious = pTraverse;
			pTraverse = pTraverse->m_pRightChild;
		}

		if (pPrevious != NULL) pPrevious->m_pRightChild = pTraverse->m_pLeftChild;
		else pTarget->m_pLeftChild = pTraverse->m_pLeftChild;

		pTarget->m_key = pTraverse->m_key;
		pTarget->m_data = pTraverse->m_data;
		delete pTraverse;
	}

	void ReplaceWithInorderSuccessor(NodeType*& pTarget)
	{
		NodeType* pPrevious = NULL;
		NodeType* pTraverse = pTarget->m_pRightChild;
		while (pTraverse->m_pLeftChild != NULL)
		{
			pPrevious = pTraverse;
			pTraverse = pTraverse->m_pLeftChild;
		}

		if (pPrevious != NULL) pPrevious->m_pLeftChild = pTraverse->m_pRightChild;
		else pTarget->m_pRightChild = pTraverse->m_pRightChild;

		pTarget->m_key = pTraverse->m_key;
		pTarget->m_data = pTraverse->m_data;
		delete pTraverse;
	}

protected:
	//"to_do_while_traverse" 함수 포인터는 전위순회로 돌면서 각 노드에 수행할 작업을 위한 인터페이스임
	//"optional_target_BST" BST 포인터는 앞선 "to_do_while_traverse" 작업에서 대상 BST 포인터가 필요한 경우를 위한 인수임.
	void PreorderTraverse(void (*pToDoWhileTraverse)(NodeType*, BST_Template*), BST_Template* pOptionalTargetBST) const
	{
		if (m_pHead == NULL) return;

		Stack<NodeType*> headStack;
		NodeType* pTraverse = NULL;
		headStack.Push(this->m_pHead);
		while (headStack.Pop(pTraverse) == true)
		{
			(*pToDoWhileTraverse)(pTraverse, pOptionalTargetBST);

			if (pTraverse->m_pRightChild != NULL) headStack.Push(pTraverse->m_pRightChild);
			if (pTraverse->m_pLeftChild != NULL) headStack.Push(pTraverse->m_pLeftChild);
		}
	}

	void InorderTraverse(void (*pToDoWhileTraverse)(NodeType*, BST_Template*), BST_Template* pOptionalTargetBST)
	{
		if (m_pHead == NULL) return;

		Stack<NodeType*> headStack;
		headStack.Push(m_pHead);
		bool newLeftSpine = true;
		while (!headStack.IsEmpty())
		{
			NodeType* headNode = headStack.GetTop();

			while (newLeftSpine && headNode->m_pLeftChild)
			{
				headStack.Push(headNode->m_pLeftChild);
			}

			NodeType* pTraverse = NULL;
			headStack.Pop(pTraverse);
			(*pToDoWhileTraverse)(pTraverse, pOptionalTargetBST);

			if (pTraverse->m_pRightChild != NULL)
			{
				headStack.Push(pTraverse->m_pRightChild);
				newLeftSpine = true;
			}
			else
			{
				newLeftSpine = false;
			}
		}
	}

	void PostorderTraverse(void (*pToDoWhileTraverse)(NodeType*, BST_Template*), BST_Template* pOptionalTargetBST)
	{
		if (m_pHead == NULL) return;

		Stack<NodeType*> headStack;
		headStack.Push(m_pHead);
		bool newLeftSpine = true;
		bool newRightSpine = true;
		while (!headStack.IsEmpty())
		{
			NodeType* headNode = NULL;
			headStack.GetTop(headNode);

			while (newLeftSpine && headNode->m_pLeftChild)
			{
				headStack.GetTop(headNode);
				headStack.Push(headNode->m_pLeftChild);
			}

			if (newRightSpine && headNode->m_pRightChild)
			{
				headStack.Push(headNode->m_pRightChild);
				newLeftSpine = true;
			}
			else
			{
				(*pToDoWhileTraverse)(headNode, pOptionalTargetBST);

				newLeftSpine = false;
				NodeType* pPrevNode = NULL;
				headStack.Pop(pPrevNode);
				NodeType* pCurrNode = NULL;
				headStack.GetTop(pCurrNode);

				if (pCurrNode && pCurrNode->m_pRightChild && (pCurrNode->m_pRightChild == pPrevNode)) newRightSpine = false;
				else newRightSpine = true;
			}
		}
	}

	static void PrintTargetNode(NodeType* pTargetNode, BST_Template* pDummyArgument)
	{
		cout << "node m_key : " << pTargetNode->m_key << " / node m_data : " << pTargetNode->m_data << endl;
	}

	static void RemoveChilds(NodeType* pTargetNode, BST_Template* pDummyArgument)
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

	static void CopyNode(NodeType* pSourceNode, BST_Template* pDestBST)
	{
		pDestBST->InsertNewNode(pSourceNode);
	}

	void InsertNewNode(NodeType* pNewNode)
	{
		NodeType* pMadeChild = Search(pNewNode->m_key, &BST_Template::SetDummyChild);
		*pMadeChild = *pNewNode;
	}

protected:
	NodeType* m_pHead;
};

#endif //BST_USING_WHILE_TEMPLATE_H
