/************************************************************************
文本写入模块的接口（标头文件）。
Copyright (C) 2022-2023 NULL_703, All rights reserved.
Created on 2022.7.9  14:48
Created by NULL_703
Last change time on 2023.4.20  22:07
************************************************************************/
#ifndef TEXTWRITER_WRITER_H
#define TEXTWRITER_WRITER_H

#define WTEXT       0    // 写入文本文件
#define WASCII      1    // 写入NSE文件

int textWriter();
int asciiWriter();
int continueWrite(int writeMode, const char* fname);
int filenameFromArgs(int writeMode, const char* fname);
#endif    // TEXTWRITER_WTITER_H