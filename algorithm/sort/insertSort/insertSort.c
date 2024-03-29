#include <stdio.h>


#define BUFFER_SIZE 10

static int swapNum(int *val1, int *val2)
{
    int tmpVal = *val1;
    *val1 = *val2;
    *val2 = tmpVal;

    return 0;
}

static int searchInsertPos(int* nums, int numsSize, int target) 
{
    int begin = 0;
    int end = numsSize - 1;
    int midIndex = 0;
    while (begin <= end)
    {
        midIndex = (begin + end) >> 1;
        if (nums[midIndex] <= target)
        {
            begin = midIndex + 1;
        }
        else
        {
            end = midIndex - 1;
        } 
    }
    return begin;
}

/* 插入排序 */
int insertSort(int *nums, int numSize)
{
    /* 插入排序默认第一个元素已经排好序了. */

    int insertPos = 0;
    for (int idx = 1; idx < numSize; idx++)
    {
        int copyNum = nums[idx];
        int prevIdx = idx - 1;

        /* 找到要排序元素要插入的位置 O(logN) */
        insertPos = searchInsertPos(nums, idx, copyNum);

        #if 0
        while (nums[prevIdx] > copyNum && prevIdx >= 0)
        {
            nums[prevIdx + 1] = nums[prevIdx];
            prevIdx--;
        }
        // nums[prevIdx] <= copyNum && prevIdx = -1
        nums[prevIdx + 1] = copyNum;
        #else
        /* 数组迁移, 从后向前迁移. */
        for (int jdx = idx; jdx > insertPos; jdx--)
        {
            nums[jdx] = nums[jdx - 1];
        }
        nums[insertPos] = copyNum;
        #endif
    }
    
    return 0;
}

int printNums(int *nums, int numSize)
{
    for (int idx = 0; idx < numSize; idx++)
    {
        printf("%d\t", nums[idx]);
    }
    printf("\n");
}

int main()
{
    int nums[BUFFER_SIZE] = {7, 21, 12, 5, 32, 45, 17, 87, 2, 9};
    insertSort(nums, BUFFER_SIZE);

    printNums(nums, BUFFER_SIZE);
    return 0;
}