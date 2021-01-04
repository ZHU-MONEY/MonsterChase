#include "FreeListAllocator.h"

void FreeListAllocator::coalescence(Node* prevNode, Node* freeNode)
{
	if (freeNode->next != nullptr &&
		(size_t) freeNode + freeNode->data.blockSize == (size_t) freeNode->next) {
		freeNode->data.blockSize += freeNode->next->data.blockSize;
		freeList.remove(freeNode, freeNode->next);
	}
	if (prevNode != nullptr &&
		(size_t) prevNode + prevNode->data.blockSize == (size_t) freeNode) {
		prevNode->data.blockSize += freeNode->data.blockSize;
		freeList.remove(prevNode, freeNode);
	}

}

void FreeListAllocator::find(const size_t size, size_t& padding, Node*& previousNode, Node*& foundNode)
{
	Node* it = freeList.head,
		* itPrev = nullptr;
	while (it != nullptr) {
		padding = calculatePaddingWithHeader((size_t)it, sizeof(AllocationHeader));
		size_t requiredSpace = size + padding;
		if (it->data.blockSize >= requiredSpace) {
			break;
		}
		itPrev = it;
		it = it->next;
	}
	previousNode = itPrev;
	foundNode = it;
}

const size_t FreeListAllocator::calculatePadding(const size_t baseAddress)
{
	const size_t multiplier = (baseAddress / ALIGNMENT) + 1;
	const size_t alignedAddress = multiplier * ALIGNMENT;
	const size_t padding = alignedAddress - baseAddress;
	return padding;
}

const size_t FreeListAllocator::calculatePaddingWithHeader(const size_t baseAddress, const size_t headerSize)
{
	size_t padding = calculatePadding(baseAddress);
	size_t neededSpace = headerSize;

	if (padding < neededSpace) {
		neededSpace -= padding;

		// calculate how many alignment I need, this part can also be done using a while loop, but this way is faster   
		if (neededSpace % ALIGNMENT > 0) {
			padding += ALIGNMENT * (1 + (neededSpace / ALIGNMENT));
		}
		else {
			padding += ALIGNMENT * (neededSpace / ALIGNMENT);
		}
	}

	return padding;
}

FreeListAllocator::FreeListAllocator(const size_t size)
{
	totalSize = size;
}

void FreeListAllocator::init()
{
	startPtr = malloc(totalSize);
	Node* firstNode = (Node*)startPtr;
	firstNode->data.blockSize = totalSize;
	firstNode->next = nullptr;
	freeList.head = nullptr;
	freeList.insert(nullptr, firstNode);
}

void* FreeListAllocator::allocate(const size_t size)
{
	const size_t allocationHeaderSize = sizeof(AllocationHeader);
	const size_t freeHeaderSize = sizeof(FreeHeader);

	size_t padding;
	Node* affectedNode,
		* previousNode;
	find(size, padding, previousNode, affectedNode);

	if (affectedNode == nullptr) {
		//NOT ENOUGH MEMORY
	}

	const size_t alignmentPadding = padding - allocationHeaderSize;
	const size_t requiredSize = size + padding;
	const size_t rest = affectedNode->data.blockSize - requiredSize;

	if (rest > 0) {
		// We have to split the block into the data block and a free block of size 'rest'
		//here is offsetting the pointer and cast it into a node
		Node* newFreeNode = (Node*)((size_t)affectedNode + requiredSize);
		newFreeNode->data.blockSize = rest;
		freeList.insert(affectedNode, newFreeNode);
	}
	freeList.remove(previousNode, affectedNode);

	const size_t headerAddress = (size_t)affectedNode + alignmentPadding;
	const size_t dataAddress = (size_t)affectedNode + padding;
	((AllocationHeader*)headerAddress)->blockSize = requiredSize;
	((AllocationHeader*)headerAddress)->padding = alignmentPadding;

	return (void*)dataAddress;
}

void FreeListAllocator::free(void* ptr)
{
	const size_t currentAddress = (size_t)ptr;
	const size_t headerAddress = currentAddress - sizeof(FreeListAllocator::AllocationHeader);
	const FreeListAllocator::AllocationHeader* allocationHeader{ (FreeListAllocator::AllocationHeader*) headerAddress };

	Node* freeNode = (Node*)(headerAddress);
	freeNode->data.blockSize = allocationHeader->blockSize + allocationHeader->padding;
	freeNode->next = nullptr;

	Node* it = freeList.head;
	Node* itPrev = nullptr;
	while (it != nullptr) {
		if (ptr < it) {
			freeList.insert(itPrev, freeNode);
			break;
		}
		itPrev = it;
		it = it->next;
	}

	coalescence(itPrev, freeNode);

}
