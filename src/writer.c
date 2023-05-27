/************************************************************************
文本写入模块。
Copyright (C) 2022-2023 NULL_703, All rights reserved.
Created on 2022.7.9  14:44
Created by NULL_703
Last change time on 2023.5.27  16:45
************************************************************************/
#include <stdlib.h>
#include <time.h>
#include <main.h>
#include <writer.h>
#include <filereader.h>

char spchars[0x5][0xf] = {"", "EXT", "NSV"};
char tempbuf[0xff];
char filename[0xff] = "default.txt";
int tempbufPointer = 0;
SHK_BOOL newfile_mode = SHK_TRUE;
SHK_BOOL haveFilename = SHK_FALSE;
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
        // ESC: EXT Fn: Quit program.
        case 1: fclose(fileptr); exit(0);
        // ESC: NSV Fn: Not save file and exit.
        case 2: fclose(fileptr); remove(filename); exit(0);
        default: return -1;
    }
}

int spcharMatch(const char* spc, FILE* fileptr)
{
    int spcharIndex = 0;
    while(spcharIndex != 5)
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

SHK_BOOL open_Infile(const char* fname)
{
    if((outfile = fopen(fname, "a")) == NULL)
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
    }else{
        fwrite(&prespc, sizeof(prespc), 1, outfile);
    }
    return statusCode;
}

int filenameFromArgs(int writeMode, const char* fname)
{
    haveFilename = SHK_TRUE;
    if(access(fname, 0) != -1)
    {
        printf("%s%s%s", F_YELLOW, W0028, NORMAL);
        return 6;
    }
    switch(writeMode)
    {
        case WTEXT: fileNameChange(fname, SHK_FALSE); return textWriter();
        case WASCII: fileNameChange(fname, SHK_TRUE); return asciiWriter();
        default: printf("%s%s%s", F_RED, W0024, NORMAL); return -1;
    }
    return 0;
}

int continueWrite(int writeMode, const char* fname)
{
    int errCode = 0;
    SHK_BOOL exist_status = SHK_FALSE;
    newfile_mode = SHK_FALSE;
    if(access(fname, 0) == -1)
    {
        printf("%s%s%s", F_LIGHT_BLUE, W0025, NORMAL);
        exist_status = SHK_TRUE;
    }
    if(shk_strlen(fname) > 0xfa) {printf("%s%s%s", F_RED, W0020, NORMAL); return 4;}
    switch(writeMode)
    {
        case WTEXT: {
            if(exist_status) return textWriter();
            errCode = textRead(fname, 0);
            fileNameChange(fname, SHK_FALSE);
            if(errCode != 0) return errCode;
            printf("\n");
            return textWriter();
        }
        case WASCII: {
            if(exist_status) return asciiWriter();
            errCode = asciiRead(fname, 0);
            fileNameChange(fname, SHK_TRUE);
            if(errCode != 0) return errCode;
            printf("\n");
            return asciiWriter();
        }
        default: printf("%s%s%s", F_RED, W0024, NORMAL); return -1;
    }
    return 0;
}

int asciiWriter()
{
    char atch;
    int editTime = time(NULL);
    if(newfile_mode && !haveFilename)
    {
        printf("%s", W0005);
        getFileName(SHK_TRUE);
    }
    if(!open_Infile(filename)) return 1;
    printf("%s", W0008);
    if(!newfile_mode) fprintf(outfile, " ,");
    else
        fprintf(outfile, "07, 03");    // 为后期版本保留的文件魔数
    while(1)
    {
        atch = getchar();
        if(atch == '^')
            if(isEscape() != 0) continue;
        fprintf(outfile, ", %d", (int)atch);
        // 距离上一次刷新缓冲区或打开文件超过1分钟则刷新缓冲区
        if(time(NULL) - editTime > 60)
        {
            fflush(outfile);
            editTime = time(NULL);
        }
    }
    fclose(outfile);
    return 0;
}

int textWriter()
{
    int editTime = time(NULL);
    char tch;
    if(newfile_mode && !haveFilename)
    {
        printf("%s", W0005);
        getFileName(SHK_FALSE);
    }
    if(!open_Infile(filename)) return 1;
    printf("%s", W0008);
    while(1)
    {
        tch = getchar();
        if(tch == '^')
            if(isEscape() != 0) continue;
        fwrite(&tch, sizeof(tch), 1, outfile);
        // 距离上一次刷新缓冲区或打开文件超过1分钟则刷新缓冲区
        if(time(NULL) - editTime > 60)
        {
            fflush(outfile);
            editTime = time(NULL);
        }
    }
    fclose(outfile);
    return 0;
}