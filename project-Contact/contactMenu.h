#ifndef __CONTACTMENU_H__
#define __CONTACTMENU_H__

enum FUNCTION_OPTION
{
    EXIT = 0,
    ADDTION,
    DELETE,
    SEARCH,
    MODIFY,
};

enum OPERATION_OPTION
{
    UP = 'A',
    DOWN = 'S',
    ENTER = 'D',
};

/* 菜单 */
int contactMenu(int optionLight);

/* 添加联系人 */
int addPerson();

#endif //__CONTACTMENU_H__