#ifndef BST_USING_RECURSE_H
#define BST_USING_RECURSE_H

#ifdef TREE_LOG
#define LogPrint(statement) cout << "(Log : " << __func__ << ") " << statement << endl
#else
#define LogPrint(statement)
#endif

#ifdef TREE_ERROR
#define ErrorPrint(statement) cout << "(Error : " << __func__ << ") " << statement << endl
#else
#define ErrorPrint(statement)
#endif

#ifdef TREE_WARNING
#define WarningPrint(statement) cout << "(Warning : " << __func__ << ") " << statement << endl
#else
#define WarningPrint(statement)
#endif

#include <iostream>	//에러 출력 함수와 순회 출력 함수에서 cin, cout을 사용함
#include <string>		//에러 출력 함수의 매개변수 타입으로 string 타입을 사용함

using namespace std;

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

	~BST() noexcept
	{
		LogPrint("destructor");

		RemoveTree();
	}

	BST<DataType>& operator = (const BST<DataType>& sourceBST)
	{
		LogPrint("copy assignment");
		
		if (this == &sourceBST)
		{
			return *this;
		}

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

	bool Insert(const int newKey, const DataType newData)
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

	bool Retrieve(const int retrieveTargetKey, DataType& outData)
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

	void RemoveTree() noexcept
	{
		LogPrint("remove tree");

		if (m_pHead != NULL)
		{
			delete m_pHead;
			m_pHead = NULL;
		}
	}

	//트리의 값전달로 인한 복사가 일어나지 않도록 하기 위해서 레퍼런스 인자를 사용함
	bool CopyTree(const BST<DataType>& sourceBST)
	{
		LogPrint("copy tree");

		if (&sourceBST == NULL)
		{
			WarningPrint("cannot copying. becuase source tree is null.");
			return false;
		}

		if (sourceBST.m_pHead == NULL)
		{
			WarningPrint("cannot coping. becuase source tree is empty.");
			return false;
		}

		RemoveTree();
		
		return CopyTreeRecurse(sourceBST.m_pHead);
	}

	void PreorderPrint()
	{
		LogPrint("preorder print");

		if (m_pHead == NULL)
		{
			WarningPrint("cannot traverse print. becuase tree is empty.");
			return;
		}

		PreorderPrintRecurse(m_pHead);
	}

	void InorderPrint()
	{
		LogPrint("inorder print");

		if (m_pHead == NULL)
		{
			WarningPrint("cannot traverse print. becuase tree is empty.");
			return;
		}

		InorderPrintRecurse(m_pHead);
	}

	void PostOrderPrint()
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
	template <typename DataType>
	class BST_Node
	{
	private:
		friend class BST<DataType>;

		int	m_key;
		DataType	m_data;
		BST_Node<DataType>* m_pLeftChild;
		BST_Node<DataType>* m_pRightChild;

		BST_Node(const int newKey, const DataType newData)
			: m_key(newKey), m_data(newData), m_pLeftChild(NULL), m_pRightChild(NULL)
		{

		}

		~BST_Node() noexcept
		{
			delete m_pLeftChild;
			delete m_pRightChild;
		}
	};

	BST_Node<DataType>* m_pHead;

	bool InsertRecurse(BST_Node<DataType>* pSearchTargetNode, const int newKey, const DataType newData);

	bool RetrieveRecurse(const BST_Node<DataType>* pSearchTargetNode, const int retrieiveTargetKey, DataType& outData);

	bool RemoveRecurse(BST_Node<DataType>* pSearchTargetNode, const int removeTargetKey);

	//부모가 가리키는 자식에 대한 정보를 NULL로 바꾸기 위해서 레퍼런스 인자를 사용함
	bool RemoveTarget(BST_Node<DataType>*& pRemoveTargetNode);

	bool ReplaceWithInorderPredecessor(BST_Node<DataType>* pRemoveTargetNode);

	bool ReplaceWithInorderSuccessor(BST_Node<DataType>* pRemoveTargetNode);

	bool CopyTreeRecurse(const BST_Node<DataType>* pSourceNode);

	void PreorderPrintRecurse(const BST_Node<DataType>* pTargetNode);

	void InorderPrintRecurse(const BST_Node<DataType>* pTargetNode);

	void PostOrderPrintRecurse(const BST_Node<DataType>* pTargetNode);
};

template <typename DataType>
bool BST<DataType>::InsertRecurse(BST_Node<DataType>* pSearchTargetNode, const int newKey, const DataType newData)
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
bool BST<DataType>::RetrieveRecurse(const BST_Node<DataType>* pSearchTargetNode, const int retrieveTargetKey, DataType& outData)
{
	if (retrieveTargetKey < pSearchTargetNode->m_key)
	{
		if (pSearchTargetNode->m_pLeftChild != NULL)
		{
			return RetrieveRecurse(pSearchTargetNode->m_pLeftChild, retrieveTargetKey, outData);
		}
		else
		{
			ErrorPrint("there is no such key in searching.");
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
			ErrorPrint("there is no such key in searching.");
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
		ErrorPrint("should not reach here");

		return false;
	}
}
template <typename DataType>
bool BST<DataType>::RemoveTarget(BST_Node<DataType>*& pRemoveTargetNode)
{
	//두 자식 모두 있는 경우엔, 중위선행자와 중위후속자 중에서 그냥 중위후속자(오른쪽 자식 트리에서 제일 작은 키 값의 노드)를 없애기로함
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
void BST<DataType>::PreorderPrintRecurse(const BST_Node<DataType>* pTargetNode)
{
	cout << "node m_key : " << pTargetNode->m_key << " / node m_data : " << pTargetNode->m_data << endl;
	if (pTargetNode->m_pLeftChild != NULL) PreorderPrintRecurse(pTargetNode->m_pLeftChild);
	if (pTargetNode->m_pRightChild != NULL) PreorderPrintRecurse(pTargetNode->m_pRightChild);
}

template <typename DataType>
void BST<DataType>::InorderPrintRecurse(const BST_Node<DataType>* pTargetNode)
{
	if (pTargetNode->m_pLeftChild != NULL) InorderPrintRecurse(pTargetNode->m_pLeftChild);
	cout << "node m_key : " << pTargetNode->m_key << " / node m_data : " << pTargetNode->m_data << endl;
	if (pTargetNode->m_pRightChild != NULL) InorderPrintRecurse(pTargetNode->m_pRightChild);
}

template <typename DataType>
void BST<DataType>::PostOrderPrintRecurse(const BST_Node<DataType>* pTargetNode)
{
	if (pTargetNode->m_pLeftChild != NULL) PostOrderPrintRecurse(pTargetNode->m_pLeftChild);
	if (pTargetNode->m_pRightChild != NULL) PostOrderPrintRecurse(pTargetNode->m_pRightChild);
	cout << "node m_key : " << pTargetNode->m_key << " / node m_data : " << pTargetNode->m_data << endl;
}

#endif //BST_USING_RECURSE_H