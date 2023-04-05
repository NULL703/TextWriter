/************************************************************************
多文件选择模块（标头文件）。
Copyright (C) 2023 NULL_703, All rights reserved.
Created on 2023.3.2  21:50
Created by NULL_703
Last change time on 2023.3.20  13:45
************************************************************************/
#ifndef TEXTWRITER_FILESELECTOR_H
#define TEXTWRITER_FILESELECTOR_H

/* 文件转换标志 */
#define OPT_TONSE        0    // 普通文件转NSE
#define OPT_TODAT        1    // NSE转普通文件
#define OPT_TOC          2    // 普通文件转C源文件
#define OPT_NSETOC       3    // NSE转C源文件

typedef struct fileobjs{
    char fname[0xff];
    SHK_BOOL haveExtname;
    unsigned int ID;
    struct fileobjs* nextobj;
} FOBJ;

int batchSelectFilenames(const char* dirname, int option, SHK_BOOL allowBigfile, int bufsize);

#endif    // TEXTWRITER_FILESELECTOR_H