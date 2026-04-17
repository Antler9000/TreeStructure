#ifndef BST_USING_WHILE_H
#define BST_USING_WHILE_H

#include "../0.공통/BST_using_while_template.h"		//정의한 이진 탐색 트리 템플릿을 구체화함
#include <utility>									//이동 시맨틱을 사용함
using namespace std;								//..	

template <typename DataType>
class BST_Node
{
	friend class BST_Template<BST_Node, DataType>;

public : 

	BST_Node(int newKey, const DataType& newData)
		: m_key(newKey), m_data(newData), m_pLeftChild(nullptr), m_pRightChild(nullptr)
	{
		
	}

	BST_Node(int newKey, DataType&& newData)
		: m_key(newKey), m_data(move(newData)), m_pLeftChild(nullptr), m_pRightChild(nullptr)
	{

	}

	BST_Node(const BST_Node& sourceNode)
	{
		m_data = sourceNode.m_data;
		m_key = sourceNode.m_key;
		m_pLeftChild = nullptr;
		m_pRightChild = nullptr;
	}

	//트리 클래스에 순회를 이용한 소멸자가 정의되어있으므로 노드의 소멸자 정의는 필요 없음
	~BST_Node() noexcept
	{

	}

	//쓰이지 않는 노드 생성 방식들
	BST_Node() = delete;

	BST_Node(BST_Node&& sourceNode) = delete;

	BST_Node& operator = (const BST_Node& sourceNode) = delete;

	BST_Node& operator = (BST_Node&& sourceNode) = delete;

private:

	int m_key;
	DataType m_data;
	BST_Node* m_pLeftChild;
	BST_Node* m_pRightChild;
};

template <typename DataType>
class BST : public BST_Template<BST_Node, DataType>
{
public:

	BST() : BST_Template<BST_Node, DataType>()
	{
	
	}
};

#endif //BST_USING_WHILE_H