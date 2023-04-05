/************************************************************************
文件转换模块的接口（标头文件）。
Copyright (C) 2022-2023 NULL_703, All rights reserved.
Created on 2022.11.1  19:43
Created by NULL_703
Last change time on 2023.4.4  13:17
************************************************************************/
#ifndef TEXTWRITER_CONVERT_H
#define TEXTWRITER_CONVERT_H

#define C_STYLE_HEAD \
    "/* Created by cmdtr. */\n" \
    "int %s[%d] = {\n"
#define C_STYLE_TAIL \
    "\n};\n" \
    "/* End of file. */"

int asciiExport(FILE* file, const char* filename, const char* outputFilename,
                SHK_BOOL bigfile, SHK_BOOL batchMode);
int restoreNSEfile(FILE* file, const char* filename, const char* outputFilename, SHK_BOOL batchMode);
int exportC_Style_Array(FILE* file, const char* filename, const char* outfile, SHK_BOOL batchMode);
int nse2C_Style_Array(FILE* file, const char* filename, const char* outfile, SHK_BOOL batchMode);
int fileSizeof(const char* filename);

#endif    // TEXTWRITER_CONVERT_H