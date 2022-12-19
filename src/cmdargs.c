/************************************************************************
程序选项解析模块。
Copyright (C) 2022 NULL_703, All rights reserved.
Created on 2022.7.9  13:20
Created by NULL_703
Last change time on 2022.12.15  8:20
************************************************************************/
#include <main.h>
#include <writer.h>
#include <filereader.h>
#include <convert.h>

SHK_BOOL haveLimitedarg = SHK_FALSE;
int sigOpt[0xa] = {1, 2, 3, 4, 5, 6, 9, 10};    // 只能单独使用的关键选项ID
const char propts[0x15][0x20] = {
    "", "--ascii", "-a","--text", "-t", "--read-as-ascii", "--read-as-text", "--help", "-h",
    "--export-as-nse", "--export-as-ori"
};

typedef struct parange{
    int startID;
    int endID;
} prange;
prange pars = {0, 0};

int argsMatch(const char* args)
{
    int arrayPointer = 0;
    while(arrayPointer != 0x15)
    {
        if(strcmp(args, propts[arrayPointer]) == 0) return arrayPointer;
        arrayPointer++;
    }
    return -1;
}

char* changeFilename(const char* origFileName)
{
    static char res[0xff] = "";
    for(int i = 0; i < shk_strlen(origFileName); i++)
    {
        res[i] = origFileName[i];
        if(origFileName[i] == '.')
        {
            res[i] = origFileName[i];
            res[i + 1] = 110;    // n
            res[i + 2] = 115;    // s
            res[i + 3] = 101;    // e
            break;
        }
    }
    return res;
}

SHK_BOOL isLimitedArg(int argID)
{
    int index = 0;
    while(index < 7)
    {
        if(sigOpt[index] == argID) return SHK_TRUE;
        index++;
    }
    return SHK_FALSE;
}

SHK_BOOL argsCheck(int argID)
{
    if(haveLimitedarg == SHK_TRUE && isLimitedArg(argID) == SHK_TRUE) return SHK_FALSE;
    haveLimitedarg = SHK_TRUE;
    return SHK_TRUE;
}

// 主选项操作
int lastexec(int laID, const char** argv)
{
    FILE* inputfile = NULL;
    switch(laID)
    {
        case 1: return asciiWriter(); break;
        case 2: return textWriter(); break;
        case 3: {
            if(shk_incscmp("-", argv[pars.startID]) == SHK_TRUE)
            {
                printf("%s%s%s", F_RED, W0015, NORMAL);
                return 2;
            }
            return asciiRead(argv[pars.startID]); break;
        }
        case 4: {
            if(shk_incscmp("-", argv[pars.startID]) == SHK_TRUE)
            {
                printf("%s%s%s", F_RED, W0015, NORMAL);
                return 2;
            }
            return textRead(argv[pars.startID]); break;
        }
        case 5: return asciiExport(inputfile, argv[pars.startID], changeFilename(argv[pars.startID]));
        case 6: {
            if(shk_incscmp("-", argv[pars.startID + 1]) == SHK_TRUE)
            {
                printf("%s%s%s", F_RED, W0015, NORMAL);
                return 2;
            }
            return restoreNSEfile(inputfile, argv[pars.startID], argv[pars.startID + 1]);
        }
        default: return 2;
    }
    return 0;
}

// 选项筛选，非主选项直接执行
int argsProcess(int argc, const char** argv)
{
    int argIndex = 1;
    int argID = 0;
    int tempID = 0;
    SHK_BOOL IDrange = SHK_FALSE;
    if(argc == 1)
    {
        printf("%s%s%s", F_RED, W0003, NORMAL);
        return 1;
    }
    while(argIndex < argc)
    {
        argID = argsMatch(argv[argIndex]);
        // 为后期版本的文件批处理保留的选项参数判断
        if(shk_incscmp("-", argv[argIndex]) == SHK_FALSE)
        {
            argIndex++;
            continue;
        }
        if(argsCheck(argID) == SHK_FALSE)
        {
            printf("%s%s%s", F_YELLOW, W0014, NORMAL);
            argIndex++;
            continue;
        }
        switch(argID)
        {
            case 0: printf("%s%s%s", F_RED, W0003, NORMAL); return 1;
            case 1:
            case 2: tempID = 1; break;
            case 3:
            case 4: tempID = 2; break;
            case 5: tempID = 3; IDrange = SHK_TRUE; pars.startID = argIndex + 1; break;
            case 6: tempID = 4; IDrange = SHK_TRUE; pars.startID = argIndex + 1; break;
            case 7:
            case 8: {
                if(argIndex > 1) return 2;
                printf("%s", W0001);
                break;
            }
            case 9: tempID = 5; IDrange = SHK_TRUE; pars.startID = argIndex + 1; break;
            case 10: tempID = 6; IDrange = SHK_TRUE; pars.startID = argIndex + 1; break;
            default: {
                printf("%s%s%s", F_RED, W0004, NORMAL);
                return 2;
            }
        }
        if(IDrange == SHK_TRUE)
        {
            IDrange = SHK_FALSE;
            pars.endID = argIndex - 1;
        }
        argIndex++;
    }
    return lastexec(tempID, argv);
}