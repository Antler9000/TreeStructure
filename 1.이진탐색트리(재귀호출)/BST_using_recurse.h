#ifndef BST_USING_RECURSE_H
#define BST_USING_RECURSE_H

#include "../0.공통/debug.h"		//정의한 디버그 출력 매크로를 사용함
#include <iostream>					//콘솔 출력을 사용함
#include <utility>					//이동 시맨틱을 사용함
using namespace std;				//..

template <typename DataType>
class BST;

template <typename DataType>
class BST_Node
{
	friend class BST<DataType>;

private:
	BST_Node(const int newKey, const DataType& newData)
		: m_key(newKey), m_data(newData), m_pLeftChild(NULL), m_pRightChild(NULL)
	{

	}

	BST_Node(const int newKey, DataType&& newData)
		: m_key(newKey), m_data(move(newData)), m_pLeftChild(NULL), m_pRightChild(NULL)
	{

	}

	~BST_Node() noexcept
	{
		delete m_pLeftChild;
		delete m_pRightChild;
	}

	//쓰이지 않는 노드 생성 방식
	BST_Node() = delete;

	BST_Node(const BST_Node& sourceNode) = delete;
	
	BST_Node(BST_Node&& sourceNode) = delete;

	BST_Node& operator = (const BST_Node& sourceNode) = delete;

	BST_Node& operator = (BST_Node&& sourceNode) = delete;

private:
	int	m_key;
	DataType m_data;
	BST_Node<DataType>* m_pLeftChild;
	BST_Node<DataType>* m_pRightChild;
};

template <typename DataType>
class BST
{
public:
	BST() : m_pHead(NULL)
	{
		LogPrint("empty constructor");
	}

	BST(const BST<DataType>& sourceBST)
	{
		LogPrint("copy constructor");

		CopyTree(sourceBST);
	}

	BST(BST<DataType>&& sourceBST) noexcept
	{
		LogPrint("move constructor");

		m_pHead = sourceBST.m_pHead;
		sourceBST.m_pHead = NULL;
	}

	BST<DataType>& operator = (const BST<DataType>& sourceBST)
	{
		LogPrint("copy assignment");

		CopyTree(sourceBST);

		return *this;
	}

	BST<DataType>& operator = (BST<DataType>&& sourceBST) noexcept
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

	~BST() noexcept
	{
		LogPrint("destructor");

		RemoveTree();
	}

	bool Insert(const int newKey, const DataType& newData)
	{
		LogPrint("insert");

		if (m_pHead == NULL)
		{
			m_pHead = new BST_Node<DataType>(newKey, newData);

			return true;
		}
		else
		{
			return InsertRecurse(m_pHead, newKey, newData);
		}
	}

	bool Insert(const int newKey, DataType&& newData)
	{
		LogPrint("insert");

		if (m_pHead == NULL)
		{
			m_pHead = new BST_Node<DataType>(newKey, move(newData));

			return true;
		}
		else
		{
			return InsertRecurse(m_pHead, newKey, move(newData));
		}
	}

	bool Retrieve(const int retrieveTargetKey, DataType& outData) const
	{
		LogPrint("retrieve");

		if (m_pHead == NULL)
		{
			WarningPrint("cannot retrieve. because tree is empty.");

			return false;
		}

		return RetrieveRecurse(m_pHead, retrieveTargetKey, outData);
	}

	bool Remove(const int removeTargetKey)
	{
		LogPrint("remove one item");

		if (m_pHead == NULL)
		{
			WarningPrint("cannot remove. because tree is empty.");

			return false;
		}
		
		if (m_pHead->m_key == removeTargetKey)
		{
			return RemoveTarget(m_pHead);
		}
		else
		{
			return RemoveRecurse(m_pHead, removeTargetKey);
		}
	}

	bool RemoveTree() noexcept
	{
		LogPrint("remove tree");

		if (m_pHead != NULL)
		{
			delete m_pHead;
			m_pHead = NULL;
		}

		return true;
	}

	//트리의 값전달로 인해 복사생성자가 실행되는 것을 막기 위해 레퍼런스 인자를 사용함.
	//복사 생성자가 호출되는 것은 성능에도 안 좋으나, 무엇보다 복사 생성자가 CopyTree(..)를 이용해 구현되어있으므로, CopyTree가 복사 생성자를 이용하면 순환 오류가 난다.
	bool CopyTree(const BST<DataType>& sourceBST)
	{
		LogPrint("copy tree");

		if (sourceBST.m_pHead == NULL)
		{
			WarningPrint("cannot coping. becuase source tree is empty.");

			return false;
		}

		RemoveTree();
		
		return CopyTreeRecurse(sourceBST.m_pHead);
	}

	void PreorderPrint() const
	{
		LogPrint("preorder print");

		if (m_pHead == NULL)
		{
			WarningPrint("cannot traverse print. becuase tree is empty.");

			return;
		}

		PreorderPrintRecurse(m_pHead);
	}

	void InorderPrint() const
	{
		LogPrint("inorder print");

		if (m_pHead == NULL)
		{
			WarningPrint("cannot traverse print. becuase tree is empty.");

			return;
		}

		InorderPrintRecurse(m_pHead);
	}

	void PostOrderPrint() const
	{
		LogPrint("postorder print");

		if (m_pHead == NULL)
		{
			WarningPrint("cannot traverse print. becuase tree is empty.");

			return;
		}

		PostOrderPrintRecurse(m_pHead);
	}

private:
	bool InsertRecurse(BST_Node<DataType>* pSearchTargetNode, const int newKey, const DataType& newData);

	bool InsertRecurse(BST_Node<DataType>* pSearchTargetNode, const int newKey, DataType&& newData);

	bool RetrieveRecurse(const BST_Node<DataType>* pSearchTargetNode, const int retrieiveTargetKey, DataType& outData) const;

	bool RemoveRecurse(BST_Node<DataType>* pSearchTargetNode, const int removeTargetKey);

	//부모가 가리키는 자식에 대한 정보를 NULL로 바꾸기 위해서 레퍼런스 인자를 사용함
	bool RemoveTarget(BST_Node<DataType>*& pRemoveTargetNode);

	bool ReplaceWithInorderPredecessor(BST_Node<DataType>* pRemoveTargetNode);

	bool ReplaceWithInorderSuccessor(BST_Node<DataType>* pRemoveTargetNode);

	bool CopyTreeRecurse(const BST_Node<DataType>* pSourceNode);

	void PreorderPrintRecurse(const BST_Node<DataType>* pTargetNode) const;

	void InorderPrintRecurse(const BST_Node<DataType>* pTargetNode) const;

	void PostOrderPrintRecurse(const BST_Node<DataType>* pTargetNode) const;

private:
	BST_Node<DataType>* m_pHead;
};

template <typename DataType>
bool BST<DataType>::InsertRecurse(BST_Node<DataType>* pSearchTargetNode, const int newKey, const DataType& newData)
{
	if (newKey < pSearchTargetNode->m_key)
	{
		if (pSearchTargetNode->m_pLeftChild == NULL)
		{
			pSearchTargetNode->m_pLeftChild = new BST_Node<DataType>(newKey, newData);

			return true;
		}
		else
		{
			return InsertRecurse(pSearchTargetNode->m_pLeftChild, newKey, newData);
		}
	}
	else if (pSearchTargetNode->m_key < newKey)
	{
		if (pSearchTargetNode->m_pRightChild == NULL)
		{
			pSearchTargetNode->m_pRightChild = new BST_Node<DataType>(newKey, newData);

			return true;
		}
		else
		{
			return InsertRecurse(pSearchTargetNode->m_pRightChild, newKey, newData);
		}
	}
	else
	{
		ErrorPrint("cannot insert because there is same key in tree already!");

		return false;
	}
}

template <typename DataType>
bool BST<DataType>::InsertRecurse(BST_Node<DataType>* pSearchTargetNode, const int newKey, DataType&& newData)
{
	if (newKey < pSearchTargetNode->m_key)
	{
		if (pSearchTargetNode->m_pLeftChild == NULL)
		{
			pSearchTargetNode->m_pLeftChild = new BST_Node<DataType>(newKey, move(newData));

			return true;
		}
		else
		{
			return InsertRecurse(pSearchTargetNode->m_pLeftChild, newKey, move(newData));
		}
	}
	else if (pSearchTargetNode->m_key < newKey)
	{
		if (pSearchTargetNode->m_pRightChild == NULL)
		{
			pSearchTargetNode->m_pRightChild = new BST_Node<DataType>(newKey, move(newData));

			return true;
		}
		else
		{
			return InsertRecurse(pSearchTargetNode->m_pRightChild, newKey, move(newData));
		}
	}
	else
	{
		ErrorPrint("cannot insert because there is same key in tree already!");

		return false;
	}
}

template <typename DataType>
bool BST<DataType>::RetrieveRecurse(const BST_Node<DataType>* pSearchTargetNode, const int retrieveTargetKey, DataType& outData) const
{
	if (retrieveTargetKey < pSearchTargetNode->m_key)
	{
		if (pSearchTargetNode->m_pLeftChild != NULL)
		{
			return RetrieveRecurse(pSearchTargetNode->m_pLeftChild, retrieveTargetKey, outData);
		}
		else
		{
			ErrorPrint("cannot retrieve because there is no same key in tree!");

			return false;
		}
	}
	else if (retrieveTargetKey > pSearchTargetNode->m_key)
	{
		if (pSearchTargetNode->m_pRightChild != NULL)
		{
			return RetrieveRecurse(pSearchTargetNode->m_pRightChild, retrieveTargetKey, outData);
		}
		else
		{
			ErrorPrint("cannot retrieve because there is no same key in tree!");

			return false;
		}
	}
	else
	{
		outData = pSearchTargetNode->m_data;

		return true;
	}
}

template <typename DataType>
bool BST<DataType>::RemoveRecurse(BST_Node<DataType>* pSearchTargetNode, const int removeTargetKey)
{
	if (removeTargetKey < pSearchTargetNode->m_key)
	{
		if (pSearchTargetNode->m_pLeftChild->m_key == removeTargetKey)
		{
			return RemoveTarget(pSearchTargetNode->m_pLeftChild);
		}
		else
		{
			return RemoveRecurse(pSearchTargetNode->m_pLeftChild, removeTargetKey);
		}
	}
	else if (removeTargetKey > pSearchTargetNode->m_key)
	{
		if (pSearchTargetNode->m_pRightChild->m_key == removeTargetKey)
		{
			return RemoveTarget(pSearchTargetNode->m_pRightChild);
		}
		else
		{
			return RemoveRecurse(pSearchTargetNode->m_pRightChild, removeTargetKey);
		}
	}
	else
	{
		ErrorPrint("should not reach here while removing! it should be removed on previous call.");

		return false;
	}

	ErrorPrint("cannot remove because there is no same key in tree!");

	return false;
}

template <typename DataType>
bool BST<DataType>::RemoveTarget(BST_Node<DataType>*& pRemoveTargetNode)
{
	//중위선행자와 중위후속자 둘 다 있으면 그냥 중위후속자를 없애기로함
	if (pRemoveTargetNode->m_pLeftChild != NULL && pRemoveTargetNode->m_pRightChild != NULL)
	{
		return ReplaceWithInorderSuccessor(pRemoveTargetNode);
	}
	else if (pRemoveTargetNode->m_pLeftChild == NULL && pRemoveTargetNode->m_pRightChild != NULL)
	{
		return ReplaceWithInorderSuccessor(pRemoveTargetNode);
	}
	else if (pRemoveTargetNode->m_pLeftChild != NULL && pRemoveTargetNode->m_pRightChild == NULL)
	{
		return ReplaceWithInorderPredecessor(pRemoveTargetNode);
	}
	else
	{
		delete pRemoveTargetNode;
		pRemoveTargetNode = NULL;

		return true;
	}
}

template <typename DataType>
bool BST<DataType>::ReplaceWithInorderPredecessor(BST_Node<DataType>* pRemoveTargetNode)
{
	BST_Node<DataType>* pPrevious = NULL;
	BST_Node<DataType>* pTraverse = pRemoveTargetNode->m_pLeftChild;
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
		pRemoveTargetNode->m_pLeftChild = pTraverse->m_pLeftChild;
		pTraverse->m_pLeftChild = NULL;
	}

	pRemoveTargetNode->m_key = pTraverse->m_key;
	pRemoveTargetNode->m_data = move(pTraverse->m_data);

	delete pTraverse;

	return true;
}

template <typename DataType>
bool BST<DataType>::ReplaceWithInorderSuccessor(BST_Node<DataType>* pRemoveTargetNode)
{
	BST_Node<DataType>* pPrevious = NULL;
	BST_Node<DataType>* pTraverse = pRemoveTargetNode->m_pRightChild;
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
		pRemoveTargetNode->m_pRightChild = pTraverse->m_pRightChild;
		pTraverse->m_pRightChild = NULL;
	}

	pRemoveTargetNode->m_key = pTraverse->m_key;
	pRemoveTargetNode->m_data = move(pTraverse->m_data);

	delete pTraverse;

	return true;
}

template <typename DataType>
bool BST<DataType>::CopyTreeRecurse(const BST_Node<DataType>* pSourceNode)
{
	bool result = Insert(pSourceNode->m_key, pSourceNode->m_data);
	if (pSourceNode->m_pLeftChild != NULL) result &= CopyTreeRecurse(pSourceNode->m_pLeftChild);
	if (pSourceNode->m_pRightChild != NULL) result &= CopyTreeRecurse(pSourceNode->m_pRightChild);

	return result;
}

template <typename DataType>
void BST<DataType>::PreorderPrintRecurse(const BST_Node<DataType>* pTargetNode) const
{
	cout << "node m_key : " << pTargetNode->m_key << " / node m_data : " << pTargetNode->m_data << endl;
	if (pTargetNode->m_pLeftChild != NULL) PreorderPrintRecurse(pTargetNode->m_pLeftChild);
	if (pTargetNode->m_pRightChild != NULL) PreorderPrintRecurse(pTargetNode->m_pRightChild);
}

template <typename DataType>
void BST<DataType>::InorderPrintRecurse(const BST_Node<DataType>* pTargetNode) const
{
	if (pTargetNode->m_pLeftChild != NULL) InorderPrintRecurse(pTargetNode->m_pLeftChild);
	cout << "node m_key : " << pTargetNode->m_key << " / node m_data : " << pTargetNode->m_data << endl;
	if (pTargetNode->m_pRightChild != NULL) InorderPrintRecurse(pTargetNode->m_pRightChild);
}

template <typename DataType>
void BST<DataType>::PostOrderPrintRecurse(const BST_Node<DataType>* pTargetNode) const
{
	if (pTargetNode->m_pLeftChild != NULL) PostOrderPrintRecurse(pTargetNode->m_pLeftChild);
	if (pTargetNode->m_pRightChild != NULL) PostOrderPrintRecurse(pTargetNode->m_pRightChild);
	cout << "node m_key : " << pTargetNode->m_key << " / node m_data : " << pTargetNode->m_data << endl;
}

#endif //BST_USING_RECURSE_H