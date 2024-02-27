#include <stdio.h>
#include <string.h>
#include "contactMenu.h"
#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>

/* 全局变量初始化一定是0. */
int g_running = 1;

/* 新建联系人默认是高亮的 */
int g_record = 1;


int enterAppoint(int option)
{
    system("clear");
    switch (option)
    {
    case ADDTION:
        addPerson();
        /* code */
        break;
    case DELETE:
        /* code */
        break;
    case SEARCH:
        /* code */
        break;
    case MODIFY:
        /* code */
        break;
    case EXIT:
        /* code */
        break;
    default:
        break;
    }

    return 0;
}

int main()
{
   


    // 关闭缓冲区, 输入字符无需按回车键盘
    system("stty -icanon"); 

    char choice = 0;
    while (g_running)
    {
        contactMenu(g_record);
        choice = getchar();
        // scanf("%c", &choice);
        /* 统一格式化成大写 */
        choice = toupper(choice);
        switch (choice)
        {
        case UP:
            g_record = (g_record - 1) % 5;
            break;
        case DOWN:
            g_record = (g_record + 1) % 5; // 0 - 5之间
            break;
        case ENTER:
            enterAppoint(g_record);
            break;
        default:
            printf("输错了, 重新输入...\n");
            break;
        }
        system("clear");
        usleep(1000);
    }

    return 0;
}