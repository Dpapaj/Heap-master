/*!
 * \file       heap.c
 * \author     Ondřej Ševčík
 * \date       6/2019
 * \brief      Implementation of the heap module in version min-heap.
 * **********************************************************************
 * \attention
 * &copy; Copyright (c) 2022 FAI UTB. All rights reserved.
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/* Includes --------------------------------------------------------------------------------------*/
#include "heap.h"

#include <stdlib.h>
#include <string.h>

/* Private macro ---------------------------------------------------------------------------------*/
#define UNUSED(x) (void)x

/* Private types ---------------------------------------------------------------------------------*/
/* Private variables -----------------------------------------------------------------------------*/
/* Private function declarations -----------------------------------------------------------------*/
/* Exported functions definitions ----------------------------------------------------------------*/



bool Heap_Init(tHeap *heap)
{
    if (heap == NULL)
    {
        return false;
    }

    heap->array = myMalloc(MAX_ITEMS_START * sizeof(Data_t));

    if (heap->array == NULL)
    {
        return false;
    }

    heap->count = 0;
    heap->maxItems = MAX_ITEMS_START;


    return true;
}

bool Heap_Insert(tHeap *heap, Data_t insertData)
 {
    if (heap == NULL)
    {
        return false;
    }

    // Check if there is enough space in the heap array
    if (heap->count == heap->maxItems)
    {
        // Double the size of the heap array
        size_t newMaxItems = heap->maxItems * 2;
        Data_t *newArray = myRealloc(heap->array, newMaxItems * sizeof(Data_t));

        if (newArray == NULL)
        {
            return false;
        }

        heap->array = newArray;
        heap->maxItems = newMaxItems;
    }

    // Add the new data to the end of the heap array
    heap->array[heap->count] = insertData;
    heap->count++;

    // Reorder the heap by swapping the new data with its parent until it is in the correct position
    size_t currentIndex = heap->count - 1;
    while (currentIndex > 0)
    {
        size_t parentIndex = (currentIndex - 1) / 2;

        if (Data_Cmp(&heap->array[currentIndex], &heap->array[parentIndex]) >= 0)
        {
            break;
        }

        Data_t tmp = heap->array[currentIndex];
        heap->array[currentIndex] = heap->array[parentIndex];
        heap->array[parentIndex] = tmp;

        currentIndex = parentIndex;
    }

    return true;
}


void Heap_Destruct(tHeap *heap)
{
    if(heap == NULL)
    {
        return;
    }

    if(heap ->array != NULL)
    {
        myFree(heap->array);
        heap->array = NULL;
    }


    heap->count = 0;
    heap->maxItems = 0;
    return;
}

bool Heap_FindMin(tHeap heap, Data_t *value)
{
    if(heap.array == NULL || heap.count == 0 || value == NULL)
    {
        return false;
    }

    *value = heap.array[0];
    return true;
}

bool Heap_DeleteMin(tHeap *heap, Data_t *deletedValue)
{
    if (heap == NULL || heap->count == 0)
    {
        return false;
    }

    if (deletedValue != NULL)
    {
        *deletedValue = heap->array[0];
    }

    // Replace the root of the heap with the last item in the heap array
    heap->array[0] = heap->array[heap->count - 1];
    heap->count--;

    // Reorder the heap by swapping the root with its smallest child until it is in the correct position
    size_t currentIndex = 0;
    while (true)
    {
        size_t leftChildIndex = 2 * currentIndex + 1;
        size_t rightChildIndex = 2 * currentIndex + 2;

        if (leftChildIndex >= heap->count)
        {
            break;
        }

        size_t smallestChildIndex = leftChildIndex;
        if (rightChildIndex < heap->count && Data_Cmp(&heap->array[rightChildIndex], &heap->array[leftChildIndex]) < 0)
        {
            smallestChildIndex = rightChildIndex;
        }

        if (Data_Cmp(&heap->array[currentIndex], &heap->array[smallestChildIndex]) <= 0)
        {
            break;
        }

        Data_t tmp = heap->array[currentIndex];
        heap->array[currentIndex] = heap->array[smallestChildIndex];
        heap->array[smallestChildIndex] = tmp;

        currentIndex = smallestChildIndex;
    }

    return true;
}

void Heap_Process(tHeap heap, heapProcessCB cb)
{
    if (heap.array == NULL || heap.count == 0 || cb == NULL)
    {
        return;
    }

    for (size_t i = 0; i < heap.count; i++)
    {
        cb(i, &(heap.array[i]));
    }
}

bool Heap_Empty(tHeap heap)
{
    if(heap.array == NULL || heap.count == 0)
    {
        return true;
    }
    return false;
}

unsigned Heap_Count(tHeap heap)
{
  return heap.count;
}
/* Private function definitions ------------------------------------------------------------------*/
