#ifndef SplayTree_H
#define SplayTree_H

#include "../0.공통/BST_using_while_template.h"
#include "../0.공통/debug.h"

template <typename DataType>
class SplayNode;

template <typename DataType>
class SplayTree;

template <typename DataType>
class SplayNode
{
	friend class SplayTree<DataType>;
	friend class BST_Template<SplayNode, DataType>;

private:

	SplayNode(int newKey, DataType newData)
	{
		m_key = newKey;
		m_data = newData;
		m_pLeftChild = NULL;
		m_pRightChild = NULL;
	}

	SplayNode(const SplayNode& sourceNode)
	{
		m_data = sourceNode.m_data;
		m_key = sourceNode.m_key;
		m_pLeftChild = nullptr;
		m_pRightChild = nullptr;
	}

private:

	int m_key;
	DataType m_data;
	SplayNode<DataType>* m_pLeftChild;
	SplayNode<DataType>* m_pRightChild;
};

template <typename DataType>
class SplayTree : public BST_Template<SplayNode, DataType>
{
private:
	void SplayTarget(SplayNode<DataType>* pGreatGrandFatherOfTarget, SplayNode<DataType>* pGrandFatherOfTarget, SplayNode<DataType>* pFatherOfTarget, SplayNode<DataType>* pTarget);

	//ZIG의 경우에는 부모까지 변화가 일어나는 경우이므로, 부모를 가르키는 조부의 자식 포인터를 직접 수정할 수 있도록 레퍼런스 인자를 사용하였다.
	//ZIG_ZIG나 ZIG_ZAG와 같이 조부까지 변화가 일어나는 경우를 위해, 조부를 가리키는 증조부의 자식 포인터를 직접 수정할 수 있도록 레퍼런스 인자를 사용하였다.
	void L_Zig(SplayNode<DataType>*& pFatherOfTarget, SplayNode<DataType>* pTarget)
	{
		cout << "L_Zig" << endl;
		pFatherOfTarget->m_pLeftChild = pTarget->m_pRightChild;
		pTarget->m_pRightChild = pFatherOfTarget;
		pFatherOfTarget = pTarget;
	}

	void R_Zig(SplayNode<DataType>*& pFatherOfTarget, SplayNode<DataType>* pTarget)
	{
		cout << "R_Zig" << endl;
		pFatherOfTarget->m_pRightChild = pTarget->m_pLeftChild;
		pTarget->m_pLeftChild = pFatherOfTarget;
		pFatherOfTarget = pTarget;
	}

	void LL_ZigZig(SplayNode<DataType>*& pGrandFatherOfTarget, SplayNode<DataType>* pFatherOfTarget, SplayNode<DataType>* pTarget)
	{
		cout << "LL_ZigZig" << endl;
		pGrandFatherOfTarget->m_pLeftChild = pFatherOfTarget->m_pRightChild;
		pFatherOfTarget->m_pRightChild = pGrandFatherOfTarget;
		pGrandFatherOfTarget = pFatherOfTarget;

		pFatherOfTarget->m_pLeftChild = pTarget->m_pRightChild;
		pTarget->m_pRightChild = pFatherOfTarget;
		pGrandFatherOfTarget = pTarget;
	}

	void LR_ZigZag(SplayNode<DataType>*& pGrandFatherOfTarget, SplayNode<DataType>* pFatherOfTarget, SplayNode<DataType>* pTarget)
	{
		cout << "LR_ZigZag" << endl;
		cout << pGrandFatherOfTarget->m_key << " " << pFatherOfTarget->m_key << " " << pTarget->m_key << endl;
		pGrandFatherOfTarget->m_pLeftChild = pTarget;
		pFatherOfTarget->m_pRightChild = pTarget->m_pLeftChild;
		pTarget->m_pLeftChild = pFatherOfTarget;

		pGrandFatherOfTarget->m_pLeftChild = pTarget->m_pRightChild;
		pTarget->m_pRightChild = pGrandFatherOfTarget;
		pGrandFatherOfTarget = pTarget;
	}

	void RL_ZigZag(SplayNode<DataType>*& pGrandFatherOfTarget, SplayNode<DataType>* pFatherOfTarget, SplayNode<DataType>* pTarget)
	{
		cout << "RL_ZigZag" << endl;
		pGrandFatherOfTarget->m_pRightChild = pTarget;
		pFatherOfTarget->m_pLeftChild = pTarget->m_pRightChild;
		pTarget->m_pRightChild = pFatherOfTarget;

		pGrandFatherOfTarget->m_pRightChild = pTarget->m_pLeftChild;
		pTarget->m_pLeftChild = pGrandFatherOfTarget;
		pGrandFatherOfTarget = pTarget;
	}

	void RR_ZigZig(SplayNode<DataType>*& pGrandFatherOfTarget, SplayNode<DataType>* pFatherOfTarget, SplayNode<DataType>* pTarget)
	{
		cout << "RR_ZigZig" << endl;
		pGrandFatherOfTarget->m_pRightChild = pFatherOfTarget->m_pLeftChild;
		pFatherOfTarget->m_pLeftChild = pGrandFatherOfTarget;
		pGrandFatherOfTarget = pFatherOfTarget;

		pFatherOfTarget->m_pRightChild = pTarget->m_pLeftChild;
		pTarget->m_pLeftChild = pFatherOfTarget;
		pGrandFatherOfTarget = pTarget;
	}


public :
	SplayTree() : BST_Template<SplayNode, DataType>() {}

	DataType Retrieve(int targetKey);
};

template <typename DataType>
DataType SplayTree<DataType>::Retrieve(int targetKey)
{
	SplayNode<DataType>* pTraversePtr = this->m_pHead;
	SplayNode<DataType>* pFatherOfTraversePtr = NULL;
	SplayNode<DataType>* pGrandFatherOfTraversePtr = NULL;
	SplayNode<DataType>* pGreatGrandFatherOfTraversePtr = NULL;
	while (pTraversePtr != NULL)
	{
		if (targetKey < pTraversePtr->m_key)
		{
			pGreatGrandFatherOfTraversePtr = pGrandFatherOfTraversePtr;
			pGrandFatherOfTraversePtr = pFatherOfTraversePtr;
			pFatherOfTraversePtr = pTraversePtr;
			pTraversePtr = pTraversePtr->m_pLeftChild;
		}
		else if (pTraversePtr->m_key < targetKey)
		{
			pGreatGrandFatherOfTraversePtr = pGrandFatherOfTraversePtr;
			pGrandFatherOfTraversePtr = pFatherOfTraversePtr;
			pFatherOfTraversePtr = pTraversePtr;
			pTraversePtr = pTraversePtr->m_pRightChild;
		}
		else
		{
			SplayTarget(pGreatGrandFatherOfTraversePtr, pGrandFatherOfTraversePtr, pFatherOfTraversePtr, pTraversePtr);

			return pTraversePtr->m_data;
		}
	}
}

template <typename DataType>
void SplayTree<DataType>::SplayTarget(SplayNode<DataType>* pGreatGrandFatherOfTarget, SplayNode<DataType>* pGrandFatherOfTarget, SplayNode<DataType>* pFatherOfTarget, SplayNode<DataType>* pTarget)
{
	if (pGreatGrandFatherOfTarget != NULL)
	{
		if (pGreatGrandFatherOfTarget->m_pLeftChild == pGrandFatherOfTarget)
		{
			if (pGrandFatherOfTarget->m_pLeftChild == pFatherOfTarget)
			{
				if (pFatherOfTarget->m_pLeftChild == pTarget) LL_ZigZig(pGreatGrandFatherOfTarget->m_pLeftChild, pFatherOfTarget, pTarget);
				else LR_ZigZag(pGreatGrandFatherOfTarget->m_pLeftChild, pFatherOfTarget, pTarget);
			}
			else
			{
				if (pFatherOfTarget->m_pLeftChild == pTarget) RL_ZigZag(pGreatGrandFatherOfTarget->m_pLeftChild, pFatherOfTarget, pTarget);
				else RR_ZigZig(pGreatGrandFatherOfTarget->m_pLeftChild, pFatherOfTarget, pTarget);
			}
		}
		else
		{
			if (pGrandFatherOfTarget->m_pLeftChild == pFatherOfTarget)
			{
				if (pFatherOfTarget->m_pLeftChild == pTarget) LL_ZigZig(pGreatGrandFatherOfTarget->m_pRightChild, pFatherOfTarget, pTarget);
				else LR_ZigZag(pGreatGrandFatherOfTarget->m_pRightChild, pFatherOfTarget, pTarget);
			}
			else
			{
				if (pFatherOfTarget->m_pLeftChild == pTarget) RL_ZigZag(pGreatGrandFatherOfTarget->m_pRightChild, pFatherOfTarget, pTarget);
				else RR_ZigZig(pGreatGrandFatherOfTarget->m_pRightChild, pFatherOfTarget, pTarget);
			}
		}
	}
	else if (pGrandFatherOfTarget != NULL)
	{
		if (pGrandFatherOfTarget->m_pLeftChild == pFatherOfTarget)
		{
			if (pFatherOfTarget->m_pLeftChild == pTarget) LL_ZigZig(this->m_pHead, pFatherOfTarget, pTarget);
			else LR_ZigZag(this->m_pHead, pFatherOfTarget, pTarget);
		}
		else
		{
			if (pFatherOfTarget->m_pLeftChild == pTarget) RL_ZigZag(this->m_pHead, pFatherOfTarget, pTarget);
			else RR_ZigZig(this->m_pHead, pFatherOfTarget, pTarget);
		}
	}
	else if (pFatherOfTarget != NULL)
	{
		if (pFatherOfTarget->m_pLeftChild == pTarget) L_Zig(this->m_pHead, pTarget);
		else R_Zig(this->m_pHead, pTarget);
	}
	else
	{
		//head를 스플레이 할 수는 없으므로, 아무것도 하지 말자
	}
}

#endif //SPLAY_TREE_H