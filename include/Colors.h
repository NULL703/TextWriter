/************************************************************************
颜色配置文件(建议用于Linux) 
Copyright (C) 2021-2022 NULL_703. All rights reserved.
Created on 2021.7.2  21:01
Created by NULL_703
Last change time on 2022.5.24  19:26
************************************************************************/
/************************************************************************
 * 配置说明：
 * Windows平台使用说明：
 * 经验证，在Windows中使用此配置文件前先使用system(cls);，在此后就可以使用
 * 下面的配置(Windows 8以上版本可能有效)。
 * Linux平台使用说明：
 * 可以直接使用，注意变量前缀，F为字体颜色，B为字体背景颜色。
 * 使用示例：
 * void demo()
 * {
 *     printf("%sHello World!",F_BLUE);
 * }
 * 此函数的运行结果：输出蓝色字体“Hello World!”。
 * NOTE：
 * 配置值不能连续使用，这将覆盖前者的属性！例如，以下写法将不能得到预期的结果：
 * void demo()
 * {
 *     printf("%s%sHello World!",B_WHITE,F_BLUE);
 * }
***********************************************************************/
#ifndef COMMON_COLORS_H
#define COMMON_COLORS_H

    //Other config
    #define NORMAL "\033[m"          //普通样式
    #define UNDERLINE "\033[4m"      //下划线
    #define DELETELINE "\033[9m"     //删除线

    //ForeColors
    #define F_RED "\033[0;32;31m"
    #define F_LIGHT_RED "\033[1;31m"
    #define F_GREEN "\033[0;32;32m"
    #define F_LIGHT_GREEN "\033[1;32m"
    #define F_BLUE "\033[0;32;34m"
    #define F_LIGHT_BLUE "\033[1;34m"
    #define F_CYAN "\033[0;36m"
    #define F_LIGHT_CYAN "\033[1;36m"
    #define F_PURPLE "\033[0;35m"
    #define F_LIGHT_PURPLE "\033[1;35m"
    #define F_YELLOW "\033[1;33m"
    #define F_WHITE "\033[1;37m"
    #define F_DARY_GRAY "\033[1;30m"
    #define F_LIGHT_GRAY "\033[0;37m"
    #define F_BROWN "\033[0;33m"
    #define F_BLACK "\033[0;30m"

    //BackColors
    #define B_RED "\033[0;32;41m"
    #define B_LIGHT_RED "\033[1;41m"
    #define B_GREEN "\033[0;32;42m"
    #define B_LIGHT_GREEN "\033[1;42m"
    #define B_BLUE "\033[0;32;44m"
    #define B_LIGHT_BLUE "\033[1;44m"
    #define B_CYAN "\033[0;46m"
    #define B_LIGHT_CYAN "\033[1;46m"
    #define B_PURPLE "\033[0;45m"
    #define B_LIGHT_PURPLE "\033[1;45m"
    #define B_YELLOW "\033[1;43m"
    #define B_WHITE "\033[1;47m"
    #define B_DARY_GRAY "\033[1;40m"
    #define B_LIGHT_GRAY "\033[0;47m"
    #define B_BROWN "\033[0;43m"

#endif