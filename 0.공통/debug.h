#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>		//로그, 경고, 에러 등의 콘솔 출력을 위한 매크로를 사용함
using namespace std;

#ifdef TREE_LOG
	#define LogPrint(statement) cout << "(Log : " << __func__ << ") " << statement << endl
#else
	#define LogPrint(statement)
#endif

#ifdef TREE_ERROR
	#define ErrorPrint(statement) cout << "(Error : " << __func__ << ") " << statement << endl
#else
	#define ErrorPrint(statement)
#endif

#ifdef TREE_WARNING
	#define WarningPrint(statement) cout << "(Warning : " << __func__ << ") " << statement << endl
#else
	#define WarningPrint(statement)
#endif

//메모리 누수로 이어진 new 할당을 추적하기 위해선 기존 new가 아니라 오버로딩된 특별한 new를 사용하여야 한다
//이를 명시적으로 사용하여야 하기 위해서, make_unique를 사용하기 보다는 unique_ptr<T>(DBG_NEW T(argument))와 같은 방식을 사용한다
#ifdef _DEBUG
	#define _CRTDBG_MAP_ALLOC
	#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
	#define DBG_NEW new
#endif

#endif //DEBUG_H