#include "contactMenu.h"
#include <stdio.h>
#include <regex.h>
#include <string.h>

#define BUFFER_SIZE  16

/* 枚举数据类型的空间占用 一定是4个字节 */
enum STATUS_CODE
{
    ON_SUCCESS,
    NULL_PRT,
    MALLOC_ERROR,
    INVALID_ACCESS,
    ILLEGALITY,
};

/* 菜单 */
int contactMenu(int optionLight)
{
    printf("\033[%d;31;47m 新建联系人  \033[0m\n", optionLight == ADDTION ? 1 : 0);
    printf("\033[%d;31;47m 删除联系人  \033[0m\n", optionLight == DELETE ? 1 : 0);
    printf("\033[%d;31;47m 查找联系人  \033[0m\n", optionLight == SEARCH ? 1 : 0);
    printf("\033[%d;31;47m 修改联系人  \033[0m\n", optionLight == MODIFY ? 1 : 0);
    printf("\033[%d;31;47m 退出通讯录  \033[0m\n", optionLight == EXIT ? 1 : 0);

    return ON_SUCCESS;
}

static int checkUserNameLegal(const char * name)
{
    if (name == NULL)
    {
        return NULL_PRT;
    }

    int userNameLength = strlen(name);
    if (userNameLength < 3 || userNameLength > 15)
    {
        return ILLEGALITY;
    }

    const char * tmpName = name;
    #if 0
    /* 方案1 */
    while (*tmpName != '\0')
    {
        if (*tmpName == '~' || *tmpName == '!' || *tmpName == '@')
        {
            return ILLEGALITY;
        }
        tmpName++;
    }
    return ON_SUCCESS;
    #else
    /* 方案2 */
    regex_t regex;
    memset(&regex, 0, sizeof(regex));

    char * pattern = "[!@$]";

    /* 编译正则表达式 */
    int ret = regcomp(&regex, pattern, 0);
    if (ret)
    {
        printf("regcomp error");
        return ret;
    }

    /* 执行正则表达式 */
    ret = regexec(&regex, name, 0, NULL, 0);
    regfree(&regex);

    if (ret == 0)
    {
        printf("存在非法字符\n");
        return ILLEGALITY;
    }
    else if (ret == REG_NOMATCH)
    {
        /* 不存在非法字符 */
        return ON_SUCCESS;
    }
    else
    {
        printf("正则匹配失败\n");
        return ILLEGALITY;
    }
    #endif
}

/* 添加联系人 */
int addPerson()
{
    #if 0
    printf("\033[31;47m-----------------------------\033[0m\n");
    printf("\033[31;47m                             \033[0m\n");
    printf("\033[31;47m                             \033[0m\n");
    printf("\033[31;47m                             \033[0m\n");
    printf("\033[31;47m                             \033[0m\n");
    printf("\033[31;47m                             \033[0m\n");
    printf("\033[31;47m                             \033[0m\n");
    printf("\033[31;47m                             \033[0m\n");
    printf("\033[31;47m                             \033[0m\n");
    printf("\033[31;47m-----------------------------\033[0m\n");
    #endif


    char userName[BUFFER_SIZE] = { 0 };
    printf("请输入用户名:");
    scanf("%s", userName);

    int ret = checkUserNameLegal(userName);
    if (ret != ON_SUCCESS)
    {
        printf("添加联系人失败\n");
        getchar();
        getchar();
        return ret;
    }


  


    getchar();
    printf("添加联系人成功");
}