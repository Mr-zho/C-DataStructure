#include "contactMenu.h"
#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <error.h>

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
#define USERNMAE_MIN    3
#define USERNMAE_MAX    15
#define CONTACT_NAME    "./contact.txt"

/* 静态函数 前置声明 */

/* 判断正则合法性 */
static int checkRegularLegal(const char *str, const char *pattern);
/* 判断密码合法性 */
static int checkPasswdLegal(const char * passwd);
/* 判断用户名合法性 */
static int checkUserNameLegal(const char * name);
/* 从终端读取字符，不回显 */
static char getch();



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


/* 合法返回0, 不合法返回状态码 */
static int checkRegularLegal(const char *str, const char *pattern)
{
    regex_t regex;
    memset(&regex, 0, sizeof(regex));

    

    /* 编译正则表达式 */
    int ret = regcomp(&regex, pattern, 0);
    if (ret)
    {
        printf("regcomp error");
        return ret;
    }

    /* 执行正则表达式 */
    ret = regexec(&regex, str, 0, NULL, 0);
    regfree(&regex);


    if (ret == 0)
    {
        return ILLEGALITY;
    }
    else if (ret == REG_NOMATCH)
    {
        /* 不存在非法字符 */
        return ON_SUCCESS;
    }
    else
    {
        return ILLEGALITY;
    }
}   

/* 从终端读取字符，不回显 */
static char getch() {
    char buf = 0;
    struct termios old = {0};
    fflush(stdout);
    if (tcgetattr(0, &old) < 0) {
        perror("tcsetattr");
        exit(-1);
    }
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0) {
        perror("tcsetattr ICANON");
        exit(-1);
    }
    if (read(0, &buf, 1) < 0) {
        perror ("read()");
        exit(-1);
    }
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0) {
        perror ("tcsetattr ~ICANON");
        exit(-1);
    }
    return (buf);
}

static int checkUserNameLegal(const char * name)
{
    if (name == NULL)
    {
        return NULL_PRT;
    }

    /* 长度 */
    int userNameLength = strlen(name);
    if (userNameLength < USERNMAE_MIN || userNameLength > USERNMAE_MAX)
    {
        return ILLEGALITY;
    }

    /* 正则 */
    char * pattern = "[!@$]";
    int ret = checkRegularLegal(name, pattern);
    if (ret != 0)
    {
        return ILLEGALITY;
    }
    return ON_SUCCESS;
}

/* 校验密码合法性 : passwd其实是明文 */
static int checkPasswdLegal(const char * passwd)
{

    return ON_SUCCESS;
}

/* 添加联系人 */
int addPerson()
{
    char fileBuffer[128] = { 0 };
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

    //  fileBuffer
    strncat(fileBuffer, userName, sizeof(userName));

    /* 密码 */
    char passWd[BUFFER_SIZE] = { 0 };
    char ch = '0';
    int idx = 0;
    printf("请输入密码:");
    while (1) 
    {
        ch = getch();
        if (ch == '\n') {
            passWd[idx] = '\0'; // 在数组末尾添加终止符
            break;
        }
        printf("*");
        passWd[idx++] = ch;
    }
    printf("\nYou entered: %s\n", passWd);
    getchar();
    getchar();
    /* */
    ret = checkPasswdLegal(passWd);
    if (ret != ON_SUCCESS)
    {
        printf("添加联系人失败\n");
        getchar();
        getchar();
        return ret;
    }
    strncat(fileBuffer + sizeof(userName), passWd, sizeof(passWd));

    
    printf("fileBuffer:%s\n", fileBuffer);
    getchar();
    getchar();
    
    /* 维护到数据结构 (树) */

    /* 自动存储到文件(落盘) todo... */
    int fd = open(CONTACT_NAME, O_RDWR | O_CREAT | O_APPEND, 0644);
    if (fd == -1)
    {
        perror("open error");
        exit(-1);
    }

    /* 组合成字符串 */
    // write(fd, );
    /* 关闭文件描述符 */
    close(fd);
    printf("添加联系人成功\n");
}

