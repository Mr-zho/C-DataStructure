#include <stdio.h>

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

/* 搜索插入位置 O(log n)复杂度 */
int searchInsert01(int *nums, int numsSize, int target)
{
    if (nums == NULL)
    {
        return -1;
    }

    if (numsSize <= 0)
    {
        return -1;
    }

    int begin = 0;
    int end = numsSize - 1;

    int ret = -1;

    while (begin < end)
    {
        int mid = (begin + end) >> 1;
        if (nums[mid] == target)
        {
            ret = mid + 1;
            begin = ret;
        }
        else if (nums[mid] < target)
        {
            begin = mid + 1;
        }
        else if (nums[mid] > target)
        {
            end = mid - 1;
        }
    }

    if (nums[begin] < target)
    {
        ret = begin + 1;
    }

    return ret;
}



int searchInsertPos(int* nums, int numsSize, int target) 
{
    int left = 0;
    int right = numsSize - 1;
    int mid = 0;
    while (left <= right)
    {
        mid = (left + right) / 2;
        if (nums[mid] <= target)
            left = mid + 1;
        else 
            right = mid - 1;
    }
    return left;
}

int main()
{
    int nums[] = {3, 4, 4, 4, 5, 6, 8, 9};

    int len = sizeof(nums) / sizeof(nums[0]);
    quickSort(nums, len);

    printNums(nums, len);


    int pos = searchInsert02(nums, len, 4);
    printf("pos:%d\n", pos);

    pos = searchInsert02(nums, len, 7);
    printf("pos:%d\n", pos);

    pos = searchInsert02(nums, len, 0);
    printf("pos:%d\n", pos);

    pos = searchInsert02(nums, len, 10);
    printf("pos:%d\n", pos);
    return 0;
}