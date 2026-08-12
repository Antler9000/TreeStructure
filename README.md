# BodoSearchTree
C++을 이용하여 구현 중인 이진 탐색 계열의 트리 자료구조입니다.  

STL에 근접한 성능과 예외 안전성을 가질 수 있도록 하는 것을 목표로 하고 있습니다. 

현재 데이터 개수를 반환하는 메서드를 추가하고 있습니다.

<br>




<!--------------------------------------------------------------------------------------------------------------------------------------------------->
## 목차
1. [제공 대상](#1-제공-대상)
2. [폴더 구조](#2-폴더-구조)
3. [사용 방법](#3-사용-방법)
4. [성능 측정](#4-성능-측정)
5. [구현 예정](#5-구현-예정)
6. [구현 제외](#6-구현-제외)
7. [참고 자료](#7-참고-자료)

<br>




<!----------------------------------------------------------------------------------------------------------------------------------------------->
## 1. 제공 대상
### 1.1. 이진 탐색 트리
이진 탐색 트리(Binary Search Tree, BST)는 각 노드의 키 값을 기준으로 자식 노드들의 대소 관계가 유지되는 트리입니다.  

부모 노드의 키(key)는 왼쪽 서브트리의 모든 키보다 크고, 오른쪽 서브트리의 모든 키보다 작아야 한다는 조건을 통해 빠르게(평균적으로 O(log(N))) 특정 키의 노드를 찾을 수 있습니다 [1].  

데이터 개수 반환 로직을 구현하고, 예외 안전성을 테스트로 확인하고, 속도 테스트에 반복 측정을 추가할 예정입니다.

- ***클래스 템플릿***
```cpp
    template <typename DataType>
    class BST;
```

- ***생성자, 할당 연산자, 소멸자***
```cpp
    BST();

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
    bool Insert(std::int32_t newKey, InsertDataType&& newData);

    //RETURN: targetKey와 같은 키를 가진 노드가 존재하지 않는 경우에 false를 반환함
    bool Retrieve(std::int32_t targetKey, DataType& outData) const;

    //RETURN: targetKey와 같은 키를 가진 노드가 존재하지 않는 경우에 false를 반환함
    bool Remove(std::int32_t targetKey);

    void RemoveTree() noexcept;

    void CopyTree(const BSTTemplate<NodeType, DataType>& sourceBST);

    //NOTE: 디버깅용
    void PreorderPrint() const;
    void InorderPrint() const;
    void PostorderPrint() const;
```

<br>




### 1.2. 스플레이 트리
스플레이 트리(Splay Tree)는 지역성이 강한 접근을 빠르게 처리하도록 한 이진 탐색 트리의 일종입니다.  

탐색의 타깃이 된 노드를 루트로 올려, 자주 탐색되는 노드와 그 인접 노드들이 더 빨리 탐색되도록 합니다 [1].  

데이터 개수 반환 로직을 구현하고, 예외 안전성을 테스트로 확인하고, 속도 테스트에 반복 측정을 추가할 예정입니다. 또한 현재 스플레이 트리는 검색 대상이 된 노드의 높이를 기존 위치의 부모나 조부모 위치까지만 올리도록 구현되어 있어, 이를 수정해 탐색 대상 노드가 루트 노드까지 올라가도록 할 예정입니다.

- ***클래스 템플릿***
```cpp
    template <typename DataType>
    class SplayTree;
```

- ***생성자, 할당 연산자, 소멸자***
```cpp
    SplayTree();

    SplayTree(const SplayTree& sourceTree);

    SplayTree(SplayTree&& sourceTree) noexcept;

    SplayTree& operator=(const SplayTree& sourceTree);

    SplayTree& operator=(SplayTree&& sourceTree) noexcept;

    ~SplayTree() noexcept;
```

- ***퍼블릭 메서드***
```cpp
    //RETURN: newKey와 같은 키의 노드가 이미 존재하는 경우에 false를 반환함
    template <typename InsertDataType = DataType>
    bool Insert(std::int32_t newKey, InsertDataType&& newData);

    //RETURN: targetKey와 같은 키를 가진 노드가 존재하지 않는 경우에 false를 반환함
    bool Retrieve(std::int32_t targetKey, DataType& outData);

    //RETURN: targetKey와 같은 키를 가진 노드가 존재하지 않는 경우에 false를 반환함
    bool Remove(std::int32_t targetKey);

    void RemoveTree() noexcept;

    void CopyTree(const BSTTemplate<NodeType, DataType>& sourceBST);

    //NOTE: 디버깅용
    void PreorderPrint() const;
    void InorderPrint() const;
    void PostorderPrint() const;
```

<br>




### 1.3. AVL 트리
AVL 트리는 키가 정렬된 노드들이 삽입될 때 이진 탐색 트리에서 발생하는 편향 문제를 해결한 균형 트리 구조입니다.

노드의 왼쪽 서브트리와 오른쪽 서브트리의 높이 차가 2 이상이 될 경우 해당 위치를 기준으로 노드들을 회전하여 트리의 균형을 조절합니다 [1].  

데이터 개수 반환 로직을 구현하고, 예외 안전성을 테스트로 확인하고, 속도 테스트에 반복 측정을 추가할 예정입니다. 또한 이동 시맨틱을 추가로 구현하고, 예외 안전성을 고려하여 구현을 수정할 예정입니다.

- ***클래스 템플릿***
```cpp
    template <typename DataType>
    class AVLTree;
```

- ***생성자, 할당 연산자, 소멸자***
```cpp
    AVLTree();
```

- ***퍼블릭 메서드***
```cpp
    void Insert(std::int32_t newKey, DataType newData);

    //RETURN: targetKey와 같은 키를 가진 노드가 존재하지 않는 경우에 false를 반환함
    bool Retrieve(std::int32_t targetKey, DataType& outData);

    void Remove(std::int32_t targetKey);

    void RemoveTree() noexcept;

    void CopyTree(const BSTTemplate<NodeType, DataType>& sourceBST);

    //NOTE: 디버깅용
    void PreorderPrint() const;
    void InorderPrint() const;
    void PostorderPrint() const;
```

<br>




<!----------------------------------------------------------------------------------------------------------------------------------------------->
## 2. 폴더 구조
- `1.BST`
    - `BST.h`

    - `TestingBST.cpp`

    - `FeatureTestAnswer.txt`

- `2.SplayTree`
    - `SplayTree.h`

    - `TestingSplayTree.cpp`

    - `FeatureTestAnswer.txt`

- `3.AVLTree`
    - `AVLTree.h`

    - `TestingAVLTree.cpp`

    - `FeatureTestAnswer.txt`

- `Common`
    - `BSTTemplate.h`  
        이진 탐색 트리 템플릿으로, 세 종류의 트리가 모두 이를 상속받습니다.

    - `Stack.h`  
        트리의 순회, 회전 등의 로직에서 이전 경로를 기억하기 위해 사용하는 스택입니다.

    - `Debug.h`  
        로그 출력 매크로, 누수 추적용 `new` 함수 매크로가 정의되어 있습니다.

<br>




<!----------------------------------------------------------------------------------------------------------------------------------------------->
## 3. 사용 방법
### 3.1. 외부 프로젝트 사용 방법
본 트리 자료구조들은 별도의 정적, 동적 라이브러리 없이 사용할 수 있도록 헤더만으로 구현되어 있습니다.

1. 사용하려는 트리의 헤더 파일을 프로젝트 디렉터리 혹은 추가 포함 디렉터리에 둡니다.  
예: `SplayTree.h`

2. 트리 구현을 위해 참조하는 `Common` 폴더 내 모든 헤더 파일도 함께 둡니다.  
예: `BSTTemplate.h`, `Stack.h`, `Debug.h`

3. 소스 코드에서 사용할 트리의 헤더 파일을 포함한 뒤, 보관할 데이터의 타입을 템플릿 인자로 지정하여 트리 객체를 선언합니다.
    ```cpp
        #include "SplayTree.h"

        SplayTree<float> testSplayTree;

        int testKey = 5;
        float retrievedData = 0.0f;

        testSplayTree.Insert(testKey, 3.14f);
        testSplayTree.Retrieve(testKey, retrievedData);
        testSplayTree.Remove(testKey);
    ```

<br>




### 3.2. 테스트 실행 방법
테스트는 Visual Studio 2026을 기준으로 구현되었습니다.

1. 리포지토리를 다운로드합니다.

2. 로컬의 리포지토리 디렉터리에 포함된 `BodoTree.sln` 솔루션 파일을 더블 클릭합니다.

3. Visual Studio가 실행되면 오른쪽의 솔루션 탐색기 창을 확인합니다.  
(해당 솔루션 탐색기 창이 없는 경우 상단의 보기(V) 메뉴에서 솔루션 탐색기(P)를 누릅니다.)

4. 해당 솔루션 탐색기 창에서 실행해 보고 싶은 트리 프로젝트를 우클릭합니다.

5. 우클릭하면 나타나는 메뉴에서 시작 프로젝트로 설정을 누르거나, 단축키 `A`를 누릅니다.

6. 기능 테스트를 실행하려면, Visual Studio 상단의 구성을 `Debug`, 플랫폼을 `x64`로 설정하고, 디버깅 시작 단축키인 F5를 누릅니다.  
실행 결과가 명령 프롬프트 창에 출력됩니다. 또한 메모리 누수가 존재한다면 Visual Studio 하단의 출력(output) 창에 누수 정보가 출력됩니다.

7. 속도 테스트를 실행하려면, 상단의 구성을 `Release`로 변경하고, 디버깅 없이 실행(Ctrl+F5)을 누릅니다.  
테스트 과정과 결과가 명령 프롬프트 창에 출력됩니다.

<br>




<!----------------------------------------------------------------------------------------------------------------------------------------------->
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
|..             |코드 생성  |런타임 라이브러리      |`다중 스레드 DLL(/MD)`                             |
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
|복사 삽입  |16.46 초   |15.83 초   |
|이동 삽입  |15.77 초   |14.58 초   |
|검색       |16.97 초   |17.64 초   |
|삭제       |21.92 초   |18.61 초   |
|소멸       |4.51 초    |4.38 초    |

- 어셈블리 파일 확인 결과 `BST`의 삽입과 검색 메서드는 모두 인라이닝되었지만 삭제 메서드는 인라이닝되지 않았습니다. 따라서 유독 삭제 메서드의 속도 차이가 큰 원인은 인라이닝되지 못한 데 있는 것으로 판단됩니다.

<br>




##### 4.3.1.2. 랜덤 로컬 워크로드
|연산       |`BST`      |`std::map` |
|-----------|----------:|----------:|
|복사 삽입  |7.75 초    |4.09 초    |
|이동 삽입  |6.74 초    |3.34 초    |
|검색       |6.60 초    |3.65 초    |
|삭제       |7.70 초    |4.11 초    |
|소멸       |3.51 초    |3.38 초    |

- 워크로드가 지역적 선형성을 가지게 되므로 앞선 랜덤 워크로드 테스트에 비해 `BST`의 트리 높이는 더 높아집니다. 그럼에도 삽입, 검색, 삭제 메서드가 더 빨라진 이유는 캐시 히트율 상승 때문일 가능성이 있습니다.

- `BST`와 `std::map`의 속도 차이가 벌어진 이유도 설계와 구현상의 캐시 히트율 최적화 차이 때문일 가능성이 있습니다.

<br>




##### 4.3.1.3. 선형 증가 워크로드
|연산       |`BST`      |`std::map` |
|-----------|----------:|----------:|
|복사 삽입  |시간 초과  |1.79 초    |
|이동 삽입  |시간 초과  |1.51 초    |
|검색       |시간 초과  |0.66 초    |
|삭제       |0.02 초    |1.84 초    |
|소멸       |0.36 초    |1.32 초    |

- 선형 워크로드는 `BST`를 편향시켜 리스트와 같은 형상이 되도록 합니다. 이로 인해 삽입 메서드와 검색 메서드의 전체 연산 과정이 `O(N^2)`의 시간 복잡도를 지니게 되기 때문에 50초를 넘겨 시간 초과로 처리됩니다.

- 시간 초과로 삽입이 덜 이루어졌으므로, 이후의 '삭제', '소멸'의 측정 시간은 신뢰할 수 없습니다.

- `BST`와 달리 `std::map`은 균형을 유지하는 트리이기 때문에 선형 워크로드에 대해서도 전체 연산이 `O(N log N)`의 시간 복잡도를 가지므로 매우 빠른 속도를 보입니다. 게다가 선형 워크로드가 가진 지역성으로 캐시 히트율이 증가해 랜덤 워크로드 테스트보다 훨씬 빠른 속도를 보이는 것으로 추측합니다.

<br>




##### 4.3.1.4. 선형 감소 워크로드
|연산       |`BST`      |`std::map` |
|-----------|----------:|----------:|
|복사 삽입  |시간 초과  |1.89 초    |
|이동 삽입  |시간 초과  |1.46 초    |
|검색       |시간 초과  |0.68 초    |
|삭제       |0.02 초    |1.64 초    |
|소멸       |0.35 초    |1.98 초    |

- 앞선 선형 증가 워크로드와 해석이 같습니다.

<br>




#### 4.3.2. 스플레이 트리
##### 4.3.2.1. 랜덤 워크로드
|연산       |`SplayTree`|`std::map` |
|-----------|----------:|----------:|
|복사 삽입  |18.20 초   |16.47 초   |
|이동 삽입  |17.20 초   |16.06 초   |
|검색       |시간 초과  |17.01 초   |
|삭제       |시간 초과  |21.99 초   |
|소멸       |9.42 초    |5.03 초    |

- 조정이 일어나지 않는 삭제 메서드도 느린 것으로 보아, 앞선 검색 메서드에서 스플레이 조정이 트리를 편향시켜 성능을 저하시키는 것으로 추측합니다.

<br>




##### 4.3.2.2. 랜덤 로컬 워크로드
|연산       |`SplayTree`|`std::map` |
|-----------|----------:|----------:|
|복사 삽입  |7.88 초    |4.02 초    |
|이동 삽입  |7.34 초    |3.35 초    |
|검색       |시간 초과  |3.65 초    |
|삭제       |시간 초과  |4.21 초    |
|소멸       |6.81 초    |3.18 초    |

- `SplayTree`에서 삽입의 속도보다 검색의 속도가 느리다는 점, 그리고 검색 이후 삭제 메서드에서도 속도가 느려졌다는 점을 고려하면, 앞선 랜덤 워크로드 테스트와 마찬가지로 검색 메서드에서 수행하는 스플레이 조정이 트리를 편향시키는 것으로 추측합니다.

<br>




##### 4.3.2.3. 선형 증가 워크로드
|연산       |`SplayTree`|`std::map` |
|-----------|----------:|----------:|
|복사 삽입  |시간 초과  |1.98 초    |
|이동 삽입  |시간 초과  |1.46 초    |
|검색       |0.28 초    |0.72 초    |
|삭제       |40.67 초   |1.78 초    |
|소멸       |0.40 초    |1.30 초    |

- 앞선 랜덤 로컬 워크로드와 달리 본 워크로드의 검색에서는 스플레이 조정으로 인해 다음 검색 대상이 항상 루트의 자식 노드에 위치하게 되므로 매우 빠른 속도를 보입니다. 반대로 삭제 메서드는 검색으로 인해 트리가 조정되어 삭제할 노드가 루트 노드에 위치하지 않게 되므로 검색보다 느린 것으로 추측합니다.

<br>




##### 4.3.2.4. 선형 감소 워크로드
|연산       |`SplayTree`|`std::map` |
|-----------|----------:|----------:|
|복사 삽입  |시간 초과  |2.11 초    |
|이동 삽입  |시간 초과  |1.74 초    |
|검색       |0.31 초    |0.74 초    |
|삭제       |시간 초과  |1.82 초    |
|소멸       |0.42 초    |2.46 초    |

- 앞선 선형 증가 워크로드와 달리 삭제 메서드에서 시간 초과가 발생하는 원인을 아직 파악하지 못하였습니다.

<br>




#### 4.3.3. AVL 트리
##### 4.3.3.1. 랜덤 워크로드
|연산       |`AVLTree`  |`std::map` |
|-----------|----------:|----------:|
|복사 삽입  |22.83 초   |14.24 초   |
|이동 삽입  |20.89 초   |13.12 초   |
|검색       |11.79 초   |15.05 초   |
|삭제       |24.85 초   |17.52 초   |
|소멸       |4.46 초    |4.37 초    |

- `std::map` 대비 `AVLTree`의 삽입 메서드와 삭제 메서드의 상대적인 속도가 `BST`보다 느린 것은 삽입 및 삭제 메서드에 작성된 균형 유지 로직의 비효율성이 원인으로 판단됩니다.

- 삽입 메서드에 이동 시맨틱이 구현되지 않았음에도 이동 삽입이 더 빠른 속도를 보이는 이유는 삽입할 데이터 인자를 전달하는 과정에서 복사 생성자 대신 이동 생성자가 호출되기 때문으로 판단됩니다.

<br>




##### 4.3.3.2. 랜덤 로컬 워크로드
|연산       |`AVLTree`  |`std::map` |
|-----------|----------:|----------:|
|복사 삽입  |7.35 초    |3.83 초    |
|이동 삽입  |7.00 초    |3.23 초    |
|검색       |2.34 초    |3.48 초    |
|삭제       |8.49 초    |3.89 초    |
|소멸       |3.23 초    |3.12 초    |

- 앞선 `BST`의 테스트와 비슷한 결과가 나온 것으로 보아, 캐시 히트율 차이도 `std::map`과의 속도 차이의 원인 중 하나일 것으로 추측합니다.

<br>




##### 4.3.3.3. 선형 증가 워크로드
|연산       |`AVLTree`  |`std::map` |
|-----------|----------:|----------:|
|복사 삽입  |4.98 초    |1.95 초    |
|이동 삽입  |4.65 초    |1.52 초    |
|검색       |0.66 초    |0.70 초    |
|삭제       |4.05 초    |1.86 초    |
|소멸       |0.97 초    |0.93 초    |

- 앞선 `BST`와 달리 `AVLTree`는 균형 트리이므로 시간 초과가 발생하지 않았습니다.

<br>




##### 4.3.3.4. 선형 감소 워크로드
|연산       |`AVLTree`  |`std::map` |
|-----------|----------:|----------:|
|복사 삽입  |5.00 초    |1.82 초    |
|이동 삽입  |4.70 초    |1.49 초    |
|검색       |0.67 초    |0.64 초    |
|삭제       |10.07 초   |2.18 초    |
|소멸       |1.06 초    |1.34 초    |

- 선형 증가 워크로드 테스트와 비교했을 때 삭제 소요 시간이 약 2배가 되었습니다. 아직 원인을 파악하지 못하였습니다.

<br>




<!----------------------------------------------------------------------------------------------------------------------------------------------->
## 5. 구현 예정
- **공통**  
  - 데이터 개수를 저장하는 멤버 변수를 반환하는 메서드를 작성하기
  - 예외 안전성 테스트를 추가하고 결과를 작성하기
  - 주어진 횟수로 속도 측정 테스트를 반복하고, 평균과 분산을 구할 수 있도록 하기

<br>

- **BST 개선**
    - 불필요한 포워딩이나 함수 객체가 있는지 확인하기
    - 삭제 메서드의 코드 분기와 크기를 줄여서 인라이닝이 일어나도록 하기

<br>

- **스플레이 트리 개선**
    - 조정이 루트까지 이루어지도록 하여 속도 개선하기
    - 삽입과 삭제에도 조정이 일어나도록 하여 속도 개선하기

<br>

- **AVL 트리 개선**
    - 앞선 단원의 개선 사항을 적용하기
    - 삽입, 삭제 속도 최적화하기

<br>




<!----------------------------------------------------------------------------------------------------------------------------------------------->
## 6. 구현 제외
- **iterator 클래스**  
    iterator를 이용한 트리 순회의 속도를 STL과 비교할 수 있으면 좋겠지만, 프로젝트 규모를 제한하고자 삽입-검색-삭제-소멸의 시간만 비교하기로 하였습니다.

<br>

- **키 타입 템플릿, emplace 메서드**  
   주어진 타입에 비교자가 정의되어 있는지 확인해야 하는 기능과 가변 인자 템플릿이 필요한 기능은 프로젝트 규모를 제한하고자 제외하였습니다.

<br>

- **메모리 풀**  
    메모리 풀의 연속된 공간에서 노드를 할당받도록 하면 동적 할당 횟수를 줄이고 캐시 히트율 상승을 기대할 수 있으나, 프로젝트 규모를 제한하고자 구현 대상에서 제외하였습니다.

<br>

- **세부적인 최적화**  
    삽입 메서드에서 단순한 데이터 타입의 매개변수에 대해서는 참조 방식이 아니라 값 전달 방식을 사용하도록 하는 것, 그리고 스택 자료구조의 내부 어레이가 확장될 때 이동 연산의 예외 안전성 여부를 확인하여 가능하면 복사 대신 이동을 사용하도록 하는 것은 프로젝트 규모를 제한하고자 제외하였습니다.

<br>

- **노드의 부모 포인터**  
    스택을 이용하지 않고 순회 및 조정을 할 수 있도록 하면 속도와 예외 안전성을 높일 수 있으나, 이를 반영하기 위해서는 각 트리의 주요 메서드들을 모두 수정해야 하므로 프로젝트 규모를 제한하고자 제외하였습니다.

<br>




<!----------------------------------------------------------------------------------------------------------------------------------------------->
## 7. 참고 자료
### 7.1. 인용 참고 자료
[1] "C C++로 배우는 자료구조론" (주우석 지음 / 한빛아카데미 출판 / 2015년 발행)

<br>




### 7.2. 구현 참고 자료
"SW코딩 역량을 위한 C++ 프로그래밍" (홍봉희 지음 / 정익사 출판 / 2017년 발행)

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