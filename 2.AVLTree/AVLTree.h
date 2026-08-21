#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "BSTTemplate.h"
#include "Stack.h"
#include "Debug.h"
#include <algorithm>
#include <iostream>
#include <memory>
#include <utility>
#include <cstdint>

template <typename DataType>
class AVLTree;

template <typename DataType>
class AVLNode
{	
	friend class BSTTemplate<AVLNode, DataType>;
	friend class AVLTree<DataType>;

	friend std::ostream& operator<<(std::ostream& out, const AVLNode<DataType>& printedNode)
	{
		std::cout << "키: " << printedNode.m_key << " / 데이터: " << printedNode.m_data << " / 높이: " << printedNode.m_height;

		return out;
	}

private:

	template <typename NewDataType = DataType>
	AVLNode(std::int64_t newKey, NewDataType&& newData)
	: m_key(newKey), m_data(std::forward<NewDataType>(newData)), m_height(0), m_pLeftChild(nullptr), m_pRightChild(nullptr)
	{

	}

	//Note: BSTTemplate의 트리 복사 과정에서 노드 복사를 사용하고, 이때 자식 포인터가 복사되지 않도록 유의해야 함
	AVLNode(const AVLNode& sourceNode)
	: m_key(sourceNode.m_key), m_data(sourceNode.m_data), m_height(sourceNode.m_height), m_pLeftChild(nullptr), m_pRightChild(nullptr)
	{

	}

private:

	std::int64_t		m_key;
	DataType			m_data;
	std::int64_t		m_height;
	AVLNode<DataType>*	m_pLeftChild;
	AVLNode<DataType>*	m_pRightChild;
};

template <typename DataType>
class AVLTree : public BSTTemplate<AVLNode, DataType>
{
public:
	
	AVLTree() noexcept = default;
	AVLTree(const AVLTree<DataType>& sourceTree) = default;
	AVLTree(AVLTree<DataType>&& sourceTree) noexcept = default;
	AVLTree<DataType>& operator=(const AVLTree<DataType>& sourceTree) = default;
	AVLTree<DataType>& operator=(AVLTree<DataType>&& sourceTree) noexcept = default;
	~AVLTree() noexcept = default;

	//RETURN:	newKey와 같은 키의 노드가 이미 존재하는 경우 false를 반환함
	//NOTE:		데이터의 값 범주가 lvalue인 경우와 rvalue인 경우를 모두 각 참조로 받을 수 있도록 포워딩을 사용함
	template <typename InsertDataType = DataType>
	bool Insert(std::int64_t newKey, InsertDataType&& newData)
	{
		LogPrint("(avl) insert");

		if (this->m_pHead == nullptr)
		{
			this->m_pHead = DBG_NEW AVLNode<DataType>(newKey, std::forward<InsertDataType>(newData));

			return true;
		}

		AVLNode<DataType>* pTraverse = this->m_pHead;
		Stack<AVLNode<DataType>*> pRouteStack;
		while (true)
		{
			if (newKey < pTraverse->m_key)
			{
				if (pTraverse->m_pLeftChild == nullptr)
				{
					pRouteStack.Push(pTraverse);

					pTraverse->m_pLeftChild = DBG_NEW AVLNode<DataType>(newKey, std::forward<InsertDataType>(newData));
					BalancingAllTargetToRoot(&pRouteStack);
						
					return true;
				}
				else
				{
					pRouteStack.Push(pTraverse);

					pTraverse = pTraverse->m_pLeftChild;
				}
			}
			else if (pTraverse->m_key < newKey)
			{
				if (pTraverse->m_pRightChild == nullptr)
				{
					pRouteStack.Push(pTraverse);

					pTraverse->m_pRightChild = DBG_NEW AVLNode<DataType>(newKey, std::forward<InsertDataType>(newData));
					BalancingAllTargetToRoot(&pRouteStack);
					return true;
				}
				else
				{
					pRouteStack.Push(pTraverse);

					pTraverse = pTraverse->m_pRightChild;
				}
			}
			else
			{
				return false;
			}
		}
	}

	//RETURN: targetKey와 같은 키를 가진 노드가 존재하지 않는 경우에 false를 반환함
	bool Remove(std::int64_t targetKey)
	{
		LogPrint("(avl) remove one item");

		if (this->m_pHead == nullptr)
		{
			std::cout << "Cannot Remove! tree is emptied" << std::endl;

			return false;
		}

		Stack<AVLNode<DataType>*> pRouteStack;

		if (this->m_pHead->m_key == targetKey)
		{
			RemoveTarget(this->m_pHead, &pRouteStack);

			return true;
		}

		AVLNode<DataType>* pTraverse = this->m_pHead;
		while (true)
		{
			if (targetKey < pTraverse->m_key)
			{
				if (pTraverse->m_pLeftChild == nullptr)
				{
					return false;
				}

				pRouteStack.Push(pTraverse);

				if (pTraverse->m_pLeftChild->m_key == targetKey)
				{
					RemoveTarget(pTraverse->m_pLeftChild, &pRouteStack);

					return true;
				}
				else
				{
					pTraverse = pTraverse->m_pLeftChild;
				}
			}
			else
			{
				if (pTraverse->m_pRightChild == nullptr)
				{
					return false;
				}

				pRouteStack.Push(pTraverse);

				if (pTraverse->m_pRightChild->m_key == targetKey)
				{
					RemoveTarget(pTraverse->m_pRightChild, &pRouteStack);

					return true;
				}
				else
				{
					pTraverse = pTraverse->m_pRightChild;
				}
			}
		}
	}

private:

	void RemoveTarget(AVLNode<DataType>*& pTargetNode, Stack<AVLNode<DataType>*>* pRouteStack);
	void ReplaceWithInorderPredecessor(AVLNode<DataType>*& pTargetNode, Stack<AVLNode<DataType>*>* pRouteStack);
	void ReplaceWithInorderSuccessor(AVLNode<DataType>*& pTargetNode, Stack<AVLNode<DataType>*>* pRouteStack);

	void BalancingAllTargetToRoot(Stack<AVLNode<DataType>*>* pRouteStack) noexcept;
	void BalancingTargetNode(AVLNode<DataType>* pTargetNode, AVLNode<DataType>* pParent) noexcept;
	void RotationLL(AVLNode<DataType>* pTargetNode, AVLNode<DataType>* pParent) noexcept;
	void RotationLR(AVLNode<DataType>* pTargetNode, AVLNode<DataType>* pParent) noexcept;
	void RotationRL(AVLNode<DataType>* pTargetNode, AVLNode<DataType>* pParent) noexcept;
	void RotationRR(AVLNode<DataType>* pTargetNode, AVLNode<DataType>* pParent) noexcept;
	void UpdateHeight(AVLNode<DataType>* pTargetNode) noexcept;
};

template <typename DataType>
inline void AVLTree<DataType>::RemoveTarget(AVLNode<DataType>*& pTargetNode, Stack<AVLNode<DataType>*>* pRouteStack)
{
	LogPrint("(avl) remove target");

	//NOTE: 중위선행자와 중위후속자가 둘 다 있는 경우에는 균형 유지에 조금이나마 도움이 되기 위해서 대체할 대상을 다소 무작위적인 홀짝 방식으로 선택함
	if (pTargetNode->m_pLeftChild != nullptr && pTargetNode->m_pRightChild != nullptr)
	{
		if (pTargetNode->m_key % 2 == 0)
		{
			ReplaceWithInorderPredecessor(pTargetNode, pRouteStack);
		}
		else
		{
			ReplaceWithInorderSuccessor(pTargetNode, pRouteStack);
		}
	}
	else if (pTargetNode->m_pLeftChild != nullptr)
	{
		ReplaceWithInorderPredecessor(pTargetNode, pRouteStack);
	}
	else if (pTargetNode->m_pRightChild != nullptr)
	{
		ReplaceWithInorderSuccessor(pTargetNode, pRouteStack);
	}
	else
	{
		delete pTargetNode;
		pTargetNode = nullptr;
	}

	BalancingAllTargetToRoot(pRouteStack);
}

template <typename DataType>
inline void AVLTree<DataType>::ReplaceWithInorderPredecessor(AVLNode<DataType>*& pTargetNode, Stack<AVLNode<DataType>*>* pRouteStack)
{
	LogPrint("(avl) replace with inorder predecessor");

	if (pTargetNode->m_pLeftChild->m_pRightChild == nullptr)
	{
		AVLNode<DataType>* pInorderPredecessor = pTargetNode->m_pLeftChild;
		pRouteStack->Push(pInorderPredecessor);

		pInorderPredecessor->m_pRightChild = pTargetNode->m_pRightChild;
		delete pTargetNode;
		pTargetNode = pInorderPredecessor;
	}
	else
	{
		AVLNode<DataType>* pInitTraverse = pTargetNode->m_pLeftChild;
		while (pInitTraverse->m_pRightChild != nullptr)
		{
			pInitTraverse = pInitTraverse->m_pRightChild;
		}
		pRouteStack->Push(pInitTraverse);

		AVLNode<DataType>* pPrevious = pTargetNode;
		AVLNode<DataType>* pTraverse = pTargetNode->m_pLeftChild;
		while (pTraverse->m_pRightChild != nullptr)
		{
			pPrevious = pTraverse;
			pTraverse = pTraverse->m_pRightChild;
			pRouteStack->Push(pPrevious);
		}

		pPrevious->m_pRightChild = pTraverse->m_pLeftChild;
		pTraverse->m_pLeftChild = pTargetNode->m_pLeftChild;
		pTraverse->m_pRightChild = pTargetNode->m_pRightChild;

		delete pTargetNode;
		pTargetNode = pTraverse;
	}
}

template <typename DataType>
inline void AVLTree<DataType>::ReplaceWithInorderSuccessor(AVLNode<DataType>*& pTargetNode, Stack<AVLNode<DataType>*>* pRouteStack)
{
	LogPrint("(avl) replace with inorder successor");

	if (pTargetNode->m_pRightChild->m_pLeftChild == nullptr)
	{
		AVLNode<DataType>* pInorderSuccessor = pTargetNode->m_pRightChild;
		pRouteStack->Push(pInorderSuccessor);

		pInorderSuccessor->m_pLeftChild = pTargetNode->m_pLeftChild;
		delete pTargetNode;
		pTargetNode = pInorderSuccessor;
	}
	else
	{
		AVLNode<DataType>* pInitTraverse = pTargetNode->m_pRightChild;
		while (pInitTraverse->m_pLeftChild != nullptr)
		{
			pInitTraverse = pInitTraverse->m_pLeftChild;
		}
		pRouteStack->Push(pInitTraverse);

		AVLNode<DataType>* pPrevious = pTargetNode;
		AVLNode<DataType>* pTraverse = pTargetNode->m_pRightChild;
		while (pTraverse->m_pLeftChild != nullptr)
		{
			pPrevious = pTraverse;
			pTraverse = pTraverse->m_pLeftChild;
			pRouteStack->Push(pPrevious);
		}

		pPrevious->m_pLeftChild = pTraverse->m_pRightChild;
		pTraverse->m_pRightChild = pTargetNode->m_pRightChild;
		pTraverse->m_pLeftChild = pTargetNode->m_pLeftChild;

		delete pTargetNode;
		pTargetNode = pTraverse;
	}
}

//Note:	Stack의 Pop(..), GetTop(..)은 출력 인자로의 데이터 복사 때문에 원래 noexcept가 아니지만,
//		여기선 Stack의 데이터 타입이 AVLNode<DataType>*로 포인터이기 때문에 예외가 발생하지 않음
template <typename DataType>
inline void AVLTree<DataType>::BalancingAllTargetToRoot(Stack<AVLNode<DataType>*>* pRouteStack) noexcept
{
	LogPrint("balancing all target to root");

	while (pRouteStack->IsEmpty() == false)
	{
		AVLNode<DataType>* pRetraverse = nullptr;
		AVLNode<DataType>* pParentOfRetraverse = nullptr;
		pRouteStack->Pop(pRetraverse);
		pRouteStack->GetTop(pParentOfRetraverse);
		UpdateHeight(pRetraverse);

		BalancingTargetNode(pRetraverse, pParentOfRetraverse);
	}
}

template <typename DataType>
inline void AVLTree<DataType>::BalancingTargetNode(AVLNode<DataType>* pTargetNode, AVLNode<DataType>* pParent) noexcept
{
	LogPrint("balancing target node");

	std::int64_t leftHeight = 0;
	std::int64_t rightHeight = 0;
	if (pTargetNode->m_pLeftChild != nullptr)
	{
		leftHeight = 1 + pTargetNode->m_pLeftChild->m_height;
	}
	if (pTargetNode->m_pRightChild != nullptr)
	{
		rightHeight = 1 + pTargetNode->m_pRightChild->m_height;
	}

	if (leftHeight - rightHeight >= 2) {
		if (pTargetNode->m_pLeftChild->m_pRightChild == nullptr)
		{
			RotationLL(pTargetNode, pParent);
		}
		else if (pTargetNode->m_pLeftChild->m_pLeftChild == nullptr)
		{
			RotationLR(pTargetNode, pParent);
		}
		else
		{
			if (pTargetNode->m_pLeftChild->m_pLeftChild->m_height > pTargetNode->m_pLeftChild->m_pRightChild->m_height)
			{
				RotationLL(pTargetNode, pParent);
			}
			else
			{
				RotationLR(pTargetNode, pParent);
			}
		}
	}
	else if (rightHeight - leftHeight >= 2)
	{
		if (pTargetNode->m_pRightChild->m_pRightChild == nullptr)
		{
			RotationRL(pTargetNode, pParent);
		}
		else if (pTargetNode->m_pRightChild->m_pLeftChild == nullptr)
		{
			RotationRR(pTargetNode, pParent);
		}
		else
		{
			if (pTargetNode->m_pRightChild->m_pLeftChild->m_height > pTargetNode->m_pRightChild->m_pRightChild->m_height)
			{
				RotationRL(pTargetNode, pParent);
			}
			else
			{
				RotationRR(pTargetNode, pParent);
			}
		}
	}
}

template <typename DataType>
inline void AVLTree<DataType>::RotationLL(AVLNode<DataType>* pTargetNode, AVLNode<DataType>* pParent) noexcept
{
	LogPrint("rotaion LL");

	AVLNode<DataType>* pRotationNode = pTargetNode->m_pLeftChild;
	pTargetNode->m_pLeftChild = pRotationNode->m_pRightChild;
	pRotationNode->m_pRightChild = pTargetNode;
	if (pParent == nullptr)
	{
		this->m_pHead = pRotationNode;
	}
	else if (pParent->m_pLeftChild == pTargetNode)
	{
		pParent->m_pLeftChild = pRotationNode;
	}
	else
	{
		pParent->m_pRightChild = pRotationNode;
	}

	UpdateHeight(pTargetNode);
	UpdateHeight(pRotationNode);
}

template <typename DataType>
inline void AVLTree<DataType>::RotationLR(AVLNode<DataType>* pTargetNode, AVLNode<DataType>* pParent) noexcept
{
	LogPrint("rotaion LR");

	AVLNode<DataType>* pRotatationNode = pTargetNode->m_pLeftChild->m_pRightChild;
	pTargetNode->m_pLeftChild->m_pRightChild = pRotatationNode->m_pLeftChild;
	pRotatationNode->m_pLeftChild = pTargetNode->m_pLeftChild;
	pTargetNode->m_pLeftChild = pRotatationNode;

	UpdateHeight(pRotatationNode->m_pLeftChild);
	UpdateHeight(pRotatationNode);
	UpdateHeight(pTargetNode);

	RotationLL(pTargetNode, pParent);
}

template <typename DataType>
inline void AVLTree<DataType>::RotationRL(AVLNode<DataType>* pTargetNode, AVLNode<DataType>* pParent) noexcept
{
	LogPrint("rotaion RL");

	AVLNode<DataType>* pRotationNode = pTargetNode->m_pRightChild->m_pLeftChild;
	pTargetNode->m_pRightChild->m_pLeftChild = pRotationNode->m_pRightChild;
	pRotationNode->m_pRightChild = pTargetNode->m_pRightChild;
	pTargetNode->m_pRightChild = pRotationNode;

	UpdateHeight(pRotationNode->m_pRightChild);
	UpdateHeight(pRotationNode);
	UpdateHeight(pTargetNode);

	RotationRR(pTargetNode, pParent);
}

template <typename DataType>
inline void AVLTree<DataType>::RotationRR(AVLNode<DataType>* pTargetNode, AVLNode<DataType>* pParent) noexcept
{
	LogPrint("rotaion RR");

	AVLNode<DataType>* pRotationNode = pTargetNode->m_pRightChild;
	pTargetNode->m_pRightChild = pRotationNode->m_pLeftChild;
	pRotationNode->m_pLeftChild = pTargetNode;
	if (pParent == nullptr)
	{
		this->m_pHead = pRotationNode;
	}
	else if (pParent->m_pLeftChild == pTargetNode)
	{
		pParent->m_pLeftChild = pRotationNode;
	}
	else
	{
		pParent->m_pRightChild = pRotationNode;
	}

	UpdateHeight(pTargetNode);
	UpdateHeight(pRotationNode);
}


template <typename DataType>
inline void AVLTree<DataType>::UpdateHeight(AVLNode<DataType>* pTargetNode) noexcept
{
	LogPrint("update height");

	std::int64_t heightFromLeftChild = 0;
	std::int64_t heightFromRightChild = 0;
	if (pTargetNode->m_pLeftChild != nullptr)
	{
		heightFromLeftChild = 1 + pTargetNode->m_pLeftChild->m_height;
	}
	if (pTargetNode->m_pRightChild != nullptr)
	{
		heightFromRightChild = 1 + pTargetNode->m_pRightChild->m_height;
	}
	
	pTargetNode->m_height = std::max(heightFromLeftChild, heightFromRightChild);
}

#endif //AVL_TREE_H