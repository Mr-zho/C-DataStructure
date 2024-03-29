#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 50

typedef struct Person
{
    int age;
    char *name;
}Person;


int main()
{
#if 0
    char * name = "yuzhiliang";
    int len = sizeof(name);
    printf("len:%d\n", len);

    len = strlen(name);
    printf("len:%d\n", len);
#endif

    Person per1;
    memset(&per1, 0, sizeof(per1));
    per1.age = 22;

    /* 在堆区分配内存 */
    per1.name = (char *)malloc(sizeof(char) * BUFFER_SIZE);
    if (per1.name == NULL)
    {
        printf("malloc error");
        return -1;
    }
#if 0
    per1.name = "yuzhiliang";
#else
    strcpy(per1.name, "yuzhiliang");
#endif
    printf("age:%d,\t name:%s\n", per1.age, per1.name);

    return 0;
}