#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 10

static int swapNum(int *val1, int *val2)
{
    int tmpVal = *val1;
    *val1 = *val2;
    *val2 = tmpVal;

    return 0;
}

/* 升序 (从小到大) */
int bubbleSort01(int *nums, int numSize)
{
    for (int end = numSize; end > 0; end--)
    {
        /* 一轮 */
        for (int begin = 1; begin < end; begin++)
        {
            if (nums[begin - 1] > nums[begin])
            {
                /* swap */
                swapNum(&(nums[begin - 1]), &(nums[begin]));
            }
        }
    }
    return 0;
}

/* 升序 (从小到大) */
/* 是不是排好序呢? */
int bubbleSort02(int *nums, int numSize)
{
    int sorted = 0;
    for (int end = numSize; end > 0; end--)
    {
        sorted = 1;
        /* 一轮 */
        for (int begin = 1; begin < end; begin++)
        {
            if (nums[begin - 1] > nums[begin])
            {
                sorted = 0;
                /* swap */
                swapNum(&(nums[begin - 1]), &(nums[begin]));
            }
        }

        /* 已经排好序了 */
        if (sorted == 1)
        {
            break;
        }
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
    bubbleSort01(nums, BUFFER_SIZE);
    
    printNums(nums, BUFFER_SIZE);
    return 0;
}