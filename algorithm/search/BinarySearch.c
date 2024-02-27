#include <stdio.h>

#define BUFFER_SIZE 10

/* 二分查找 : 已经排好序的数组 */
int binarySearch(int *nums, int numSize, int target)
{
    int begin = 0;
    int end = numSize - 1;

    int midIndex = 0;
    while (begin <= end)
    {
        /* 更新中间位置 */
        midIndex = (begin + end) >> 1;
        if (nums[midIndex] > target)
        {
            end = midIndex - 1;
        }
        else if (nums[midIndex] < target)
        {
            begin = midIndex + 1;
        }
        else
        {
            return midIndex;
        }
    }
    return -1;
}



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

    int index = binarySearch(nums, len, 35);
    printf("index:%d\n", index);

    index = binarySearch(nums, len, 4);
    printf("index:%d\n", index);

    index = binarySearch(nums, len, 47);
    printf("index:%d\n", index);

    index = binarySearch(nums, len, 5);
    printf("index:%d\n", index);

    return 0;
}