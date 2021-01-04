#pragma once
#include "SinglyLinkedList.h"
#include <stdlib.h>
class FreeListAllocator
{

private:
	const static size_t ALIGNMENT = 4;

	struct FreeHeader
	{
		size_t blockSize;
	};

	struct AllocationHeader
	{
		size_t blockSize;
		//padding can also be saved as char, becasue it will only be a small number, using char will require less memory
		size_t padding;
	};

	void* startPtr;
	size_t totalSize;
	SinglyLinkedList<FreeHeader> freeList;
	typedef SinglyLinkedList<FreeHeader>::Node Node;

	void coalescence(Node* prevNode, Node* freeNode);
	void find(const size_t size, size_t& padding, Node*& previousNode, Node*& foundNode);
	const size_t calculatePadding(const size_t baseAddress);
	const size_t calculatePaddingWithHeader(const size_t baseAddress, const size_t headerSize);


public:
	FreeListAllocator(const size_t size);
	void init();
	void* allocate(const size_t size);
	void free(void* ptr);


};

