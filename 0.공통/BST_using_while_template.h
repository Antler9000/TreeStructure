#ifndef BST_USING_WHILE_TEMPLATE_H
#define BST_USING_WHILE_TEMPLATE_H

#include "../0.공통/debug_print.h"	//정의한 디버그 출력 매크로를 사용함
#include "../0.공통/stack.h"		//정의한 스택을 사용해, 재귀를 반복문으로 모방함
#include <iostream>					//콘솔 출력을 사용함
#include <memory>					//스마트 포인터를 사용함
#include <utility>					//이동 시맨틱을 사용함
using namespace std;				//..			

template <template <typename> class NodeType, typename DataType>
class BST_Template
{
public:
	BST_Template() : m_pHead(NULL)
	{
		LogPrint("empty constructor");
	}

	//TODO : sourceBST는 const여야 함 (함수 포인터 방식을 개선해야함)
	BST_Template(BST_Template<NodeType, DataType>& sourceBST)
	{
		LogPrint("copy constructor");

		CopyTree(sourceBST);
	}

	BST_Template(BST_Template<NodeType, DataType>&& sourceBST) noexcept
	{
		LogPrint("move constructor");

		m_pHead = sourceBST.m_pHead;
		sourceBST.m_pHead = NULL;
	}

	//TODO : sourceBST는 const여야 함 (함수 포인터 방식을 개선해야함)
	BST_Template<NodeType, DataType>& operator = (BST_Template<NodeType, DataType>& sourceBST)
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
		sourceBST.m_pHead = NULL;

		return *this;
	}

	~BST_Template() noexcept
	{
		LogPrint("destructor");

		RemoveTree();
	}

public:
	//TODO : newData는 const lvalue 참조, rvalue 참조 두가지 버전이 있어야 함 (함수 포인터 방식을 개선해야함)
	bool Insert(const int newKey, DataType newData)
	{
		LogPrint("insert");
		
		try
		{
			unique_ptr<NodeType<DataType>> upNewNode = make_unique<NodeType<DataType>>(newKey, newData);
			return Search(newKey, &BST_Template::InsertNode, move(upNewNode));
		}
		catch (bad_alloc e)
		{
			ErrorPrint("cannot insert because there is no space in heap!");
			return false;
		}
	}

	//TODO : const 메소드여야 함 (함수 포인터 방식을 개선해야함)
	bool Retrieve(const int targetKey, DataType& outData)
	{
		LogPrint("retrieve");

		return Search(targetKey, &BST_Template::RetrieveNode, (DataType*) &outData);
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

		try
		{
			return sourceBST.PreorderTraverse(&BST_Template::CopyNode, this);
		}
		catch (bad_alloc e)
		{
			ErrorPrint("cannot copytree because there is no space in heap!");
			return false;
		}
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
	//argument 인자를 move로 하위 작업 메소드로 넘겨주는 이유는, 삽입시 새로 삽입될 노드가 unique_ptr에 담겨(RAII 원칙 때문에) 삽입될 위치까지 이동하기 때문이다. 검색 메소드는 출력 매개변수의 포인터를 이용하고, 삭제 메소드는 이 매개변수에 더미만 넘겨주기에 move(..)로 넘겨줘도 문제는 발생하지 않는다
	template <typename ArgumentType>
	bool Search(const int targetKey, bool (BST_Template::* pToDoWithTargetNode)(NodeType<DataType>*&, ArgumentType), ArgumentType argument)
	{
		if (m_pHead == NULL)
		{
			return (this->*pToDoWithTargetNode)(m_pHead, move(argument));
		}
		else if (targetKey == m_pHead->m_key) 
		{
			return (this->*pToDoWithTargetNode)(m_pHead, move(argument));
		}
		else
		{
			NodeType<DataType>* pSearch = m_pHead;
			while (true)
			{
				if (targetKey < pSearch->m_key)
				{
					if (pSearch->m_pLeftChild == NULL || pSearch->m_pLeftChild->m_key == targetKey)
					{
						return (this->*pToDoWithTargetNode)(pSearch->m_pLeftChild, move(argument));
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
						return (this->*pToDoWithTargetNode)(pSearch->m_pRightChild, move(argument));
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
	bool InsertNode(NodeType<DataType>*& pInsertPosition, unique_ptr<NodeType<DataType>> upNewNode)
	{
		if (pInsertPosition != NULL)
		{
			ErrorPrint("cannot insert because there is same key in tree already!");

			return false;
		}

		pInsertPosition = upNewNode.release();

		return true;
	}
	
	//TODO : const 메소드여야 함 (함수 포인터 방식을 개선해야함)
	//TODO : pTargetNode는 const NodeType*&여야 함 (함수 포인터 방식을 개선해야함)
	bool RetrieveNode(NodeType<DataType>*& pTargetNode, DataType* outData)
	{
		if (pTargetNode == NULL)
		{
			ErrorPrint("cannot retrieve because there is no same key in tree!");

			return false;
		}

		*outData = pTargetNode->m_data;

		return true;
	}

	bool RemoveNode(NodeType<DataType>*& pTargetNode, void* pDummyParameter)
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

	bool ReplaceWithInorderPredecessor(NodeType<DataType>*& pTargetNode)
	{
		NodeType<DataType>* pPrevious = NULL;
		NodeType<DataType>* pTraverse = pTargetNode->m_pLeftChild;
		while (pTraverse->m_pRightChild != NULL)
		{
			pPrevious = pTraverse;
			pTraverse = pTraverse->m_pRightChild;
		}

		if (pPrevious != NULL)
		{
			pPrevious->m_pRightChild = pTraverse->m_pLeftChild;
			pTraverse->m_pLeftChild = NULL;
		}
		else
		{
			pTargetNode->m_pLeftChild = pTraverse->m_pLeftChild;
			pTraverse->m_pLeftChild = NULL;
		}

		pTraverse->m_pLeftChild = pTargetNode->m_pLeftChild;
		pTraverse->m_pRightChild = pTargetNode->m_pRightChild;

		NodeType<DataType>* pTrashedTargetNode = pTargetNode;
		pTargetNode = pTraverse;
		delete pTrashedTargetNode;

		return true;
	}

	bool ReplaceWithInorderSuccessor(NodeType<DataType>*& pTargetNode)
	{
		NodeType<DataType>* pPrevious = NULL;
		NodeType<DataType>* pTraverse = pTargetNode->m_pRightChild;
		while (pTraverse->m_pLeftChild != NULL)
		{
			pPrevious = pTraverse;
			pTraverse = pTraverse->m_pLeftChild;
		}

		if (pPrevious != NULL)
		{
			pPrevious->m_pLeftChild = pTraverse->m_pRightChild;
			pTraverse->m_pRightChild = NULL;
		}
		else
		{
			pTargetNode->m_pRightChild = pTraverse->m_pRightChild;
			pTraverse->m_pRightChild = NULL;
		}

		NodeType<DataType>* pTrashedTargetNode = pTargetNode;
		pTargetNode = pTraverse;
		delete pTrashedTargetNode;

		return true;
	}

protected:
	//TODO : 하위 작업 메소드가 const이거나 해당 메소드로 넘겨주는 인자가 const인 경우를 명시할 수 있도록 함수 포인터 방식을 개선해야 함
	// 
	//"pToDoWhileTraverse" 함수 포인터는 전위순회로 돌면서 각 노드에 수행할 작업을 위한 인터페이스임
	//포인터 매개변수를 이용하는 이유는, 노드나 트리가 구체적인 메소드로 전달될 때 복사가 일어나지 않도록 하며, 매개변수를 사용하지 않는 경우 NULL을 더미로 넘길 수 있도록 하기 위함이다
	bool PreorderTraverse(bool (BST_Template::* pToDoWhileTraverse)(NodeType<DataType>*, BST_Template<NodeType, DataType>*), BST_Template<NodeType, DataType>* pOptionalTargetTree)
	{
		if (m_pHead == NULL)
		{
			WarningPrint("cannot traverse. becuase tree is empty.");

			return false;
		}

		bool ret = true;

		NodeType<DataType>* pTraverse = NULL;
		Stack<NodeType<DataType>*> rightChildStack;
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

	bool InorderTraverse(bool (BST_Template::* pToDoWhileTraverse)(NodeType<DataType>*, BST_Template<NodeType, DataType>*), BST_Template<NodeType, DataType>* pOptionalTargetTree)
	{
		if (m_pHead == NULL)
		{
			WarningPrint("cannot traverse. becuase tree is empty.");

			return false;
		}

		bool ret = true;

		NodeType<DataType>* pTraverse = m_pHead;
		Stack<NodeType<DataType>*> rightSideAncestorStack;
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

	bool PostorderTraverse(bool (BST_Template::* pToDoWhileTraverse)(NodeType<DataType>*, BST_Template<NodeType, DataType>*), BST_Template<NodeType, DataType>* pOptionalTargetTree)
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

	bool RemoveTwoChilds(NodeType<DataType>* pTargetNode, BST_Template<NodeType, DataType>* pDummyParameter)
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
	bool CopyNode(NodeType<DataType>* pSourceNode, BST_Template<NodeType, DataType>* pDestTree)
	{
		unique_ptr<NodeType<DataType>> upCopiedNode = make_unique<NodeType<DataType>>(*pSourceNode);
		return pDestTree->Search(pSourceNode->m_key, &BST_Template::InsertNode, move(upCopiedNode));
	}

	//TODO : const 메소드여야 함 (함수 포인터 방식을 개선해야함)
	//TODO : pTargetNode는 const NodeType*여야 함 (함수 포인터 방식을 개선해야함)
	bool PrintTargetNode(NodeType<DataType>* pTargetNode, BST_Template<NodeType, DataType>* pDummyParameter)
	{
		cout << "pNode m_key : " << pTargetNode->m_key << " / pNode m_data : " << pTargetNode->m_data << endl;

		return true;
	}

protected:
	NodeType<DataType>* m_pHead;
};

#endif //BST_USING_WHILE_TEMPLATE_H
