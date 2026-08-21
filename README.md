# BodoSearchTree
C++을 이용하여 구현한 BST와 AVL 트리입니다.  

<br>




<!---------------------------------------------------------------------------------------------------------------------------------------------->
## 목차
1. [제공 대상](#1-제공-대상)
2. [폴더 구조](#2-폴더-구조)
3. [사용 방법](#3-사용-방법)
4. [성능 측정](#4-성능-측정)
5. [구현 제외](#5-구현-제외)
6. [구현 참고](#6-구현-참고)

<br>




<!---------------------------------------------------------------------------------------------------------------------------------------------->
## 1. 제공 대상
### 1.1. 이진 탐색 트리
이진 탐색 트리(Binary Search Tree, BST)는 각 노드의 키 값을 기준으로 자식 노드들의 대소 관계가 유지되는 트리입니다.  

부모 노드의 키(key)는 왼쪽 서브트리의 모든 키보다 크고, 오른쪽 서브트리의 모든 키보다 작아야 한다는 조건을 통해 빠르게(O(log N)) 특정 키의 노드를 찾을 수 있습니다.  

- ***클래스 템플릿***
```cpp
    template <typename DataType>
    class BST;
```

- ***생성자, 할당 연산자, 소멸자***
```cpp
    BST() noexcept;

    BST(const BST<DataType>& sourceTree);

    BST(BST<DataType>&& sourceTree) noexcept;

    BST<DataType>& operator=(const BST<DataType>& sourceTree);

    BST<DataType>& operator=(BST<DataType>&& sourceTree) noexcept;

    ~BST() noexcept;
```

- ***퍼블릭 메서드***
```cpp
    //RETURN: newKey와 같은 키의 노드가 이미 존재하는 경우에 false를 반환함
    template <typename InsertDataType = DataType>
    bool Insert(std::int64_t newKey, InsertDataType&& newData);

    //RETURN: targetKey와 같은 키를 가진 노드가 존재하지 않는 경우에 false를 반환함
    bool Retrieve(std::int64_t targetKey, DataType& outData) const;

    //RETURN: targetKey와 같은 키를 가진 노드가 존재하지 않는 경우에 false를 반환함
    bool Remove(std::int64_t targetKey);

    void RemoveTree() noexcept;

    void CopyTree(const BSTTemplate<NodeType, DataType>& sourceBST);

    //NOTE: 디버깅용
    void PreorderPrint() const;
    void InorderPrint() const;
    void PostorderPrint() const;
```

<br>




### 1.2. AVL 트리
AVL 트리는 키가 정렬된 노드들이 삽입될 때 이진 탐색 트리에서 발생하는 편향 문제를 해결한 균형 트리 구조입니다.

노드의 왼쪽 서브트리와 오른쪽 서브트리의 높이 차가 2 이상이 될 경우 해당 위치를 기준으로 노드들을 회전하여 트리의 균형을 조절합니다.  

- ***클래스 템플릿***
```cpp
    template <typename DataType>
    class AVLTree;
```

- ***생성자, 할당 연산자, 소멸자***
```cpp
    AVLTree() noexcept;

    AVLTree(const AVLTree<DataType>& sourceTree);

    AVLTree(AVLTree<DataType>&& sourceTree) noexcept;

    AVLTree<DataType>& operator=(const AVLTree<DataType>& sourceTree);

    AVLTree<DataType>& operator=(AVLTree<DataType>&& sourceTree) noexcept;

    ~AVLTree() noexcept;
```

- ***퍼블릭 메서드***
```cpp
    //RETURN: newKey와 같은 키의 노드가 이미 존재하는 경우에 false를 반환함
    template <typename InsertDataType = DataType>
    bool Insert(std::int64_t newKey, InsertDataType&& newData)

    //RETURN: targetKey와 같은 키를 가진 노드가 존재하지 않는 경우에 false를 반환함
    bool Retrieve(std::int64_t targetKey, DataType& outData) const;

    //RETURN: targetKey와 같은 키를 가진 노드가 존재하지 않는 경우에 false를 반환함
    void Remove(std::int64_t targetKey);

    void RemoveTree() noexcept;

    void CopyTree(const BSTTemplate<NodeType, DataType>& sourceBST);

    //NOTE: 디버깅용
    void PreorderPrint() const;
    void InorderPrint() const;
    void PostorderPrint() const;
```

<br>




<!---------------------------------------------------------------------------------------------------------------------------------------------->
## 2. 폴더 구조
- `1.BST`
    - `BST.h`

    - `TestingBST.cpp`

- `2.AVLTree`
    - `AVLTree.h`

    - `TestingAVLTree.cpp`

- `Common`
    - `BSTTemplate.h`  
        이진 탐색 트리 템플릿으로, 두 종류의 트리가 모두 이를 상속받습니다.

    - `Stack.h`  
        트리의 순회, 회전 등의 로직에서 이전 경로를 기억하기 위해 사용하는 스택입니다.

    - `Debug.h`  
        로그 출력 매크로, 누수 추적용 `new` 함수 매크로가 정의되어 있습니다.

<br>




<!---------------------------------------------------------------------------------------------------------------------------------------------->
## 3. 사용 방법
### 3.1. 외부 프로젝트 사용 방법
본 트리 자료구조들은 별도의 정적, 동적 라이브러리 없이 사용할 수 있도록 헤더만으로 구현되어 있습니다.

1. 사용하려는 트리의 헤더 파일을 프로젝트 디렉터리 혹은 추가 포함 디렉터리에 둡니다.  
예: `AVLTree.h`

2. 트리 구현을 위해 참조하는 `Common` 폴더 내 모든 헤더 파일도 함께 둡니다.  
예: `BSTTemplate.h`, `Stack.h`, `Debug.h`

3. 소스 코드에서 사용할 트리의 헤더 파일을 포함한 뒤, 보관할 데이터의 타입을 템플릿 인자로 지정하여 트리 객체를 선언합니다.
    ```cpp
        #include "AVLTree.h"

        int main()
        {
            AVLTree<float> testAVLTree;

            int testKey = 5;
            float retrievedData = 0.0f;

            testAVLTree.Insert(testKey, 3.14f);
            testAVLTree.Retrieve(testKey, retrievedData);
            testAVLTree.Remove(testKey);
        }
    ```

<br>




### 3.2. 테스트 실행 방법
테스트는 Visual Studio 2026을 기준으로 구현되었습니다.

1. 리포지토리를 다운로드합니다.

2. 로컬의 리포지토리 디렉터리에 포함된 `BodoSearchTree.sln` 솔루션 파일을 더블 클릭합니다.

3. Visual Studio가 실행되면 오른쪽의 솔루션 탐색기 창을 확인합니다.  
(해당 솔루션 탐색기 창이 없는 경우 상단의 보기(V) 메뉴에서 솔루션 탐색기(P)를 누릅니다.)

4. 해당 솔루션 탐색기 창에서 실행해 보고 싶은 트리 프로젝트를 우클릭합니다.

5. 우클릭하면 나타나는 메뉴에서 시작 프로젝트로 설정을 누르거나, 단축키 `A`를 누릅니다.

6. 기능 테스트를 실행하려면, Visual Studio 상단의 구성을 `Debug`, 플랫폼을 `x64`로 설정하고, 디버깅 시작 단축키인 F5를 누릅니다.  
실행 결과가 명령 프롬프트 창에 출력됩니다. 또한 메모리 누수가 존재한다면 Visual Studio 하단의 출력(output) 창에 누수 정보가 출력됩니다.

7. 속도 테스트를 실행하려면, 상단의 구성을 `Release`로 변경하고, 디버깅 없이 실행(Ctrl+F5)을 누릅니다.  
테스트 과정과 결과가 명령 프롬프트 창에 출력됩니다.

<br>




<!---------------------------------------------------------------------------------------------------------------------------------------------->
## 4. 성능 측정
### 4.1. 측정 환경
[기반]
|구성 요소          |사양                                                           |
|-------------------|---------------------------------------------------------------|    
|CPU                |i5-13600KF, 3500 MHz, 14 코어, 20 논리 프로세서                |
|RAM                |32 GB, DDR4, 3600 MHz                                          |
|OS                 |Windows 11, 버전 25H2, 빌드 26200.8973                         |
|IDE                |Microsoft Visual Studio Community 2026 (64 - bit) 버전 18.8.2  |
|플랫폼 도구 집합   |v145 for Microsoft C++ Build Tools                             |
|컴파일러 버전      |x86용 Microsoft (R) C/C++ 최적화 컴파일러 버전 19.51.36252     |

<br>

[구성]
|구분           |           |                       |설정                                               |
|---------------|-----------|-----------------------|---------------------------------------------------|
|구성 선택      |           |					    |`Release x64`                                      |
|디버깅 여부    |           |                       |디버깅하지 않고 시작(Ctrl+F5)                      |
|C/C++          |일반       |디버그 정보 형식       |`프로그램 데이터베이스(/Zi)`                       |
|..             |최적화     |최적화		            |`최대 최적화(속도 우선)(/O2)`                      |
|..             |..         |인라인 함수 확장	    |`적합한 것 모두 확장(/Ob2)`                        |
|..             |..         |내장 함수 사용         |`예(/Oi)`                                          |
|..             |..         |크기 또는 속도	        |`코드 속도 우선(/Ot)`                              |
|..             |..         |전체 프로그램 최적화   |`예(/GL)`                                          |
|..             |전처리기   |전처리기 정의          |`NDEBUG;_CONSOLE;%(PreprocessorDefinitions)`       |
|..             |코드 생성  |기본 런타임 검사	    |`기본값`                                           |
|..             |..         |런타임 라이브러리      |`다중 스레드 DLL(/MD)`                             |
|..             |언어       |C++ 언어 표준		    |`기본값(ISO C++20 표준)`                           |
|..             |출력 파일  |어셈블러 출력 	        |`소스 코드로 구성된 어셈블리(/FAs)`                |
|링커           |최적화     |링크 타임 코드 생성    |`빠른 링크 타임 코드 생성 사용(/LTCG:incremental)` |

<br>




### 4.2. 측정 방식
구현된 모든 트리는 아래의 워크로드로 동일하게 속도 테스트를 진행합니다.  
측정 대상 연산은 복사 삽입(트리 A), 이동 삽입(트리 B), 검색(트리 A), 삭제(트리 A), 소멸(트리 B)입니다.

<br>

- 랜덤 워크로드  
    |구분           |설정                                                   |
    |---------------|-------------------------------------------------------|
    |키 분포        |삽입, 검색, 삭제별로 독립 랜덤 셔플                    |
    |키 범위        |0~9,999,999                                          |
    |데이터 개수    |10,000,000                                             |
    |데이터 요소    |길이 30의 `std::string`                                |
    |측정 반복 횟수 |1회                                                    |

<br>

- 랜덤 로컬 워크로드  
    |구분           |설정                                                   |
    |---------------|-------------------------------------------------------|
    |키 분포        |10개 단위로 묶은 뒤 삽입, 검색, 삭제별로 독립 랜덤 셔플|
    |키 범위        |위와 동일                                              |
    |데이터 개수    |위와 동일                                              |
    |데이터 요소    |위와 동일                                              |
    |측정 반복 횟수 |위와 동일                                              |

<br>

- 선형 증가 워크로드
    |구분           |설정                                                   |
    |---------------|-------------------------------------------------------|
    |키 분포        |셔플하지 않고 선형 그대로 사용함                       |
    |키 범위        |위와 동일                                              |
    |데이터 개수    |위와 동일                                              |
    |데이터 요소    |위와 동일                                              |
    |측정 반복 횟수 |위와 동일                                              |

<br>

- 선형 감소 워크로드
    |구분           |설정                                                   |
    |---------------|-------------------------------------------------------|
    |키 분포        |셔플하지 않되 키를 역순으로 사용함                     |
    |키 범위        |위와 동일                                              |
    |데이터 개수    |위와 동일                                              |
    |데이터 요소    |위와 동일                                              |
    |측정 반복 횟수 |위와 동일                                              |

<br>




### 4.3. 측정 결과
#### 4.3.1. 이진 탐색 트리
##### 4.3.1.1. 랜덤 워크로드
|연산       |`BST`      |`std::map` |
|-----------|----------:|----------:|
|복사 삽입  |14.79 초   |14.06 초   |
|이동 삽입  |13.95 초   |13.13 초   |
|검색       |13.76 초   |14.98 초   |
|삭제       |20.48 초   |18.07 초   |
|소멸       |4.32 초    |4.33 초    |

- 어셈블리 파일 확인 결과 `BST`의 삽입과 검색 메서드는 모두 인라이닝되었지만 삭제 메서드의 하위 함수 객체 호출은 인라이닝되지 않았습니다. 따라서 유독 삭제 메서드가 느린 원인은 하위 작업 호출이 인라이닝되지 못한 데 있는 것으로 판단됩니다.

<br>




##### 4.3.1.2. 랜덤 로컬 워크로드
|연산       |`BST`      |`std::map` |
|-----------|----------:|----------:|
|복사 삽입  |7.20 초    |3.86 초    |
|이동 삽입  |6.49 초    |3.20 초    |
|검색       |6.17 초    |3.43 초    |
|삭제       |7.47 초    |3.99 초    |
|소멸       |3.38 초    |3.08 초    |

- 워크로드가 지역적 선형성을 가지게 되므로 앞선 랜덤 워크로드 테스트에 비해 `BST`의 트리 높이는 더 높아집니다. 그럼에도 삽입, 검색, 삭제 메서드가 더 빨라진 이유는 캐시 히트율 상승 때문일 가능성이 있습니다.

- `BST`와 `std::map`의 속도 차이가 벌어진 이유도 설계와 구현상의 캐시 히트율 최적화 차이 때문일 가능성이 있습니다.

<br>




##### 4.3.1.3. 선형 증가 워크로드
|연산       |`BST`      |`std::map` |
|-----------|----------:|----------:|
|복사 삽입  |시간 초과  |1.89 초    |
|이동 삽입  |시간 초과  |1.43 초    |
|검색       |시간 초과  |0.69 초    |
|삭제       |0.02 초    |1.69 초    |
|소멸       |0.37 초    |1.33 초    |

- 선형 워크로드는 `BST`를 편향시켜 리스트와 같은 형상이 되도록 합니다. 이로 인해 삽입 메서드와 검색 메서드가 `O(N)`의 시간 복잡도를 지니게 되기 때문에 50초를 넘겨 시간 초과로 처리됩니다.

- 시간 초과로 삽입이 덜 이루어졌으므로, 이후의 '삭제', '소멸'의 측정 시간은 신뢰할 수 없습니다.

- `BST`와 달리 `std::map`은 균형을 유지하는 트리이기 때문에 선형 워크로드에 대해서도 메서드의 시간 복잡도가 `O(log N)`을 따르기 때문에 매우 빠른 속도를 보입니다. 게다가 선형 워크로드가 가진 지역성으로 캐시 히트율이 증가해 랜덤 워크로드 테스트보다 훨씬 빠른 속도를 보이는 것으로 추측합니다.

<br>




##### 4.3.1.4. 선형 감소 워크로드
|연산       |`BST`      |`std::map` |
|-----------|----------:|----------:|
|복사 삽입  |시간 초과  |1.88 초    |
|이동 삽입  |시간 초과  |1.46 초    |
|검색       |시간 초과  |0.67 초    |
|삭제       |0.02 초    |1.67 초    |
|소멸       |0.27 초    |2.06 초    |

- 앞선 선형 증가 워크로드와 해석이 같습니다.

<br>




#### 4.3.2. AVL 트리
##### 4.3.2.1. 랜덤 워크로드
|연산       |`AVLTree`  |`std::map` |
|-----------|----------:|----------:|
|복사 삽입  |20.45 초   |14.70 초   |
|이동 삽입  |17.81 초   |13.77 초   |
|검색       |13.77 초   |15.45 초   |
|삭제       |24.71 초   |17.91 초   |
|소멸       |4.48 초    |4.63 초    |

- `std::map` 대비 `AVLTree`의 삽입 메서드와 삭제 메서드의 상대적인 속도가 `BST`보다 느린 것은 삽입 및 삭제 메서드에 작성된 균형 유지 로직의 비효율성이 원인으로 판단됩니다. 특히 삭제 메서드는 중위선행자나 후속자를 찾는 경로를 기록하는 과정에서 두 번 탐색을 수행하는 현재 로직이 느린 속도의 원인으로 추측됩니다.

<br>




##### 4.3.2.2. 랜덤 로컬 워크로드
|연산       |`AVLTree`  |`std::map` |
|-----------|----------:|----------:|
|복사 삽입  |5.92 초    |4.04 초    |
|이동 삽입  |5.13 초    |3.39 초    |
|검색       |2.53 초    |3.84 초    |
|삭제       |7.62 초    |4.20 초    |
|소멸       |3.32 초    |3.26 초    |

- 앞선 `BST`의 테스트와 비슷한 결과가 나온 것으로 보입니다.

<br>




##### 4.3.2.3. 선형 증가 워크로드
|연산       |`AVLTree`  |`std::map` |
|-----------|----------:|----------:|
|복사 삽입  |3.47 초    |2.06 초    |
|이동 삽입  |2.93 초    |1.56 초    |
|검색       |0.63 초    |0.69 초    |
|삭제       |3.04 초    |2.01 초    |
|소멸       |1.03 초    |1.06 초    |

- 앞선 `BST`와 달리 `AVLTree`는 균형 트리이므로 시간 초과가 발생하지 않았습니다. 다만 랜덤 워크로드와 마찬가지로 `std::map`에 비해선 최적화 부족으로 인해 상대적으로 느린 속도가 나타나고 있습니다.

<br>




##### 4.3.2.4. 선형 감소 워크로드
|연산       |`AVLTree`  |`std::map` |
|-----------|----------:|----------:|
|복사 삽입  |3.28 초    |1.89 초    |
|이동 삽입  |2.86 초    |1.44 초    |
|검색       |0.65 초    |0.69 초    |
|삭제       |3.09 초    |2.19 초    |
|소멸       |1.21 초    |1.28 초    |

- 앞선 선형 증가 워크로드와 해석이 같습니다.

<br>




<!---------------------------------------------------------------------------------------------------------------------------------------------->
## 5. 구현 제외
- **범용 컨테이너 기능**  
    데이터 개수 조회 메서드, `iterator`, 범용 키 타입과 비교자, `emplace` 메서드 등 STL 컨테이너 수준의 추가 인터페이스 기능은 제외하였습니다.

<br>

- **추가 최적화**  
    코드 축약, 부모 노드 포인터, 메모리 풀, 인자 전달 및 예외 안전성 여부에 따른 세부 최적화 등 기존 구조를 크게 변경하거나 핵심 학습 범위를 벗어나는 최적화는 제외하였습니다.

<br>

- **테스트 고도화**  
    예외 안전성 테스트와 속도 반복 통계 테스트는 구현 대상에서 제외하고, 기초적인 기능 테스트와 속도 테스트에 집중하였습니다.

<br>




<!---------------------------------------------------------------------------------------------------------------------------------------------->
## 6. 구현 참고
"SW코딩 역량을 위한 C++ 프로그래밍" (홍봉희 지음 / 정익사 출판 / 2017년 발행)

"C C++로 배우는 자료구조론" (주우석 지음 / 한빛아카데미 출판 / 2015년 발행)

"Welcome back to C++ - Modern C++" (Microsoft Learn / 2026년 7월 열람)  
[https://learn.microsoft.com/en-us/cpp/cpp/welcome-back-to-cpp-modern-cpp?view=msvc-170](https://learn.microsoft.com/en-us/cpp/cpp/welcome-back-to-cpp-modern-cpp?view=msvc-170)

"Move Constructors and Move Assignment Operators (C++)" (Microsoft Learn / 2026년 6월 열람)  
[https://learn.microsoft.com/en-us/cpp/cpp/move-constructors-and-move-assignment-operators-cpp?view=msvc-170](https://learn.microsoft.com/en-us/cpp/cpp/move-constructors-and-move-assignment-operators-cpp?view=msvc-170)

"Rvalue reference declarator: &&" (Microsoft Learn / 2026년 6월 열람)  
[https://learn.microsoft.com/en-us/cpp/cpp/rvalue-reference-declarator-amp-amp?view=msvc-170](https://learn.microsoft.com/en-us/cpp/cpp/rvalue-reference-declarator-amp-amp?view=msvc-170)

"Modern C++ best practices for exceptions and error handling" (Microsoft Learn / 2026년 7월 열람)  
[https://learn.microsoft.com/en-us/cpp/cpp/errors-and-exception-handling-modern-cpp?view=msvc-170](https://learn.microsoft.com/en-us/cpp/cpp/errors-and-exception-handling-modern-cpp?view=msvc-170)

"Exceptions and Stack Unwinding in C++" (Microsoft Learn / 2026년 7월 열람)  
[https://learn.microsoft.com/en-us/cpp/cpp/exceptions-and-stack-unwinding-in-cpp?view=msvc-170](https://learn.microsoft.com/en-us/cpp/cpp/exceptions-and-stack-unwinding-in-cpp?view=msvc-170)

"How to: Design for exception safety" (Microsoft Learn / 2026년 6월 열람)  
[https://learn.microsoft.com/en-us/cpp/cpp/how-to-design-for-exception-safety?view=msvc-170](https://learn.microsoft.com/en-us/cpp/cpp/how-to-design-for-exception-safety?view=msvc-170)

"Object lifetime and resource management (RAII)" (Microsoft Learn / 2026년 6월 열람)   
[https://learn.microsoft.com/en-us/cpp/cpp/object-lifetime-and-resource-management-modern-cpp?view=msvc-170](https://learn.microsoft.com/en-us/cpp/cpp/object-lifetime-and-resource-management-modern-cpp?view=msvc-170)

"Smart pointers (Modern C++)" (Microsoft Learn / 2026년 7월 열람)  
[https://learn.microsoft.com/en-us/cpp/cpp/smart-pointers-modern-cpp?view=msvc-170](https://learn.microsoft.com/en-us/cpp/cpp/smart-pointers-modern-cpp?view=msvc-170)

"How to: Create and use unique_ptr instances" (Microsoft Learn / 2026년 6월 열람)  
[https://learn.microsoft.com/en-us/cpp/cpp/how-to-create-and-use-unique-ptr-instances?view=msvc-170](https://learn.microsoft.com/en-us/cpp/cpp/how-to-create-and-use-unique-ptr-instances?view=msvc-170)

"Find memory leaks with the CRT library" (Microsoft Learn / 2026년 6월 열람)  
[https://learn.microsoft.com/en-us/cpp/c-runtime-library/find-memory-leaks-using-the-crt-library?view=msvc-170](https://learn.microsoft.com/en-us/cpp/c-runtime-library/find-memory-leaks-using-the-crt-library?view=msvc-170)

<br>