//로그 출력문들을 활성화하고 싶을 시 아래 구문의 주석을 해제할 것
//#define TREE_LOG	
//#define TREE_WARNING
//#define TREE_ERROR

#include "RedBlackTree.h"
#include <crtdbg.h>
#include <iostream>
#include <chrono>
#include <string>
#include <numeric>
#include <random>
#include <algorithm>
#include <vector>
#include <map>
#include <utility>

using namespace std;
using namespace chrono;

template <typename DataType>
void PrintKeyAndData(int key, const DataType& retrievedData);

void RandomWorkloadSpeedTest(int workloadNum, int workloadPerDataLen);
void RandomLocalWorkloadTest(int workloadNum, int workloadPerDataLen, int localBlockSize);
void LinearIncreaseWorkloadTest(int workloadNum, int workloadPerDataLen);
void LinearDecreaseWorkloadTest(int workloadNum, int workloadPerDataLen);

//NOTE	: insertDataWorkload는 복사 비용이 크지만, 그럼에도 하나의 워크로드를 RedBlackTree와 map에 반복해서 사용할 수 있도록 값복사 형식의 매개변수를 사용함
time_point<steady_clock> TestRedBlackTree(steady_clock& clock, int workloadNum, vector<string> insertDataWorkload, const vector<int>& insertKeyWorkload, const vector<int>& retrieveKeyWorkload, const vector<int>& removeKeyWorkload);
time_point<steady_clock> TestMap(steady_clock& clock, int workloadNum, vector<string> insertDataWorkload, const vector<int>& insertKeyWorkload, const vector<int>& retrieveKeyWorkload, const vector<int>& removeKeyWorkload);

int main()
{
	//NOTE : 디버깅 실행이 종료될 시점에도 해제되지 않은 동적 메모리 누수가 존재할 시, Visual Studio의 하단의 출력창(output)에 해당 누수에 대한 정보가 출력됨
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	cout << endl << "기능 테스트 1/7 : Balancing 1--------------------------------------------------------------------" << endl;

	RedBlackTree<int> balancingTestRedBlackTree1;

	cout << endl << "삽입 5" << endl;
	balancingTestRedBlackTree1.Insert(5, 55);
	balancingTestRedBlackTree1.PreorderPrint();

	cout << endl << "삽입 9" << endl;
	balancingTestRedBlackTree1.Insert(9, 99);
	balancingTestRedBlackTree1.PreorderPrint();

	cout << endl << "삽입 8" << endl;
	balancingTestRedBlackTree1.Insert(8, 88);
	balancingTestRedBlackTree1.PreorderPrint();

	cout << endl << "삽입 6" << endl;
	balancingTestRedBlackTree1.Insert(6, 66);
	balancingTestRedBlackTree1.PreorderPrint();

	cout << endl << "삽입 7" << endl;
	balancingTestRedBlackTree1.Insert(7, 77);
	balancingTestRedBlackTree1.PreorderPrint();

	cout << endl << "삽입 1" << endl;
	balancingTestRedBlackTree1.Insert(1, 11);
	balancingTestRedBlackTree1.PreorderPrint();

	cout << endl << "삽입 2" << endl;
	balancingTestRedBlackTree1.Insert(2, 22);
	balancingTestRedBlackTree1.PreorderPrint();

	cout << endl << "삽입 3" << endl;
	balancingTestRedBlackTree1.Insert(3, 33);
	balancingTestRedBlackTree1.PreorderPrint();

	cout << endl << "삽입 4" << endl;
	balancingTestRedBlackTree1.Insert(4, 44);
	balancingTestRedBlackTree1.PreorderPrint();

	cout << endl << "삭제 1" << endl;
	balancingTestRedBlackTree1.Remove(1);
	balancingTestRedBlackTree1.PreorderPrint();

	cout << endl << "삭제 2" << endl;
	balancingTestRedBlackTree1.Remove(2);
	balancingTestRedBlackTree1.PreorderPrint();

	cout << endl << "삭제 3" << endl;
	balancingTestRedBlackTree1.Remove(3);
	balancingTestRedBlackTree1.PreorderPrint();

	cout << endl << "삭제 4" << endl;
	balancingTestRedBlackTree1.Remove(4);
	balancingTestRedBlackTree1.PreorderPrint();

	cout << endl << "삭제 5" << endl;
	balancingTestRedBlackTree1.Remove(5);
	balancingTestRedBlackTree1.PreorderPrint();

	cout << endl << "삭제 6" << endl;
	balancingTestRedBlackTree1.Remove(6);
	balancingTestRedBlackTree1.PreorderPrint();

	cout << endl << "삭제 7" << endl;
	balancingTestRedBlackTree1.Remove(7);
	balancingTestRedBlackTree1.PreorderPrint();

	cout << endl << "삭제 8" << endl;
	balancingTestRedBlackTree1.Remove(8);
	balancingTestRedBlackTree1.PreorderPrint();

	cout << endl << "삭제 9" << endl;
	balancingTestRedBlackTree1.Remove(9);
	balancingTestRedBlackTree1.PreorderPrint();

	cout << endl << "기능 테스트 2/7 : Balancing 2---------------------------------------------------------------------" << endl;

	RedBlackTree<int> balancingTestRedBlackTree2;

	cout << endl << "삽입 1" << endl;
	balancingTestRedBlackTree2.Insert(1, 11);
	balancingTestRedBlackTree2.PreorderPrint();

	cout << endl << "삽입 2" << endl;
	balancingTestRedBlackTree2.Insert(2, 22);
	balancingTestRedBlackTree2.PreorderPrint();

	cout << endl << "삽입 3" << endl;
	balancingTestRedBlackTree2.Insert(3, 33);
	balancingTestRedBlackTree2.PreorderPrint();

	cout << endl << "삽입 4" << endl;
	balancingTestRedBlackTree2.Insert(4, 44);
	balancingTestRedBlackTree2.PreorderPrint();

	cout << endl << "삽입 5" << endl;
	balancingTestRedBlackTree2.Insert(5, 55);
	balancingTestRedBlackTree2.PreorderPrint();

	cout << endl << "삽입 6" << endl;
	balancingTestRedBlackTree2.Insert(6, 66);
	balancingTestRedBlackTree2.PreorderPrint();

	cout << endl << "삽입 7" << endl;
	balancingTestRedBlackTree2.Insert(7, 77);
	balancingTestRedBlackTree2.PreorderPrint();

	cout << endl << "삭제 1" << endl;
	balancingTestRedBlackTree2.Remove(1);
	balancingTestRedBlackTree2.PreorderPrint();

	cout << endl << "삭제 2" << endl;
	balancingTestRedBlackTree2.Remove(2);
	balancingTestRedBlackTree2.PreorderPrint();

	cout << endl << "삭제 3" << endl;
	balancingTestRedBlackTree2.Remove(3);
	balancingTestRedBlackTree2.PreorderPrint();

	cout << endl << "삭제 4" << endl;
	balancingTestRedBlackTree2.Remove(4);
	balancingTestRedBlackTree2.PreorderPrint();

	cout << endl << "삭제 5" << endl;
	balancingTestRedBlackTree2.Remove(5);
	balancingTestRedBlackTree2.PreorderPrint();

	cout << endl << "삭제 6" << endl;
	balancingTestRedBlackTree2.Remove(6);
	balancingTestRedBlackTree2.PreorderPrint();

	cout << endl << "삭제 7" << endl;
	balancingTestRedBlackTree2.Remove(7);
	balancingTestRedBlackTree2.PreorderPrint();

	cout << endl << "기능 테스트 3/7 : Balancing 3---------------------------------------------------------------------" << endl;

	RedBlackTree<int> balancingTestRedBlackTree3;

	cout << endl << "삽입 7" << endl;
	balancingTestRedBlackTree3.Insert(7, 77);
	balancingTestRedBlackTree3.PreorderPrint();

	cout << endl << "삽입 6" << endl;
	balancingTestRedBlackTree3.Insert(6, 66);
	balancingTestRedBlackTree3.PreorderPrint();

	cout << endl << "삽입 5" << endl;
	balancingTestRedBlackTree3.Insert(5, 55);
	balancingTestRedBlackTree3.PreorderPrint();

	cout << endl << "삽입 4" << endl;
	balancingTestRedBlackTree3.Insert(4, 44);
	balancingTestRedBlackTree3.PreorderPrint();

	cout << endl << "삽입 3" << endl;
	balancingTestRedBlackTree3.Insert(3, 33);
	balancingTestRedBlackTree3.PreorderPrint();

	cout << endl << "삽입 2" << endl;
	balancingTestRedBlackTree3.Insert(2, 22);
	balancingTestRedBlackTree3.PreorderPrint();

	cout << endl << "삽입 1" << endl;
	balancingTestRedBlackTree3.Insert(1, 11);
	balancingTestRedBlackTree3.PreorderPrint();

	cout << endl << "삭제 7" << endl;
	balancingTestRedBlackTree3.Remove(7);
	balancingTestRedBlackTree3.PreorderPrint();

	cout << endl << "삭제 6" << endl;
	balancingTestRedBlackTree3.Remove(6);
	balancingTestRedBlackTree3.PreorderPrint();

	cout << endl << "삭제 5" << endl;
	balancingTestRedBlackTree3.Remove(5);
	balancingTestRedBlackTree3.PreorderPrint();

	cout << endl << "삭제 4" << endl;
	balancingTestRedBlackTree3.Remove(4);
	balancingTestRedBlackTree3.PreorderPrint();

	cout << endl << "삭제 3" << endl;
	balancingTestRedBlackTree3.Remove(3);
	balancingTestRedBlackTree3.PreorderPrint();

	cout << endl << "삭제 2" << endl;
	balancingTestRedBlackTree3.Remove(2);
	balancingTestRedBlackTree3.PreorderPrint();

	cout << endl << "삭제 1" << endl;
	balancingTestRedBlackTree3.Remove(1);
	balancingTestRedBlackTree3.PreorderPrint();

	cout << endl << "기능 테스트 4/7 : Balancing 4---------------------------------------------------------------------" << endl;

	RedBlackTree<int> balancingTestRedBlackTree4;

	cout << endl << "삽입 1" << endl;
	balancingTestRedBlackTree4.Insert(1, 11);
	balancingTestRedBlackTree4.PreorderPrint();

	cout << endl << "삽입 7" << endl;
	balancingTestRedBlackTree4.Insert(7, 77);
	balancingTestRedBlackTree4.PreorderPrint();

	cout << endl << "삽입 2" << endl;
	balancingTestRedBlackTree4.Insert(2, 22);
	balancingTestRedBlackTree4.PreorderPrint();

	cout << endl << "삽입 6" << endl;
	balancingTestRedBlackTree4.Insert(6, 66);
	balancingTestRedBlackTree4.PreorderPrint();

	cout << endl << "삽입 3" << endl;
	balancingTestRedBlackTree4.Insert(3, 33);
	balancingTestRedBlackTree4.PreorderPrint();

	cout << endl << "삽입 5" << endl;
	balancingTestRedBlackTree4.Insert(5, 55);
	balancingTestRedBlackTree4.PreorderPrint();

	cout << endl << "삽입 4" << endl;
	balancingTestRedBlackTree4.Insert(4, 44);
	balancingTestRedBlackTree4.PreorderPrint();

	cout << endl << "삭제 1" << endl;
	balancingTestRedBlackTree4.Remove(1);
	balancingTestRedBlackTree4.PreorderPrint();

	cout << endl << "삭제 7" << endl;
	balancingTestRedBlackTree4.Remove(7);
	balancingTestRedBlackTree4.PreorderPrint();

	cout << endl << "삭제 2" << endl;
	balancingTestRedBlackTree4.Remove(2);
	balancingTestRedBlackTree4.PreorderPrint();

	cout << endl << "삭제 6" << endl;
	balancingTestRedBlackTree4.Remove(6);
	balancingTestRedBlackTree4.PreorderPrint();

	cout << endl << "삭제 3" << endl;
	balancingTestRedBlackTree4.Remove(3);
	balancingTestRedBlackTree4.PreorderPrint();

	cout << endl << "삭제 5" << endl;
	balancingTestRedBlackTree4.Remove(5);
	balancingTestRedBlackTree4.PreorderPrint();

	cout << endl << "삭제 4" << endl;
	balancingTestRedBlackTree4.Remove(4);
	balancingTestRedBlackTree4.PreorderPrint();

	cout << endl << "기능 테스트 5/7 : RedBlackTree<int>-------------------------------------------------------------------" << endl;

	RedBlackTree<int> intTestRedBlackTree;

	cout << endl << "삽입 (트리 A)" << endl;
	intTestRedBlackTree.Insert(5, 55);
	intTestRedBlackTree.Insert(7, 77);
	intTestRedBlackTree.Insert(3, 33);
	intTestRedBlackTree.Insert(4, 44);
	intTestRedBlackTree.Insert(6, 66);
	intTestRedBlackTree.Insert(9, 99);
	intTestRedBlackTree.Insert(2, 22);
	intTestRedBlackTree.PreorderPrint();

	cout << endl << "중위 순회 출력 (트리 A)" << endl;
	intTestRedBlackTree.InorderPrint();

	cout << endl << "후위 순회 출력 (트리 A)" << endl;
	intTestRedBlackTree.PostorderPrint();

	cout << endl << "검색 (트리 A)" << endl;
	int intRetrievedData = 0;
	intTestRedBlackTree.Retrieve(3, intRetrievedData);
	PrintKeyAndData(3, intRetrievedData);

	cout << endl << "명시적 복사 (트리 A -> B)" << endl;
	RedBlackTree<int> intExplicitCopyTestRedBlackTree;
	intExplicitCopyTestRedBlackTree.CopyTree(intTestRedBlackTree);
	intExplicitCopyTestRedBlackTree.PreorderPrint();

	cout << endl << "복사 생성자 (트리 A -> C)" << endl;
	RedBlackTree<int> intCopyConstructorTestRedBlackTree = intTestRedBlackTree;
	intCopyConstructorTestRedBlackTree.PreorderPrint();

	cout << endl << "복사 할당 연산자 (트리 A -> D)" << endl;
	RedBlackTree<int> intCopyAssignmentTestRedBlackTree;
	intCopyAssignmentTestRedBlackTree = intTestRedBlackTree;
	intCopyAssignmentTestRedBlackTree.PreorderPrint();

	cout << endl << "이동 생성자 (트리 C -> E)" << endl;
	RedBlackTree<int> intMoveConstructorTestRedBlackTree = move(intCopyConstructorTestRedBlackTree);
	intMoveConstructorTestRedBlackTree.PreorderPrint();

	cout << endl << "이동 할당 연산자 (트리 D -> F)" << endl;
	RedBlackTree<int> intMoveAssignmentTestRedBlackTree;
	intMoveAssignmentTestRedBlackTree = move(intCopyAssignmentTestRedBlackTree);
	intMoveAssignmentTestRedBlackTree.PreorderPrint();

	cout << endl << "이동 후 소스 트리는 비워짐 (트리 C, D)" << endl;
	intCopyConstructorTestRedBlackTree.PreorderPrint();
	intCopyAssignmentTestRedBlackTree.PreorderPrint();

	cout << endl << "요소별 삭제 (트리 A)" << endl;
	intTestRedBlackTree.Remove(7);
	intTestRedBlackTree.PreorderPrint();

	cout << endl << "요소별 삭제 (트리 A)" << endl;
	intTestRedBlackTree.Remove(3);
	intTestRedBlackTree.PreorderPrint();

	cout << endl << "전체 삭제 (트리 A)" << endl;
	intTestRedBlackTree.RemoveTree();
	intTestRedBlackTree.PreorderPrint();

	cout << endl << "복사한 트리는 원본과 독립적임 (트리 B)" << endl;
	intExplicitCopyTestRedBlackTree.PreorderPrint();

	cout << endl << "기능 테스트 6/7 : RedBlackTree<float>-----------------------------------------------------------------" << endl;

	RedBlackTree<float> floatTestRedBlackTree;

	cout << endl << "삽입 (트리 A)" << endl;
	floatTestRedBlackTree.Insert(5, 0.55f);
	floatTestRedBlackTree.Insert(7, 0.77f);
	floatTestRedBlackTree.Insert(3, 0.33f);
	floatTestRedBlackTree.Insert(4, 0.44f);
	floatTestRedBlackTree.Insert(6, 0.66f);
	floatTestRedBlackTree.Insert(9, 0.99f);
	floatTestRedBlackTree.Insert(2, 0.22f);
	floatTestRedBlackTree.PreorderPrint();

	cout << endl << "중위 순회 출력 (트리 A)" << endl;
	floatTestRedBlackTree.InorderPrint();

	cout << endl << "후위 순회 출력 (트리 A)" << endl;
	floatTestRedBlackTree.PostorderPrint();

	cout << endl << "검색 (트리 A)" << endl;
	float floatRetrievedData = 0.0f;
	floatTestRedBlackTree.Retrieve(3, floatRetrievedData);
	PrintKeyAndData(3, floatRetrievedData);

	cout << endl << "명시적 복사 (트리 A -> B)" << endl;
	RedBlackTree<float> floatExplicitCopyTestRedBlackTree;
	floatExplicitCopyTestRedBlackTree.CopyTree(floatTestRedBlackTree);
	floatExplicitCopyTestRedBlackTree.PreorderPrint();

	cout << endl << "복사 생성자 (트리 A -> C)" << endl;
	RedBlackTree<float> floatCopyConstructorTestRedBlackTree = floatTestRedBlackTree;
	floatCopyConstructorTestRedBlackTree.PreorderPrint();

	cout << endl << "복사 할당 연산자 (트리 A -> D)" << endl;
	RedBlackTree<float> floatCopyAssignmentTestRedBlackTree;
	floatCopyAssignmentTestRedBlackTree = floatTestRedBlackTree;
	floatCopyAssignmentTestRedBlackTree.PreorderPrint();

	cout << endl << "이동 생성자 (트리 C -> E)" << endl;
	RedBlackTree<float> floatMoveConstructorTestRedBlackTree = move(floatCopyConstructorTestRedBlackTree);
	floatMoveConstructorTestRedBlackTree.PreorderPrint();

	cout << endl << "이동 할당 연산자 (트리 D -> F)" << endl;
	RedBlackTree<float> floatMoveAssignmentTestRedBlackTree;
	floatMoveAssignmentTestRedBlackTree = move(floatCopyAssignmentTestRedBlackTree);
	floatMoveAssignmentTestRedBlackTree.PreorderPrint();

	cout << endl << "이동 후 소스 트리는 비워짐 (트리 C, D)" << endl;
	floatCopyConstructorTestRedBlackTree.PreorderPrint();
	floatCopyAssignmentTestRedBlackTree.PreorderPrint();

	cout << endl << "요소별 삭제 (트리 A)" << endl;
	floatTestRedBlackTree.Remove(7);
	floatTestRedBlackTree.PreorderPrint();

	cout << endl << "요소별 삭제 (트리 A)" << endl;
	floatTestRedBlackTree.Remove(3);
	floatTestRedBlackTree.PreorderPrint();

	cout << endl << "전체 삭제 (트리 A)" << endl;
	floatTestRedBlackTree.RemoveTree();
	floatTestRedBlackTree.PreorderPrint();

	cout << endl << "복사한 트리는 원본과 독립적임 (트리 B)" << endl;
	floatExplicitCopyTestRedBlackTree.PreorderPrint();

	cout << endl << "기능 테스트 7/7 : RedBlackTree<string>----------------------------------------------------------------" << endl;

	RedBlackTree<string> stringTestRedBlackTree;

	cout << endl << "삽입 (트리 A)" << endl;
	stringTestRedBlackTree.Insert(5, "Panther");
	stringTestRedBlackTree.Insert(7, "Comet");
	stringTestRedBlackTree.Insert(3, "Crusader");
	stringTestRedBlackTree.Insert(4, "Sherman");
	stringTestRedBlackTree.Insert(6, "Tiger");
	stringTestRedBlackTree.Insert(9, "Mouse");
	stringTestRedBlackTree.Insert(2, "Stuart");
	stringTestRedBlackTree.PreorderPrint();

	cout << endl << "중위 순회 출력 (트리 A)" << endl;
	stringTestRedBlackTree.InorderPrint();

	cout << endl << "후위 순회 출력 (트리 A)" << endl;
	stringTestRedBlackTree.PostorderPrint();

	cout << endl << "검색 (트리 A)" << endl;
	string stringRetrievedData = "";
	stringTestRedBlackTree.Retrieve(3, stringRetrievedData);
	PrintKeyAndData(3, stringRetrievedData);

	cout << endl << "명시적 복사 (트리 A -> B)" << endl;
	RedBlackTree<string> stringExplicitCopyTestRedBlackTree;
	stringExplicitCopyTestRedBlackTree.CopyTree(stringTestRedBlackTree);
	stringExplicitCopyTestRedBlackTree.PreorderPrint();

	cout << endl << "복사 생성자 (트리 A -> C)" << endl;
	RedBlackTree<string> stringCopyConstructorTestRedBlackTree = stringTestRedBlackTree;
	stringCopyConstructorTestRedBlackTree.PreorderPrint();

	cout << endl << "복사 할당 연산자 (트리 A -> D)" << endl;
	RedBlackTree<string> stringCopyAssignmentTestRedBlackTree;
	stringCopyAssignmentTestRedBlackTree = stringTestRedBlackTree;
	stringCopyAssignmentTestRedBlackTree.PreorderPrint();

	cout << endl << "이동 생성자 (트리 C -> E)" << endl;
	RedBlackTree<string> stringMoveConstructorTestRedBlackTree = move(stringCopyConstructorTestRedBlackTree);
	stringMoveConstructorTestRedBlackTree.PreorderPrint();

	cout << endl << "이동 할당 연산자 (트리 D -> F)" << endl;
	RedBlackTree<string> stringMoveAssignmentTestRedBlackTree;
	stringMoveAssignmentTestRedBlackTree = move(stringCopyAssignmentTestRedBlackTree);
	stringMoveAssignmentTestRedBlackTree.PreorderPrint();

	cout << endl << "이동 후 소스 트리는 비워짐 (트리 C, D)" << endl;
	stringCopyConstructorTestRedBlackTree.PreorderPrint();
	stringCopyAssignmentTestRedBlackTree.PreorderPrint();

	cout << endl << "요소별 삭제 (트리 A)" << endl;
	stringTestRedBlackTree.Remove(7);
	stringTestRedBlackTree.PreorderPrint();

	cout << endl << "요소별 삭제 (트리 A)" << endl;
	stringTestRedBlackTree.Remove(3);
	stringTestRedBlackTree.PreorderPrint();

	cout << endl << "전체 삭제 (트리 A)" << endl;
	stringTestRedBlackTree.RemoveTree();
	stringTestRedBlackTree.PreorderPrint();

	cout << endl << "복사한 트리는 원본과 독립적임 (트리 B)" << endl;
	stringExplicitCopyTestRedBlackTree.PreorderPrint();
#endif

#ifndef _DEBUG
	cout << fixed << setprecision(2);

	cout << endl << "속도 테스트 1/4 : 랜덤 워크로드 테스트-------------------------------------------------------" << endl;

	/*	(테스팅 방법)
		randomWorkloadNum 횟수만큼 복사 삽입(트리 A), 이동 삽입(트리 B), 검색(트리 A), 삭제(트리 A)와 소멸(트리 B)을 수행함
		키는 [0,randomWorkloadNum-1] 의 중복되지 않는 키 값들을 랜덤하게 셔플해놓고 사용함(삽입, 검색, 삭제의 키 값들은 각각 독립으로 셔플됨)
		데이터는 randomWorkloadPerDataLen 으로 지정된 길이의 string 객체를 randomWorkloadNum 개 만들어놓고 사용함
	*/

	/*	(테스팅 결과)
		[randomWorkloadNum			= 10,000,000]
		[randomWorkloadPerDataLen	= 30]

		복사 삽입	: RedBlackTree = 26.45초	|	std::map = ??.??초
		이동 삽입	: RedBlackTree = 24.45초	|	std::map = ??.??초
		검색		: RedBlackTree = 12.47초	|	std::map = ??.??초
		삭제		: RedBlackTree = 오류발생	|	std::map = ??.??초
		소멸		: RedBlackTree = ??.??초	|	std::map = ??.??초
	*/

	/*	(테스팅 해석)
		삭제가 10% 정도 수행되고 있을 때 "Cannot Remove! Cannot find such target node!" 오류 출력됨
	*/

	constexpr int randomWorkloadNum = 10000000;
	constexpr int randomWorkloadPerDataLen = 30;
	RandomWorkloadSpeedTest(randomWorkloadNum, randomWorkloadPerDataLen);

	cout << endl << "속도 테스트 2/4 : 랜덤 로컬 워크로드 테스트--------------------------------------------------" << endl;

	/*	(테스팅 방법)
		앞선 1번 랜덤 워크로드 테스트와 비슷하나, 키 값들이 localBlockSize 단위로 내부에서 선형 증가 연속성을 가지도록 하였음
	*/

	/*	(테스팅 결과)
		[randomLocalWorkloadNum			= 앞선 1번 랜덤 워크로드 테스트와 동일]
		[randomLocalWorkloadPerDataLen	= 앞선 1번 랜덤 워크로드 테스트와 동일]
		[localBlockSize					= 10]

		복사 삽입	: RedBlackTree = ??.??초	|	std::map = ??.??초
		이동 삽입	: RedBlackTree = ??.??초	|	std::map = ??.??초
		검색		: RedBlackTree = ??.??초	|	std::map = ??.??초
		삭제		: RedBlackTree = ??.??초	|	std::map = ??.??초
		소멸		: RedBlackTree = ??.??초	|	std::map = ??.??초
	*/

	/*	(테스팅 해석)
		앞선 테스트의 오류로 측정 불가함
	*/

	constexpr int randomLocalWorkloadNum = randomWorkloadNum;
	constexpr int randomLocalWorkloadPerDataLen = randomWorkloadPerDataLen;
	constexpr int localBlockSize = 10;
	RandomLocalWorkloadTest(randomLocalWorkloadNum, randomLocalWorkloadPerDataLen, localBlockSize);

	cout << endl << "속도 테스트 3/4 : 선형 증가 워크로드 테스트--------------------------------------------------" << endl;

	/*	(테스팅 방법)
		앞선 1번 랜덤 워크로드 테스트와 비슷하나, 키값들을 뒤섞지 않고 선형 그대로 사용함
	*/

	/*	(테스팅 결과)
		[linearIncreaseWorkloadNum			= 앞선 1번 랜덤 워크로드 테스트와 동일]
		[linearIncreaseWorkloadPerDataLen	= 앞선 1번 랜덤 워크로드 테스트와 동일]

		복사 삽입	: RedBlackTree = ??.??초	|	std::map = ??.??초
		이동 삽입	: RedBlackTree = ??.??초	|	std::map = ??.??초
		검색		: RedBlackTree = ??.??초	|	std::map = ??.??초
		삭제		: RedBlackTree = ??.??초	|	std::map = ??.??초
		소멸		: RedBlackTree = ??.??초	|	std::map = ??.??초
	*/

	/*	(테스팅 해석)
		앞선 테스트의 오류로 측정 불가함
	*/

	constexpr int linearIncreaseWorkloadNum = randomWorkloadNum;
	constexpr int linearIncreaseWorkloadPerDataLen = randomWorkloadPerDataLen;
	LinearIncreaseWorkloadTest(linearIncreaseWorkloadNum, linearIncreaseWorkloadPerDataLen);

	cout << endl << "속도 테스트 4/4 : 선형 감소 워크로드 테스트--------------------------------------------------" << endl;

	/*	(테스팅 방법)
		앞선 3번 선형 증가 워크로드 테스트와 비슷하나, 키를 역순으로 사용함
	*/

	/*	(테스팅 결과)
		[linearDecreaseWorkloadNum			= 앞선 1번 랜덤 워크로드 테스트와 동일]
		[linearDecreaseWorkloadPerDataLen	= 앞선 1번 랜덤 워크로드 테스트와 동일]

		복사 삽입	: RedBlackTree = ??.??초	|	std::map = ??.??초
		이동 삽입	: RedBlackTree = ??.??초	|	std::map = ??.??초
		검색		: RedBlackTree = ??.??초	|	std::map = ??.??초
		삭제		: RedBlackTree = ??.??초	|	std::map = ??.??초
		소멸		: RedBlackTree = ??.??초	|	std::map = ??.??초
	*/

	/*	(테스팅 해석)
		앞선 테스트의 오류로 측정 불가함
	*/

	constexpr int linearDecreaseWorkloadNum = randomWorkloadNum;
	constexpr int linearDecreaseWorkloadPerDataLen = randomWorkloadPerDataLen;
	LinearDecreaseWorkloadTest(linearDecreaseWorkloadNum, linearDecreaseWorkloadPerDataLen);
#endif

	cout << endl << "테스트 종료----------------------------------------------------------------------------------" << endl;

	return 0;
}

template <typename DataType>
void PrintKeyAndData(int key, const DataType& retrievedData)
{
	cout << "검색한 키 : " << key << " / 검색된 데이터 : " << retrievedData << endl;
}

void RandomWorkloadSpeedTest(int workloadNum, int workloadPerDataLen)
{
	cout << endl << "랜덤 워크로드 준비 중...." << endl;

	vector<string> insertDataWorkload;
	insertDataWorkload.reserve(workloadNum);
	for (int i = 0; i < workloadNum; i++)
	{
		insertDataWorkload.emplace_back(string(workloadPerDataLen, 'A'));
	}

	vector<int> insertKeyWorkload(workloadNum);
	iota(insertKeyWorkload.begin(), insertKeyWorkload.end(), 0);
	mt19937 insertTestRng(123456);
	shuffle(insertKeyWorkload.begin(), insertKeyWorkload.end(), insertTestRng);

	vector<int> retrieveKeyWorkload(workloadNum);
	iota(retrieveKeyWorkload.begin(), retrieveKeyWorkload.end(), 0);
	mt19937 retrieveTestRng(654321);
	shuffle(retrieveKeyWorkload.begin(), retrieveKeyWorkload.end(), retrieveTestRng);

	vector<int> removeKeyWorkload(workloadNum);
	iota(removeKeyWorkload.begin(), removeKeyWorkload.end(), 0);
	mt19937 removeTestRng(162534);
	shuffle(removeKeyWorkload.begin(), removeKeyWorkload.end(), removeTestRng);

	steady_clock clock;
	time_point<steady_clock> timeBegin;
	time_point<steady_clock> timeEnd;
	duration<double> timeDiff;

	cout << endl << "랜덤 워크로드 복사 중...." << endl;
	timeBegin = TestRedBlackTree(clock, workloadNum, insertDataWorkload, insertKeyWorkload, retrieveKeyWorkload, removeKeyWorkload);

	timeEnd = clock.now();
	timeDiff = timeEnd - timeBegin;

	cout << endl << "RedBlackTree : " << workloadNum << "번의 소멸자 동안 흐른 시간은 : " << timeDiff.count() << " 초" << endl;

	cout << endl << "---------------------------------------------------------------------------" << endl;

	cout << endl << "랜덤 워크로드 복사 중...." << endl;
	timeBegin = TestMap(clock, workloadNum, insertDataWorkload, insertKeyWorkload, retrieveKeyWorkload, removeKeyWorkload);

	timeEnd = clock.now();
	timeDiff = timeEnd - timeBegin;

	cout << endl << "map : " << workloadNum << "번의 소멸자 동안 흐른 시간은 : " << timeDiff.count() << " 초" << endl;

	cout << endl << endl << endl << endl << endl;
}

void RandomLocalWorkloadTest(int workloadNum, int workloadPerDataLen, int localBlockSize)
{
	cout << endl << "랜덤 로컬 워크로드 준비 중...." << endl;

	vector<string> insertDataWorkload;
	insertDataWorkload.reserve(workloadNum);
	for (int i = 0; i < workloadNum; i++)
	{
		insertDataWorkload.emplace_back(string(workloadPerDataLen, 'A'));
	}

	vector<int> insertTestKeyBlocks(workloadNum / localBlockSize);
	iota(insertTestKeyBlocks.begin(), insertTestKeyBlocks.end(), 0);
	mt19937 insertTestRng(123456);
	shuffle(insertTestKeyBlocks.begin(), insertTestKeyBlocks.end(), insertTestRng);
	vector<int> insertKeyWorkload;
	for (int blockIndex = 0; blockIndex < insertTestKeyBlocks.size(); blockIndex++)
	{
		for (int offset = 0; offset < localBlockSize; offset++)
		{
			insertKeyWorkload.push_back(insertTestKeyBlocks[blockIndex] * localBlockSize + offset);
		}
	}

	vector<int> retrieveTestKeyBlocks(workloadNum / localBlockSize);
	iota(retrieveTestKeyBlocks.begin(), retrieveTestKeyBlocks.end(), 0);
	mt19937 retrieveTestRng(654321);
	shuffle(retrieveTestKeyBlocks.begin(), retrieveTestKeyBlocks.end(), retrieveTestRng);
	vector<int> retrieveKeyWorkload;
	for (int blockIndex = 0; blockIndex < retrieveTestKeyBlocks.size(); blockIndex++)
	{
		for (int offset = 0; offset < localBlockSize; offset++)
		{
			retrieveKeyWorkload.push_back(retrieveTestKeyBlocks[blockIndex] * localBlockSize + offset);
		}
	}

	vector<int> removeTestKeyBlocks(workloadNum / localBlockSize);
	iota(removeTestKeyBlocks.begin(), removeTestKeyBlocks.end(), 0);
	mt19937 removeTestRng(162534);
	shuffle(removeTestKeyBlocks.begin(), removeTestKeyBlocks.end(), removeTestRng);
	vector<int> removeKeyWorkload;
	for (int blockIndex = 0; blockIndex < removeTestKeyBlocks.size(); blockIndex++)
	{
		for (int offset = 0; offset < localBlockSize; offset++)
		{
			removeKeyWorkload.push_back(removeTestKeyBlocks[blockIndex] * localBlockSize + offset);
		}
	}

	steady_clock clock;
	time_point<steady_clock> timeBegin;
	time_point<steady_clock> timeEnd;
	duration<double> timeDiff;

	int realWorkloadNum = (workloadNum / localBlockSize) * localBlockSize;

	cout << endl << "랜덤 로컬 워크로드 복사 중...." << endl;
	timeBegin = TestRedBlackTree(clock, realWorkloadNum, insertDataWorkload, insertKeyWorkload, retrieveKeyWorkload, removeKeyWorkload);

	timeEnd = clock.now();
	timeDiff = timeEnd - timeBegin;

	cout << endl << "RedBlackTree : " << realWorkloadNum << "번의 소멸자 동안 흐른 시간은 : " << timeDiff.count() << " 초" << endl;

	cout << endl << "---------------------------------------------------------------------------" << endl;

	cout << endl << "랜덤 로컬 워크로드 복사 중...." << endl;
	timeBegin = TestMap(clock, realWorkloadNum, insertDataWorkload, insertKeyWorkload, retrieveKeyWorkload, removeKeyWorkload);

	timeEnd = clock.now();
	timeDiff = timeEnd - timeBegin;

	cout << endl << "map : " << realWorkloadNum << "번의 소멸자 동안 흐른 시간은 : " << timeDiff.count() << " 초" << endl;

	cout << endl << endl << endl << endl << endl;
}

void LinearIncreaseWorkloadTest(int workloadNum, int workloadPerDataLen)
{
	cout << endl << "선형 증가 워크로드 준비 중...." << endl;

	vector<string> insertDataWorkload;
	insertDataWorkload.reserve(workloadNum);
	for (int i = 0; i < workloadNum; i++)
	{
		insertDataWorkload.emplace_back(string(workloadPerDataLen, 'A'));
	}

	vector<int> insertKeyWorkload(workloadNum);
	iota(insertKeyWorkload.begin(), insertKeyWorkload.end(), 0);

	vector<int> retrieveKeyWorkload = insertKeyWorkload;

	vector<int> removeKeyWorkload = insertKeyWorkload;

	steady_clock clock;
	time_point<steady_clock> timeBegin;
	time_point<steady_clock> timeEnd;
	duration<double> timeDiff;

	cout << endl << "선형 증가 워크로드 복사 중...." << endl;
	timeBegin = TestRedBlackTree(clock, workloadNum, insertDataWorkload, insertKeyWorkload, retrieveKeyWorkload, removeKeyWorkload);

	timeEnd = clock.now();
	timeDiff = timeEnd - timeBegin;

	cout << endl << "RedBlackTree : " << workloadNum << "번의 소멸자 동안 흐른 시간은 : " << timeDiff.count() << " 초" << endl;

	cout << endl << "---------------------------------------------------------------------------" << endl;

	cout << endl << "선형 증가 워크로드 복사 중...." << endl;
	timeBegin = TestMap(clock, workloadNum, insertDataWorkload, insertKeyWorkload, retrieveKeyWorkload, removeKeyWorkload);

	timeEnd = clock.now();
	timeDiff = timeEnd - timeBegin;

	cout << endl << "map : " << workloadNum << "번의 소멸자 동안 흐른 시간은 : " << timeDiff.count() << " 초" << endl;

	cout << endl << endl << endl << endl << endl;
}

void LinearDecreaseWorkloadTest(int workloadNum, int workloadPerDataLen)
{
	cout << endl << "선형 감소 워크로드 준비 중...." << endl;

	vector<string> insertDataWorkload;
	insertDataWorkload.reserve(workloadNum);
	for (int i = 0; i < workloadNum; i++)
	{
		insertDataWorkload.emplace_back(string(workloadPerDataLen, 'A'));
	}

	vector<int> insertKeyWorkload(workloadNum);
	iota(insertKeyWorkload.rbegin(), insertKeyWorkload.rend(), 0);

	vector<int> retrieveKeyWorkload = insertKeyWorkload;

	vector<int> removeKeyWorkload = insertKeyWorkload;

	steady_clock clock;
	time_point<steady_clock> timeBegin;
	time_point<steady_clock> timeEnd;
	duration<double> timeDiff;

	cout << endl << "선형 감소 워크로드 복사 중...." << endl;
	timeBegin = TestRedBlackTree(clock, workloadNum, insertDataWorkload, insertKeyWorkload, retrieveKeyWorkload, removeKeyWorkload);

	timeEnd = clock.now();
	timeDiff = timeEnd - timeBegin;

	cout << endl << "RedBlackTree : " << workloadNum << "번의 소멸자 동안 흐른 시간은 : " << timeDiff.count() << " 초" << endl;

	cout << endl << "---------------------------------------------------------------------------" << endl;

	cout << endl << "선형 감소 워크로드 복사 중...." << endl;
	timeBegin = TestMap(clock, workloadNum, insertDataWorkload, insertKeyWorkload, retrieveKeyWorkload, removeKeyWorkload);

	timeEnd = clock.now();
	timeDiff = timeEnd - timeBegin;

	cout << endl << "map : " << workloadNum << "번의 소멸자 동안 흐른 시간은 : " << timeDiff.count() << " 초" << endl;

	cout << endl << endl << endl << endl << endl;
}


time_point<steady_clock> TestRedBlackTree(steady_clock& clock, int workloadNum, vector<string> insertDataWorkload, const vector<int>& insertKeyWorkload, const vector<int>& retrieveKeyWorkload, const vector<int>& removeKeyWorkload)
{
	RedBlackTree<string> copyInsertTestRedBlackTree;
	RedBlackTree<string> moveInsertTestRedBlackTree;

	time_point<steady_clock> timeBegin;
	time_point<steady_clock> timeEnd;
	duration<double> timeDiff;

	cout << endl << "[RedBlackTree 복사 삽입 측정 시작]" << endl;
	cout << endl << "|------------------------------------------------|" << endl;

	timeBegin = clock.now();

	for (int i = 0; i < workloadNum; i++)
	{
		if (i % (workloadNum / 50) == 0)
		{
			cout << "*";
		}

		if (i % 10000 == 0)
		{
			timeEnd = clock.now();
			timeDiff = timeEnd - timeBegin;
			if (timeDiff.count() > 50)
			{
				break;
			}
		}

		copyInsertTestRedBlackTree.Insert(insertKeyWorkload[i], insertDataWorkload[i]);
	}
	cout << endl;

	timeEnd = clock.now();
	timeDiff = timeEnd - timeBegin;

	if (timeDiff.count() < 50)
	{
		cout << endl << "RedBlackTree : " << workloadNum << "번의 복사 삽입 동안 흐른 시간은 : " << timeDiff.count() << " 초" << endl;
	}
	else
	{
		cout << endl << "RedBlackTree : " << workloadNum << "번의 복사 삽입 동안 흐른 시간은 : 50+ 초(시간 초과)" << endl;
	}

	cout << endl << "[RedBlackTree 이동 삽입 측정 시작]" << endl;
	cout << endl << "|------------------------------------------------|" << endl;

	timeBegin = clock.now();

	for (int i = 0; i < workloadNum; i++)
	{
		if (i % (workloadNum / 50) == 0)
		{
			cout << "*";
		}

		if (i % 10000 == 0)
		{
			timeEnd = clock.now();
			timeDiff = timeEnd - timeBegin;
			if (timeDiff.count() > 50)
			{
				break;
			}
		}

		moveInsertTestRedBlackTree.Insert(insertKeyWorkload[i], move(insertDataWorkload[i]));
	}
	cout << endl;

	timeEnd = clock.now();
	timeDiff = timeEnd - timeBegin;

	if (timeDiff.count() < 50)
	{
		cout << endl << "RedBlackTree : " << workloadNum << "번의 이동 삽입 동안 흐른 시간은 : " << timeDiff.count() << " 초" << endl;
	}
	else
	{
		cout << endl << "RedBlackTree : " << workloadNum << "번의 이동 삽입 동안 흐른 시간은 : 50+ 초(시간 초과)" << endl;
	}

	string retrievedData;

	cout << endl << "[RedBlackTree 검색 측정 시작]" << endl;
	cout << endl << "|------------------------------------------------|" << endl;

	timeBegin = clock.now();

	for (int i = 0; i < workloadNum; i++)
	{
		if (i % (workloadNum / 50) == 0)
		{
			cout << "*";
		}

		if (i % 10000 == 0)
		{
			timeEnd = clock.now();
			timeDiff = timeEnd - timeBegin;
			if (timeDiff.count() > 50)
			{
				break;
			}
		}

		copyInsertTestRedBlackTree.Retrieve(insertKeyWorkload[i], retrievedData);
		retrievedData += 'a';			//NOTE : 컴파일, 링킹 최적화로 테스트 중의 검색 메소드 호출이 건너뛰어지는 경우가 없도록 하기 위한 추가 명령문임
	}
	cout << endl;

	if (timeDiff.count() < 50)
	{
		cout << endl << "RedBlackTree : " << workloadNum << "번의 검색 동안 흐른 시간은 : " << timeDiff.count() << " 초" << endl;
	}
	else
	{
		cout << endl << "RedBlackTree : " << workloadNum << "번의 검색 동안 흐른 시간은 : 50+ 초(시간 초과)" << endl;
	}

	cout << endl << "[RedBlackTree 삭제 측정 시작]" << endl;
	cout << endl << "|------------------------------------------------|" << endl;

	timeBegin = clock.now();

	for (int i = 0; i < workloadNum; i++)
	{
		if (i % (workloadNum / 50) == 0)
		{
			cout << "*";
		}

		if (i % 10000 == 0)
		{
			timeEnd = clock.now();
			timeDiff = timeEnd - timeBegin;
			if (timeDiff.count() > 50)
			{
				break;
			}
		}

		copyInsertTestRedBlackTree.Remove(removeKeyWorkload[i]);
	}
	cout << endl;

	timeEnd = clock.now();
	timeDiff = timeEnd - timeBegin;

	if (timeDiff.count() < 50)
	{
		cout << endl << "RedBlackTree : " << workloadNum << "번의 삭제 동안 흐른 시간은 : " << timeDiff.count() << " 초" << endl;
	}
	else
	{
		cout << endl << "RedBlackTree : " << workloadNum << "번의 삭제 동안 흐른 시간은 : 50+ 초(시간 초과)" << endl;
	}

	cout << endl << "[RedBlackTree 소멸자 측정 시작]" << endl;
	return clock.now();
}

time_point<steady_clock> TestMap(steady_clock& clock, int workloadNum, vector<string> insertDataWorkload, const vector<int>& insertKeyWorkload, const vector<int>& retrieveKeyWorkload, const vector<int>& removeKeyWorkload)
{
	map<int, string> copyInsertTestMap;
	map<int, string> moveInsertTestMap;

	time_point<steady_clock> timeBegin;
	time_point<steady_clock> timeEnd;
	duration<double> timeDiff;

	cout << endl << "[map 복사 삽입 측정 시작]" << endl;
	cout << endl << "|------------------------------------------------|" << endl;

	timeBegin = clock.now();

	for (int i = 0; i < workloadNum; i++)
	{
		if (i % (workloadNum / 50) == 0)
		{
			cout << "*";
		}

		if (i % 10000 == 0)
		{
			timeEnd = clock.now();
			timeDiff = timeEnd - timeBegin;
			if (timeDiff.count() > 50)
			{
				break;
			}
		}

		copyInsertTestMap.emplace(insertKeyWorkload[i], insertDataWorkload[i]);
	}
	cout << endl;

	timeEnd = clock.now();
	timeDiff = timeEnd - timeBegin;

	if (timeDiff.count() < 50)
	{
		cout << endl << "map : " << workloadNum << "번의 복사 삽입 동안 흐른 시간은 : " << timeDiff.count() << " 초" << endl;
	}
	else
	{
		cout << endl << "map : " << workloadNum << "번의 복사 삽입 동안 흐른 시간은 : 50+ 초(시간 초과)" << endl;
	}

	cout << endl << "[map 이동 삽입 측정 시작]" << endl;
	cout << endl << "|------------------------------------------------|" << endl;

	timeBegin = clock.now();

	for (int i = 0; i < workloadNum; i++)
	{
		if (i % (workloadNum / 50) == 0)
		{
			cout << "*";
		}

		if (i % 10000 == 0)
		{
			timeEnd = clock.now();
			timeDiff = timeEnd - timeBegin;
			if (timeDiff.count() > 50)
			{
				break;
			}
		}

		moveInsertTestMap.emplace(insertKeyWorkload[i], move(insertDataWorkload[i]));
	}
	cout << endl;

	timeEnd = clock.now();
	timeDiff = timeEnd - timeBegin;

	if (timeDiff.count() < 50)
	{
		cout << endl << "map : " << workloadNum << "번의 이동 삽입 동안 흐른 시간은 : " << timeDiff.count() << " 초" << endl;
	}
	else
	{
		cout << endl << "map : " << workloadNum << "번의 이동 삽입 동안 흐른 시간은 : 50+ 초(시간 초과)" << endl;
	}

	cout << endl << "[map 검색 측정 시작]" << endl;
	cout << endl << "|------------------------------------------------|" << endl;

	timeBegin = clock.now();

	for (int i = 0; i < workloadNum; i++)
	{
		if (i % (workloadNum / 50) == 0)
		{
			cout << "*";
		}

		if (i % 10000 == 0)
		{
			timeEnd = clock.now();
			timeDiff = timeEnd - timeBegin;
			if (timeDiff.count() > 50)
			{
				break;
			}
		}

		auto iterator = copyInsertTestMap.find(retrieveKeyWorkload[i]);
		iterator->second += 'a';			//NOTE : 컴파일, 링킹 최적화로 테스트 중의 검색 메소드 호출이 건너뛰어지는 경우가 없도록 하기 위한 추가 명령문임
	}
	cout << endl;

	timeEnd = clock.now();
	timeDiff = timeEnd - timeBegin;

	if (timeDiff.count() < 50)
	{
		cout << endl << "map : " << workloadNum << "번의 검색 동안 흐른 시간은 : " << timeDiff.count() << " 초" << endl;
	}
	else
	{
		cout << endl << "map : " << workloadNum << "번의 검색 동안 흐른 시간은 : 50+ 초(시간 초과)" << endl;
	}

	cout << endl << "[map 삭제 측정 시작]" << endl;
	cout << endl << "|------------------------------------------------|" << endl;

	timeBegin = clock.now();

	for (int i = 0; i < workloadNum; i++)
	{
		if (i % (workloadNum / 50) == 0)
		{
			cout << "*";
		}

		if (i % 10000 == 0)
		{
			timeEnd = clock.now();
			timeDiff = timeEnd - timeBegin;
			if (timeDiff.count() > 50)
			{
				break;
			}
		}

		copyInsertTestMap.erase(insertKeyWorkload[i]);
	}
	cout << endl;

	timeEnd = clock.now();
	timeDiff = timeEnd - timeBegin;

	if (timeDiff.count() < 50)
	{
		cout << endl << "map : " << workloadNum << "번의 삭제 동안 흐른 시간은 : " << timeDiff.count() << " 초" << endl;
	}
	else
	{
		cout << endl << "map : " << workloadNum << "번의 삭제 동안 흐른 시간은 : 50+ 초(시간 초과)" << endl;
	}

	cout << endl << "[map 소멸자 측정 시작]" << endl;
	return clock.now();
}