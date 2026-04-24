#ifndef BST_USING_RECURSE_H
#define BST_USING_RECURSE_H

#include "../Common/Debug.h"		//정의한 디버그 출력 매크로를 사용함
#include <iostream>					//콘솔 출력을 사용함
#include <utility>					//이동 시맨틱을 사용함
using namespace std;				//..

template <typename DataType>
class Bst;

template <typename DataType>
class BstNode
{
	friend class Bst<DataType>;

private:
	BstNode(const int newKey, const DataType& newData)
		: m_key(newKey), m_data(newData), m_pLeftChild(NULL), m_pRightChild(NULL)
	{

	}

	BstNode(const int newKey, DataType&& newData)
		: m_key(newKey), m_data(move(newData)), m_pLeftChild(NULL), m_pRightChild(NULL)
	{

	}

	~BstNode() noexcept
	{
		delete m_pLeftChild;
		delete m_pRightChild;
	}

	//쓰이지 않는 노드 생성 방식
	BstNode() = delete;

	BstNode(const BstNode& sourceNode) = delete;
	
	BstNode(BstNode&& sourceNode) = delete;

	BstNode& operator = (const BstNode& sourceNode) = delete;

	BstNode& operator = (BstNode&& sourceNode) = delete;

private:
	int	m_key;
	DataType m_data;
	BstNode<DataType>* m_pLeftChild;
	BstNode<DataType>* m_pRightChild;
};

template <typename DataType>
class Bst
{
public:
	Bst() : m_pHead(NULL)
	{
		LogPrint("empty constructor");
	}

	Bst(const Bst<DataType>& sourceBST)
	{
		LogPrint("copy constructor");

		CopyTree(sourceBST);
	}

	Bst(Bst<DataType>&& sourceBST) noexcept
	{
		LogPrint("move constructor");

		m_pHead = sourceBST.m_pHead;
		sourceBST.m_pHead = NULL;
	}

	Bst<DataType>& operator = (const Bst<DataType>& sourceBST)
	{
		LogPrint("copy assignment");

		CopyTree(sourceBST);

		return *this;
	}

	Bst<DataType>& operator = (Bst<DataType>&& sourceBST) noexcept
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

	~Bst() noexcept
	{
		LogPrint("destructor");

		RemoveTree();
	}

	bool Insert(const int newKey, const DataType& newData)
	{
		LogPrint("insert");

		if (m_pHead == NULL)
		{
			m_pHead = new BstNode<DataType>(newKey, newData);

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
			m_pHead = new BstNode<DataType>(newKey, move(newData));

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
	bool CopyTree(const Bst<DataType>& sourceBST)
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
	bool InsertRecurse(BstNode<DataType>* pSearchTargetNode, const int newKey, const DataType& newData);

	bool InsertRecurse(BstNode<DataType>* pSearchTargetNode, const int newKey, DataType&& newData);

	bool RetrieveRecurse(const BstNode<DataType>* pSearchTargetNode, const int retrieiveTargetKey, DataType& outData) const;

	bool RemoveRecurse(BstNode<DataType>* pSearchTargetNode, const int removeTargetKey);

	//부모가 가리키는 자식에 대한 정보를 NULL로 바꾸기 위해서 레퍼런스 인자를 사용함
	bool RemoveTarget(BstNode<DataType>*& pRemoveTargetNode);

	bool ReplaceWithInorderPredecessor(BstNode<DataType>* pRemoveTargetNode);

	bool ReplaceWithInorderSuccessor(BstNode<DataType>* pRemoveTargetNode);

	bool CopyTreeRecurse(const BstNode<DataType>* pSourceNode);

	void PreorderPrintRecurse(const BstNode<DataType>* pTargetNode) const;

	void InorderPrintRecurse(const BstNode<DataType>* pTargetNode) const;

	void PostOrderPrintRecurse(const BstNode<DataType>* pTargetNode) const;

private:
	BstNode<DataType>* m_pHead;
};

template <typename DataType>
bool Bst<DataType>::InsertRecurse(BstNode<DataType>* pSearchTargetNode, const int newKey, const DataType& newData)
{
	if (newKey < pSearchTargetNode->m_key)
	{
		if (pSearchTargetNode->m_pLeftChild == NULL)
		{
			pSearchTargetNode->m_pLeftChild = new BstNode<DataType>(newKey, newData);

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
			pSearchTargetNode->m_pRightChild = new BstNode<DataType>(newKey, newData);

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
bool Bst<DataType>::InsertRecurse(BstNode<DataType>* pSearchTargetNode, const int newKey, DataType&& newData)
{
	if (newKey < pSearchTargetNode->m_key)
	{
		if (pSearchTargetNode->m_pLeftChild == NULL)
		{
			pSearchTargetNode->m_pLeftChild = new BstNode<DataType>(newKey, move(newData));

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
			pSearchTargetNode->m_pRightChild = new BstNode<DataType>(newKey, move(newData));

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
bool Bst<DataType>::RetrieveRecurse(const BstNode<DataType>* pSearchTargetNode, const int retrieveTargetKey, DataType& outData) const
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
bool Bst<DataType>::RemoveRecurse(BstNode<DataType>* pSearchTargetNode, const int removeTargetKey)
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
bool Bst<DataType>::RemoveTarget(BstNode<DataType>*& pRemoveTargetNode)
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
bool Bst<DataType>::ReplaceWithInorderPredecessor(BstNode<DataType>* pRemoveTargetNode)
{
	BstNode<DataType>* pPrevious = NULL;
	BstNode<DataType>* pTraverse = pRemoveTargetNode->m_pLeftChild;
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
bool Bst<DataType>::ReplaceWithInorderSuccessor(BstNode<DataType>* pRemoveTargetNode)
{
	BstNode<DataType>* pPrevious = NULL;
	BstNode<DataType>* pTraverse = pRemoveTargetNode->m_pRightChild;
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
bool Bst<DataType>::CopyTreeRecurse(const BstNode<DataType>* pSourceNode)
{
	bool result = Insert(pSourceNode->m_key, pSourceNode->m_data);
	if (pSourceNode->m_pLeftChild != NULL) result &= CopyTreeRecurse(pSourceNode->m_pLeftChild);
	if (pSourceNode->m_pRightChild != NULL) result &= CopyTreeRecurse(pSourceNode->m_pRightChild);

	return result;
}

template <typename DataType>
void Bst<DataType>::PreorderPrintRecurse(const BstNode<DataType>* pTargetNode) const
{
	cout << "node m_key : " << pTargetNode->m_key << " / node m_data : " << pTargetNode->m_data << endl;
	if (pTargetNode->m_pLeftChild != NULL) PreorderPrintRecurse(pTargetNode->m_pLeftChild);
	if (pTargetNode->m_pRightChild != NULL) PreorderPrintRecurse(pTargetNode->m_pRightChild);
}

template <typename DataType>
void Bst<DataType>::InorderPrintRecurse(const BstNode<DataType>* pTargetNode) const
{
	if (pTargetNode->m_pLeftChild != NULL) InorderPrintRecurse(pTargetNode->m_pLeftChild);
	cout << "node m_key : " << pTargetNode->m_key << " / node m_data : " << pTargetNode->m_data << endl;
	if (pTargetNode->m_pRightChild != NULL) InorderPrintRecurse(pTargetNode->m_pRightChild);
}

template <typename DataType>
void Bst<DataType>::PostOrderPrintRecurse(const BstNode<DataType>* pTargetNode) const
{
	if (pTargetNode->m_pLeftChild != NULL) PostOrderPrintRecurse(pTargetNode->m_pLeftChild);
	if (pTargetNode->m_pRightChild != NULL) PostOrderPrintRecurse(pTargetNode->m_pRightChild);
	cout << "node m_key : " << pTargetNode->m_key << " / node m_data : " << pTargetNode->m_data << endl;
}

#endif //BST_USING_RECURSE_H