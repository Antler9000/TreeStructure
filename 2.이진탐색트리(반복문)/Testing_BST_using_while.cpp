//디버그 출력문들을 활성화하고 싶을 시 주석을 해제할 것
//#define TREE_LOG	
//#define TREE_ERROR
//#define TREE_WARNING

#include "BST_using_while.h"	//정의한 BST를 테스팅함

int main()
{
	Stack<int> testStackInt;
	testStackInt.Push(1);
	testStackInt.Push(2);
	testStackInt.Push(3);
	testStackInt.Push(4);
	testStackInt.Push(5);
	
	int getTopRetrieved = 0;
	testStackInt.GetTop(getTopRetrieved);
	cout << "get top is " << getTopRetrieved << endl;

	Stack<int> testCopyStackInt = testStackInt;
	testCopyStackInt.Push(6);

	getTopRetrieved = 0;
	testStackInt.GetTop(getTopRetrieved);
	cout << "original stack get top is " << getTopRetrieved << endl;

	getTopRetrieved = 0;
	testCopyStackInt.GetTop(getTopRetrieved);
	cout << "copy dest stack get top is " << getTopRetrieved << endl;

	Stack<int> testMoveStackInt = move(testStackInt);
	testMoveStackInt.Push(7);

	getTopRetrieved = 0;
	testStackInt.GetTop(getTopRetrieved);
	cout << "original stack get top is " << getTopRetrieved << endl;

	getTopRetrieved = 0;
	testMoveStackInt.GetTop(getTopRetrieved);
	cout << "move dest stack get top is " << getTopRetrieved << endl;

	BST testBST =  BST();
	testBST.Insert(5, 1515);
	testBST.Insert(7, 2727);
	testBST.Insert(3, 1313);
	testBST.Insert(4, 2424);
	testBST.Insert(6, 3636);
	testBST.Insert(1, 5151);
	testBST.Insert(8, 5858);
	testBST.PreorderPrint();
	cout << endl;

	cout << "retrieve test" << endl;
	int retrievedData = 0;
	testBST.Retrieve(7, retrievedData);
	cout << "retrieved Data : " << retrievedData << endl;

	cout << "copy test" << endl;
	BST copied_test_BST = BST();
	copied_test_BST.CopyTree(testBST);
	copied_test_BST.PreorderPrint();
	cout << endl;

	cout << "remove test" << endl;
	testBST.PreorderPrint();

	testBST.Remove(7);
	testBST.PreorderPrint();
	cout << endl;

	testBST.Remove(3);
	testBST.PreorderPrint();
	cout << endl;

	testBST.Remove(5);
	testBST.PreorderPrint();
	cout << endl;

	testBST.Remove(4);
	testBST.PreorderPrint();
	cout << endl;

	testBST.Remove(6);
	testBST.PreorderPrint();
	cout << endl;

	testBST.Remove(1);
	testBST.PreorderPrint();
	cout << endl;

	testBST.Remove(8);
	testBST.PreorderPrint();
	cout << endl;

	cout << "copied tree independency test" << endl;
	copied_test_BST.PreorderPrint();

	cout << "ended" << endl;

	return 0;
}