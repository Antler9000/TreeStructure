#ifndef BST_USING_WHILE_TEMPLATE_H
#define BST_USING_WHILE_TEMPLATE_H

#include "../0.공통/debug_print.h"	//정의한 디버그 출력 매크로를 사용함
#include "../0.공통/stack.h"		//정의한 스택을 사용해, 재귀를 반복문으로 모방함
#include <iostream>					//콘솔 출력을 사용함
#include <utility>					//이동 시맨틱을 사용함
using namespace std;				//..			

template <class NodeType>
class BST_Template
{
public:
	BST_Template() : m_pHead(NULL)
	{
		LogPrint("empty constructor");
	}

	//TODO : sourceBST는 const여야 함 (함수 포인터 방식을 개선해야함)
	BST_Template(BST_Template<NodeType>& sourceBST)
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

	//TODO : sourceBST는 const여야 함 (함수 포인터 방식을 개선해야함)
	BST_Template<NodeType>& operator = (BST_Template<NodeType>& sourceBST)
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

	~BST_Template() noexcept
	{
		LogPrint("destructor");

		RemoveTree();
	}

public:
	bool Insert(const int newKey, const int newData)
	{
		LogPrint("insert");

		NodeType* pNewNode = new NodeType(newKey, newData);
		return Search(newKey, &BST_Template::InsertNode, pNewNode);
	}

	//TODO : const 메소드여야 함 (함수 포인터 방식을 개선해야함)
	bool Retrieve(const int targetKey, int& outData)
	{
		LogPrint("retrieve");

		return Search(targetKey, &BST_Template::RetrieveNode, &outData);
	}

	bool Remove(const int targetKey)
	{
		LogPrint("remove one item");

		return Search(targetKey, &BST_Template::RemoveNode, (void*)NULL);
	}

public:
	bool RemoveTree() noexcept
	{
		LogPrint("remove tree");

		bool ret = PostorderTraverse(&BST_Template::RemoveTwoChilds, NULL);
		delete m_pHead;
		m_pHead = NULL;

		return ret;
	}

	//TODO : sourceBST는 const여야 함 (함수 포인터 방식을 개선해야함)
	//
	//트리의 값전달로 인해 복사생성자가 실행되는 것을 막기 위해 레퍼런스 인자를 사용함
	//복사 생성자가 호출되는 것은 성능에도 안 좋으나, 무엇보다 복사 생성자가 CopyTree(..)를 이용해 구현되어있으므로, CopyTree가 복사 생성자를 이용하면 순환 오류가 난다
	bool CopyTree(BST_Template& sourceBST)
	{
		LogPrint("copy tree");

		return sourceBST.PreorderTraverse(&BST_Template::CopyNode, this);
	}

	//TODO : const 메소드여야 함 (함수 포인터 방식을 개선해야함)
	void PreorderPrint()
	{
		LogPrint("preorder print");

		PreorderTraverse(&BST_Template::PrintTargetNode, NULL);
	}

	//TODO : const 메소드여야 함 (함수 포인터 방식을 개선해야함)
	void InorderPrint()
	{
		LogPrint("inorder print");

		InorderTraverse(&BST_Template::PrintTargetNode, NULL);
	}

	//TODO : const 메소드여야 함 (함수 포인터 방식을 개선해야함)
	void PostorderPrint()
	{
		LogPrint("postorder print");

		PostorderTraverse(&BST_Template::PrintTargetNode, NULL);
	}

protected:
	//TODO : 하위 작업 메소드가 const이거나 해당 메소드로 넘겨주는 인자가 const인 경우를 명시할 수 있도록 함수 포인터 방식을 개선해야 함
	// 
	//"pToDoWithTargetNode" 메소드 포인터는 특정 target_key를 가진 노드의 위치에 대해 수행할 작업을 넘겨주는 인터페이스임
	//작업 메소드에 NodeType*&와 같이 레퍼런스 매개변수를 사용한 이유는, 삽입과 삭제 메소드에서 부모가 자식을 가리키는 포인터 변수를 직접 수정할 수 있도록 하기 위함이다
	//argument 매개변수를 ArgumentType*와 같이 포인터 매개변수로 둔 이유는, 검색 메소드에서는 출력용 매개변수를 사용할 수 있도록, 삽입 메소드에서는 노드 복사 전달이 일어나지 않도록, 삭제 메소드에서는 해당 매개변수를 사용하지 않음을 표시할 NULL을 사용할 수 있도록 하기 위함이다
	template <typename ArgumentType = void>
	bool Search(const int targetKey, bool (BST_Template::* pToDoWithTargetNode)(NodeType*&, ArgumentType*), ArgumentType* argument)
	{
		if (m_pHead == NULL)
		{
			return (this->*pToDoWithTargetNode)(m_pHead, argument);
		}
		else if (targetKey == m_pHead->m_key) 
		{
			return (this->*pToDoWithTargetNode)(m_pHead, argument);
		}
		else
		{
			NodeType* pSearch = m_pHead;
			while (true)
			{
				if (targetKey < pSearch->m_key)
				{
					if (pSearch->m_pLeftChild == NULL || pSearch->m_pLeftChild->m_key == targetKey)
					{
						return (this->*pToDoWithTargetNode)(pSearch->m_pLeftChild, argument);
					}
					else
					{
						pSearch = pSearch->m_pLeftChild;
					}
				}
				else
				{
					if (pSearch->m_pRightChild == NULL || pSearch->m_pRightChild->m_key == targetKey)
					{
						return (this->*pToDoWithTargetNode)(pSearch->m_pRightChild, argument);
					}
					else
					{
						pSearch = pSearch->m_pRightChild;
					}
				}
			}
		}
	}

	//TODO : pNewNode는 const NodeType*여야 함 (함수 포인터 방식을 개선해야함)
	bool InsertNode(NodeType*& pInsertPosition, NodeType* pNewNode)
	{
		if (pInsertPosition != NULL)
		{
			ErrorPrint("cannot insert because there is same key in tree already!");

			return false;
		}

		pInsertPosition = pNewNode;

		return true;
	}

	//TODO : const 메소드여야 함 (함수 포인터 방식을 개선해야함)
	//TODO : pTargetNode는 const NodeType*&여야 함 (함수 포인터 방식을 개선해야함)
	bool RetrieveNode(NodeType*& pTargetNode, int* outData)
	{
		if (pTargetNode == NULL)
		{
			ErrorPrint("cannot retrieve because there is no same key in tree!");

			return false;
		}

		*outData = pTargetNode->m_data;

		return true;
	}

	bool RemoveNode(NodeType*& pTargetNode, void* pDummyParameter)
	{
		if (pTargetNode == NULL)
		{
			ErrorPrint("cannot remove because there is no same key in tree!");

			return false;
		}

		//중위선행자와 중위후속자 둘 다 있으면 그냥 중위후속자를 없애기로함
		if (pTargetNode->m_pLeftChild != NULL && pTargetNode->m_pRightChild != NULL)
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
	//TODO : 하위 작업 메소드가 const이거나 해당 메소드로 넘겨주는 인자가 const인 경우를 명시할 수 있도록 함수 포인터 방식을 개선해야 함
	// 
	//"pToDoWhileTraverse" 함수 포인터는 전위순회로 돌면서 각 노드에 수행할 작업을 위한 인터페이스임
	//포인터 매개변수를 이용하는 이유는, 노드나 트리가 구체적인 메소드로 전달될 때 복사가 일어나지 않도록 하며, 매개변수를 사용하지 않는 경우 NULL을 더미로 넘길 수 있도록 하기 위함이다
	bool PreorderTraverse(bool (BST_Template::* pToDoWhileTraverse)(NodeType*, BST_Template<NodeType>*), BST_Template<NodeType>* pOptionalTargetTree)
	{
		if (m_pHead == NULL)
		{
			WarningPrint("cannot traverse. becuase tree is empty.");

			return false;
		}

		bool ret = true;

		NodeType* pTraverse = NULL;
		Stack<NodeType*> rightChildStack;
		rightChildStack.Push(this->m_pHead);
		while (rightChildStack.Pop(pTraverse) == true)
		{
			while (pTraverse != NULL)
			{
				ret &= (this->*pToDoWhileTraverse)(pTraverse, pOptionalTargetTree);

				if (pTraverse->m_pRightChild != NULL)
				{
					rightChildStack.Push(pTraverse->m_pRightChild);
				}

				pTraverse = pTraverse->m_pLeftChild;
			}
		}

		return ret;
	}

	bool InorderTraverse(bool (BST_Template::* pToDoWhileTraverse)(NodeType*, BST_Template<NodeType>*), BST_Template<NodeType>* pOptionalTargetTree)
	{
		if (m_pHead == NULL)
		{
			WarningPrint("cannot traverse. becuase tree is empty.");

			return false;
		}

		bool ret = true;

		NodeType* pTraverse = m_pHead;
		Stack<NodeType*> rightSideAncestorStack;	
		while (pTraverse != NULL)
		{
			rightSideAncestorStack.Push(pTraverse);
			pTraverse = pTraverse->m_pLeftChild;
		}
		while (rightSideAncestorStack.Pop(pTraverse) == true)
		{
			ret &= (this->*pToDoWhileTraverse)(pTraverse, pOptionalTargetTree);

			if (pTraverse->m_pRightChild != NULL)
			{
				pTraverse = pTraverse->m_pRightChild;

				while (pTraverse != NULL)
				{
					rightSideAncestorStack.Push(pTraverse);
					pTraverse = pTraverse->m_pLeftChild;
				}
			}
		}

		return ret;
	}

	bool PostorderTraverse(bool (BST_Template::* pToDoWhileTraverse)(NodeType*, BST_Template<NodeType>*), BST_Template<NodeType>* pOptionalTargetTree)
	{
		if (m_pHead == NULL)
		{
			WarningPrint("cannot traverse. becuase tree is empty.");

			return false;
		}

		bool ret = true;

		struct Record
		{
			enum NodeJob
			{
				KEEP_SEARCH,
				DO_TODO
			};

			NodeJob nodeJob;
			NodeType* pNode;
		};

		Record traverseRecord;
		Stack<Record> depthFirstSearchStack;
		depthFirstSearchStack.Push({ Record::KEEP_SEARCH , m_pHead });
		while (depthFirstSearchStack.Pop(traverseRecord) == true)
		{
			if (traverseRecord.nodeJob == Record::KEEP_SEARCH)
			{
				depthFirstSearchStack.Push({ Record::DO_TODO , traverseRecord.pNode });

				if (traverseRecord.pNode->m_pRightChild != NULL)
				{
					depthFirstSearchStack.Push({ Record::KEEP_SEARCH, traverseRecord.pNode->m_pRightChild });
				}

				if (traverseRecord.pNode->m_pLeftChild != NULL)
				{
					depthFirstSearchStack.Push({ Record::KEEP_SEARCH, traverseRecord.pNode->m_pLeftChild });
				}
			}
			else if(traverseRecord.nodeJob == Record::DO_TODO)
			{
				ret &= (this->*pToDoWhileTraverse)(traverseRecord.pNode, pOptionalTargetTree);
			}
		}

		return ret;
	}

	bool RemoveTwoChilds(NodeType* pTargetNode, BST_Template<NodeType>* pDummyParameter)
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

		return true;
	}

	//TODO : const 메소드여야 함 (함수 포인터 방식을 개선해야함)
	//TODO : pSourceNode는 const NodeType*여야 함 (함수 포인터 방식을 개선해야함)
	bool CopyNode(NodeType* pSourceNode, BST_Template<NodeType>* pDestTree)
	{
		NodeType* copiedNode = new NodeType(*pSourceNode);
		return pDestTree->Search(pSourceNode->m_key, &BST_Template::InsertNode, copiedNode);
	}

	//TODO : const 메소드여야 함 (함수 포인터 방식을 개선해야함)
	//TODO : pTargetNode는 const NodeType*여야 함 (함수 포인터 방식을 개선해야함)
	bool PrintTargetNode(NodeType* pTargetNode, BST_Template<NodeType>* pDummyParameter)
	{
		cout << "pNode m_key : " << pTargetNode->m_key << " / pNode m_data : " << pTargetNode->m_data << endl;

		return true;
	}

protected:
	NodeType* m_pHead;
};

#endif //BST_USING_WHILE_TEMPLATE_H
