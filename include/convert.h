/************************************************************************
文件转换模块的接口（标头文件）。
Copyright (C) 2022 NULL_703, All rights reserved.
Created on 2022.11.1  19:43
Created by NULL_703
Last change time on 2022.11.5  22:39
************************************************************************/
#ifndef TEXTWRITER_CONVERT_H
#define TEXTWRITER_CONVERT_H

int asciiExport(FILE* file, const char* filename, const char* outputFilename);
int restoreNSEfile(FILE* file, const char* filename, const char* outputFilename);

#endif    // TEXTWRITER_CONVERT_H