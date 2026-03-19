#ifndef BST_USING_WHILE_H
#define BST_USING_WHILE_H

#include "../0.공통/BST_using_while_template.h"		//정의한 이진 탐색 트리 템플릿을 구체화함
#include <utility>									//이동 시맨틱을 사용함
using namespace std;								//..	

class BST_Node
{
	friend class BST_Template<BST_Node>;

private : 
	BST_Node(int newKey, const int& newData)
		: m_key(newKey), m_data(newData), m_pLeftChild(NULL), m_pRightChild(NULL)
	{
		
	}

	BST_Node(int newKey, int&& newData)
		: m_key(newKey), m_data(move(newData)), m_pLeftChild(NULL), m_pRightChild(NULL)
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
		m_pLeftChild = NULL;
		m_pRightChild = NULL;

		return *this;
	}

	BST_Node& operator = (BST_Node&& sourceNode) noexcept
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

	//트리 클래스에 순회를 이용한 소멸자가 정의되어있으므로 노드의 소멸자 정의는 필요 없음
	~BST_Node() noexcept
	{

	}

	//쓰이지 않는 노드 생성 방식들
	BST_Node() = delete;

	BST_Node(const BST_Node& sourceNode) = delete;

	BST_Node(BST_Node&& sourceNode) = delete;

private:
	//TODO : 트리 높이가 커지면 오류가 발생하므로, 반복문으로 고칠 것
	bool RemoveNode() noexcept
	{
		delete m_pLeftChild;
		delete m_pRightChild;

		return true;
	}

private:
	int m_key;
	int m_data;
	BST_Node* m_pLeftChild;
	BST_Node* m_pRightChild;
};

class BST : public BST_Template<BST_Node>
{
public:
	BST() : BST_Template()
	{
	
	}
};

#endif //BST_USING_WHILE_H