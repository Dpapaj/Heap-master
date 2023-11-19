/*!
 * \file       main.c
 * \author     Adam Jurča
 * \date       26.3.2021
 * \brief      Main file for heap
 * **************************************************************
 * \attention
 * &copy; Copyright (c) 2022 FAI UTB. All rights reserved.
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/* Private includes -------------------------------------------------------- */
#include "heap.h"
#include "ioutils.h"

#include <ctype.h>
#include <stdio.h>

static const char menu[] = "----------\n\n"
                           "0: Heap_Init,\n"
                           "1: Heap_Insert,\n"
                           "2: Heap_Print,\n"
                           "3: Heap_DeleteMin\n"
                           "4: Heap_FindMin\n"
                           "M: Menu\n"
                           "E: END";

static bool menuRequireInit(char userInput);
static void print(size_t index, const Data_t *item);

int main()
{
  tHeap heap;
  Data_t dataPerson;

  bool init = false;
  bool running = true;
  char userInput;

  puts(menu);

  while (running) {
    running = io_utils_get_char(&userInput);
    printf("%c\n", userInput);

    if (init == false && menuRequireInit(userInput)) {
      puts("Heap initialization required!");
      continue;
    }

    switch (userInput) {
      case '0':
        puts("Your choice: 0 - Heap_Init\n");
        if (init == false) {
          puts("Initializing heap!");
          init = Heap_Init(&heap);
        } else {
          puts("Heap was already initialized!");
        }
        break;
      case '1':
        puts("Your choice: 1 - Heap_Insert\n");
        Data_Get(&dataPerson);
        Heap_Insert(&heap, dataPerson);
        break;
      case '2':
        puts("Your choice: 2 - Heap_Print\n");
        Heap_Process(heap, print);
        break;
      case '3':
        puts("Your choice: 3 - Heap_DeleteMin\n");
        if (Heap_DeleteMin(&heap, &dataPerson)) {
          printf("Deleted item: ");
          Data_Print(&dataPerson);
        } else {
          puts("Heap is empty.");
        }
        break;
      case '4':
        puts("Your choice: 4 - Heap_FindMin\n");
        if (Heap_FindMin(heap, &dataPerson)) {
          printf("The smallest item is: ");
          Data_Print(&dataPerson);
        } else {
          puts("Heap is empty.");
        }
        break;
      case 'm':
      case 'M':
        puts(menu);
        break;
      case 'e':
      case 'E':
        running = false;
        break;
      default:
        puts("Unknown option!");
        break;
    }

    puts("\nType char 0-A, E=END, M=MENU:\n"
         "************************************************************");
  }

  Heap_Destruct(&heap);
  return 0;
}

static bool menuRequireInit(const char userInput)
{
  switch (tolower(userInput)) {
    case 'e':
    case 'm':
    case '0':
      return false;
    default:
      return true;
  }
}

static void print(size_t index, const Data_t *item)
{
  printf("Index %zu \t", index + 1);
  Data_Print(item);
}