/************************************************************************
程序文本(简体中文)。
Copyright (C) 2022-2023 NULL_703, All rights reserved.
Created on 2022.11.20  12:03
Created by NULL_703
Last change time on 2023.2.13  11:00
************************************************************************/
#ifndef ZH_CN_H
#define ZH_CN_H
    #define W0001 "TextWriter V1.0.2, Copyright (C) 2022 NULL_703, All rights reserved.\n"\
        "用法：cmdtr [--ascii] [-a] [--text] [-t] [--read-as-ascii] [--read-as-text] [--help] [-h] "\
        "[--export-as-nse] [--export-as-ori]\n"\
        "[--ascii] [-a]: 保存为ascii数字序列。\n"\
        "[--text] [-t]: 保存为文本文件。\n"\
        "[--read-as-ascii]: 读取ascii数字序列文件（只读）\n"\
        "[--read-as-text]: 读取文本文件。（只读）\n"\
        "[--help] [-h]: 显示帮助信息。\n"\
        "[--export-as-nse]: 将文件转换为数字序列文件。\n"\
        "[--export-as-ori]: 将数字序列文件转换为源数据。\n"\
        "[--bufsize]: 设置打印到终端的字符数量，如果设置的参数为0，则打印文件的所有内容到终端。\n"\
        "[--unlimited]: 取消输入文件最大大小为16MB的限制。（只有[--export-as-nse]选项有这个限制）\n"\
        "[--file2C]: 将指定的文件转换为C语言源文件。（文件大小限制无法取消）\n"\
        "[--nse2C]: 将指定的数字序列文件转换为C语言源文件。\n"
    #define W0002 "错误：参数过少！[E_1001]\n"
    #define W0003 "错误：必须要有一个参数或选项！[E_1002]\n"
    #define W0004 "错误：无效的参数或选项！[E_1003]\n"
    #define W0005 "请输入文件名：（键入 `<` 以跳过）\n"
    #define W0006 "错误：文件读取失败！[E_2001]\n"
    #define W0007 "警告：这个文件已存在，请再次重命名。[W_2001]\n"
    #define W0008 "键入文本：\n"
    #define W0009 "警告：这个选项只能用于打开ascii数字序列文件。[W_1001]\n"
    #define W0010 "\n\033[1;34m 按任意键以显示下一页...\033[m\n"
    #define W0011 "错误：无效的文件魔数！[E_2002]\n"
    #define W0012 "警告：文件大小获取失败，导出进度无法显示。[W_2001]\n"
    #define W0013 "文件导出进度： \n"
    #define W0014 "警告：无效的选项用法。[W_1002]\n"
    #define W0015 "错误：必须指定一个文件名！[E_1004]\n"
    #define W0016 "警告：文件过大，操作已经终止。（所允许的最大大小：16MB）[W_2002]\n"
    #define W0017 "文件转换中...\n"
    #define W0018 "错误：这个选项必须要提供一个值！[E_1005]\n"
    #define W0019 "信息：操作完成！[I_1001]\n"
    #define W0020 "错误：文件名过长！[E_2003]\n"
    #define W0021 "警告：输入文件的大小必须小于8MB，操作已终止。[W_2002]\n"
#endif    // ZH_CN_H