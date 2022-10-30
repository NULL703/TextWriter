/************************************************************************
文本写入模块的接口（标头文件）。
Copyright (C) 2022 NULL_703, All rights reserved.
Created on 2022.7.9  14:48
Created by NULL_703
Last change time on 2022.10.29  21:27
************************************************************************/
#ifndef TEXTWRITER_WRITER_H
#define TEXTWRITER_WRITER_H

#include <unistd.h>
#ifdef __WIN32
    #define access _access
#endif

int textWriter();
int asciiWriter();
#endif    // TEXTWRITER_WTITER_H