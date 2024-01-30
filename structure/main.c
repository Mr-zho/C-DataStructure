#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE     32


#define SIZE    3

/* typedef 取别名 */
/* 字节对齐 */
typedef struct StuInfo
{
    int age;                // 4
    char sex;               // 1
    #if 0
    char name[BUFFER_SIZE]; // 32
    #else
    char * address;
    #endif
    char height;            // 1
} StuInfo;

#if 0
/* 值传递 : 浪费资源 */
/* 地址传递 : 节省资源 */
int printStruct(StuInfo *pInfo, int size)
{
    int ret = 0;
    if (pInfo == NULL)
    {
        return 0;
    }
    for (int idx = 0; idx < size; idx++)
    {
        /* 结构体指针取值使用的是 -> */
        printf("age:%d\t, sex:%c\t, name:%s\t, height:%d\n", pInfo[idx].age, pInfo[idx].sex, pInfo[idx].name, pInfo[idx].height);
    }
    
    return ret;
}
#endif


int main()
{
#if 0
    /* 结构体的基本使用 */
    StuInfo stu1;

    int len = sizeof(stu1);
    printf("len:%d\n", len);

    len = sizeof(struct StuInfo);
    printf("len:%d\n", len);

    /* 清空脏数据 */
    memset(&stu1, 0, sizeof(stu1));

    /* 赋值 */
#if 0
    /* 数组名是数组的首地址, 常量不可以更改  */
    stu1.name = "zhangsan";
#endif
    strcpy(stu1.name, "zhangsan");
    stu1.age = 20;
    stu1.height = 60;
    stu1.sex = 'm';


    /* 写一个函数, 打印该结构体 */
    printStruct(&stu1);
#endif

    
#if 0
    StuInfo info[SIZE];
    int len = sizeof(info);
    printf("len:%d\n", len);
    /* 清除脏数据 */
    memset(info, 0, sizeof(info));


    info[0].age = 20;
#if 0
    // info[0].name = "lisi"
#else   
    strcpy(info[0].name, "lisi");
#endif
    info[0].sex = 'm';
    info[0].height = 70;

    info[1].age = 30;
#if 0
    // info[0].name = "lisi"
#else   
    strcpy(info[1].name, "zhangsan");
#endif
    info[1].sex = 'f';
    info[1].height = 50;



    info[2].age = 40;
#if 0
    // info[0].name = "lisi"
#else   
    strcpy(info[2].name, "wangwu");
#endif
    info[2].sex = 'm';
    info[2].height = 100;

#if 0
    for(int idx = 0; idx < SIZE; idx++)
    {
        printStruct(&(info[idx]));
    }
#else
    printStruct(info, sizeof(info) / sizeof(info[0]));
#endif

#endif


#if 1
    StuInfo stu;
    memset(&stu, 0, sizeof(stu));
    // stu.address = "jiangshuyancheng";
    stu.address = (char *)malloc(sizeof(char) * BUFFER_SIZE);
    if (stu.address == NULL)
    {
        perror("malloc error");
        exit(-1);
    }
    strcpy(stu.address, "jiangshuyancheng");
    stu.age = 22;
    stu.height = 65;
    stu.sex = 'm';

    printf("age:%d\t, sex:%c\t, address:%s\t, height:%d\n", stu.age, stu.sex, stu.address, stu.height);
#endif

    return 0;
}