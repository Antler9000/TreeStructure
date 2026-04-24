#include "heap.h"

int main()
{
	MinHeap testHeap;

	testHeap.Push(345);
	testHeap.Push(234);
	testHeap.Push(123);
	testHeap.Push(500);
	testHeap.Push(600);
	testHeap.Push(400);
	cout << testHeap.Pop() << endl;
	cout << testHeap.Pop() << endl;
	cout << testHeap.Pop() << endl;
	cout << testHeap.Pop() << endl;
	cout << testHeap.Pop() << endl;
	cout << testHeap.Pop() << endl;

	return 0;
}