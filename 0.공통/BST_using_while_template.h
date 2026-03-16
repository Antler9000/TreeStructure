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

public:
	bool Insert(int newKey,int newData)
	{
		LogPrint("insert");

		NodeType* pInsertedNode = NULL;
		bool ret = Search(newKey, pInsertedNode, &BST_Template::SetDummyChild);
		
		if (pInsertedNode != NULL)
		{
			pInsertedNode->m_key = newKey;
			pInsertedNode->m_data = newData;
		}

		return ret;
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
	//"pToDoWithTargetNode" 메소드 포인터는 특정 target_key를 가진 노드의 위치에 대해 수행할 작업을 넘겨주는 인터페이스임.
	//삽입과 삭제 메소드가 기능하려면 부모가 자식을 가리키는 포인터 변수를 직접 수정할 수 있어야 하기에, NodeType*&과 같이 레퍼런스 인자를 사용함.
	template <typename OutDataType>
	bool Search(int targetKey, OutDataType& outData, bool (BST_Template::* pToDoWithTargetNode)(NodeType*&, OutDataType&))
	{
		if (m_pHead == NULL)
		{
			return (this->*pToDoWithTargetNode)(m_pHead, outData);
		}
		else if (targetKey == m_pHead->m_key) 
		{
			return (this->*pToDoWithTargetNode)(m_pHead, outData);
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
						return (this->*pToDoWithTargetNode)(pSearch->m_pLeftChild, outData);
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
						return (this->*pToDoWithTargetNode)(pSearch->m_pRightChild, outData);
					}
				}
			}
		}
	}

	bool SetDummyChild(NodeType*& pParentSeat, NodeType*& pOutNode)
	{
		pOutNode = pParentSeat = new NodeType(0, 0);

		return true;
	}

	bool GetNodeData(NodeType*& pInNode, int& pOutNodeData)
	{
		pOutNodeData = pInNode->m_data;

		return true;
	}

	bool RemoveTarget(NodeType*& pTarget, char& dummyParmeter)
	{
		if (pTarget->m_pLeftChild != NULL && pTarget->m_pRightChild != NULL)		//중위선행자와 중위후속자 둘 다 있으면 그냥 중위후속자를 없애기로함
		{
			return ReplaceWithInorderSuccessor(pTarget);
		}
		else if (pTarget->m_pLeftChild == NULL && pTarget->m_pRightChild != NULL)
		{
			return ReplaceWithInorderSuccessor(pTarget);
		}
		else if (pTarget->m_pLeftChild != NULL && pTarget->m_pRightChild == NULL)
		{
			return ReplaceWithInorderPredecessor(pTarget);
		}
		else
		{
			delete pTarget;
			pTarget = NULL;

			return true;
		}
	}

	bool ReplaceWithInorderPredecessor(NodeType*& pTarget)
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

		return true;
	}

	bool ReplaceWithInorderSuccessor(NodeType*& pTarget)
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

		return true;
	}

protected:
	//"pToDoWhileTraverse" 함수 포인터는 전위순회로 돌면서 각 노드에 수행할 작업을 위한 인터페이스임
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
		NodeType* pInsertedNode = NULL;
		
		bool ret = pDestBST->Search(pSourceNode->m_key, pInsertedNode, &BST_Template::SetDummyChild);

		*pInsertedNode = *pSourceNode;
	}

	static void PrintTargetNode(NodeType* pTargetNode, BST_Template* pDummyArgument)
	{
		cout << "node m_key : " << pTargetNode->m_key << " / node m_data : " << pTargetNode->m_data << endl;
	}

protected:
	NodeType* m_pHead;
};

#endif //BST_USING_WHILE_TEMPLATE_H
