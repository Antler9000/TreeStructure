#ifndef BST_USING_WHILE_H
#define BST_USING_WHILE_H

#include "../0.공통/BST_using_while_template.h"		//정의한 이진 탐색 트리 템플릿을 구체화해서 이진 탐색 트리를 정의함
using namespace std;								//생성자 리스트에서 std::move(..)를 사용함

class BST_Node
{
private:
	friend class BST_Template<BST_Node>;

	int m_key;
	int m_data;
	BST_Node* m_pLeftChild;
	BST_Node* m_pRightChild;

	BST_Node(int newKey, const int& newData)
		: m_key(newKey), m_data(newData), m_pLeftChild(NULL), m_pRightChild(NULL)
	{
		
	}

	BST_Node(int newKey, int&& newData)
		: m_key(newKey), m_data(move(newData)), m_pLeftChild(NULL), m_pRightChild(NULL)
	{

	}

	//이 노드를 사용하는 BST에서는 순회를 이용한 소멸자가 정의되어있으므로,
	//일단 노드 소멸자에서 m_pLeftChild, m_pRightChild와 그 자식들의 해제를 하는 코드를 작성할 필요는 없음
	~BST_Node() noexcept
	{

	}

	BST_Node& operator = (const BST_Node& sourceNode)
	{
		if (this == &sourceNode)
		{
			return *this;
		}

		RemoveNode();

		m_data = sourceNode.m_data;
		m_key = sourceNode.m_key;
		m_pLeftChild = sourceNode.m_pLeftChild;
		m_pRightChild = sourceNode.m_pRightChild;

		return *this;
	}

	BST_Node& operator = (BST_Node&& sourceNode)
	{
		if (this == &sourceNode)
		{
			return *this;
		}

		RemoveNode();

		m_data = sourceNode.m_data;
		m_key = sourceNode.m_key;
		m_pLeftChild = sourceNode.m_pLeftChild;
		m_pRightChild = sourceNode.m_pRightChild;

		sourceNode.m_data = 0;
		sourceNode.m_key = 0;
		sourceNode.m_pLeftChild = NULL;
		sourceNode.m_pRightChild = NULL;

		return *this;
	}

	//노드에 저장될 데이터를 인자로 명시해주는 경우에만 생성할 수 있도록 한다.
	BST_Node() = delete;

	BST_Node(const BST_Node& sourceNode) = delete;

	BST_Node(BST_Node&& sourceNode) = delete;

	//일단은 재귀로 작성해두고서 빌드하려고 함
	//추후 반복문으로 고칠 것
	bool RemoveNode()
	{
		delete m_pLeftChild;
		delete m_pRightChild;

		return true;
	}
};

class BST : public BST_Template<BST_Node>
{
public:
	BST() : BST_Template() {}
};

#endif //BST_USING_WHILE_H