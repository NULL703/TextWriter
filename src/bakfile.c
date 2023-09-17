/************************************************************************
临时备份文件处理模块。
Copyright (C) 2023 NULL_703, All rights reserved.
Created on 2023.9.13  17:10
Created by NULL_703
Last change time on 2023.9.17  17:06
************************************************************************/
#include <time.h>
#include <main.h>
#include <bakfile.h>
#include <convert.h>

char bakname[8] = ".";
FILE* tempfile = NULL;
FILE* origfile = NULL;

char namech[62] = {
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
    'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
    'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd',
    'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
    'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x',
    'y', 'z'
};

// 生成随机的临时文件名
int createTempFilename(const char* oname, char* retname)
{
    srand((unsigned)time(NULL));
    int id = 0;
    for(int i = 1; i < 8; i++)
    {
        id = rand()%(62 + 1);
        retname[i] = namech[id];
    }
    if(access(retname, 0) != -1) return createTempFilename(oname, retname);
    return 0;
}

int createTempFile(const char* oname)
{
    char ch = '\0';
    createTempFilename(oname, bakname);
    tempfile = fopen(bakname, "ab");
    origfile = fopen(oname, "rb");
    if(tempfile == NULL || origfile == NULL)
    {
        printf("%s%s%s", F_RED, W0006, NORMAL);
        return 1;
    }
    if(fileSizeof(oname) > 0x400000) printf("%s%s%s", F_BLUE, W0033, NORMAL);
    ch = fgetc(origfile);
    while(!feof(origfile))
    {
        fputc((int)ch, tempfile);
        ch = fgetc(origfile);
    }
    fclose(origfile);
    fclose(tempfile);
    return 0;
}

void recfile(const char* oname)
{
    remove(oname);
    rename(bakname, oname);
}