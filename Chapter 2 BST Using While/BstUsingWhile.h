#ifndef BST_USING_WHILE_H
#define BST_USING_WHILE_H

#include "../Common/BstUsingWhileTemplate.h"		//정의한 이진 탐색 트리 템플릿을 구체화함
#include <utility>									//이동 시맨틱을 사용함
using namespace std;								//..	

template <typename DataType>
class BstNode
{
	friend class BstTemplate<BstNode, DataType>;

public : 

	BstNode(int newKey, const DataType& newData)
		: m_key(newKey), m_data(newData), m_pLeftChild(nullptr), m_pRightChild(nullptr)
	{
		
	}

	BstNode(int newKey, DataType&& newData)
		: m_key(newKey), m_data(move(newData)), m_pLeftChild(nullptr), m_pRightChild(nullptr)
	{

	}

	BstNode(const BstNode& sourceNode)
	{
		m_data = sourceNode.m_data;
		m_key = sourceNode.m_key;
		m_pLeftChild = nullptr;
		m_pRightChild = nullptr;
	}

	//트리 클래스에 순회를 이용한 소멸자가 정의되어있으므로 노드의 소멸자 정의는 필요 없음
	~BstNode() noexcept
	{

	}

	//쓰이지 않는 노드 생성 방식들
	BstNode() = delete;

	BstNode(BstNode&& sourceNode) = delete;

	BstNode& operator = (const BstNode& sourceNode) = delete;

	BstNode& operator = (BstNode&& sourceNode) = delete;

private:

	int m_key;
	DataType m_data;
	BstNode* m_pLeftChild;
	BstNode* m_pRightChild;
};

template <typename DataType>
class Bst : public BstTemplate<BstNode, DataType>
{
public:

	Bst() : BstTemplate<BstNode, DataType>()
	{
	
	}
};

#endif //BST_USING_WHILE_H