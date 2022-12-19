/************************************************************************
文本写入模块。
Copyright (C) 2022 NULL_703, All rights reserved.
Created on 2022.7.9  14:44
Created by NULL_703
Last change time on 2022.11.6  12:59
************************************************************************/
#include <main.h>
#include <stdlib.h>
#include <writer.h>

char spchars[0x2][0xf] = {"", "EXT"};
char tempbuf[0xff];
char filename[0xff] = "default.txt";
int tempbufPointer = 0;
FILE* outfile;

// 应用用户输入的文件名
void fileNameChange(const char* objName, SHK_BOOL nseMode)
{
    int loop = 0;
    int nameSize = shk_strlen(objName) - 1;
    for(int i = 0; i != nameSize + 3; i++, loop++)
        filename[i] = objName[i];
    if(nseMode == SHK_TRUE)
    {
        filename[loop] = '.';
        filename[loop++] = 'n';
        filename[loop++] = 's';
        filename[loop++] = 'e';
        filename[loop++] = '\0';
    }
}

int spcharEx(int spcharIndex, FILE* fileptr)
{
    switch(spcharIndex)
    {
        case 0:
        // ESC: EXT role: Quit program.
        case 1: fclose(fileptr); exit(0);
        default: return -1;
    }
}

int spcharMatch(const char* spc, FILE* fileptr)
{
    int spcharIndex = 0;
    while(spcharIndex != 2)
    {
        if(strcmp(spchars[spcharIndex], spc) == 0) break;
        spcharIndex++;
    }
    return spcharEx(spcharIndex, fileptr);
}

void getFileName(SHK_BOOL nseMode)
{
    int tempbuf = 0;
    char tempfn[0xff] = "";
    SHK_BOOL renameMark = SHK_FALSE;
    for(int i = 0; i < 0xf0; i++)
    {
        tempbuf = getchar();
        if(tempbuf == 10)
        {
            tempfn[i] = '\0';
            break;
        }
        tempfn[i] = tempbuf;
    }
    if(shk_incscmp(tempfn, "<") == SHK_TRUE && access("default.txt", 0) == -1) return;
    if(access(tempfn, 0) != -1) renameMark = SHK_TRUE;
    // 用于处理同名文件存在的情况
    if(access(tempfn, 0) != -1 || renameMark == SHK_TRUE)
    {
        // 反复重命名，直到文件名唯一为止
        while(access(tempfn, 0) != -1 || renameMark == SHK_TRUE)
        {
            printf("%s%s%s", F_RED, W0007, NORMAL);
            for(int i = 0; i < 0xf0; i++)
            {
                tempbuf = getchar();
                if(tempbuf == 10)
                {
                    tempfn[i] = '\0';
                    break;
                }
                tempfn[i] = tempbuf;
            }
            if(access(tempfn, 0) == -1) break;
        }
    }
    fileNameChange(tempfn, nseMode);
}

SHK_BOOL openfile()
{
    if((outfile = fopen(filename, "a")) == NULL)
    {
        printf("%s%s%s", F_RED, W0006, NORMAL);
        return SHK_FALSE;
    }
    return SHK_TRUE;
}

int isEscape()
{
    SHK_BOOL NextlineStatus = SHK_FALSE;
    char prespc;
    char spchar[10];
    int statusCode = 0;
    prespc = getchar();
    if(prespc == '#')
    {
        for(int i = 0; i < 9; i++)
        {
            spchar[i] = getchar();
            if(spchar[i] == '\n')
            {
                spchar[i] = '\0';
                NextlineStatus = SHK_TRUE;
                break;
            }
        }
        if(NextlineStatus != SHK_TRUE)
        {
            // 屏蔽转义前缀后面的所有字符，直到遇到回车字符为止。（类似于编程语言的注释）
            while('\n' != getchar());
        }
        statusCode = spcharMatch(spchar, outfile);
    }
    return statusCode;
}

int asciiWriter()
{
    char atch;
    printf("%s", W0005);
    getFileName(SHK_TRUE);
    if(!openfile()) return 1;
    printf("%s", W0008);
    fprintf(outfile, "07, 03");    // 为后期版本保留的文件魔数
    while(1)
    {
        atch = getchar();
        if(atch == '^')
            if(isEscape() != 0) continue;
        fprintf(outfile, ", %d", (int)atch);
    }
    fclose(outfile);
    return 0;
}

int textWriter()
{
    char tch;
    printf("%s", W0005);
    getFileName(SHK_FALSE);
    if(!openfile()) return 1;
    printf("%s", W0008);
    while(1)
    {
        tch = getchar();
        if(tch == '^')
            if(isEscape() != 0) continue;
        fwrite(&tch, sizeof(tch), 1, outfile);
    }
    fclose(outfile);
    return 0;
}