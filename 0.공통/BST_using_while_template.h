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

	//TODO : sourceBST는 const여야 함 (함수 포인터 방식을 개선해야함)
	BST_Template(BST_Template<NodeType, DataType>& sourceBST)
	{
		LogPrint("copy constructor");

		BST_Template<NodeType, DataType> tempTree;
		bool ret = sourceBST.PreorderTraverse(&BST_Template::CopyNode, &tempTree);
		if (ret == true)
		{
			*this = move(tempTree);
		}
	}

	BST_Template(BST_Template<NodeType, DataType>&& sourceBST) noexcept
	{
		LogPrint("move constructor");

		m_pHead = sourceBST.m_pHead;
		sourceBST.m_pHead = nullptr;
	}

	//TODO : sourceBST는 const여야 함 (함수 포인터 방식을 개선해야함)
	BST_Template<NodeType, DataType>& operator = (BST_Template<NodeType, DataType>& sourceBST)
	{
		LogPrint("copy assignment");

		if (this == &sourceBST)
		{
			return *this;
		}

		BST_Template<NodeType, DataType> tempTree;
		bool ret = sourceBST.PreorderTraverse(&BST_Template::CopyNode, &tempTree);
		if (ret == true)
		{
			*this = move(tempTree);
		}

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
	//TODO : 그러나 랜덤 삽입 워크로드에서 이동 삽입이 복사 삽입과 시간 차이가 나지 않는 결과가 나왔으니 이를 검토해보기
	template <typename InsertDataType = DataType>
	bool Insert(const int newKey, InsertDataType&& newData)
	{
		LogPrint("insert");
		
		try
		{
			unique_ptr<NodeType<DataType>> upNewNode = make_unique<NodeType<DataType>>(newKey, forward<InsertDataType>(newData));
			return Search(newKey, &BST_Template::InsertNode, move(upNewNode));
		}
		catch (bad_alloc e)
		{
			ErrorPrint("cannot insert because there is no space in heap!");
			return false;
		}
		catch (exception e)
		{
			ErrorPrint("cannot insert because there is something error(but not heap shortage)!");
			return false;
		}
	}

	//TODO : const 메소드여야 함 (함수 포인터 방식을 개선해야함)
	bool Retrieve(const int targetKey, DataType& outData)
	{
		LogPrint("retrieve");

		return Search(targetKey, &BST_Template::RetrieveNode, outData);
	}

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

	//TODO : sourceBST는 const여야 함 (함수 포인터 방식을 개선해야함)
	//트리의 값전달로 인해 복사생성자가 실행되는 것을 막기 위해 레퍼런스 인자를 사용함
	//복사 생성자가 호출되는 것은 성능에도 안 좋으나, 무엇보다 복사 생성자가 CopyTree(..)를 이용해 구현되어있으므로, CopyTree가 복사 생성자를 이용하면 순환 오류가 난다
	bool CopyTree(BST_Template& sourceBST)
	{
		LogPrint("copy tree");

		try
		{
			BST_Template<NodeType, DataType> tempTree;
			bool ret = sourceBST.PreorderTraverse(&BST_Template::CopyNode, &tempTree);
			if (ret == true)
			{
				*this = move(tempTree);
			}

			return ret;
		}
		catch (bad_alloc e)
		{
			ErrorPrint("cannot copytree because there is no space in heap!");
			return false;
		}
		catch (exception e)
		{
			ErrorPrint("cannot copytree because there is something error(but not heap shortage)!");
			return false;
		}
	}

	//TODO : const 메소드여야 함 (함수 포인터 방식을 개선해야함)
	void PreorderPrint()
	{
		LogPrint("preorder print");

		PreorderTraverse(&BST_Template::PrintTargetNode, nullptr);
	}

	//TODO : const 메소드여야 함 (함수 포인터 방식을 개선해야함)
	void InorderPrint()
	{
		LogPrint("inorder print");

		InorderTraverse(&BST_Template::PrintTargetNode, nullptr);
	}

	//TODO : const 메소드여야 함 (함수 포인터 방식을 개선해야함)
	void PostorderPrint()
	{
		LogPrint("postorder print");

		PostorderTraverse(&BST_Template::PrintTargetNode, nullptr);
	}


protected:	//제너릭 메소드들
	//TODO : 상위 메소드와 하위 작업 메소드가 const 메소드인 경우가 가능하도록 수정해야 함
	//특정 target_key를 가진 노드의 위치에 대해 수행할 작업을 넘겨주는 제너릭 메소드임
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

	//TODO : 상위 메소드와 하위 작업 메소드가 const 메소드인 경우가 가능하도록 수정해야 함
	//전위순회로 돌면서 각 노드에 수행할 작업을 수행하는 제너릭 메소드임
	template <typename MethodType, typename ArgumentType>
	bool PreorderTraverse(MethodType&& method, ArgumentType&& argument)
	{
		if (m_pHead == nullptr)
		{
			WarningPrint("cannot traverse. becuase tree is empty.");

			return false;
		}

		bool ret = true;

		NodeType<DataType>* pTraverse = nullptr;
		Stack<NodeType<DataType>*> rightChildStack;
		rightChildStack.Push(this->m_pHead);
		while (rightChildStack.Pop(pTraverse) == true)
		{
			while (pTraverse != nullptr)
			{
				ret &= (this->*forward<MethodType>(method))(pTraverse, forward<ArgumentType>(argument));

				if (pTraverse->m_pRightChild != nullptr)
				{
					rightChildStack.Push(pTraverse->m_pRightChild);
				}

				pTraverse = pTraverse->m_pLeftChild;
			}
		}

		return ret;
	}

	template <typename MethodType, typename ArgumentType>
	bool InorderTraverse(MethodType&& method, ArgumentType&& argument)
	{
		if (m_pHead == nullptr)
		{
			WarningPrint("cannot traverse. becuase tree is empty.");

			return false;
		}

		bool ret = true;

		NodeType<DataType>* pTraverse = m_pHead;
		Stack<NodeType<DataType>*> rightSideAncestorStack;
		while (pTraverse != nullptr)
		{
			rightSideAncestorStack.Push(pTraverse);
			pTraverse = pTraverse->m_pLeftChild;
		}
		while (rightSideAncestorStack.Pop(pTraverse) == true)
		{
			ret &= (this->*forward<MethodType>(method))(pTraverse, forward<ArgumentType>(argument));

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

		return ret;
	}

	template <typename MethodType, typename ArgumentType>
	bool PostorderTraverse(MethodType&& method, ArgumentType&& argument)
	{
		if (m_pHead == nullptr)
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
				ret &= (this->*forward<MethodType>(method))(traverseRecord.pNode, forward<ArgumentType>(argument));
			}
		}

		return ret;
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

	//TODO : const 메소드여야 함 (함수 포인터 방식을 개선해야함)
	bool RetrieveNode(const NodeType<DataType>* pTargetNode, DataType& outData)
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

		//중위선행자와 중위후속자 둘 다 있으면 그냥 중위후속자를 없애기로함
		if (pTargetNode->m_pLeftChild != nullptr && pTargetNode->m_pRightChild != nullptr)
		{
			return ReplaceWithInorderSuccessor(pTargetNode);
		}
		else if (pTargetNode->m_pLeftChild == nullptr && pTargetNode->m_pRightChild != nullptr)
		{
			return ReplaceWithInorderSuccessor(pTargetNode);
		}
		else if (pTargetNode->m_pLeftChild != nullptr && pTargetNode->m_pRightChild == nullptr)
		{
			return ReplaceWithInorderPredecessor(pTargetNode);
		}
		else
		{
			delete pTargetNode;
			pTargetNode = nullptr;

			return true;
		}
	}

	bool ReplaceWithInorderPredecessor(NodeType<DataType>*& pTargetNode)
	{
		NodeType<DataType>* pPrevious = nullptr;
		NodeType<DataType>* pTraverse = pTargetNode->m_pLeftChild;
		while (pTraverse->m_pRightChild != nullptr)
		{
			pPrevious = pTraverse;
			pTraverse = pTraverse->m_pRightChild;
		}

		if (pPrevious != nullptr)
		{
			pPrevious->m_pRightChild = pTraverse->m_pLeftChild;
			pTraverse->m_pLeftChild = nullptr;
		}
		else
		{
			pTargetNode->m_pLeftChild = pTraverse->m_pLeftChild;
			pTraverse->m_pLeftChild = nullptr;
		}

		pTraverse->m_pLeftChild = pTargetNode->m_pLeftChild;
		pTraverse->m_pRightChild = pTargetNode->m_pRightChild;

		delete pTargetNode;
		pTargetNode = pTraverse;

		return true;
	}

	bool ReplaceWithInorderSuccessor(NodeType<DataType>*& pTargetNode)
	{
		NodeType<DataType>* pPrevious = nullptr;
		NodeType<DataType>* pTraverse = pTargetNode->m_pRightChild;
		while (pTraverse->m_pLeftChild != nullptr)
		{
			pPrevious = pTraverse;
			pTraverse = pTraverse->m_pLeftChild;
		}

		if (pPrevious != nullptr)
		{
			pPrevious->m_pLeftChild = pTraverse->m_pRightChild;
			pTraverse->m_pRightChild = nullptr;
		}
		else
		{
			pTargetNode->m_pRightChild = pTraverse->m_pRightChild;
			pTraverse->m_pRightChild = nullptr;
		}

		pTraverse->m_pLeftChild = pTargetNode->m_pLeftChild;
		pTraverse->m_pRightChild = pTargetNode->m_pRightChild;

		delete pTargetNode;
		pTargetNode = pTraverse;

		return true;
	}

	//TODO : const 메소드여야 함 (함수 포인터 방식을 개선해야함)
	bool CopyNode(const NodeType<DataType>* pSourceNode, BST_Template<NodeType, DataType>* pDestTree)
	{
		unique_ptr<NodeType<DataType>> upCopiedNode = make_unique<NodeType<DataType>>(*pSourceNode);
		return pDestTree->Search(pSourceNode->m_key, &BST_Template::InsertNode, move(upCopiedNode));
	}

	//TODO : const 메소드여야 함 (함수 포인터 방식을 개선해야함)
	bool PrintTargetNode(const NodeType<DataType>* pTargetNode, void* pDummyParameter)
	{
		cout << "pNode m_key : " << pTargetNode->m_key << " / pNode m_data : " << pTargetNode->m_data << endl;

		return true;
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
