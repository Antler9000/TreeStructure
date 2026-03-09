//로그, 에러, 경고 콘솔 출력문들을 활성화하기 위한 전처리 상수 정의
//#define TREE_LOG	
//#define TREE_ERROR
//#define TREE_WARNING

#include "BST_using_recurse.h"	//이진 탐색 트리가 정의된 헤더파일
#include <chrono>;				//속도 테스트용도
#include <numeric>;			//..
#include <random>;				//..
#include <map>;				//..
using namespace chrono;		//..

template <typename DataType>
void RetrieveResultPrint(const int key, const DataType retrievedData);

void SpeedTest(const int speedTestRepeat, const int speedTestPerDataLen);

void SpeedTestBST(const int speedTestRepeat, vector<string> insertTestDatum, vector<int>& insertTestKeys, vector<int>& retrieveTestKeys, vector<int>& removeTestKeys);

void SpeedComparisonTestMap(const int speedTestRepeat, vector<string> insertTestDatum, vector<int>& insertTestKeys, vector<int>& retrieveTestKeys, vector<int>& removeTestKeys);

void SafetyTest(const int safetyTestRepeat);

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

	/*
		작성자의 테스팅 환경은 아래와 같음
		- 실행 방법			: 디버깅하지 않고 실행(Ctrl + F5)
		- OS					: Windows 11, 버전 25H2, 빌드 26200.7922
		- IDE				: Microsoft Visual Studio Community 2022 (64 - bit) 버전 17.14.23
		- 플랫폼 도구 집합		: Visual Studio 2022 (v143)
		- 컴파일러 버전		: x86용 Microsoft(R) C / C++ 최적화 컴파일러 버전 19.44.35222
		- 스택 크기 설정		: 프로젝트 기본 설정(공란)
		- C / C++ 최적화 설정	: 최대 최적화(속도 우선)(/O2)
		- 기본 런타임 검사		: 기본값
	*/

	/*
		하나의 트리에 speedTestRepeat 횟수만큼 삽입, 검색, 삭제를 수행함
		키는 미리 [0,speedTestRepeat-1]의 중복되지 않는 키 값들을 랜덤하게 셔플해놓고 사용함
		데이터는 미리 speedTestPerDataLen으로 지정된 길이의 string 객체를 speedTestRepeat 개 만들어놓고 사용함
		작성자의 테스팅 환경에서는 speedTestRepeat이 10,000,000 이고, speedTestPerDataLen이 30 일 때,
		BST 삽입에는 153.3초가 걸렸고, 비교용 std::map 삽입에는 25.4초가 걸렸음
		BST 검색에는 19.0초가 걸렸고, 비교용 std::map 검색에는 19.1초가 걸렸음
		BST 삭제에는 34.5초가 걸렸고, 비교용 std::map 삭제에는 28.4초가 걸렸음
	*/

	/*
		트리 균형이 유지되는 stl::map과 달리, 여기서 구현된 BST는 균형을 유지하지 않으므로,
		테스트용 키 값들이 정렬된 순서로 삽입되는 선형 워크로드에서 stl::map이 크게 유리할 것으로 추측함
		여기서 구현된 트리는 재귀로 구현됨에 따라 스택 오버플로우가 발생하는 깊이 제한이 있어 (아래의 안전성 테스트 참고),
		선형 워크로드에서의 유의미한 시간 비교를 수행할 수 없음
	*/

	const int speedTestRepeat = 10000000;
	const int speedTestPerDataLen = 30;
	SpeedTest(speedTestRepeat, speedTestPerDataLen);

	cout << endl << "testing 5 : Safety Test------------------------------------------------------------------------" << endl;

	/*
		하나의 트리에 safetyTestRepeat 횟수만큼 삽입을 수행함
		편향 삽입 패턴을 사용하여 safetyTestRepeat의 높이인 트리를 형성하도록 함
		작성자의 테스팅 환경에서는 safetyTestRepeat이 특정 값을 넘어가면 스택 오버플로우가 나는 것을 확인하였음.
		safetyTestRepeat >= 1800 : 소멸 과정에서 스택 오버플로우 발생
		safetyTestRepeat >= 2700 : 삽입 과정에서 스택 오버플로우 발생
	*/

	const int safetyTestRepeat = 1700;
	SafetyTest(safetyTestRepeat);

	cout << endl << "testing ended----------------------------------------------------------------------------------" << endl;
	
	return 0;
}

template <typename DataType>
void RetrieveResultPrint(const int key, const DataType retrievedData)
{
	cout << "retrieve key : " << key << ", retrieved data : " << retrievedData << endl;
}

void SpeedTest(const int speedTestRepeat, const int speedTestPerDataLen)
{
	vector<string> insertTestDatum;
	insertTestDatum.reserve(speedTestRepeat);
	for (int i = 0; i < speedTestRepeat; i++)
	{
		insertTestDatum.emplace_back(string(speedTestPerDataLen, 'A'));
	}
	
	vector<int> insertTestKeys(speedTestRepeat);
	iota(insertTestKeys.begin(), insertTestKeys.end(), 0);
	mt19937 insertTestRng(123456);
	shuffle(insertTestKeys.begin(), insertTestKeys.end(), insertTestRng);

	vector<int> retrieveTestKeys(speedTestRepeat);
	iota(retrieveTestKeys.begin(), retrieveTestKeys.end(), 0);
	mt19937 retrieveTestRng(654321);
	shuffle(retrieveTestKeys.begin(), retrieveTestKeys.end(), retrieveTestRng);

	vector<int> removeTestKeys(speedTestRepeat);
	iota(removeTestKeys.begin(), removeTestKeys.end(), 0);
	mt19937 removeTestRng(162534);
	shuffle(removeTestKeys.begin(), removeTestKeys.end(), removeTestRng);

	SpeedTestBST(speedTestRepeat, insertTestDatum, insertTestKeys, retrieveTestKeys, removeTestKeys);

	SpeedComparisonTestMap(speedTestRepeat, insertTestDatum, insertTestKeys, retrieveTestKeys, removeTestKeys);
}

void SpeedTestBST(const int speedTestRepeat, vector<string> insertTestDatum, vector<int>& insertTestKeys, vector<int>& retrieveTestKeys, vector<int>& removeTestKeys)
{
	BST<string> speedTestBST;

	steady_clock clock;
	time_point<steady_clock> timeBegin;
	time_point<steady_clock> timeEnd;
	duration<double> timeDiff;

	cout << endl << "BST 랜덤 삽입 측정 시작" << endl;
	cout << endl << "|------------------|" << endl;

	timeBegin = clock.now();

	for (int i = 0; i < speedTestRepeat; i++)
	{
		if (i % ((speedTestRepeat / 20) + 1) == 0) cout << "*";

		speedTestBST.Insert(insertTestKeys[i], insertTestDatum[i]);
	}
	cout << endl;

	timeEnd = clock.now();

	cout << endl << "BST 랜덤 삽입 측정 종료" << endl;

	timeDiff = timeEnd - timeBegin;

	cout << endl << "BST : " << speedTestRepeat << "번의 삽입 동안 흐른 시간은 : " << timeDiff.count() << endl;

	string retrievedData;

	cout << endl << "BST 랜덤 검색 측정 시작" << endl;
	cout << endl << "|------------------|" << endl;

	timeBegin = clock.now();

	for (int i = 0; i < speedTestRepeat; i++)
	{
		if (i % ((speedTestRepeat / 20) + 1) == 0) cout << "*";

		speedTestBST.Retrieve(insertTestKeys[i], retrievedData);
	}
	cout << endl;

	timeEnd = clock.now();

	cout << endl << "BST 랜덤 검색 측정 종료" << endl;

	timeDiff = timeEnd - timeBegin;

	cout << endl << "BST : " << speedTestRepeat << "번의 검색 동안 흐른 시간은 : " << timeDiff.count() << endl;

	cout << endl << "BST 랜덤 삭제 측정 시작" << endl;
	cout << endl << "|------------------|" << endl;

	timeBegin = clock.now();

	for (int i = 0; i < speedTestRepeat; i++)
	{
		if (i % ((speedTestRepeat / 20) + 1) == 0) cout << "*";
		
		speedTestBST.Remove(removeTestKeys[i]);
	}
	cout << endl;

	timeEnd = clock.now();

	cout << endl << "BST 랜덤 삭제 측정 종료" << endl;

	timeDiff = timeEnd - timeBegin;

	cout << endl << "BST : " << speedTestRepeat << "번의 삭제 동안 흐른 시간은 : " << timeDiff.count() << endl;
}

void SpeedComparisonTestMap(const int speedTestRepeat, vector<string> insertTestDatum, vector<int>& insertTestKeys, vector<int>& retrieveTestKeys, vector<int>& removeTestKeys)
{
	map<int, string> speedCompareTestMap;

	steady_clock clock;
	time_point<steady_clock> timeBegin;
	time_point<steady_clock> timeEnd;
	duration<double> timeDiff;

	cout << endl << "map 랜덤 삽입 측정 시작" << endl;
	cout << endl << "|------------------|" << endl;

	timeBegin = clock.now();

	for (int i = 0; i < speedTestRepeat; i++)
	{
		if (i % ((speedTestRepeat / 20) + 1) == 0) cout << "*";

		speedCompareTestMap.emplace(insertTestKeys[i], insertTestDatum[i]);
	}
	cout << endl;

	timeEnd = clock.now();

	cout << endl << "map 랜덤 삽입 측정 종료" << endl;

	timeDiff = timeEnd - timeBegin;

	cout << endl << "map : " << speedTestRepeat << "번의 삽입 동안 흐른 시간은 : " << timeDiff.count() << endl;

	int retrievedData = 0;

	cout << endl << "map 랜덤 검색 측정 시작" << endl;
	cout << endl << "|------------------|" << endl;

	timeBegin = clock.now();

	for (int i = 0; i < speedTestRepeat; i++)
	{
		if (i % ((speedTestRepeat / 20) + 1) == 0) cout << "*";

		speedCompareTestMap.find(retrieveTestKeys[i]);
	}
	cout << endl;

	timeEnd = clock.now();

	cout << endl << "map 랜덤 검색 측정 종료" << endl;

	timeDiff = timeEnd - timeBegin;

	cout << endl << "map : " << speedTestRepeat << "번의 검색 동안 흐른 시간은 : " << timeDiff.count() << endl;

	cout << endl << "map 랜덤 삭제 측정 시작" << endl;
	cout << endl << "|------------------|" << endl;

	timeBegin = clock.now();

	for (int i = 0; i < speedTestRepeat; i++)
	{
		if (i % ((speedTestRepeat / 20) + 1) == 0) cout << "*";

		speedCompareTestMap.erase(insertTestKeys[i]);
	}
	cout << endl;

	timeEnd = clock.now();

	cout << endl << "map 랜덤 삭제 측정 종료" << endl;

	timeDiff = timeEnd - timeBegin;

	cout << endl << "map : " << speedTestRepeat << "번의 삭제 동안 흐른 시간은 : " << timeDiff.count() << endl;


}

void SafetyTest(const int safetyTestRepeat)
{
	BST<int> safetyTestBST;

	cout << endl << "선형 삽입 시작" << endl;

	for (int i = 0; i < safetyTestRepeat; i++)
	{
		safetyTestBST.Insert(i, i);
	}

	cout << endl << "선형 삽입 성공" << endl;
}