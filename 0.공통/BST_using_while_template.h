#ifndef BST_USING_WHILE_TEMPLATE_H
#define BST_USING_WHILE_TEMPLATE_H

#include "../0.공통/debug_print.h"	//정의한 디버그 출력 매크로를 사용함
#include "../0.공통/stack.h"		//정의한 스택을 사용해, 재귀를 반복문으로 모방함
#include <iostream>					//콘솔 출력을 사용함
#include <memory>					//유니크 포인터를 사용함
#include <utility>					//이동 시맨틱을 사용함
using namespace std;				//..			

template <template <typename> class NodeType, typename DataType>
class BST_Template
{
public:

	BST_Template() : m_pHead(nullptr)
	{
		LogPrint("empty constructor");
	}

	BST_Template(const BST_Template<NodeType, DataType>& sourceBST)
	{
		LogPrint("copy constructor");

		CopyTree(sourceBST);
	}

	BST_Template(BST_Template<NodeType, DataType>&& sourceBST) noexcept
	{
		LogPrint("move constructor");

		m_pHead = sourceBST.m_pHead;
		sourceBST.m_pHead = nullptr;
	}

	BST_Template<NodeType, DataType>& operator = (const BST_Template<NodeType, DataType>& sourceBST)
	{
		LogPrint("copy assignment");

		if (this == &sourceBST)
		{
			return *this;
		}

		CopyTree(sourceBST);

		return *this;
	}

	BST_Template<NodeType, DataType>& operator = (BST_Template<NodeType, DataType>&& sourceBST) noexcept
	{
		LogPrint("move assignment");

		if (this == &sourceBST)
		{
			return *this;
		}

		RemoveTree();

		m_pHead = sourceBST.m_pHead;
		sourceBST.m_pHead = nullptr;

		return *this;
	}

	~BST_Template() noexcept
	{
		LogPrint("destructor");

		RemoveTree();
	}

	//newData가 lvalue 참조와 rvalue 참조인 경우를 각각 다르게 처리하기 위해서 참조 붕괴를 사용했음
	//bool 반환값이 false인 경우 : newKey와 같은 키의 노드가 이미 존재하는 경우 
	template <typename InsertDataType = DataType>
	bool Insert(const int newKey, InsertDataType&& newData)
	{
		LogPrint("insert");
		
		unique_ptr<NodeType<DataType>> upNewNode = make_unique<NodeType<DataType>>(newKey, forward<InsertDataType>(newData));
		return Search(newKey, &BST_Template::InsertNode, move(upNewNode));

	}

	//bool 반환값이 false인 경우 : targetKey와 같은 키를 가진 노드가 존재하지 않는 경우
	bool Retrieve(const int targetKey, DataType& outData) const
	{
		LogPrint("retrieve");

		return Search(targetKey, &BST_Template::RetrieveNode, outData);
	}

	//bool 반환값이 false인 경우 : targetKey와 같은 키를 가진 노드가 존재하지 않는 경우
	bool Remove(const int targetKey)
	{
		LogPrint("remove one item");

		return Search(targetKey, &BST_Template::RemoveNode, nullptr);
	}

	//트리의 소멸자와 이동 할당 연산자에 사용되므로 실패를 반환하거나 예외를 던지는 경우가 없도록 하였다
	void RemoveTree() noexcept
	{
		LogPrint("remove tree");

		RemovingTreeByRotationRR();
	}

	//트리의 값전달로 인해 복사생성자가 실행되는 것을 막기 위해 레퍼런스 인자를 사용함
	//복사 생성자가 호출되는 것은 성능에도 안 좋으나, 무엇보다 복사 생성자가 CopyTree(..)를 이용해 구현되어있으므로, CopyTree가 복사 생성자를 이용하면 순환 오류가 난다
	void CopyTree(const BST_Template& sourceBST)
	{
		LogPrint("copy tree");

		BST_Template<NodeType, DataType> tempTree;
		sourceBST.PreorderTraverse(&BST_Template::CopyNode, &tempTree);
		*this = move(tempTree);
	}

	void PreorderPrint() const
	{
		LogPrint("preorder print");

		PreorderTraverse(&BST_Template::PrintTargetNode, nullptr);
	}

	void InorderPrint() const
	{
		LogPrint("inorder print");

		InorderTraverse(&BST_Template::PrintTargetNode, nullptr);
	}

	void PostorderPrint() const
	{
		LogPrint("postorder print");

		PostorderTraverse(&BST_Template::PrintTargetNode, nullptr);
	}


protected:	//제너릭 메소드들

	//특정 target_key를 가진 노드의 위치에 대해 수행할 작업을 넘겨주는 제너릭 메소드임
	//상위 메소드와 하위 작업 메소드가 const 메소드인 경우를 지원하기 위한 const 버전의 제너릭 메소드 버전도 같이 있음
	//TODO : 컴파일 시점에 코드 치환이 확실히 일어나도록 제너릭 프로그래밍 방식을 개선하기
	//TODO : const 여부에 상관없는 하나의 제너릭 메소드로 통합할 수 있도록 제너럭 프로그래밍 방식을 개선하기
	template <typename MethodType, typename ArgumentType>
	bool Search(const int targetKey, MethodType&& method, ArgumentType&& argument)
	{
		if (m_pHead == nullptr)
		{
			return (this->*forward<MethodType>(method))(m_pHead, forward<ArgumentType>(argument));
		}
		else if (targetKey == m_pHead->m_key) 
		{
			return (this->*forward<MethodType>(method))(m_pHead, forward<ArgumentType>(argument));
		}
		else
		{
			NodeType<DataType>* pSearch = m_pHead;
			while (true)
			{
				if (targetKey < pSearch->m_key)
				{
					if (pSearch->m_pLeftChild == nullptr || pSearch->m_pLeftChild->m_key == targetKey)
					{
						return (this->*forward<MethodType>(method))(pSearch->m_pLeftChild, forward<ArgumentType>(argument));
					}
					else
					{
						pSearch = pSearch->m_pLeftChild;
					}
				}
				else
				{
					if (pSearch->m_pRightChild == nullptr || pSearch->m_pRightChild->m_key == targetKey)
					{
						return (this->*forward<MethodType>(method))(pSearch->m_pRightChild, forward<ArgumentType>(argument));
					}
					else
					{
						pSearch = pSearch->m_pRightChild;
					}
				}
			}
		}
	}

	template <typename MethodType, typename ArgumentType>
	bool Search(const int targetKey, MethodType&& method, ArgumentType&& argument) const
	{
		if (m_pHead == nullptr)
		{
			return (this->*forward<MethodType>(method))(m_pHead, forward<ArgumentType>(argument));
		}
		else if (targetKey == m_pHead->m_key)
		{
			return (this->*forward<MethodType>(method))(m_pHead, forward<ArgumentType>(argument));
		}
		else
		{
			NodeType<DataType>* pSearch = m_pHead;
			while (true)
			{
				if (targetKey < pSearch->m_key)
				{
					if (pSearch->m_pLeftChild == nullptr || pSearch->m_pLeftChild->m_key == targetKey)
					{
						return (this->*forward<MethodType>(method))(pSearch->m_pLeftChild, forward<ArgumentType>(argument));
					}
					else
					{
						pSearch = pSearch->m_pLeftChild;
					}
				}
				else
				{
					if (pSearch->m_pRightChild == nullptr || pSearch->m_pRightChild->m_key == targetKey)
					{
						return (this->*forward<MethodType>(method))(pSearch->m_pRightChild, forward<ArgumentType>(argument));
					}
					else
					{
						pSearch = pSearch->m_pRightChild;
					}
				}
			}
		}
	}

	//전위순회로 돌면서 각 노드에 수행할 작업을 수행하는 제너릭 메소드임
	//트리 복사의 소스 트리에서 실행되거나, 순회 출력 메소드에서만 사용되므로 const 메소드로 선언하였음
	//TODO : 컴파일 시점에 코드 치환이 확실히 일어날 수 있도록 제너릭 프로그래밍 방식을 개선하기
	template <typename MethodType, typename ArgumentType>
	void PreorderTraverse(MethodType&& method, ArgumentType&& argument) const
	{
		if (m_pHead == nullptr)
		{
			WarningPrint("cannot traverse. becuase tree is empty.");

			return;
		}

		NodeType<DataType>* pTraverse = nullptr;
		Stack<NodeType<DataType>*> rightChildStack;
		rightChildStack.Push(this->m_pHead);
		while (rightChildStack.Pop(pTraverse) == true)
		{
			while (pTraverse != nullptr)
			{
				(this->*forward<MethodType>(method))(pTraverse, forward<ArgumentType>(argument));

				if (pTraverse->m_pRightChild != nullptr)
				{
					rightChildStack.Push(pTraverse->m_pRightChild);
				}

				pTraverse = pTraverse->m_pLeftChild;
			}
		}
	}

	template <typename MethodType, typename ArgumentType>
	void InorderTraverse(MethodType&& method, ArgumentType&& argument) const
	{
		if (m_pHead == nullptr)
		{
			WarningPrint("cannot traverse. becuase tree is empty.");

			return;
		}

		NodeType<DataType>* pTraverse = m_pHead;
		Stack<NodeType<DataType>*> rightSideAncestorStack;
		while (pTraverse != nullptr)
		{
			rightSideAncestorStack.Push(pTraverse);
			pTraverse = pTraverse->m_pLeftChild;
		}
		while (rightSideAncestorStack.Pop(pTraverse) == true)
		{
			(this->*forward<MethodType>(method))(pTraverse, forward<ArgumentType>(argument));

			if (pTraverse->m_pRightChild != nullptr)
			{
				pTraverse = pTraverse->m_pRightChild;

				while (pTraverse != nullptr)
				{
					rightSideAncestorStack.Push(pTraverse);
					pTraverse = pTraverse->m_pLeftChild;
				}
			}
		}
	}

	template <typename MethodType, typename ArgumentType>
	void PostorderTraverse(MethodType&& method, ArgumentType&& argument) const
	{
		if (m_pHead == nullptr)
		{
			WarningPrint("cannot traverse. becuase tree is empty.");

			return;
		}

		struct Record
		{
			enum NodeJob
			{
				KEEP_SEARCH,
				DO_TODO
			};

			NodeJob nodeJob;
			NodeType<DataType>* pNode;
		};

		Record traverseRecord;
		Stack<Record> depthFirstSearchStack;
		depthFirstSearchStack.Push({ Record::KEEP_SEARCH , m_pHead });
		while (depthFirstSearchStack.Pop(traverseRecord) == true)
		{
			if (traverseRecord.nodeJob == Record::KEEP_SEARCH)
			{
				depthFirstSearchStack.Push({ Record::DO_TODO , traverseRecord.pNode });

				if (traverseRecord.pNode->m_pRightChild != nullptr)
				{
					depthFirstSearchStack.Push({ Record::KEEP_SEARCH, traverseRecord.pNode->m_pRightChild });
				}

				if (traverseRecord.pNode->m_pLeftChild != nullptr)
				{
					depthFirstSearchStack.Push({ Record::KEEP_SEARCH, traverseRecord.pNode->m_pLeftChild });
				}
			}
			else if(traverseRecord.nodeJob == Record::DO_TODO)
			{
				(this->*forward<MethodType>(method))(traverseRecord.pNode, forward<ArgumentType>(argument));
			}
		}

		return;
	}

protected:	//제너릭 메소드에 전달되는 하위 작업 메소드들

	bool InsertNode(NodeType<DataType>*& pInsertPosition, unique_ptr<NodeType<DataType>> upNewNode)
	{
		if (pInsertPosition != nullptr)
		{
			ErrorPrint("cannot insert because there is same key in tree already!");

			return false;
		}

		pInsertPosition = upNewNode.release();

		return true;
	}

	bool RetrieveNode(const NodeType<DataType>* pTargetNode, DataType& outData) const
	{
		if (pTargetNode == nullptr)
		{
			ErrorPrint("cannot retrieve because there is no same key in tree!");

			return false;
		}

		outData = pTargetNode->m_data;

		return true;
	}

	bool RemoveNode(NodeType<DataType>*& pTargetNode, void* pDummyParameter)
	{
		if (pTargetNode == nullptr)
		{
			ErrorPrint("cannot remove because there is no same key in tree!");

			return false;
		}

		//중위선행자와 중위후속자 둘 다 있는 경우에는 중위 선행자를 없애도록 함
		if (pTargetNode->m_pLeftChild != nullptr)
		{
			ReplaceWithInorderPredecessor(pTargetNode);
		}
		else if (pTargetNode->m_pRightChild != nullptr)
		{
			ReplaceWithInorderSuccessor(pTargetNode);
		}
		else
		{
			delete pTargetNode;
			pTargetNode = nullptr;
		}

		return true;
	}

	void ReplaceWithInorderPredecessor(NodeType<DataType>*& pTargetNode)
	{
		if (pTargetNode->m_pLeftChild->m_pRightChild == nullptr)
		{
			NodeType<DataType>* pInorderPredecessor = pTargetNode->m_pLeftChild;
			pInorderPredecessor->m_pRightChild = pTargetNode->m_pRightChild;
			delete pTargetNode;
			pTargetNode = pInorderPredecessor;
		}
		else
		{
			NodeType<DataType>* pPrevious = nullptr;
			NodeType<DataType>* pTraverse = pTargetNode->m_pLeftChild;
			while (pTraverse->m_pRightChild != nullptr)
			{
				pPrevious = pTraverse;
				pTraverse = pTraverse->m_pRightChild;
			}

			pPrevious->m_pRightChild = pTraverse->m_pLeftChild;
			pTraverse->m_pLeftChild = pTargetNode->m_pLeftChild;
			pTraverse->m_pRightChild = pTargetNode->m_pRightChild;

			delete pTargetNode;
			pTargetNode = pTraverse;
		}
	}

	void ReplaceWithInorderSuccessor(NodeType<DataType>*& pTargetNode)
	{
		if (pTargetNode->m_pRightChild->m_pLeftChild == nullptr)
		{
			NodeType<DataType>* pInorderSuccessor = pTargetNode->m_pRightChild;
			pInorderSuccessor->m_pLeftChild = pTargetNode->m_pLeftChild;
			delete pTargetNode;
			pTargetNode = pInorderSuccessor;
		}
		else
		{
			NodeType<DataType>* pPrevious = nullptr;
			NodeType<DataType>* pTraverse = pTargetNode->m_pRightChild;
			while (pTraverse->m_pLeftChild != nullptr)
			{
				pPrevious = pTraverse;
				pTraverse = pTraverse->m_pLeftChild;
			}

			pPrevious->m_pLeftChild = pTraverse->m_pRightChild;
			pTraverse->m_pRightChild = pTargetNode->m_pRightChild;
			pTraverse->m_pLeftChild = pTargetNode->m_pLeftChild;

			delete pTargetNode;
			pTargetNode = pTraverse;
		}
	}

	void CopyNode(const NodeType<DataType>* pSourceNode, BST_Template<NodeType, DataType>* pDestTree) const
	{
		unique_ptr<NodeType<DataType>> upCopiedNode = make_unique<NodeType<DataType>>(*pSourceNode);
		pDestTree->Search(pSourceNode->m_key, &BST_Template::InsertNode, move(upCopiedNode));
	}

	void PrintTargetNode(const NodeType<DataType>* pTargetNode, void* pDummyParameter) const
	{
		cout << "pNode m_key : " << pTargetNode->m_key << " / pNode m_data : " << pTargetNode->m_data << endl;
	}

protected:	//논 제너릭 하위 메소드

	//트리의 소멸자와 이동 할당 연산자의 하위 메소드로 사용되므로 실패를 반환하거나 예외를 던지는 경우가 없도록 하였다
	void RemovingTreeByRotationRR() noexcept
	{
		while (m_pHead != nullptr)
		{
			if (m_pHead->m_pRightChild != nullptr)
			{
				NodeType<DataType>* pNewHeadNode = m_pHead->m_pRightChild;
				m_pHead->m_pRightChild = m_pHead->m_pRightChild->m_pLeftChild;
				pNewHeadNode->m_pLeftChild = m_pHead;
				m_pHead = pNewHeadNode;

				continue;
			}

			NodeType<DataType>* pTrashNode = m_pHead;
			m_pHead = m_pHead->m_pLeftChild;
			delete pTrashNode;
		}
	}

protected:

	NodeType<DataType>* m_pHead;
};

#endif //BST_USING_WHILE_TEMPLATE_H
