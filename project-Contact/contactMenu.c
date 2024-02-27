#include "contactMenu.h"
#include <stdio.h>

/* 枚举数据类型的空间占用 一定是4个字节 */
enum STATUS_CODE
{
    ON_SUCCESS,
    NULL_PRT,
    MALLOC_ERROR,
    INVALID_ACCESS,
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

/* 添加联系人 */
int addPerson()
{
    /* */
    printf("\033[31;47mgfgghtynt联系人  \033[0m\n");
    printf("\033[31;47mfergtrgtrg 删除联系人  \033[0m\n");
    printf("\033[31;47mfregthg5t联系人  \033[0m\n");

    getchar();
}