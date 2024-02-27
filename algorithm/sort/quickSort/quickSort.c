#include <stdio.h>


#define BUFFER_SIZE 10

static int swapNum(int *val1, int *val2)
{
    int tmpVal = *val1;
    *val1 = *val2;
    *val2 = tmpVal;

    return 0;
}


static int innerQuickSort(int *nums, int begin, int end)
{
    if (begin >= end)
    {
        return 0;
    }

    /* 记录基准值 */
    int pivot = nums[begin];

    /* 备份begin & end */
    int tmpBegin = begin;
    int tmpEnd = end;
    while (begin < end)
    {
        while (begin < end)
        {
            /* 从右向左 */
            if (nums[end] >= pivot)
            {
                end--;
            }
            else
            {
                nums[begin++] = nums[end];
                break;
            }
        }

        while (begin < end)
        {
            /* 从左向右 */
            if (nums[begin] > pivot)
            {
                nums[end--] = nums[begin];
                break;
            }
            else
            {
                begin++;
            }
        }
    }
    /* 退出这个条件 begin == end. */
    nums[begin] = pivot;
    innerQuickSort(nums, tmpBegin, begin - 1);
    innerQuickSort(nums, begin + 1, tmpEnd);

    return 0;
}

/* 快速排序 */
int quickSort(int *nums, int numSize)
{
    if (nums == NULL)
    {
        return 0;
    }
    return innerQuickSort(nums, 0, numSize - 1);
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
    int nums[] = {31, 47, 25, 16, 4, 35, 38};

    int len = sizeof(nums) / sizeof(nums[0]);
    quickSort(nums, len);

    printNums(nums, len);
    return 0;
}

