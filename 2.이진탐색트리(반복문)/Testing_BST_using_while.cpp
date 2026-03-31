//디버그 출력문들을 활성화하고 싶을 시 주석을 해제할 것
//#define TREE_LOG	
//#define TREE_ERROR
//#define TREE_WARNING

#include "BST_using_while.h"	//정의한 BST를 테스팅함
#include <chrono>;				//속도 테스트를 위해 사용함
#include <string>;				//..
#include <numeric>;				//..
#include <random>;				//..
#include <map>;					//..
using namespace chrono;			//..

template <typename DataType>
void RetrieveResultPrint(const int key, const DataType retrievedData);

void RandomWorkloadSpeedTest(const int workloadNum, const int workloadPerDataLen);

void LinearIncreaseWorkloadSpeedTest(const int workloadNum, const int workloadPerDataLen);

void LinearDecreaseWorkloadSpeedTest(const int workloadNum, const int workloadPerDataLen);

time_point<steady_clock> SpeedTestBST(steady_clock& clock, const int workloadNum, vector<string> insertDataWorkload, const vector<int>& insertKeyWorkload, const vector<int>& retrieveKeyWorkload, const vector<int>& removeKeyWorkload);

time_point<steady_clock> SpeedTestMap(steady_clock& clock, const int workloadNum, vector<string> insertDataWorkload, const vector<int>& insertKeyWorkload, const vector<int>& retrieveKeyWorkload, const vector<int>& removeKeyWorkload);

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

	cout << endl << "testing 4 : Random Workload Speed Test-------------------------------------------------------------------------" << endl;

	/*	(테스팅 환경)
		- 실행 방법						: 디버깅하지 않고 실행(Ctrl + F5)
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
		복사 삽입 : BST = 30.2초	|	std::map = 27.8초
		이동 삽입 : BST = 28.1초	|	std::map = 32.5초
		검색 삽입 : BST = 19.3초	|	std::map = 24.5초
		삭제 삽입 : BST = 33.6초	|	std::map = 34.2초
		소멸 삽입 : BST = 25.4초	|	std::map = 21.7초
	*/

	/*	(테스팅 해석)
		트리 균형이 유지되는 stl::map과 달리, 여기서 구현된 BST는 균형을 유지하지 않으므로,
		키 값들이 정렬된 순서로 삽입되는 아래의 선형 워크로드 테스트도 실행해야함
	*/

	const int randomWorkloadNum = 10000000;
	const int randomWorkloadPerDataLen = 30;
	RandomWorkloadSpeedTest(randomWorkloadNum, randomWorkloadPerDataLen);

	cout << endl << "testing 5 : Linear Increasing Workload Safety Test------------------------------------------------------------------------" << endl;

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
		복사 삽입 : BST = 32.4초	|	std::map = 0.11초
		이동 삽입 : BST = 32.8초	|	std::map = 0.09초
		검색 삽입 : BST = 31.5초	|	std::map = 0.03초
		삭제 삽입 : BST = 0.03초	|	std::map = 0.07초
		소멸 삽입 : BST = 117.7초	|	std::map = 0.04초
	*/

	/*	(테스팅 해석)
		트리 균형이 유지되는 std::map과 달리, 여기서 구현된 BST는 균형을 유지하지 않으므로,
		테스트에 nlog(n)의 시간복잡도를 가지는 std::map과 달리, BST는 n^2의 시간 복잡도가 걸리기에 큰 차이가 난다.
		다만 BST의 삭제는 헤드에서 바로 삭제가 일어나기에 트리의 높이에 영향을 받지 않으므로 빠른 속도를 보인다. 
	*/

	const int linearIncreaseWorkloadNum = 100000;
	const int linearIncreaseWorkloadPerDataLen = 30;
	LinearIncreaseWorkloadSpeedTest(linearIncreaseWorkloadNum, linearIncreaseWorkloadPerDataLen);

	cout << endl << "testing 5 : Linear Decreasing Workload Safety Test------------------------------------------------------------------------" << endl;

	/*	(테스팅 환경)
		앞선 테스트와 동일
	*/

	/*	(테스팅 방법)
		앞선 테스트와 동일하나 키를 역순으로 사용함
	*/

	/*	(테스팅 결과)
		(linearDecreaseWorkloadNum = 100,000  |  linearDecreaseWorkloadPerDataLen = 30)
		복사 삽입 : BST = 32.6초	|	std::map = 0.1초
		이동 삽입 : BST = 30.4초	|	std::map = 0.08초
		검색 삽입 : BST = 31.8초	|	std::map = 0.03초
		삭제 삽입 : BST = 00.3초	|	std::map = 0.08초
		소멸 삽입 : BST = 117.9초	|	std::map = 0.04초
	*/

	/*	(테스팅 해석)
		앞선 테스트와 동일
	*/

	const int linearDecreaseWorkloadNum = 100000;
	const int linearDecreaseWorkloadPerDataLen = 30;
	LinearDecreaseWorkloadSpeedTest(linearDecreaseWorkloadNum, linearDecreaseWorkloadPerDataLen);

	cout << endl << "testing ended----------------------------------------------------------------------------------" << endl;

	return 0;
}

template <typename DataType>
void RetrieveResultPrint(const int key, const DataType retrievedData)
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

	cout << endl << "선형 감소 워크로드 복사 중...." << endl;
	timeBegin = SpeedTestMap(clock, workloadNum, insertTestDatum, insertTestKeys, retrieveTestKeys, removeTestKeys);

	timeEnd = clock.now();

	cout << endl << "map 소멸자 측정 종료" << endl;

	timeDiff = timeEnd - timeBegin;

	cout << endl << "map : " << workloadNum << "번의 소멸자 동안 흐른 시간은 : " << timeDiff.count() << endl;
}

//insertTestDatum은 복사 비용이 크지만, 그럼에도 이동 삽입 속도 테스트 과정에서 데이터 원본을 안전하게 두기 위해 값복사가 일어나는 기본 인자로 둔다.
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

	cout << endl << "BST 소멸자 측정 시작" << endl;
	return clock.now();
}