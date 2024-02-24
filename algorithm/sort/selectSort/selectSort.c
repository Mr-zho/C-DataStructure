#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 10

static int swapNum(int *val1, int *val2)
{
    int tmpVal = *val1;
    *val1 = *val2;
    *val2 = tmpVal;

    return 0;
}

/* 找到数组的最小值 */
int findNumMinVal(int *nums, int numSize, int *ppos)
{
    int mini = nums[0];
    for (int pos = 0; pos < BUFFER_SIZE; pos++)
    {
        if (nums[pos] < mini)
        {
            mini = nums[pos];
            *ppos = pos;
        } 
    }
    return mini;
}

/* 找到数组指定范围的最小值 */
static int findNumRangeMinVal(int *nums, int begin, int end, int *mini, int *minPos)
{
    int min = nums[begin];
    for (int pos = begin; pos < end; pos++)
    {
        if (nums[pos] < min)
        {
            min = nums[pos];
            *minPos = pos;
        } 
    }
    *mini = min;
    return 0;
}

int selectSort01(int *nums, int numSize)
{
    int mini = 0;
    int minPos = 0;
    for (int pos = 0; pos < BUFFER_SIZE; pos++)
    {
        for (int idx = pos + 1; idx < BUFFER_SIZE; idx++)
        {
            if (nums[idx] < mini)
            {
                mini = nums[idx];
                minPos = idx;
            } 
        }
        /* 找到之后的最小值. */
        if (nums[pos] > mini)
        {
            swapNum(&(nums[pos]), &(nums[minPos]));
        }
    }
}

int selectSort02(int *nums, int numSize)
{
    int mini = 0;
    int minPos = 0;
    for (int pos = 0; pos < BUFFER_SIZE; pos++)
    {
        findNumRangeMinVal(nums, pos, BUFFER_SIZE, &mini, &minPos);
        /* 找到之后的最小值. */
        if (nums[pos] > mini)
        {
            swapNum(&(nums[pos]), &(nums[minPos]));
        }
    }
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
    selectSort(nums, BUFFER_SIZE);

    printNums(nums, BUFFER_SIZE);
    return 0;
}