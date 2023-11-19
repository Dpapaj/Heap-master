/*!
 * \file       tests.cpp
 * \author     Jurena
 * \date       9. 2. 2022
 * \brief      Unit tests for vector module.
 * ******************************************
 * \attention
 * &copy; Copyright (c) 2022 FAI UTB. All rights reserved.
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/* Includes --------------------------------------------------------------------------------------*/

#include "fff.h"
#include "gmock/gmock.h"

#include "gtest/gtest.h"
#include <limits>
#include <vector>

extern "C" {
#include "heap.h"
}

/* Private types ---------------------------------------------------------------------------------*/
/* Private macros --------------------------------------------------------------------------------*/
#define TEST_DATA_SIZE (5)

/* Private variables -----------------------------------------------------------------------------*/
DEFINE_FFF_GLOBALS
FAKE_VOID_FUNC(MockProcessCB, size_t, const Data_t *)

static const Data_t testData[TEST_DATA_SIZE] = {
  {"9", 9, 0, 0}, {"5", 5, 0, 0}, {"6", 6, 0, 0}, {"2", 2, 0, 0}, {"3", 3, 0, 0}};

static const Data_t testExpected[TEST_DATA_SIZE] = {
  testData[3], testData[4], testData[2], testData[0], testData[1]};

/* Private function declarations -----------------------------------------------------------------*/
/* Test functions --------------------------------------------------------------------------------*/
bool operator==(const Data_t &lhs, const Data_t &rhs)
{
  return Data_Cmp(&lhs, &rhs) == 0;
}

class HeapTest : public ::testing::Test
{
  // Test interface
protected:
  virtual void SetUp() override { Heap_Init(&heap); }

  virtual void TearDown() override { Heap_Destruct(&heap); }

  tHeap heap;
};

class HeapTestParam : public ::testing::TestWithParam<std::tuple<Data_t, std::vector<Data_t>>>
{
  // Test interface
protected:
  virtual void SetUp() override
  {
    Heap_Init(&heap);
    for (int i = 0; i < TEST_DATA_SIZE; i++) {
      Heap_Insert(&heap, testData[i]);
    }
  }

  virtual void TearDown() override { Heap_Destruct(&heap); }

  tHeap heap;
};

TEST(Heap, init)
{
  tHeap heap = {NULL, 10, 0};

  ASSERT_TRUE(Heap_Init(&heap));
  ASSERT_EQ(heap.count, 0);
  ASSERT_GT(heap.maxItems, 0);
}

TEST(Heap, initNull)
{
  ASSERT_FALSE(Heap_Init(NULL));
}

TEST(Heap, destruct)
{
  tHeap heap;
  Heap_Init(&heap);

  Heap_Destruct(&heap);
  ASSERT_EQ(heap.array, nullptr);
  ASSERT_EQ(heap.maxItems, 0);
  ASSERT_EQ(heap.count, 0);
}

TEST_F(HeapTest, insertSingleValue)
{
  ASSERT_TRUE(Heap_Insert(&heap, *testData));  // 9
  ASSERT_EQ(*heap.array, *testData);
}

TEST_F(HeapTest, insertTwoValuesSecondIsBiggerThanFirst)
{
  ASSERT_TRUE(Heap_Insert(&heap, *(testData + 1)));  // 5
  ASSERT_TRUE(Heap_Insert(&heap, *testData));        // 9
  ASSERT_EQ(*heap.array, *(testData + 1));           // 9
  ASSERT_EQ(*(heap.array + 1), *testData);           // 5
}

TEST_F(HeapTest, insertTwoValuesSecondIsSmallerThanFirst)
{
  ASSERT_TRUE(Heap_Insert(&heap, *testData));        // 9
  ASSERT_TRUE(Heap_Insert(&heap, *(testData + 1)));  // 5
  ASSERT_EQ(*heap.array, *(testData + 1));           // 5
  ASSERT_EQ(*(heap.array + 1), *testData);           // 9
}

TEST_F(HeapTest, insertThreeValuesSecondAndThirdIsBiggerThanFirst)
{
  ASSERT_TRUE(Heap_Insert(&heap, *(testData + 1)));  // 5
  ASSERT_TRUE(Heap_Insert(&heap, *(testData + 2)));  // 6
  ASSERT_TRUE(Heap_Insert(&heap, *testData));        // 9
  ASSERT_EQ(*heap.array, *(testData + 1));           // 5
  ASSERT_EQ(*(heap.array + 1), *(testData + 2));     // 6
  ASSERT_EQ(*(heap.array + 2), *testData);           // 9
}

TEST_F(HeapTest, insertBiggestSmallerAndSmallestValues)
{
  ASSERT_TRUE(Heap_Insert(&heap, *testData));        // 9
  ASSERT_TRUE(Heap_Insert(&heap, *(testData + 2)));  // 6
  ASSERT_TRUE(Heap_Insert(&heap, *(testData + 1)));  // 5
  ASSERT_EQ(*heap.array, *(testData + 1));           // 5
  ASSERT_EQ(*(heap.array + 1), *testData);           // 9
  ASSERT_EQ(*(heap.array + 2), *(testData + 2));     // 6
}

TEST_F(HeapTest, insertMoreValuesThanDefaultStorage)
{
  for (int i = 0; i < TEST_DATA_SIZE; i++) {
    ASSERT_TRUE(Heap_Insert(&heap, testData[i]));
  }

  ASSERT_THAT(std::vector<Data_t>(heap.array, heap.array + Heap_Count(heap)),
              ::testing::ElementsAreArray(testExpected, Heap_Count(heap)));
}

TEST(Heap, insertNull)
{
  Data_t data;
  ASSERT_FALSE(Heap_Insert(NULL, data));
}

TEST_F(HeapTest, heapIsEmptyAfterInit)
{
  ASSERT_TRUE(Heap_Empty(heap));
}

TEST_F(HeapTest, heapIsNotEmptyAfterInsert)
{
  Data_t data = {"John", 1, 2, 3};

  Heap_Insert(&heap, data);
  ASSERT_FALSE(Heap_Empty(heap));
}

TEST_F(HeapTest, heapFindMinWithSingleValue)
{
  Data_t data;

  Heap_Insert(&heap, *testData);  // 9
  Heap_FindMin(heap, &data);

  ASSERT_EQ(data, *testData);
}

TEST_F(HeapTest, heapFindMinTwoValues)
{
  Data_t data;

  Heap_Insert(&heap, *testData);        // 9
  Heap_Insert(&heap, *(testData + 1));  // 5
  Heap_FindMin(heap, &data);

  ASSERT_EQ(data, *(testData + 1));
}

TEST_F(HeapTest, heapFindMinThreeValues)
{
  Data_t data;

  Heap_Insert(&heap, *testData);        // 9
  Heap_Insert(&heap, *(testData + 1));  // 5
  Heap_Insert(&heap, *(testData + 2));  // 6
  Heap_FindMin(heap, &data);

  ASSERT_EQ(data, *(testData + 1));
}

TEST_P(HeapTestParam, deletemin)
{
  Data_t min;
  auto [deleted, expectedHeap] = GetParam();
  for (size_t i = 0; i < TEST_DATA_SIZE - expectedHeap.size(); ++i) {
    Heap_DeleteMin(&heap, &min);
  }
  ASSERT_EQ(min, deleted);
  ASSERT_EQ(Heap_Count(heap), expectedHeap.size());
  ASSERT_THAT(std::vector<Data_t>(heap.array, heap.array + Heap_Count(heap)),
              ::testing::ElementsAreArray(expectedHeap));
}

INSTANTIATE_TEST_SUITE_P(
  deletemin,
  HeapTestParam,
  testing::Values(
    std::make_tuple(
      testData[3],
      std::vector<Data_t>({testData[4], testData[1], testData[2], testData[0]})),  // 3, 5, 6, 9
    std::make_tuple(testData[4],
                    std::vector<Data_t>({testData[1], testData[0], testData[2]})),  // 5, 9, 6
    std::make_tuple(testData[1], std::vector<Data_t>({testData[2], testData[0]})),  // 6, 9
    std::make_tuple(testData[2], std::vector<Data_t>({testData[0]}))));             // 9

TEST_F(HeapTest, heapProcess)
{
  Heap_Insert(&heap, *testData);
  Heap_Insert(&heap, *(testData + 1));
  Heap_Insert(&heap, *(testData + 2));

  Heap_Process(heap, MockProcessCB);

  ASSERT_EQ(MockProcessCB_fake.call_count, 3);
}

/* Private function definitions ------------------------------------------------------------------*/
