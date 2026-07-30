//로그 출력문들을 활성화하고 싶을 시 아래 구문의 주석을 해제할 것
//#define TREE_LOG	
//#define TREE_WARNING
//#define TREE_ERROR

#include "SplayTree.h"
#include <crtdbg.h>
#include <iostream>
#include <iomanip>
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

void RandomWorkloadTest(int workloadNum, int workloadPerDataLen);
void RandomLocalWorkloadTest(int workloadNum, int workloadPerDataLen, int localBlockSize);
void LinearIncreaseWorkloadTest(int workloadNum, int workloadPerDataLen);
void LinearDecreaseWorkloadTest(int workloadNum, int workloadPerDataLen);

//paramter : insertDataWorkload는 복사 비용이 크지만, 그럼에도 하나의 워크로드를 SplayTree와 map에 반복해서 사용할 수 있도록 값복사 형식의 매개변수를 사용함
time_point<steady_clock> TestSplayTree(steady_clock& clock, int workloadNum, vector<string> insertDataWorkload, const vector<int>& insertKeyWorkload, const vector<int>& retrieveKeyWorkload, const vector<int>& removeKeyWorkload);
time_point<steady_clock> TestMap(steady_clock& clock, int workloadNum, vector<string> insertDataWorkload, const vector<int>& insertKeyWorkload, const vector<int>& retrieveKeyWorkload, const vector<int>& removeKeyWorkload);

int main()
{
	//NOTE : 디버깅 실행이 종료될 시점에도 해제되지 않은 동적 메모리 누수가 존재할 시, Visual Studio의 하단의 출력창(output)에 해당 누수에 대한 정보가 출력됨
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	cout << endl << "기능 테스트 1/4 : Splaying-----------------------------------------------------------------------" << endl;

	SplayTree<int> splayingTestSplayTree;

	cout << endl << "삽입 5" << endl;
	splayingTestSplayTree.Insert(5, 55);
	splayingTestSplayTree.PreorderPrint();

	cout << endl << "삽입 9" << endl;
	splayingTestSplayTree.Insert(9, 99);
	splayingTestSplayTree.PreorderPrint();

	cout << endl << "삽입 8" << endl;
	splayingTestSplayTree.Insert(8, 88);
	splayingTestSplayTree.PreorderPrint();

	cout << endl << "삽입 7" << endl;
	splayingTestSplayTree.Insert(7, 77);
	splayingTestSplayTree.PreorderPrint();

	cout << endl << "삽입 1" << endl;
	splayingTestSplayTree.Insert(1, 11);
	splayingTestSplayTree.PreorderPrint();

	cout << endl << "삽입 2" << endl;
	splayingTestSplayTree.Insert(2, 22);
	splayingTestSplayTree.PreorderPrint();

	cout << endl << "삽입 3" << endl;
	splayingTestSplayTree.Insert(3, 33);
	splayingTestSplayTree.PreorderPrint();

	cout << endl << "검색 2" << endl;
	int out2 = 0;
	splayingTestSplayTree.Retrieve(2, out2);
	splayingTestSplayTree.PreorderPrint();

	cout << endl << "검색 5" << endl;
	int out5 = 0;
	splayingTestSplayTree.Retrieve(5, out5);
	splayingTestSplayTree.PreorderPrint();

	cout << endl << "검색 8" << endl;
	int out8 = 0;
	splayingTestSplayTree.Retrieve(8, out8);
	splayingTestSplayTree.PreorderPrint();

	cout << endl << "검색 1" << endl;
	int out1 = 0;
	splayingTestSplayTree.Retrieve(1, out1);
	splayingTestSplayTree.PreorderPrint();

	cout << endl << "검색 3" << endl;
	int out3 = 0;
	splayingTestSplayTree.Retrieve(3, out3);
	splayingTestSplayTree.PreorderPrint();

	cout << endl << "검색 7" << endl;
	int out7 = 0;
	splayingTestSplayTree.Retrieve(7, out7);
	splayingTestSplayTree.PreorderPrint();

	cout << endl << "검색 9" << endl;
	int out9 = 0;
	splayingTestSplayTree.Retrieve(9, out9);
	splayingTestSplayTree.PreorderPrint();

	cout << endl << "삭제 1" << endl;
	splayingTestSplayTree.Remove(1);
	splayingTestSplayTree.PreorderPrint();

	cout << endl << "삭제 2" << endl;
	splayingTestSplayTree.Remove(2);
	splayingTestSplayTree.PreorderPrint();

	cout << endl << "삭제 3" << endl;
	splayingTestSplayTree.Remove(3);
	splayingTestSplayTree.PreorderPrint();

	cout << endl << "삭제 5" << endl;
	splayingTestSplayTree.Remove(5);
	splayingTestSplayTree.PreorderPrint();

	cout << endl << "삭제 7" << endl;
	splayingTestSplayTree.Remove(7);
	splayingTestSplayTree.PreorderPrint();

	cout << endl << "삭제 8" << endl;
	splayingTestSplayTree.Remove(8);
	splayingTestSplayTree.PreorderPrint();

	cout << endl << "삭제 9" << endl;
	splayingTestSplayTree.Remove(9);
	splayingTestSplayTree.PreorderPrint();

	cout << endl << "기능 테스트 2/4 : SplayTree<int>-------------------------------------------------------------" << endl;

	SplayTree<int> intTestSplayTree;

	cout << endl << "삽입 (트리 A)" << endl;
	intTestSplayTree.Insert(5, 55);
	intTestSplayTree.Insert(7, 77);
	intTestSplayTree.Insert(3, 33);
	intTestSplayTree.Insert(4, 44);
	intTestSplayTree.Insert(6, 66);
	intTestSplayTree.Insert(9, 99);
	intTestSplayTree.Insert(2, 22);
	intTestSplayTree.PreorderPrint();

	cout << endl << "중위 순회 출력 (트리 A)" << endl;
	intTestSplayTree.InorderPrint();

	cout << endl << "후위 순회 출력 (트리 A)" << endl;
	intTestSplayTree.PostorderPrint();

	cout << endl << "검색 (트리 A)" << endl;
	int intRetrievedData = 0;
	intTestSplayTree.Retrieve(3, intRetrievedData);
	PrintKeyAndData(3, intRetrievedData);

	cout << endl << "명시적 복사 (트리 A -> B)" << endl;
	SplayTree<int> intExplicitCopyTestSplayTree;
	intExplicitCopyTestSplayTree.CopyTree(intTestSplayTree);
	intExplicitCopyTestSplayTree.PreorderPrint();

	cout << endl << "복사 생성자 (트리 A -> C)" << endl;
	SplayTree<int> intCopyConstructorTestSplayTree = intTestSplayTree;
	intCopyConstructorTestSplayTree.PreorderPrint();

	cout << endl << "복사 할당 연산자 (트리 A -> D)" << endl;
	SplayTree<int> intCopyAssignmentTestSplayTree;
	intCopyAssignmentTestSplayTree = intTestSplayTree;
	intCopyAssignmentTestSplayTree.PreorderPrint();

	cout << endl << "이동 생성자 (트리 C -> E)" << endl;
	SplayTree<int> intMoveConstructorTestSplayTree = move(intCopyConstructorTestSplayTree);
	intMoveConstructorTestSplayTree.PreorderPrint();

	cout << endl << "이동 할당 연산자 (트리 D -> F)" << endl;
	SplayTree<int> intMoveAssignmentTestSplayTree;
	intMoveAssignmentTestSplayTree = move(intCopyAssignmentTestSplayTree);
	intMoveAssignmentTestSplayTree.PreorderPrint();

	cout << endl << "이동 후 소스 트리는 비워짐 (트리 C, D)" << endl;
	intCopyConstructorTestSplayTree.PreorderPrint();
	intCopyAssignmentTestSplayTree.PreorderPrint();

	cout << endl << "요소별 삭제 (트리 A)" << endl;
	intTestSplayTree.Remove(7);
	intTestSplayTree.PreorderPrint();

	cout << endl << "요소별 삭제 (트리 A)" << endl;
	intTestSplayTree.Remove(3);
	intTestSplayTree.PreorderPrint();

	cout << endl << "전체 삭제 (트리 A)" << endl;
	intTestSplayTree.RemoveTree();
	intTestSplayTree.PreorderPrint();

	cout << endl << "복사한 트리는 원본과 독립적임 (트리 B)" << endl;
	intExplicitCopyTestSplayTree.PreorderPrint();

	cout << endl << "기능 테스트 3/4 : SplayTree<float>-----------------------------------------------------------" << endl;

	SplayTree<float> floatTestSplayTree;

	cout << endl << "삽입 (트리 A)" << endl;
	floatTestSplayTree.Insert(5, 0.55f);
	floatTestSplayTree.Insert(7, 0.77f);
	floatTestSplayTree.Insert(3, 0.33f);
	floatTestSplayTree.Insert(4, 0.44f);
	floatTestSplayTree.Insert(6, 0.66f);
	floatTestSplayTree.Insert(9, 0.99f);
	floatTestSplayTree.Insert(2, 0.22f);
	floatTestSplayTree.PreorderPrint();

	cout << endl << "중위 순회 출력 (트리 A)" << endl;
	floatTestSplayTree.InorderPrint();

	cout << endl << "후위 순회 출력 (트리 A)" << endl;
	floatTestSplayTree.PostorderPrint();

	cout << endl << "검색 (트리 A)" << endl;
	float floatRetrievedData = 0.0f;
	floatTestSplayTree.Retrieve(3, floatRetrievedData);
	PrintKeyAndData(3, floatRetrievedData);

	cout << endl << "명시적 복사 (트리 A -> B)" << endl;
	SplayTree<float> floatExplicitCopyTestSplayTree;
	floatExplicitCopyTestSplayTree.CopyTree(floatTestSplayTree);
	floatExplicitCopyTestSplayTree.PreorderPrint();

	cout << endl << "복사 생성자 (트리 A -> C)" << endl;
	SplayTree<float> floatCopyConstructorTestSplayTree = floatTestSplayTree;
	floatCopyConstructorTestSplayTree.PreorderPrint();

	cout << endl << "복사 할당 연산자 (트리 A -> D)" << endl;
	SplayTree<float> floatCopyAssignmentTestSplayTree;
	floatCopyAssignmentTestSplayTree = floatTestSplayTree;
	floatCopyAssignmentTestSplayTree.PreorderPrint();

	cout << endl << "이동 생성자 (트리 C -> E)" << endl;
	SplayTree<float> floatMoveConstructorTestSplayTree = move(floatCopyConstructorTestSplayTree);
	floatMoveConstructorTestSplayTree.PreorderPrint();

	cout << endl << "이동 할당 연산자 (트리 D -> F)" << endl;
	SplayTree<float> floatMoveAssignmentTestSplayTree;
	floatMoveAssignmentTestSplayTree = move(floatCopyAssignmentTestSplayTree);
	floatMoveAssignmentTestSplayTree.PreorderPrint();

	cout << endl << "이동 후 소스 트리는 비워짐 (트리 C, D)" << endl;
	floatCopyConstructorTestSplayTree.PreorderPrint();
	floatCopyAssignmentTestSplayTree.PreorderPrint();

	cout << endl << "요소별 삭제 (트리 A)" << endl;
	floatTestSplayTree.Remove(7);
	floatTestSplayTree.PreorderPrint();

	cout << endl << "요소별 삭제 (트리 A)" << endl;
	floatTestSplayTree.Remove(3);
	floatTestSplayTree.PreorderPrint();

	cout << endl << "전체 삭제 (트리 A)" << endl;
	floatTestSplayTree.RemoveTree();
	floatTestSplayTree.PreorderPrint();

	cout << endl << "복사한 트리는 원본과 독립적임 (트리 B)" << endl;
	floatExplicitCopyTestSplayTree.PreorderPrint();

	cout << endl << "기능 테스트 4/4 : SplayTree<string>----------------------------------------------------------" << endl;

	SplayTree<string> stringTestSplayTree;

	cout << endl << "삽입 (트리 A)" << endl;
	stringTestSplayTree.Insert(5, "Panther");
	stringTestSplayTree.Insert(7, "Comet");
	stringTestSplayTree.Insert(3, "Crusader");
	stringTestSplayTree.Insert(4, "Sherman");
	stringTestSplayTree.Insert(6, "Tiger");
	stringTestSplayTree.Insert(9, "Mouse");
	stringTestSplayTree.Insert(2, "Stuart");
	stringTestSplayTree.PreorderPrint();

	cout << endl << "중위 순회 출력 (트리 A)" << endl;
	stringTestSplayTree.InorderPrint();

	cout << endl << "후위 순회 출력 (트리 A)" << endl;
	stringTestSplayTree.PostorderPrint();

	cout << endl << "검색 (트리 A)" << endl;
	string stringRetrievedData = "";
	stringTestSplayTree.Retrieve(3, stringRetrievedData);
	PrintKeyAndData(3, stringRetrievedData);

	cout << endl << "명시적 복사 (트리 A -> B)" << endl;
	SplayTree<string> stringExplicitCopyTestSplayTree;
	stringExplicitCopyTestSplayTree.CopyTree(stringTestSplayTree);
	stringExplicitCopyTestSplayTree.PreorderPrint();

	cout << endl << "복사 생성자 (트리 A -> C)" << endl;
	SplayTree<string> stringCopyConstructorTestSplayTree = stringTestSplayTree;
	stringCopyConstructorTestSplayTree.PreorderPrint();

	cout << endl << "복사 할당 연산자 (트리 A -> D)" << endl;
	SplayTree<string> stringCopyAssignmentTestSplayTree;
	stringCopyAssignmentTestSplayTree = stringTestSplayTree;
	stringCopyAssignmentTestSplayTree.PreorderPrint();

	cout << endl << "이동 생성자 (트리 C -> E)" << endl;
	SplayTree<string> stringMoveConstructorTestSplayTree = move(stringCopyConstructorTestSplayTree);
	stringMoveConstructorTestSplayTree.PreorderPrint();

	cout << endl << "이동 할당 연산자 (트리 D -> F)" << endl;
	SplayTree<string> stringMoveAssignmentTestSplayTree;
	stringMoveAssignmentTestSplayTree = move(stringCopyAssignmentTestSplayTree);
	stringMoveAssignmentTestSplayTree.PreorderPrint();

	cout << endl << "이동 후 소스 트리는 비워짐 (트리 C, D)" << endl;
	stringCopyConstructorTestSplayTree.PreorderPrint();
	stringCopyAssignmentTestSplayTree.PreorderPrint();

	cout << endl << "요소별 삭제 (트리 A)" << endl;
	stringTestSplayTree.Remove(7);
	stringTestSplayTree.PreorderPrint();

	cout << endl << "요소별 삭제 (트리 A)" << endl;
	stringTestSplayTree.Remove(3);
	stringTestSplayTree.PreorderPrint();

	cout << endl << "전체 삭제 (트리 A)" << endl;
	stringTestSplayTree.RemoveTree();
	stringTestSplayTree.PreorderPrint();

	cout << endl << "복사한 트리는 원본과 독립적임 (트리 B)" << endl;
	stringExplicitCopyTestSplayTree.PreorderPrint();
#endif

#ifndef _DEBUG
	cout << fixed << setprecision(2);

	cout << endl << "속도 테스트 1/4 : 랜덤 워크로드 테스트-------------------------------------------------------" << endl;

	constexpr int randomWorkloadNum = 10000000;
	constexpr int randomWorkloadPerDataLen = 30;
	RandomWorkloadTest(randomWorkloadNum, randomWorkloadPerDataLen);

	cout << endl << "속도 테스트 2/4 : 랜덤 로컬 워크로드 테스트--------------------------------------------------" << endl;

	constexpr int randomLocalWorkloadNum = randomWorkloadNum;
	constexpr int randomLocalWorkloadPerDataLen	= randomWorkloadPerDataLen;
	constexpr int localBlockSize = 10;
	RandomLocalWorkloadTest(randomLocalWorkloadNum, randomLocalWorkloadPerDataLen, localBlockSize);

	cout << endl << "속도 테스트 3/4 : 선형 증가 워크로드 테스트--------------------------------------------------" << endl;

	constexpr int linearIncreaseWorkloadNum = randomWorkloadNum;
	constexpr int linearIncreaseWorkloadPerDataLen = randomWorkloadPerDataLen;
	LinearIncreaseWorkloadTest(linearIncreaseWorkloadNum, linearIncreaseWorkloadPerDataLen);

	cout << endl << "속도 테스트 4/4 : 선형 감소 워크로드 테스트--------------------------------------------------" << endl;

	constexpr int linearDecreaseWorkloadNum = randomWorkloadNum;
	constexpr int linearDecreaseWorkloadPerDataLen = randomWorkloadPerDataLen;
	LinearDecreaseWorkloadTest(linearDecreaseWorkloadNum, linearDecreaseWorkloadPerDataLen);
#endif

	cout << endl << "테스트 종료-----------------------------------------------------------------------------------------" << endl;

	return 0;
}

template <typename DataType>
void PrintKeyAndData(int key, const DataType& retrievedData)
{
	cout << "검색한 키 : " << key << " / 검색된 데이터 : " << retrievedData << endl;
}

void RandomWorkloadTest(int workloadNum, int workloadPerDataLen)
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
	timeBegin = TestSplayTree(clock, workloadNum, insertDataWorkload, insertKeyWorkload, retrieveKeyWorkload, removeKeyWorkload);

	timeEnd = clock.now();
	timeDiff = timeEnd - timeBegin;

	cout << endl << "SplayTree : " << workloadNum << "번의 소멸자 동안 흐른 시간은 : " << timeDiff.count() << " 초" << endl;

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

	vector<int> insertTestKeyBlocks(workloadNum/localBlockSize);
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
	timeBegin = TestSplayTree(clock, realWorkloadNum, insertDataWorkload, insertKeyWorkload, retrieveKeyWorkload, removeKeyWorkload);

	timeEnd = clock.now();
	timeDiff = timeEnd - timeBegin;

	cout << endl << "SplayTree : " << realWorkloadNum << "번의 소멸자 동안 흐른 시간은 : " << timeDiff.count() << " 초" << endl;

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
	timeBegin = TestSplayTree(clock, workloadNum, insertDataWorkload, insertKeyWorkload, retrieveKeyWorkload, removeKeyWorkload);

	timeEnd = clock.now();
	timeDiff = timeEnd - timeBegin;

	cout << endl << "SplayTree : " << workloadNum << "번의 소멸자 동안 흐른 시간은 : " << timeDiff.count() << " 초" << endl;

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
	timeBegin = TestSplayTree(clock, workloadNum, insertDataWorkload, insertKeyWorkload, retrieveKeyWorkload, removeKeyWorkload);

	timeEnd = clock.now();
	timeDiff = timeEnd - timeBegin;

	cout << endl << "SplayTree : " << workloadNum << "번의 소멸자 동안 흐른 시간은 : " << timeDiff.count() << " 초" << endl;

	cout << endl << "---------------------------------------------------------------------------" << endl;

	cout << endl << "선형 감소 워크로드 복사 중...." << endl;
	timeBegin = TestMap(clock, workloadNum, insertDataWorkload, insertKeyWorkload, retrieveKeyWorkload, removeKeyWorkload);

	timeEnd = clock.now();
	timeDiff = timeEnd - timeBegin;

	cout << endl << "map : " << workloadNum << "번의 소멸자 동안 흐른 시간은 : " << timeDiff.count() << " 초" << endl;

	cout << endl << endl << endl << endl << endl;
}

time_point<steady_clock> TestSplayTree(steady_clock& clock, int workloadNum, vector<string> insertDataWorkload, const vector<int>& insertKeyWorkload, const vector<int>& retrieveKeyWorkload, const vector<int>& removeKeyWorkload)
{
	SplayTree<string> copyInsertTestSplayTree;
	SplayTree<string> moveInsertTestSplayTree;

	time_point<steady_clock> timeBegin;
	time_point<steady_clock> timeEnd;
	duration<double> timeDiff;

	cout << endl << "[SplayTree 복사 삽입 측정 시작]" << endl;
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

		copyInsertTestSplayTree.Insert(insertKeyWorkload[i], insertDataWorkload[i]);
	}
	cout << endl;

	timeEnd = clock.now();
	timeDiff = timeEnd - timeBegin;

	if (timeDiff.count() < 50)
	{
		cout << endl << "SplayTree : " << workloadNum << "번의 복사 삽입 동안 흐른 시간은 : " << timeDiff.count() << " 초" << endl;
	}
	else
	{
		cout << endl << "SplayTree : " << workloadNum << "번의 복사 삽입 동안 흐른 시간은 : 50+ 초(시간 초과)" << endl;
	}

	cout << endl << "[SplayTree 이동 삽입 측정 시작]" << endl;
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

		moveInsertTestSplayTree.Insert(insertKeyWorkload[i], move(insertDataWorkload[i]));
	}
	cout << endl;

	timeEnd = clock.now();
	timeDiff = timeEnd - timeBegin;

	if (timeDiff.count() < 50)
	{
		cout << endl << "SplayTree : " << workloadNum << "번의 이동 삽입 동안 흐른 시간은 : " << timeDiff.count() << " 초" << endl;
	}
	else
	{
		cout << endl << "SplayTree : " << workloadNum << "번의 이동 삽입 동안 흐른 시간은 : 50+ 초(시간 초과)" << endl;
	}

	string retrievedData;

	cout << endl << "[SplayTree 검색 측정 시작]" << endl;
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

		copyInsertTestSplayTree.Retrieve(insertKeyWorkload[i], retrievedData);
		retrievedData += 'a';			//NOTE : 컴파일, 링킹 최적화로 테스트 중의 검색 메소드 호출이 건너뛰어지는 경우가 없도록 하기 위한 추가 명령문임
	}
	cout << endl;

	if (timeDiff.count() < 50)
	{
		cout << endl << "SplayTree : " << workloadNum << "번의 검색 동안 흐른 시간은 : " << timeDiff.count() << " 초" << endl;
	}
	else
	{
		cout << endl << "SplayTree : " << workloadNum << "번의 검색 동안 흐른 시간은 : 50+ 초(시간 초과)" << endl;
	}

	cout << endl << "[SplayTree 삭제 측정 시작]" << endl;
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

		copyInsertTestSplayTree.Remove(removeKeyWorkload[i]);
	}
	cout << endl;

	timeEnd = clock.now();
	timeDiff = timeEnd - timeBegin;

	if (timeDiff.count() < 50)
	{
		cout << endl << "SplayTree : " << workloadNum << "번의 삭제 동안 흐른 시간은 : " << timeDiff.count() << " 초" << endl;
	}
	else
	{
		cout << endl << "SplayTree : " << workloadNum << "번의 삭제 동안 흐른 시간은 : 50+ 초(시간 초과)" << endl;
	}

	cout << endl << "[SplayTree 소멸자 측정 시작]" << endl;
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