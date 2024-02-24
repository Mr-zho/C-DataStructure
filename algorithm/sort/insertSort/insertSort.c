#include <stdio.h>


#define BUFFER_SIZE 10

static int swapNum(int *val1, int *val2)
{
    int tmpVal = *val1;
    *val1 = *val2;
    *val2 = tmpVal;

    return 0;
}

/* 插入排序 */
int insertSort(int *nums, int numSize)
{
    /* 插入排序默认第一个元素已经排好序了. */

    for (int idx = 1; idx < numSize; idx++)
    {
        int copyNum = nums[idx];
        int prevIdx = idx - 1;

        while (nums[prevIdx] > copyNum && prevIdx >= 0)
        {
            nums[prevIdx + 1] = nums[prevIdx];
            prevIdx--;
        }
        // nums[prevIdx] <= copyNum && prevIdx = -1
        nums[prevIdx + 1] = copyNum;
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