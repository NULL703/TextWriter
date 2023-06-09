/************************************************************************
文件读取模块的外部接口 。
Copyright (C) 2022-2023 NULL_703, All rights reserved.
Created on 2022.9.3  16:31
Created by NULL_703
Last change time on 2023.6.8  10:04
************************************************************************/
#ifndef TEXTWRITER_FILEREADER_H
#define TEXTWRITER_FILEREADER_H

#include <defvar.h>

typedef int RMODE;
#define READTEXT        0
#define READNSE         1

int textRead(const char* name, int bufsize, SHK_BOOL lineMode);
int asciiRead(const char* name, int bufsize, SHK_BOOL lineMode);
#endif    // TEXTWRITER_FILEREADER_H