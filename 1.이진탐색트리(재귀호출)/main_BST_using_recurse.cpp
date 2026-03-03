//로그, 에러, 경고 콘솔 출력문들을 활성화하기 위한 전처리 상수 정의
//"testing 4 : Speed Test"에서 시간을 보다 정확히 측정하고 싶을 경우 상수 정의들을 주석처리 해야함
#define TREE_LOG	
#define TREE_ERROR
#define TREE_WARNING

#include <chrono>;				//속도 테스트용도
#include "BST_using_recurse.h"	//이진 탐색 트리가 정의된 헤더파일

using namespace chrono;

template <typename DataType>
inline void RetrieveResultPrint(const int key, const DataType retrievedData)
{
	cout << "retrieve key : " << key << ", retrieved data : " << retrievedData << endl;
}

int main()
{
	cout << endl << "testing 1 : BST<int>--------------------------------------------------------------------------" << endl;

	BST<int> intTestBST;
	
	cout << endl << "삽입" << endl;
	intTestBST.Insert(5, 1515);
	intTestBST.Insert(7, 2727);
	intTestBST.Insert(3, 1313);
	intTestBST.Insert(4, 2424);
	intTestBST.Insert(6, 3636);
	intTestBST.PreorderPrint();

	cout << endl << "검색" << endl;
	int intRetrievedData = 0;
	intTestBST.Retrieve(3, intRetrievedData);
	RetrieveResultPrint(3, intRetrievedData);

	cout << endl << "명시적 복사" << endl;
	BST<int> intExplicitCopyTestBST;
	intExplicitCopyTestBST.CopyTree(intTestBST);
	intExplicitCopyTestBST.PreorderPrint();

	cout << endl << "복사 생성자" << endl;
	BST<int> intCopyConstructorTestBST = intTestBST;
	intCopyConstructorTestBST.PreorderPrint();
	
	cout << endl << "복사 할당 연산자" << endl;
	BST<int> intCopyAssignmentTestBST;
	intCopyAssignmentTestBST = intTestBST;
	intCopyAssignmentTestBST.PreorderPrint();

	cout << endl << "이동 생성자" << endl;
	BST<int> intMoveConstructorTestBST = move(intCopyConstructorTestBST);
	intMoveConstructorTestBST.PreorderPrint();
	intCopyConstructorTestBST.PreorderPrint();

	cout << endl << "이동 할당 연산자" << endl;
	BST<int> intMoveAssignmentTestBST;
	intMoveAssignmentTestBST = move(intCopyAssignmentTestBST);
	intMoveAssignmentTestBST.PreorderPrint();
	intCopyAssignmentTestBST.PreorderPrint();

	cout << endl << "요소별 삭제" << endl;
	intTestBST.Remove(7);
	intTestBST.PreorderPrint();

	cout << endl << "전체 삭제" << endl;
	intTestBST.RemoveTree();
	intTestBST.PreorderPrint();

	cout << endl << "testing 2 : BST<float>--------------------------------------------------------------------------" << endl;

	BST<float> floatTestBST;
	
	cout << endl << "삽입" << endl;
	floatTestBST.Insert(5, 1.515f);
	floatTestBST.Insert(7, 2.727f);
	floatTestBST.Insert(3, 1.313f);
	floatTestBST.Insert(4, 2.424f);
	floatTestBST.Insert(6, 3.636f);
	floatTestBST.PreorderPrint();

	cout << endl << "검색" << endl;
	float floatRetrievedData = 0;
	floatTestBST.Retrieve(3, floatRetrievedData);
	RetrieveResultPrint(3, floatRetrievedData);

	cout << endl << "명시적 복사" << endl;
	BST<float> floatExplicitCopyTestBST;
	floatExplicitCopyTestBST.CopyTree(floatTestBST);
	floatExplicitCopyTestBST.PreorderPrint();

	cout << endl << "복사 생성자" << endl;
	BST<float> floatCopyConstructorTestBST = floatTestBST;
	floatCopyConstructorTestBST.PreorderPrint();

	cout << endl << "복사 할당 연산자" << endl;
	BST<float> floatCopyAssignmentTestBST;
	floatCopyAssignmentTestBST = floatTestBST;
	floatCopyAssignmentTestBST.PreorderPrint();

	cout << endl << "이동 생성자" << endl;
	BST<float> floatMoveConstructorTestBST = move(floatCopyConstructorTestBST);
	floatMoveConstructorTestBST.PreorderPrint();
	floatCopyConstructorTestBST.PreorderPrint();

	cout << endl << "이동 할당 연산자" << endl;
	BST<float> floatMoveAssignmentTestBST;
	floatMoveAssignmentTestBST = move(floatCopyAssignmentTestBST);
	floatMoveAssignmentTestBST.PreorderPrint();
	floatCopyAssignmentTestBST.PreorderPrint();

	cout << endl << "요소별 삭제" << endl;
	floatTestBST.Remove(7);
	floatTestBST.PreorderPrint();

	cout << endl << "전체 삭제" << endl;
	floatTestBST.RemoveTree();
	floatTestBST.PreorderPrint();

	cout << endl << "testing 3 : BST<string>--------------------------------------------------------------------------" << endl;

	BST<string> stringTestBST;
	
	cout << endl << "삽입" << endl;
	stringTestBST.Insert(5, "Panther");
	stringTestBST.Insert(7, "Sherman");
	stringTestBST.Insert(3, "Crusader");
	stringTestBST.Insert(4, "Comet");
	stringTestBST.Insert(6, "Tiger");
	stringTestBST.PreorderPrint();

	cout << endl << "검색" << endl;
	string stringRetrievedData = "";
	stringTestBST.Retrieve(3, stringRetrievedData);
	RetrieveResultPrint(3, stringRetrievedData);

	cout << endl << "명시적 복사" << endl;
	BST<string> stringExplicitCopyTestBST;
	stringExplicitCopyTestBST.CopyTree(stringTestBST);
	stringExplicitCopyTestBST.PreorderPrint();

	cout << endl << "복사 생성자" << endl;
	BST<string> stringCopyConstructorTestBST = stringTestBST;
	stringCopyConstructorTestBST.PreorderPrint();

	cout << endl << "복사 할당 연산자" << endl;
	BST<string> stringCopyAssignmentTestBST;
	stringCopyAssignmentTestBST = stringTestBST;
	stringCopyAssignmentTestBST.PreorderPrint();

	cout << endl << "이동 생성자" << endl;
	BST<string> stringMoveConstructorTestBST = move(stringCopyConstructorTestBST);
	stringMoveConstructorTestBST.PreorderPrint();
	stringCopyConstructorTestBST.PreorderPrint();

	cout << endl << "이동 할당 연산자" << endl;
	BST<string> stringMoveAssignmentTestBST;
	stringMoveAssignmentTestBST = move(stringCopyAssignmentTestBST);
	stringMoveAssignmentTestBST.PreorderPrint();
	stringCopyAssignmentTestBST.PreorderPrint();

	cout << endl << "요소별 삭제" << endl;
	stringTestBST.Remove(7);
	stringTestBST.PreorderPrint();

	cout << endl << "전체 삭제" << endl;
	stringTestBST.RemoveTree();
	stringTestBST.PreorderPrint();

	cout << endl << "testing 4 : Speed Test-------------------------------------------------------------------------" << endl;

	BST<int> speedTestBST;
	const int speedTestNumber = 1000;

	//Tomorrow Do : 랜덤 삽입을 위한 삽입 데이터 미리 준비하기

	steady_clock clock;

	time_point<steady_clock> timeBegin = clock.now();
	
	//Tomorrow Do : 준비된 삽입 데이터들을 모두 삽입하기

	time_point<steady_clock> timeEnd =	clock.now();

	duration<double> timeDiff = timeEnd - timeBegin;

	cout << speedTestNumber << "번의 삽입 동안 흐른 시간은 : " << timeDiff.count() << endl;

	cout << endl << "testing 5 : Stack Safety Test-------------------------------------------------------------------------" << endl;

	/*
		stackSafetyTestNumber 횟수만큼 하나의 트리에 삽입을 수행함
		작성자의 테스팅 환경에서는 stackSafetyTestNumber이 특정 값을 넘어가면 스택 오버플로우가 나는 것을 확인했음
		stackSafetyTestNumber >= 1800 : 마지막의 노드 소멸 과정에서 스택 오버플로우 발생
		stackSafetyTestNumber >= 2700 : 그보다 앞선 삽입 과정에서 스택 오버플로우 발생

		작성자의 테스팅 환경은 아래와 같음
		-삽입 패턴		: 편향 삽입을 통한 높이 N의 트리 형성
		-실행 방법		: 디버깅 실행(F5)
		-OS				: Windows 11, 버전 25H2, 빌드 26200.7922
		-IDE				: Microsoft Visual Studio Community 2022 (64-bit) 버전 17.14.23
		-플랫폼 도구 집합	: Visual Studio 2022 (v143)
		-컴파일러 버전	: x86용 Microsoft (R) C/C++ 최적화 컴파일러 버전 19.44.35222
		-스택 크기 설정	: 프로젝트 기본 설정(공란)
		-C/C++ 최적화 설정	: 사용 안 함(/Od)

	*/

	BST<int> stackSafetyTestBST;
	const int stackSafetyTestNumber = 1700;

	cout << "삽입 시작" << endl;

	for (int i = 0; i < stackSafetyTestNumber; i++)
	{
		stackSafetyTestBST.Insert(i, i);
	}

	cout << "삽입 성공" << endl;

	return 0;
}