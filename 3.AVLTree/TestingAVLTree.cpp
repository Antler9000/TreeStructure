//로그 출력문들을 활성화하고 싶을 시 아래 구문의 주석을 해제할 것
//#define TREE_LOG	
//#define TREE_WARNING
//#define TREE_ERROR

#include "AVLTree.h"
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

//NOTE	: insertDataWorkload는 복사 비용이 크지만, 그럼에도 하나의 워크로드를 AVLTree와 map에 반복해서 사용할 수 있도록 값복사 형식의 매개변수를 사용함
time_point<steady_clock> TestAVLTree(steady_clock& clock, int workloadNum, vector<string> insertDataWorkload, const vector<int>& insertKeyWorkload, const vector<int>& retrieveKeyWorkload, const vector<int>& removeKeyWorkload);
time_point<steady_clock> TestMap(steady_clock& clock, int workloadNum, vector<string> insertDataWorkload, const vector<int>& insertKeyWorkload, const vector<int>& retrieveKeyWorkload, const vector<int>& removeKeyWorkload);

int main()
{
	//NOTE : 디버깅 실행이 종료될 시점에도 해제되지 않은 동적 메모리 누수가 존재할 시, Visual Studio의 하단의 출력창(output)에 해당 누수에 대한 정보가 출력됨
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	cout << endl << "기능 테스트 1/4 : 균형 유지 확인----------------------------------------------------------------" << endl;

	AVLTree<int> balancingTestAVLTree;

	cout << endl << "삽입 5" << endl;
	balancingTestAVLTree.Insert(5, 55);
	balancingTestAVLTree.PreorderPrint();

	cout << endl << "삽입 9" << endl;
	balancingTestAVLTree.Insert(9, 99);
	balancingTestAVLTree.PreorderPrint();

	cout << endl << "삽입 8" << endl;
	balancingTestAVLTree.Insert(8, 88);
	balancingTestAVLTree.PreorderPrint();

	cout << endl << "삽입 7" << endl;
	balancingTestAVLTree.Insert(7, 77);
	balancingTestAVLTree.PreorderPrint();

	cout << endl << "삽입 1" << endl;
	balancingTestAVLTree.Insert(1, 11);
	balancingTestAVLTree.PreorderPrint();

	cout << endl << "삽입 2" << endl;
	balancingTestAVLTree.Insert(2, 22);
	balancingTestAVLTree.PreorderPrint();

	cout << endl << "삽입 3" << endl;
	balancingTestAVLTree.Insert(3, 33);
	balancingTestAVLTree.PreorderPrint();

	cout << endl << "삭제 1" << endl;
	balancingTestAVLTree.Remove(1);
	balancingTestAVLTree.PreorderPrint();

	cout << endl << "삭제 2" << endl;
	balancingTestAVLTree.Remove(2);
	balancingTestAVLTree.PreorderPrint();

	cout << endl << "삭제 3" << endl;
	balancingTestAVLTree.Remove(3);
	balancingTestAVLTree.PreorderPrint();

	cout << endl << "삭제 4" << endl;
	balancingTestAVLTree.Remove(5);
	balancingTestAVLTree.PreorderPrint();

	cout << endl << "삭제 7" << endl;
	balancingTestAVLTree.Remove(7);
	balancingTestAVLTree.PreorderPrint();

	cout << endl << "삭제 8" << endl;
	balancingTestAVLTree.Remove(8);
	balancingTestAVLTree.PreorderPrint();

	cout << endl << "삭제 9" << endl;
	balancingTestAVLTree.Remove(9);
	balancingTestAVLTree.PreorderPrint();

	cout << endl << "기능 테스트 2/4 : AVLTree<int>-------------------------------------------------------------------" << endl;

	AVLTree<int> intTestAVLTree;

	cout << endl << "삽입 (트리 A)" << endl;
	intTestAVLTree.Insert(5, 55);
	intTestAVLTree.Insert(7, 77);
	intTestAVLTree.Insert(3, 33);
	intTestAVLTree.Insert(4, 44);
	intTestAVLTree.Insert(6, 66);
	intTestAVLTree.Insert(9, 99);
	intTestAVLTree.Insert(2, 22);
	intTestAVLTree.PreorderPrint();

	cout << endl << "중위 순회 출력 (트리 A)" << endl;
	intTestAVLTree.InorderPrint();

	cout << endl << "후위 순회 출력 (트리 A)" << endl;
	intTestAVLTree.PostorderPrint();

	cout << endl << "검색 (트리 A)" << endl;
	int intRetrievedData = 0;
	intTestAVLTree.Retrieve(3, intRetrievedData);
	PrintKeyAndData(3, intRetrievedData);

	cout << endl << "명시적 복사 (트리 A -> B)" << endl;
	AVLTree<int> intExplicitCopyTestAVLTree;
	intExplicitCopyTestAVLTree.CopyTree(intTestAVLTree);
	intExplicitCopyTestAVLTree.PreorderPrint();

	cout << endl << "복사 생성자 (트리 A -> C)" << endl;
	AVLTree<int> intCopyConstructorTestAVLTree = intTestAVLTree;
	intCopyConstructorTestAVLTree.PreorderPrint();

	cout << endl << "복사 할당 연산자 (트리 A -> D)" << endl;
	AVLTree<int> intCopyAssignmentTestAVLTree;
	intCopyAssignmentTestAVLTree = intTestAVLTree;
	intCopyAssignmentTestAVLTree.PreorderPrint();

	cout << endl << "이동 생성자 (트리 C -> E)" << endl;
	AVLTree<int> intMoveConstructorTestAVLTree = move(intCopyConstructorTestAVLTree);
	intMoveConstructorTestAVLTree.PreorderPrint();

	cout << endl << "이동 할당 연산자 (트리 D -> F)" << endl;
	AVLTree<int> intMoveAssignmentTestAVLTree;
	intMoveAssignmentTestAVLTree = move(intCopyAssignmentTestAVLTree);
	intMoveAssignmentTestAVLTree.PreorderPrint();

	cout << endl << "이동 후 소스 트리는 비워짐 (트리 C, D)" << endl;
	intCopyConstructorTestAVLTree.PreorderPrint();
	intCopyAssignmentTestAVLTree.PreorderPrint();

	cout << endl << "요소별 삭제 (트리 A)" << endl;
	intTestAVLTree.Remove(7);
	intTestAVLTree.PreorderPrint();

	cout << endl << "요소별 삭제 (트리 A)" << endl;
	intTestAVLTree.Remove(3);
	intTestAVLTree.PreorderPrint();

	cout << endl << "전체 삭제 (트리 A)" << endl;
	intTestAVLTree.RemoveTree();
	intTestAVLTree.PreorderPrint();

	cout << endl << "복사한 트리는 원본과 독립적임 (트리 B)" << endl;
	intExplicitCopyTestAVLTree.PreorderPrint();

	cout << endl << "기능 테스트 3/4 : AVLTree<float>-----------------------------------------------------------------" << endl;

	AVLTree<float> floatTestAVLTree;

	cout << endl << "삽입 (트리 A)" << endl;
	floatTestAVLTree.Insert(5, 0.55f);
	floatTestAVLTree.Insert(7, 0.77f);
	floatTestAVLTree.Insert(3, 0.33f);
	floatTestAVLTree.Insert(4, 0.44f);
	floatTestAVLTree.Insert(6, 0.66f);
	floatTestAVLTree.Insert(9, 0.99f);
	floatTestAVLTree.Insert(2, 0.22f);
	floatTestAVLTree.PreorderPrint();

	cout << endl << "중위 순회 출력 (트리 A)" << endl;
	floatTestAVLTree.InorderPrint();

	cout << endl << "후위 순회 출력 (트리 A)" << endl;
	floatTestAVLTree.PostorderPrint();

	cout << endl << "검색 (트리 A)" << endl;
	float floatRetrievedData = 0.0f;
	floatTestAVLTree.Retrieve(3, floatRetrievedData);
	PrintKeyAndData(3, floatRetrievedData);

	cout << endl << "명시적 복사 (트리 A -> B)" << endl;
	AVLTree<float> floatExplicitCopyTestAVLTree;
	floatExplicitCopyTestAVLTree.CopyTree(floatTestAVLTree);
	floatExplicitCopyTestAVLTree.PreorderPrint();

	cout << endl << "복사 생성자 (트리 A -> C)" << endl;
	AVLTree<float> floatCopyConstructorTestAVLTree = floatTestAVLTree;
	floatCopyConstructorTestAVLTree.PreorderPrint();

	cout << endl << "복사 할당 연산자 (트리 A -> D)" << endl;
	AVLTree<float> floatCopyAssignmentTestAVLTree;
	floatCopyAssignmentTestAVLTree = floatTestAVLTree;
	floatCopyAssignmentTestAVLTree.PreorderPrint();

	cout << endl << "이동 생성자 (트리 C -> E)" << endl;
	AVLTree<float> floatMoveConstructorTestAVLTree = move(floatCopyConstructorTestAVLTree);
	floatMoveConstructorTestAVLTree.PreorderPrint();

	cout << endl << "이동 할당 연산자 (트리 D -> F)" << endl;
	AVLTree<float> floatMoveAssignmentTestAVLTree;
	floatMoveAssignmentTestAVLTree = move(floatCopyAssignmentTestAVLTree);
	floatMoveAssignmentTestAVLTree.PreorderPrint();

	cout << endl << "이동 후 소스 트리는 비워짐 (트리 C, D)" << endl;
	floatCopyConstructorTestAVLTree.PreorderPrint();
	floatCopyAssignmentTestAVLTree.PreorderPrint();

	cout << endl << "요소별 삭제 (트리 A)" << endl;
	floatTestAVLTree.Remove(7);
	floatTestAVLTree.PreorderPrint();

	cout << endl << "요소별 삭제 (트리 A)" << endl;
	floatTestAVLTree.Remove(3);
	floatTestAVLTree.PreorderPrint();

	cout << endl << "전체 삭제 (트리 A)" << endl;
	floatTestAVLTree.RemoveTree();
	floatTestAVLTree.PreorderPrint();

	cout << endl << "복사한 트리는 원본과 독립적임 (트리 B)" << endl;
	floatExplicitCopyTestAVLTree.PreorderPrint();

	cout << endl << "기능 테스트 4/4 : AVLTree<string>----------------------------------------------------------------" << endl;

	AVLTree<string> stringTestAVLTree;

	cout << endl << "삽입 (트리 A)" << endl;
	stringTestAVLTree.Insert(5, "Panther");
	stringTestAVLTree.Insert(7, "Comet");
	stringTestAVLTree.Insert(3, "Crusader");
	stringTestAVLTree.Insert(4, "Sherman");
	stringTestAVLTree.Insert(6, "Tiger");
	stringTestAVLTree.Insert(9, "Mouse");
	stringTestAVLTree.Insert(2, "Stuart");
	stringTestAVLTree.PreorderPrint();

	cout << endl << "중위 순회 출력 (트리 A)" << endl;
	stringTestAVLTree.InorderPrint();

	cout << endl << "후위 순회 출력 (트리 A)" << endl;
	stringTestAVLTree.PostorderPrint();

	cout << endl << "검색 (트리 A)" << endl;
	string stringRetrievedData = "";
	stringTestAVLTree.Retrieve(3, stringRetrievedData);
	PrintKeyAndData(3, stringRetrievedData);

	cout << endl << "명시적 복사 (트리 A -> B)" << endl;
	AVLTree<string> stringExplicitCopyTestAVLTree;
	stringExplicitCopyTestAVLTree.CopyTree(stringTestAVLTree);
	stringExplicitCopyTestAVLTree.PreorderPrint();

	cout << endl << "복사 생성자 (트리 A -> C)" << endl;
	AVLTree<string> stringCopyConstructorTestAVLTree = stringTestAVLTree;
	stringCopyConstructorTestAVLTree.PreorderPrint();

	cout << endl << "복사 할당 연산자 (트리 A -> D)" << endl;
	AVLTree<string> stringCopyAssignmentTestAVLTree;
	stringCopyAssignmentTestAVLTree = stringTestAVLTree;
	stringCopyAssignmentTestAVLTree.PreorderPrint();

	cout << endl << "이동 생성자 (트리 C -> E)" << endl;
	AVLTree<string> stringMoveConstructorTestAVLTree = move(stringCopyConstructorTestAVLTree);
	stringMoveConstructorTestAVLTree.PreorderPrint();

	cout << endl << "이동 할당 연산자 (트리 D -> F)" << endl;
	AVLTree<string> stringMoveAssignmentTestAVLTree;
	stringMoveAssignmentTestAVLTree = move(stringCopyAssignmentTestAVLTree);
	stringMoveAssignmentTestAVLTree.PreorderPrint();

	cout << endl << "이동 후 소스 트리는 비워짐 (트리 C, D)" << endl;
	stringCopyConstructorTestAVLTree.PreorderPrint();
	stringCopyAssignmentTestAVLTree.PreorderPrint();

	cout << endl << "요소별 삭제 (트리 A)" << endl;
	stringTestAVLTree.Remove(7);
	stringTestAVLTree.PreorderPrint();

	cout << endl << "요소별 삭제 (트리 A)" << endl;
	stringTestAVLTree.Remove(3);
	stringTestAVLTree.PreorderPrint();

	cout << endl << "전체 삭제 (트리 A)" << endl;
	stringTestAVLTree.RemoveTree();
	stringTestAVLTree.PreorderPrint();

	cout << endl << "복사한 트리는 원본과 독립적임 (트리 B)" << endl;
	stringExplicitCopyTestAVLTree.PreorderPrint();
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

		복사 삽입	: AVLTree = 22.83초	|	std::map = 14.24초
		이동 삽입	: AVLTree = 20.89초	|	std::map = 13.12초
		검색		: AVLTree = 11.79초	|	std::map = 15.05초
		삭제		: AVLTree = 24.85초	|	std::map = 17.52초
		소멸		: AVLTree =  4.46초	|	std::map =  4.37초
	*/

	/*	(테스팅 해석)
		삽입, 삭제 메소드의 속도가 std::map에 비해 크게 느린 것으로 보아 관련 메소드들을 최적화할 필요성이 있음
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

		복사 삽입	: AVLTree =  7.35초	|	std::map =  3.83초
		이동 삽입	: AVLTree =  7.00초	|	std::map =  3.23초
		검색		: AVLTree =  2.34초	|	std::map =  3.48초
		삭제		: AVLTree =  8.49초	|	std::map =  3.89초
		소멸		: AVLTree =  3.23초	|	std::map =  3.12초
	*/

	/*	(테스팅 해석)
		BST에서의 테스트와 비슷한 결과가 나왔으므로, 아무래도 캐시 히트율 차이로 인해 std::map과의 속도 차이가 난 듯함
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

		복사 삽입	: AVLTree =  4.98초	|	std::map =  1.95초
		이동 삽입	: AVLTree =  4.65초	|	std::map =  1.52초
		검색		: AVLTree =  0.66초	|	std::map =  0.70초
		삭제		: AVLTree =  4.05초	|	std::map =  1.86초
		소멸		: AVLTree =  0.97초 |	std::map =  0.93초
	*/

	/*	(테스팅 해석)
		균형이 유지되므로 이전 BST와 달리 삽입과 검색에서 시간 초과가 나지 않게 되었음
		그러나 랜덤 워크로드 테스트와 마찬가지로 회전 관련 로직들의 최적화가 필요함을 보임
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

		복사 삽입	: AVLTree =  5.00초	|	std::map =  1.82초
		이동 삽입	: AVLTree =  4.70초	|	std::map =  1.49초
		검색		: AVLTree =  0.67초	|	std::map =  0.64초
		삭제		: AVLTree = 10.07초	|	std::map =  2.18초
		소멸		: AVLTree =  1.06초 |	std::map =  1.34초
	*/

	/*	(테스팅 해석)
		선형 증가 워크로드 테스트와 비교해서 특이하게 삭제에서의 시간 소요가 2배로 늘어났음
		원인을 파악할 예정임
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
	timeBegin = TestAVLTree(clock, workloadNum, insertDataWorkload, insertKeyWorkload, retrieveKeyWorkload, removeKeyWorkload);

	timeEnd = clock.now();
	timeDiff = timeEnd - timeBegin;

	cout << endl << "AVLTree : " << workloadNum << "번의 소멸자 동안 흐른 시간은 : " << timeDiff.count() << " 초" << endl;

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
	timeBegin = TestAVLTree(clock, realWorkloadNum, insertDataWorkload, insertKeyWorkload, retrieveKeyWorkload, removeKeyWorkload);

	timeEnd = clock.now();
	timeDiff = timeEnd - timeBegin;

	cout << endl << "AVLTree : " << realWorkloadNum << "번의 소멸자 동안 흐른 시간은 : " << timeDiff.count() << " 초" << endl;

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
	timeBegin = TestAVLTree(clock, workloadNum, insertDataWorkload, insertKeyWorkload, retrieveKeyWorkload, removeKeyWorkload);

	timeEnd = clock.now();
	timeDiff = timeEnd - timeBegin;

	cout << endl << "AVLTree : " << workloadNum << "번의 소멸자 동안 흐른 시간은 : " << timeDiff.count() << " 초" << endl;

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
	timeBegin = TestAVLTree(clock, workloadNum, insertDataWorkload, insertKeyWorkload, retrieveKeyWorkload, removeKeyWorkload);

	timeEnd = clock.now();
	timeDiff = timeEnd - timeBegin;

	cout << endl << "AVLTree : " << workloadNum << "번의 소멸자 동안 흐른 시간은 : " << timeDiff.count() << " 초" << endl;

	cout << endl << "---------------------------------------------------------------------------" << endl;

	cout << endl << "선형 감소 워크로드 복사 중...." << endl;
	timeBegin = TestMap(clock, workloadNum, insertDataWorkload, insertKeyWorkload, retrieveKeyWorkload, removeKeyWorkload);

	timeEnd = clock.now();
	timeDiff = timeEnd - timeBegin;

	cout << endl << "map : " << workloadNum << "번의 소멸자 동안 흐른 시간은 : " << timeDiff.count() << " 초" << endl;

	cout << endl << endl << endl << endl << endl;
}


time_point<steady_clock> TestAVLTree(steady_clock& clock, int workloadNum, vector<string> insertDataWorkload, const vector<int>& insertKeyWorkload, const vector<int>& retrieveKeyWorkload, const vector<int>& removeKeyWorkload)
{
	AVLTree<string> copyInsertTestAVLTree;
	AVLTree<string> moveInsertTestAVLTree;

	time_point<steady_clock> timeBegin;
	time_point<steady_clock> timeEnd;
	duration<double> timeDiff;

	cout << endl << "[AVLTree 복사 삽입 측정 시작]" << endl;
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

		copyInsertTestAVLTree.Insert(insertKeyWorkload[i], insertDataWorkload[i]);
	}
	cout << endl;

	timeEnd = clock.now();
	timeDiff = timeEnd - timeBegin;

	if (timeDiff.count() < 50)
	{
		cout << endl << "AVLTree : " << workloadNum << "번의 복사 삽입 동안 흐른 시간은 : " << timeDiff.count() << " 초" << endl;
	}
	else
	{
		cout << endl << "AVLTree : " << workloadNum << "번의 복사 삽입 동안 흐른 시간은 : 50+ 초(시간 초과)" << endl;
	}

	cout << endl << "[AVLTree 이동 삽입 측정 시작]" << endl;
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

		moveInsertTestAVLTree.Insert(insertKeyWorkload[i], move(insertDataWorkload[i]));
	}
	cout << endl;

	timeEnd = clock.now();
	timeDiff = timeEnd - timeBegin;

	if (timeDiff.count() < 50)
	{
		cout << endl << "AVLTree : " << workloadNum << "번의 이동 삽입 동안 흐른 시간은 : " << timeDiff.count() << " 초" << endl;
	}
	else
	{
		cout << endl << "AVLTree : " << workloadNum << "번의 이동 삽입 동안 흐른 시간은 : 50+ 초(시간 초과)" << endl;
	}

	string retrievedData;

	cout << endl << "[AVLTree 검색 측정 시작]" << endl;
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

		copyInsertTestAVLTree.Retrieve(insertKeyWorkload[i], retrievedData);
		retrievedData += 'a';			//NOTE : 컴파일, 링킹 최적화로 테스트 중의 검색 메소드 호출이 건너뛰어지는 경우가 없도록 하기 위한 추가 명령문임
	}
	cout << endl;

	if (timeDiff.count() < 50)
	{
		cout << endl << "AVLTree : " << workloadNum << "번의 검색 동안 흐른 시간은 : " << timeDiff.count() << " 초" << endl;
	}
	else
	{
		cout << endl << "AVLTree : " << workloadNum << "번의 검색 동안 흐른 시간은 : 50+ 초(시간 초과)" << endl;
	}

	cout << endl << "[AVLTree 삭제 측정 시작]" << endl;
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

		copyInsertTestAVLTree.Remove(removeKeyWorkload[i]);
	}
	cout << endl;

	timeEnd = clock.now();
	timeDiff = timeEnd - timeBegin;

	if (timeDiff.count() < 50)
	{
		cout << endl << "AVLTree : " << workloadNum << "번의 삭제 동안 흐른 시간은 : " << timeDiff.count() << " 초" << endl;
	}
	else
	{
		cout << endl << "AVLTree : " << workloadNum << "번의 삭제 동안 흐른 시간은 : 50+ 초(시간 초과)" << endl;
	}

	cout << endl << "[AVLTree 소멸자 측정 시작]" << endl;
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