//디버그 출력문들을 활성화하고 싶을 시 아래 구문의 주석을 해제할 것
//#define TREE_LOG	
//#define TREE_ERROR
//#define TREE_WARNING

//디버깅 실행시(F5) 메모리 누수를 확인하고 싶으면 아래 구문의 주석을 해제할 것
#define MEMORY_DEBUG

//속도 테스트를 활성화하고 싶을 시 아래 구문의 주석을 해제할 것
#define RANDOM_WORKLOAD_SPEED_TEST
#define LINEAR_INCREASE_WORKLOAD_SPEED_TEST
#define LINEAR_DECREASE_WORKLOAD_SPEED_TEST

#include "BST_using_while.h"	//정의한 BST를 테스팅함
#include <chrono>;				//속도 테스트를 위해 사용함
#include <string>;				//..
#include <numeric>;				//..
#include <random>;				//..
#include <map>;					//..
using namespace chrono;			//..

template <typename DataType>
void PrintKeyAndData(const int key, const DataType retrievedData);

void RandomWorkloadSpeedTest(const int workloadNum, const int workloadPerDataLen);

void LinearIncreaseWorkloadSpeedTest(const int workloadNum, const int workloadPerDataLen);

void LinearDecreaseWorkloadSpeedTest(const int workloadNum, const int workloadPerDataLen);

//insertDataWorkload은 복사 비용이 크지만, 그럼에도 하나의 워크로드를 BST와 map에 반복해서 사용할 수 있도록 값복사가 일어나는 기본 인자로 둔다
time_point<steady_clock> SpeedTestBST(steady_clock& clock, const int workloadNum, vector<string> insertDataWorkload, const vector<int>& insertKeyWorkload, const vector<int>& retrieveKeyWorkload, const vector<int>& removeKeyWorkload);

time_point<steady_clock> SpeedTestMap(steady_clock& clock, const int workloadNum, vector<string> insertDataWorkload, const vector<int>& insertKeyWorkload, const vector<int>& retrieveKeyWorkload, const vector<int>& removeKeyWorkload);

int main()
{
//디버깅 실행시 메모리 누수를 확인한다. 누수가 존재할 시 Visual Studio의 하단에 위치한 출력(output)에 메모리 누수 정보가 출력된다
#ifdef MEMORY_DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	cout << endl << "testing 1 : BST<int>--------------------------------------------------------------------------" << endl;

	BST<int> intTestBST;

	cout << endl << "삽입 (트리 A)" << endl;
	intTestBST.Insert(5, 1515);
	intTestBST.Insert(7, 2727);
	intTestBST.Insert(3, 2323);
	intTestBST.Insert(4, 3434);
	intTestBST.Insert(6, 3636);
	intTestBST.Insert(9, 3939);
	intTestBST.Insert(2, 3232);
	intTestBST.PreorderPrint();

	cout << endl << "중위 순회 출력 (트리 A)" << endl;
	intTestBST.InorderPrint();

	cout << endl << "후위 순회 출력 (트리 A)" << endl;
	intTestBST.PostorderPrint();

	cout << endl << "검색 (트리 A)" << endl;
	int intRetrievedData = 0;
	intTestBST.Retrieve(3, intRetrievedData);
	PrintKeyAndData(3, intRetrievedData);

	cout << endl << "명시적 복사 (트리 A -> B)" << endl;
	BST<int> intExplicitCopyTestBST;
	intExplicitCopyTestBST.CopyTree(intTestBST);
	intExplicitCopyTestBST.PreorderPrint();

	cout << endl << "복사 생성자 (트리 A -> C)" << endl;
	BST<int> intCopyConstructorTestBST = intTestBST;
	intCopyConstructorTestBST.PreorderPrint();

	cout << endl << "복사 할당 연산자 (트리 A -> D)" << endl;
	BST<int> intCopyAssignmentTestBST;
	intCopyAssignmentTestBST = intTestBST;
	intCopyAssignmentTestBST.PreorderPrint();

	cout << endl << "이동 생성자 (트리 C -> E)" << endl;
	BST<int> intMoveConstructorTestBST = move(intCopyConstructorTestBST);
	intMoveConstructorTestBST.PreorderPrint();

	cout << endl << "이동 할당 연산자 (트리 D -> F)" << endl;
	BST<int> intMoveAssignmentTestBST;
	intMoveAssignmentTestBST = move(intCopyAssignmentTestBST);
	intMoveAssignmentTestBST.PreorderPrint();

	cout << endl << "이동 후 소스 트리는 비워짐 (트리 C, D)" << endl;
	intCopyConstructorTestBST.PreorderPrint();
	intCopyAssignmentTestBST.PreorderPrint();

	cout << endl << "요소별 삭제 (트리 A)" << endl;
	intTestBST.Remove(7);
	intTestBST.PreorderPrint();

	cout << endl << "요소별 삭제 (트리 A)" << endl;
	intTestBST.Remove(3);
	intTestBST.PreorderPrint();

	cout << endl << "전체 삭제 (트리 A)" << endl;
	intTestBST.RemoveTree();
	intTestBST.PreorderPrint();

	cout << endl << "복사한 트리는 원본과 독립적임 (트리 B)" << endl;
	intExplicitCopyTestBST.PreorderPrint();

	cout << endl << "testing 2 : BST<float>--------------------------------------------------------------------------" << endl;

	BST<float> floatTestBST;

	cout << endl << "삽입 (트리 A)" << endl;
	floatTestBST.Insert(5, 0.515f);
	floatTestBST.Insert(7, 0.727f);
	floatTestBST.Insert(3, 0.323f);
	floatTestBST.Insert(4, 0.434f);
	floatTestBST.Insert(6, 0.636f);
	floatTestBST.Insert(9, 0.939f);
	floatTestBST.Insert(2, 0.232f);
	floatTestBST.PreorderPrint();

	cout << endl << "중위 순회 출력 (트리 A)" << endl;
	floatTestBST.InorderPrint();

	cout << endl << "후위 순회 출력 (트리 A)" << endl;
	floatTestBST.PostorderPrint();

	cout << endl << "검색 (트리 A)" << endl;
	float floatRetrievedData = 0.0f;
	floatTestBST.Retrieve(3, floatRetrievedData);
	PrintKeyAndData(3, floatRetrievedData);

	cout << endl << "명시적 복사 (트리 A -> B)" << endl;
	BST<float> floatExplicitCopyTestBST;
	floatExplicitCopyTestBST.CopyTree(floatTestBST);
	floatExplicitCopyTestBST.PreorderPrint();

	cout << endl << "복사 생성자 (트리 A -> C)" << endl;
	BST<float> floatCopyConstructorTestBST = floatTestBST;
	floatCopyConstructorTestBST.PreorderPrint();

	cout << endl << "복사 할당 연산자 (트리 A -> D)" << endl;
	BST<float> floatCopyAssignmentTestBST;
	floatCopyAssignmentTestBST = floatTestBST;
	floatCopyAssignmentTestBST.PreorderPrint();

	cout << endl << "이동 생성자 (트리 C -> E)" << endl;
	BST<float> floatMoveConstructorTestBST = move(floatCopyConstructorTestBST);
	floatMoveConstructorTestBST.PreorderPrint();

	cout << endl << "이동 할당 연산자 (트리 D -> F)" << endl;
	BST<float> floatMoveAssignmentTestBST;
	floatMoveAssignmentTestBST = move(floatCopyAssignmentTestBST);
	floatMoveAssignmentTestBST.PreorderPrint();

	cout << endl << "이동 후 소스 트리는 비워짐 (트리 C, D)" << endl;
	floatCopyConstructorTestBST.PreorderPrint();
	floatCopyAssignmentTestBST.PreorderPrint();

	cout << endl << "요소별 삭제 (트리 A)" << endl;
	floatTestBST.Remove(7);
	floatTestBST.PreorderPrint();

	cout << endl << "요소별 삭제 (트리 A)" << endl;
	floatTestBST.Remove(3);
	floatTestBST.PreorderPrint();

	cout << endl << "전체 삭제 (트리 A)" << endl;
	floatTestBST.RemoveTree();
	floatTestBST.PreorderPrint();

	cout << endl << "복사한 트리는 원본과 독립적임 (트리 B)" << endl;
	floatExplicitCopyTestBST.PreorderPrint();

	cout << endl << "testing 3 : BST<string>--------------------------------------------------------------------------" << endl;

	BST<string> stringTestBST;

	cout << endl << "삽입 (트리 A)" << endl;
	stringTestBST.Insert(5, "Panther");
	stringTestBST.Insert(7, "Comet");
	stringTestBST.Insert(3, "Crusader");
	stringTestBST.Insert(4, "Sherman");
	stringTestBST.Insert(6, "Tiger");
	stringTestBST.Insert(9, "Mouse");
	stringTestBST.Insert(2, "Stuart");
	stringTestBST.PreorderPrint();

	cout << endl << "중위 순회 출력 (트리 A)" << endl;
	stringTestBST.InorderPrint();

	cout << endl << "후위 순회 출력 (트리 A)" << endl;
	stringTestBST.PostorderPrint();

	cout << endl << "검색 (트리 A)" << endl;
	string stringRetrievedData = "";
	stringTestBST.Retrieve(3, stringRetrievedData);
	PrintKeyAndData(3, stringRetrievedData);

	cout << endl << "명시적 복사 (트리 A -> B)" << endl;
	BST<string> stringExplicitCopyTestBST;
	stringExplicitCopyTestBST.CopyTree(stringTestBST);
	stringExplicitCopyTestBST.PreorderPrint();

	cout << endl << "복사 생성자 (트리 A -> C)" << endl;
	BST<string> stringCopyConstructorTestBST = stringTestBST;
	stringCopyConstructorTestBST.PreorderPrint();

	cout << endl << "복사 할당 연산자 (트리 A -> D)" << endl;
	BST<string> stringCopyAssignmentTestBST;
	stringCopyAssignmentTestBST = stringTestBST;
	stringCopyAssignmentTestBST.PreorderPrint();

	cout << endl << "이동 생성자 (트리 C -> E)" << endl;
	BST<string> stringMoveConstructorTestBST = move(stringCopyConstructorTestBST);
	stringMoveConstructorTestBST.PreorderPrint();

	cout << endl << "이동 할당 연산자 (트리 D -> F)" << endl;
	BST<string> stringMoveAssignmentTestBST;
	stringMoveAssignmentTestBST = move(stringCopyAssignmentTestBST);
	stringMoveAssignmentTestBST.PreorderPrint();

	cout << endl << "이동 후 소스 트리는 비워짐 (트리 C, D)" << endl;
	stringCopyConstructorTestBST.PreorderPrint();
	stringCopyAssignmentTestBST.PreorderPrint();

	cout << endl << "요소별 삭제 (트리 A)" << endl;
	stringTestBST.Remove(7);
	stringTestBST.PreorderPrint();

	cout << endl << "요소별 삭제 (트리 A)" << endl;
	stringTestBST.Remove(3);
	stringTestBST.PreorderPrint();

	cout << endl << "전체 삭제 (트리 A)" << endl;
	stringTestBST.RemoveTree();
	stringTestBST.PreorderPrint();

	cout << endl << "복사한 트리는 원본과 독립적임 (트리 B)" << endl;
	stringExplicitCopyTestBST.PreorderPrint();

	cout << endl << "testing 4 : Random Workload Speed Test---------------------------------------------------------" << endl;

	/*	(테스팅 환경)
		- 실행 방법						: 디버깅하지 않고 실행(Ctrl + F5)
		- CPU							: i5-13600KF, 3500Mhz, 14 코어, 20 논리 프로세서
		- RAM							: 32GB, DDR4
		- OS							: Windows 11, 버전 25H2, 빌드 26200.8039
		- IDE							: Microsoft Visual Studio Community 2022 (64 - bit) 버전 17.14.23
		- 플랫폼 도구 집합				: Visual Studio 2022 (v143)
		- C++ 언어 표준					: 기본값(ISO C++ 14 표준)
		- 컴파일러 버전					: x86용 Microsoft(R) C / C++ 최적화 컴파일러 버전 19.44.35222
		- 링커 스택 크기 설정			: 프로젝트 기본 설정(공란)
		- C / C++ 최적화 설정			: 최대 최적화(속도 우선)(/O2)
		- C / C++ 인라인 함수 확장		: 적합한 것 모두 확장(/Ob2)
		- C / C++ 내장 함수 사용		: 예(/Oi)
		- C / C++ 크기 또는 속도		: 코드 속도 우선(/Ot)
		- C / C++ 기본 런타임 검사		: 기본값
	*/

	/*	(테스팅 방법)
		하나의 트리에 randomWorkloadNum 횟수만큼 복사 삽입, 이동 삽입, 검색, 삭제과 트리의 소멸을 수행함
		키는 [0,randomWorkloadNum-1] 의 중복되지 않는 키 값들을 랜덤하게 셔플해놓고 사용함
		데이터는 randomWorkloadPerDataLen 으로 지정된 길이의 string 객체를 randomWorkloadNum 개 만들어놓고 사용함
	*/

	/*	(테스팅 결과)
		(randomWorkloadNum = 10,000,000  |  randomWorkloadPerDataLen = 30)
		복사 삽입	: BST = 23.8초	|	std::map = 26.0초
		이동 삽입	: BST = 21.3초	|	std::map = 23.4초
		검색		: BST = 17.9초	|	std::map = 19.4초
		삭제		: BST = 33.7초	|	std::map = 28.6초
		소멸		: BST = 16.1초	|	std::map = 19.8초
	*/

	/*	(테스팅 해석)
		트리 균형이 유지되는 stl::map과 달리, 여기서 구현된 BST는 균형을 유지하지 않으므로,
		키 값들이 정렬된 순서로 삽입되는 아래의 선형 워크로드 테스트도 실행해야함
	*/

	#ifdef RANDOM_WORKLOAD_SPEED_TEST
	const int randomWorkloadNum = 10000000;
	const int randomWorkloadPerDataLen = 30;
	RandomWorkloadSpeedTest(randomWorkloadNum, randomWorkloadPerDataLen);
	#endif

	cout << endl << "testing 5 : Linear Increasing Workload Safety Test---------------------------------------------" << endl;

	/*	(테스팅 환경)
		앞선 테스트와 동일
	*/

	/*	(테스팅 방법)
		하나의 트리에 linearIncreaseWorkloadNum 횟수만큼 복사 삽입, 이동 삽입, 검색, 삭제과 트리의 소멸을 수행함
		키는 [0,linearIncreaseWorkloadNum-1]의 선형 키값들을 일렬로 사용함
		데이터는 linearIncreaseWorkloadPerDataLen으로 지정된 길이의 string 객체를 linearIncreaseWorkloadNum 개 만들어놓고 사용함
		편향 삽입이 이뤄지므로 linearIncreaseWorkloadNum의 높이인 트리를 형성하도록 함
	*/

	/*	(테스팅 결과)
		(linearIncreaseWorkloadNum = 100,000  |  linearIncreaseWorkloadPerDataLen = 30)
		복사 삽입	: BST = 29.5초	|	std::map = 0.10초
		이동 삽입	: BST = 31.7초	|	std::map = 0.09초
		검색		: BST = 32.9초	|	std::map = 0.03초
		삭제		: BST = 0.03초	|	std::map = 0.07초
		소멸		: BST = 0.04초	|	std::map = 0.04초
	*/

	/*	(테스팅 해석)
		트리 균형이 유지되는 std::map과 달리, 여기서 구현된 BST는 균형을 유지하지 않으므로,
		테스트에 nlog(n)의 시간복잡도를 가지는 std::map과 달리, BST는 n^2의 시간 복잡도가 걸리기에 큰 차이가 난다.
		다만 BST의 삭제는 헤드에서 바로 삭제가 일어나기에 트리의 높이에 영향을 받지 않으므로 빠른 속도를 보인다. 
	*/

	#ifdef LINEAR_INCREASE_WORKLOAD_SPEED_TEST
	const int linearIncreaseWorkloadNum = 100000;
	const int linearIncreaseWorkloadPerDataLen = 30;
	LinearIncreaseWorkloadSpeedTest(linearIncreaseWorkloadNum, linearIncreaseWorkloadPerDataLen);
	#endif

	cout << endl << "testing 5 : Linear Decreasing Workload Safety Test---------------------------------------------" << endl;

	/*	(테스팅 환경)
		앞선 테스트와 동일
	*/

	/*	(테스팅 방법)
		앞선 테스트와 동일하나 키를 역순으로 사용함
	*/

	/*	(테스팅 결과)
		(linearDecreaseWorkloadNum = 100,000  |  linearDecreaseWorkloadPerDataLen = 30)
		복사 삽입	: BST = 33.8초	|	std::map = 0.09초
		이동 삽입	: BST = 30.5초	|	std::map = 0.08초
		검색		: BST = 33.4초	|	std::map = 0.03초
		삭제		: BST = 0.02초	|	std::map = 0.08초
		소멸		: BST = 0.04초	|	std::map = 0.04초
	*/

	/*	(테스팅 해석)
		앞선 테스트와 동일
	*/

	#ifdef LINEAR_DECREASE_WORKLOAD_SPEED_TEST
	const int linearDecreaseWorkloadNum = 100000;
	const int linearDecreaseWorkloadPerDataLen = 30;
	LinearDecreaseWorkloadSpeedTest(linearDecreaseWorkloadNum, linearDecreaseWorkloadPerDataLen);
	#endif

	cout << endl << "testing ended----------------------------------------------------------------------------------" << endl;

	return 0;
}

template <typename DataType>
void PrintKeyAndData(const int key, const DataType retrievedData)
{
	cout << "retrieve key : " << key << ", retrieved data : " << retrievedData << endl;
}

void RandomWorkloadSpeedTest(const int workloadNum, const int workloadPerDataLen)
{
	cout << endl << "랜덤 워크로드 준비 중...." << endl;

	vector<string> insertTestDatum;
	insertTestDatum.reserve(workloadNum);
	for (int i = 0; i < workloadNum; i++)
	{
		insertTestDatum.emplace_back(string(workloadPerDataLen, 'A'));
	}

	vector<int> insertTestKeys(workloadNum);
	iota(insertTestKeys.begin(), insertTestKeys.end(), 0);
	mt19937 insertTestRng(123456);
	shuffle(insertTestKeys.begin(), insertTestKeys.end(), insertTestRng);

	vector<int> retrieveTestKeys(workloadNum);
	iota(retrieveTestKeys.begin(), retrieveTestKeys.end(), 0);
	mt19937 retrieveTestRng(654321);
	shuffle(retrieveTestKeys.begin(), retrieveTestKeys.end(), retrieveTestRng);

	vector<int> removeTestKeys(workloadNum);
	iota(removeTestKeys.begin(), removeTestKeys.end(), 0);
	mt19937 removeTestRng(162534);
	shuffle(removeTestKeys.begin(), removeTestKeys.end(), removeTestRng);

	steady_clock clock;
	time_point<steady_clock> timeBegin;
	time_point<steady_clock> timeEnd;
	duration<double> timeDiff;

	cout << endl << "랜덤 워크로드 복사 중...." << endl;
	timeBegin = SpeedTestBST(clock, workloadNum, insertTestDatum, insertTestKeys, retrieveTestKeys, removeTestKeys);

	timeEnd = clock.now();

	cout << endl << "BST 소멸자 측정 종료" << endl;

	timeDiff = timeEnd - timeBegin;

	cout << endl << "BST : " << workloadNum << "번의 소멸자 동안 흐른 시간은 : " << timeDiff.count() << endl;

	cout << endl << "-----------------------------------------------------------" << endl;

	cout << endl << "랜덤 워크로드 복사 중...." << endl;
	timeBegin = SpeedTestMap(clock, workloadNum, insertTestDatum, insertTestKeys, retrieveTestKeys, removeTestKeys);

	timeEnd = clock.now();

	cout << endl << "map 소멸자 측정 종료" << endl;

	timeDiff = timeEnd - timeBegin;

	cout << endl << "map : " << workloadNum << "번의 소멸자 동안 흐른 시간은 : " << timeDiff.count() << endl;
}

void LinearIncreaseWorkloadSpeedTest(const int workloadNum, const int workloadPerDataLen)
{
	cout << endl << "선형 증가 워크로드 준비 중...." << endl;

	vector<string> insertTestDatum;
	insertTestDatum.reserve(workloadNum);
	for (int i = 0; i < workloadNum; i++)
	{
		insertTestDatum.emplace_back(string(workloadPerDataLen, 'A'));
	}

	vector<int> insertTestKeys(workloadNum);
	iota(insertTestKeys.begin(), insertTestKeys.end(), 0);

	vector<int> retrieveTestKeys = insertTestKeys;

	vector<int> removeTestKeys = insertTestKeys;

	steady_clock clock;
	time_point<steady_clock> timeBegin;
	time_point<steady_clock> timeEnd;
	duration<double> timeDiff;

	cout << endl << "선형 증가 워크로드 복사 중...." << endl;
	timeBegin = SpeedTestBST(clock, workloadNum, insertTestDatum, insertTestKeys, retrieveTestKeys, removeTestKeys);

	timeEnd = clock.now();

	cout << endl << "BST 소멸자 측정 종료" << endl;

	timeDiff = timeEnd - timeBegin;

	cout << endl << "BST : " << workloadNum << "번의 소멸자 동안 흐른 시간은 : " << timeDiff.count() << endl;

	cout << endl << "-----------------------------------------------------------" << endl;

	cout << endl << "선형 증가 워크로드 복사 중...." << endl;
	timeBegin = SpeedTestMap(clock, workloadNum, insertTestDatum, insertTestKeys, retrieveTestKeys, removeTestKeys);

	timeEnd = clock.now();

	cout << endl << "map 소멸자 측정 종료" << endl;

	timeDiff = timeEnd - timeBegin;

	cout << endl << "map : " << workloadNum << "번의 소멸자 동안 흐른 시간은 : " << timeDiff.count() << endl;
}

void LinearDecreaseWorkloadSpeedTest(const int workloadNum, const int workloadPerDataLen)
{
	cout << endl << "선형 감소 워크로드 준비 중...." << endl;

	vector<string> insertTestDatum;
	insertTestDatum.reserve(workloadNum);
	for (int i = 0; i < workloadNum; i++)
	{
		insertTestDatum.emplace_back(string(workloadPerDataLen, 'A'));
	}

	vector<int> insertTestKeys(workloadNum);
	iota(insertTestKeys.rbegin(), insertTestKeys.rend(), 0);

	vector<int> retrieveTestKeys = insertTestKeys;

	vector<int> removeTestKeys = insertTestKeys;

	steady_clock clock;
	time_point<steady_clock> timeBegin;
	time_point<steady_clock> timeEnd;
	duration<double> timeDiff;

	cout << endl << "선형 감소 워크로드 복사 중...." << endl;
	timeBegin = SpeedTestBST(clock, workloadNum, insertTestDatum, insertTestKeys, retrieveTestKeys, removeTestKeys);

	timeEnd = clock.now();

	cout << endl << "BST 소멸자 측정 종료" << endl;

	timeDiff = timeEnd - timeBegin;

	cout << endl << "BST : " << workloadNum << "번의 소멸자 동안 흐른 시간은 : " << timeDiff.count() << endl;

	cout << endl << "-----------------------------------------------------------" << endl;

	cout << endl << "선형 감소 워크로드 복사 중...." << endl;
	timeBegin = SpeedTestMap(clock, workloadNum, insertTestDatum, insertTestKeys, retrieveTestKeys, removeTestKeys);

	timeEnd = clock.now();

	cout << endl << "map 소멸자 측정 종료" << endl;

	timeDiff = timeEnd - timeBegin;

	cout << endl << "map : " << workloadNum << "번의 소멸자 동안 흐른 시간은 : " << timeDiff.count() << endl;
}

time_point<steady_clock> SpeedTestBST(steady_clock& clock, const int workloadNum, vector<string> insertDataWorkload, const vector<int>& insertKeyWorkload, const vector<int>& retrieveKeyWorkload, const vector<int>& removeKeyWorkload)
{
	BST<string> copyInsertTestBST;
	BST<string> moveInsertTestBST;

	time_point<steady_clock> timeBegin;
	time_point<steady_clock> timeEnd;
	duration<double> timeDiff;

	cout << endl << "BST 복사 삽입 측정 시작" << endl;
	cout << endl << "|------------------|" << endl;

	timeBegin = clock.now();

	for (int i = 0; i < workloadNum; i++)
	{
		if (i % ((workloadNum / 20) + 1) == 0) cout << "*";

		copyInsertTestBST.Insert(insertKeyWorkload[i], insertDataWorkload[i]);
	}
	cout << endl;

	timeEnd = clock.now();

	cout << endl << "BST 복사 삽입 측정 종료" << endl;

	timeDiff = timeEnd - timeBegin;

	cout << endl << "BST : " << workloadNum << "번의 복사 삽입 동안 흐른 시간은 : " << timeDiff.count() << endl;

	cout << endl << "BST 이동 삽입 측정 시작" << endl;
	cout << endl << "|------------------|" << endl;

	timeBegin = clock.now();

	for (int i = 0; i < workloadNum; i++)
	{
		if (i % ((workloadNum / 20) + 1) == 0) cout << "*";

		moveInsertTestBST.Insert(insertKeyWorkload[i], move(insertDataWorkload[i]));
	}
	cout << endl;

	timeEnd = clock.now();

	cout << endl << "BST 이동 삽입 측정 종료" << endl;

	timeDiff = timeEnd - timeBegin;

	cout << endl << "BST : " << workloadNum << "번의 이동 삽입 동안 흐른 시간은 : " << timeDiff.count() << endl;

	string retrievedData;

	cout << endl << "BST 검색 측정 시작" << endl;
	cout << endl << "|------------------|" << endl;

	timeBegin = clock.now();

	for (int i = 0; i < workloadNum; i++)
	{
		if (i % ((workloadNum / 20) + 1) == 0) cout << "*";

		copyInsertTestBST.Retrieve(insertKeyWorkload[i], retrievedData);
	}
	cout << endl;

	timeEnd = clock.now();

	cout << endl << "BST 검색 측정 종료" << endl;

	timeDiff = timeEnd - timeBegin;

	cout << endl << "BST : " << workloadNum << "번의 검색 동안 흐른 시간은 : " << timeDiff.count() << endl;

	cout << endl << "BST 삭제 측정 시작" << endl;
	cout << endl << "|------------------|" << endl;

	timeBegin = clock.now();

	for (int i = 0; i < workloadNum; i++)
	{
		if (i % ((workloadNum / 20) + 1) == 0) cout << "*";

		copyInsertTestBST.Remove(removeKeyWorkload[i]);
	}
	cout << endl;

	timeEnd = clock.now();

	cout << endl << "BST 삭제 측정 종료" << endl;

	timeDiff = timeEnd - timeBegin;

	cout << endl << "BST : " << workloadNum << "번의 삭제 동안 흐른 시간은 : " << timeDiff.count() << endl;

	cout << endl << "BST 소멸자 측정 시작" << endl;
	return clock.now();
}

time_point<steady_clock> SpeedTestMap(steady_clock& clock, const int speedTestRepeat, vector<string> insertTestDatum, const vector<int>& insertTestKeys, const vector<int>& retrieveTestKeys, const vector<int>& removeTestKeys)
{
	map<int, string> copyInsertTestMap;
	map<int, string> moveInsertTestMap;

	time_point<steady_clock> timeBegin;
	time_point<steady_clock> timeEnd;
	duration<double> timeDiff;

	cout << endl << "map 복사 삽입 측정 시작" << endl;
	cout << endl << "|------------------|" << endl;

	timeBegin = clock.now();

	for (int i = 0; i < speedTestRepeat; i++)
	{
		if (i % ((speedTestRepeat / 20) + 1) == 0) cout << "*";

		copyInsertTestMap.emplace(insertTestKeys[i], insertTestDatum[i]);
	}
	cout << endl;

	timeEnd = clock.now();

	cout << endl << "map 복사 삽입 측정 종료" << endl;

	timeDiff = timeEnd - timeBegin;

	cout << endl << "map : " << speedTestRepeat << "번의 삽입 동안 흐른 시간은 : " << timeDiff.count() << endl;

	cout << endl << "map 이동 삽입 측정 시작" << endl;
	cout << endl << "|------------------|" << endl;

	timeBegin = clock.now();

	for (int i = 0; i < speedTestRepeat; i++)
	{
		if (i % ((speedTestRepeat / 20) + 1) == 0) cout << "*";

		moveInsertTestMap.emplace(insertTestKeys[i], move(insertTestDatum[i]));
	}
	cout << endl;

	timeEnd = clock.now();

	cout << endl << "map 이동 삽입 측정 종료" << endl;

	timeDiff = timeEnd - timeBegin;

	cout << endl << "map : " << speedTestRepeat << "번의 이동 삽입 동안 흐른 시간은 : " << timeDiff.count() << endl;

	int retrievedData = 0;

	cout << endl << "map 검색 측정 시작" << endl;
	cout << endl << "|------------------|" << endl;

	timeBegin = clock.now();

	for (int i = 0; i < speedTestRepeat; i++)
	{
		if (i % ((speedTestRepeat / 20) + 1) == 0) cout << "*";

		copyInsertTestMap.find(retrieveTestKeys[i]);
	}
	cout << endl;

	timeEnd = clock.now();

	cout << endl << "map 검색 측정 종료" << endl;

	timeDiff = timeEnd - timeBegin;

	cout << endl << "map : " << speedTestRepeat << "번의 검색 동안 흐른 시간은 : " << timeDiff.count() << endl;

	cout << endl << "map 삭제 측정 시작" << endl;
	cout << endl << "|------------------|" << endl;

	timeBegin = clock.now();

	for (int i = 0; i < speedTestRepeat; i++)
	{
		if (i % ((speedTestRepeat / 20) + 1) == 0) cout << "*";

		copyInsertTestMap.erase(insertTestKeys[i]);
	}
	cout << endl;

	timeEnd = clock.now();

	cout << endl << "map 삭제 측정 종료" << endl;

	timeDiff = timeEnd - timeBegin;

	cout << endl << "map : " << speedTestRepeat << "번의 삭제 동안 흐른 시간은 : " << timeDiff.count() << endl;

	cout << endl << "map 소멸자 측정 시작" << endl;
	return clock.now();
}