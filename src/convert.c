/************************************************************************
文件转换模块。
Copyright (C) 2022 NULL_703, All rights reserved.
Created on 2022.11.1  19:40
Created by NULL_703
Last change time on 2022.12.18  17:21
************************************************************************/
#include <main.h>
#include <convert.h>
#include <time.h>

FILE* exportfile;
SHK_BOOL firstFlag = SHK_TRUE;
int outputCharCount = 0;
int filesize = 0;

SHK_BOOL openfile_cv(const char* fileName, const char* readMode)
{
    if((exportfile = fopen(fileName, readMode)) == NULL)
    {
        printf("%s%s%s", F_RED, W0006, NORMAL);
        return SHK_FALSE;
    }
    return SHK_TRUE;
}

FILE* openInputFile(const char* fileName)
{
    FILE* res = fopen(fileName, "rb");
    if(res == NULL)
    {
        printf("%s%s%s", F_RED, W0006, NORMAL);
        exit(1);
    }
    return res;
}

SHK_BOOL procressBarDrawer(int totalByte, int exportByte)
{
    int totalUnit = 25;
    int usedProcs = ((exportByte * 100) / totalByte) / 4;
    if(firstFlag == SHK_FALSE)
    {
        printf("\r");
        for(int k = 0; k < outputCharCount; k++)
            printf("%c", 32);
        printf("\r");
    }
    outputCharCount += printf("[");
    for(int i = 0; i < usedProcs; i++)
        outputCharCount += printf("|");
    for(int j = 0; j < totalUnit - usedProcs; j++)
        outputCharCount += printf(".");
    outputCharCount += printf("]  %d%c", ((exportByte * 100) / totalByte), '%');
    if(firstFlag == SHK_TRUE) firstFlag = SHK_FALSE;
    if(usedProcs == totalUnit) return SHK_FALSE;
    outputCharCount = 0;
    return SHK_TRUE;
}

int fileSizeof(const char* filename)
{
    FILE* tf;
    int filesize = 0;
    if((tf = fopen(filename, "r")) == NULL) return -1;
    fseek(tf, 0, SEEK_END);
    filesize = ftell(tf);
    fclose(tf);
    return filesize;
}

int asciiExport(FILE* file, const char* filename, const char* outputFilename)
{
    char tempbuf = 32;    // Default character is space.
    int loop = 0;
    SHK_BOOL first = SHK_TRUE;
    filesize = fileSizeof(filename);
    if(filesize > 0x1000000)
    {
        printf("%s%s%s", F_YELLOW, W0016, NORMAL);
        return 16;
    }
    file = openInputFile(filename);
    if(!openfile_cv(outputFilename, "a")) return 1;
    printf("%s%s", F_LIGHT_BLUE, W0013);
    fprintf(exportfile, "07, 03");
    while(1)
    {
        loop++;
        if(first == SHK_TRUE)
        {
            first = SHK_FALSE;
            continue;
        }
        if(((loop * 100) / filesize) % 4 == 0) procressBarDrawer(filesize, loop);
        tempbuf = fgetc(file);
        if(feof(file)) break;
        fprintf(exportfile, ", %d", (int)tempbuf);
    }
    printf("%s\n", NORMAL);    // 恢复为终端的默认字体
    fclose(file);
    fclose(exportfile);
    return 0;
}

int restoreNSEfile(FILE* file, const char* filename, const char* outputFilename)
{
    char magicNum[0x10];
    char tempbuf[0xa];
    char ch = 0;
    file = openInputFile(filename);
    int loop = 0;
    int tempint = 0;
    if(!openfile_cv(outputFilename, "ab")) return 1;
    for(int i = 0; i < 7; i++)
        magicNum[i] = fgetc(file);
    if(shk_scmp(magicNum, "07, 03,") == SHK_FALSE)
    {
        printf("%s%s%s", F_RED, W0011, NORMAL);
        return 3;
    }
    printf("%s", W0017);
    while(1)
    {
        loop++;
        if(loop == 1) continue;
        for(int i = 0; i < 0xa; i++)
        {
            ch = fgetc(file);
            if(ch == ',')
            {
                tempbuf[i] = '\0';
                break;
            }
            if(ch == EOF)
            {
                tempbuf[i] = '\0';
                tempint = atoi(tempbuf);
                fwrite(&tempint, sizeof(char), 1, exportfile);
                return 0;
            }
            tempbuf[i] = ch;
        }
        fgetc(file);
        tempint = atoi(tempbuf);
        fwrite(&tempint, sizeof(char), 1, exportfile);
    }
    fclose(file);
    fclose(exportfile);
    return 0;
}