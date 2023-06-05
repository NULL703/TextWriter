/************************************************************************
程序选项解析模块。
Copyright (C) 2022-2023 NULL_703, All rights reserved.
Created on 2022.7.9  13:20
Created by NULL_703
Last change time on 2023.5.30  15:03
************************************************************************/
#include <main.h>
#include <writer.h>
#include <filereader.h>
#include <convert.h>
#include <fileselector.h>

SHK_BOOL haveLimitedarg = SHK_FALSE;
int sigOpt[0x15] = {1, 2, 3, 4, 5, 6, 9, 10, 13, 14};    // 只能单独使用的关键选项ID
const char propts[0x20][0x20] = {
    /* ID range: 0 ~ 8 */
    "", "--ascii", "-a", "--text", "-t", "--read-as-ascii", "--read-as-text", "--help", "-h",
    /* ID range: 9 ~ 14 */
    "--export-as-nse", "--export-as-ori", "--bufsize", "--unlimited", "--file2C", "--nse2C",
    /* ID range 15 ~ 20 */
    "-A", "--showall", "-c", "--continue", "-b", "--batch"
};

// 修饰选项对应的默认状态值
SHK_BOOL allowBigfile = SHK_FALSE;
SHK_BOOL contWrite = SHK_FALSE;
int textblockSize = 1000;

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

/*
    NOTE: 当前暂时无法得知某些情况下拓展名无法与主文件名合并的问题来源，对此问题的定位还在进行中。
*/
char* changeFilename(const char* origFileName, const char* mode)
{
    static char res[0xff] = "";
    if(shk_strlen(origFileName) + shk_strlen(mode) >= 0xff)
    {
        printf("%s%s%s", F_RED, W0020, NORMAL);
        exit(4);
    }
    for(int i = 0, j = 0; i < shk_strlen(origFileName); i++, j++)
    {
        if((shk_incscmp("..", origFileName) == SHK_TRUE || origFileName[0] == '.') && i == 0)
            i += 2;
        if(origFileName[i] == '\\' || origFileName[i] == '/')
        {
            j = -1;
            res[1] = '\0';
            continue;
        }
        res[j] = origFileName[i];
        if((origFileName[i] == '.' || i == shk_strlen(origFileName)) && shk_scmp(mode, "NSE"))
        {
            res[j] = origFileName[i];
            if(origFileName[i] != '.') res[j++] = '.';
            j++;
            res[j++] = 110;    // n
            res[j++] = 115;    // s
            res[j++] = 101;    // e
            break;
        }
        if((origFileName[i] == '.' || i == shk_strlen(origFileName)) && shk_scmp(mode, "C"))
        {
            res[j] = origFileName[i];
            if(origFileName[i] != '.') res[j++] = '.';
            j++;
            res[j++] = 99;    // c
            break;
        }
    }
    return res;
}

SHK_BOOL isLimitedArg(int argID)
{
    int index = 0;
    while(index < 0x16)
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

SHK_BOOL fileSpecifyCheck(const char* nextArg)
{
    if(nextArg == NULL)
    {
        printf("%s%s%s", F_RED, W0002, NORMAL);
        exit(255);
    }
    if(shk_incscmp("-", nextArg) == SHK_TRUE)
    {
        printf("%s%s%s", F_RED, W0015, NORMAL);
        return SHK_FALSE;
    }
    return SHK_TRUE;
}

void argIsNull(const char** args, int argc, int range)
{
    int count = 0;
    while(count < range)
    {
        count++;
        if(args[argc] == NULL)
        {
            printf("%s%s%s", F_RED, W0002, NORMAL);
            exit(255);
        }
        argc++;
    }
}

int batchReadfile(const char** argv, int argc, int argcOffset, RMODE readMode)
{
    int errcode = 0;
    if(argv[argcOffset] == NULL)
    {
        printf("%s%s%s", F_RED, W0002, NORMAL);
        return 255;
    }
    while(argcOffset < argc)
    {
        switch(readMode)
        {
            case READTEXT: errcode = textRead(argv[argcOffset], textblockSize); break;
            case READNSE: errcode = asciiRead(argv[argcOffset], textblockSize); break;
        }
        argcOffset++;
        if(errcode != 0) break;
    }
    return errcode;
}

int convertMainOptionID(int tmpID)
{
    switch(tmpID)
    {
        case 5: return OPT_TONSE;
        case 6: return OPT_TODAT;
        case 7: return OPT_TOC;
        case 8: return OPT_NSETOC;
        default: return -1;
    }
}

// 主选项操作
int lastexec(int laID, const char** argv)
{
    FILE* inputfile = NULL;
    switch(laID)
    {
        case 1: {
            if(contWrite) return continueWrite(WASCII, argv[3]);
            return asciiWriter();
        }
        case 2: {
            if(contWrite) return continueWrite(WTEXT, argv[3]);
            return textWriter();
        }
        case 3: {
            if(!fileSpecifyCheck(argv[pars.startID])) return 2;
            return batchReadfile(argv, pars.endID, pars.startID, READNSE); break;
        }
        case 4: {
            if(!fileSpecifyCheck(argv[pars.startID])) return 2;
            return batchReadfile(argv, pars.endID, pars.startID, READTEXT); break;
        }
        case 5:
            return asciiExport(inputfile, argv[pars.startID], changeFilename(argv[pars.startID], "NSE"), allowBigfile, SHK_FALSE);
        case 6: {
            if(!fileSpecifyCheck(argv[pars.startID + 1])) return 2;
            return restoreNSEfile(inputfile, argv[pars.startID], argv[pars.startID + 1], SHK_FALSE);
        }
        case 7: {
            if(!fileSpecifyCheck(argv[pars.startID])) return 2;
            return exportC_Style_Array(inputfile, argv[pars.startID], changeFilename(argv[pars.startID], "C"), SHK_FALSE);
        }
        case 8: {
            if(!fileSpecifyCheck(argv[pars.startID])) return 2;
            return nse2C_Style_Array(inputfile, argv[pars.startID], changeFilename(argv[pars.startID], "C"), SHK_FALSE);
        }
        default: printf("%s%s%s", F_RED, W0004, NORMAL); return 2;
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
    SHK_BOOL dirOpt = SHK_FALSE;
    if(argc == 1)
    {
        printf("%s%s%s", F_RED, W0003, NORMAL);
        return 1;
    }
    while(argIndex < argc)
    {
        if(argv[argIndex] == NULL)
        {
            printf("%s%s%s", F_RED, W0002, NORMAL);
            return 255;
        }
        argID = argsMatch(argv[argIndex]);
        if(shk_incscmp("-", argv[argIndex]) == SHK_FALSE)
        {
            if(argIndex == argc - 1 && pars.endID == 1) pars.endID = argIndex + 1;
            IDrange = SHK_TRUE;
            argIndex++;
            continue;
        }
        switch(argID)
        {
            case 0: printf("%s%s%s", F_RED, W0003, NORMAL); return 1;
            case 1:
            case 2: {
                if(!contWrite && argc > argIndex + 1) return filenameFromArgs(WASCII, argv[argIndex + 1]);
                tempID = 1; break;
            }
            case 3:
            case 4: {
                if(!contWrite && argc > argIndex + 1) return filenameFromArgs(WTEXT, argv[argIndex + 1]);
                tempID = 2; break;
            }
            case 5: tempID = 3; IDrange = SHK_TRUE; pars.startID = argIndex + 1; break;
            case 6: tempID = 4; IDrange = SHK_TRUE; pars.startID = argIndex + 1; break;
            case 7:
            case 8: {
                if(argIndex > 1) return 2;
                printf("%s", W0001);
                return 0;
            }
            case 9: {
                argIsNull(argv, argIndex, 2); tempID = 5; IDrange = SHK_TRUE; pars.startID = argIndex + 1;
                if(dirOpt == SHK_TRUE)
                    return batchSelectFilenames(argv[argIndex + 1], convertMainOptionID(tempID), allowBigfile, textblockSize);
                break;
            }
            case 10: {
                if(!dirOpt) argIsNull(argv, argIndex, 3);
                else
                    argIsNull(argv, argIndex, 2);
                tempID = 6; IDrange = SHK_TRUE; pars.startID = argIndex + 1;
                if(dirOpt == SHK_TRUE)
                    return batchSelectFilenames(argv[argIndex + 1], convertMainOptionID(tempID), allowBigfile, textblockSize);
                break;
            }
            case 11: {
                if(argc == argIndex)
                {
                    printf("%s%s%s", F_RED, W0018, NORMAL);
                    return 2;
                }
                textblockSize = atoi(argv[argIndex + 1]);
                break;
            }
            case 12: allowBigfile = SHK_TRUE; break;
            case 13: {
                argIsNull(argv, argIndex, 2); tempID = 7; IDrange = SHK_TRUE; pars.startID = argIndex + 1;
                if(dirOpt == SHK_TRUE)
                    return batchSelectFilenames(argv[argIndex + 1], convertMainOptionID(tempID), allowBigfile, textblockSize);
                break;
            }
            case 14: {
                argIsNull(argv, argIndex, 2); tempID = 8; IDrange = SHK_TRUE; pars.startID = argIndex + 1;
                if(dirOpt == SHK_TRUE)
                    return batchSelectFilenames(argv[argIndex + 1], convertMainOptionID(tempID), allowBigfile, textblockSize);
                break;
            }
            case 15:
            case 16: textblockSize = 0; return batchReadfile(argv, argc, argIndex + 1, READTEXT);
            case 17:
            case 18: {
                if(argc != 4)
                {
                    printf("%s%s%s", F_RED, W0026, NORMAL);
                    return 11;
                }
                contWrite = SHK_TRUE; break;
            }
            case 19:
            case 20: dirOpt = SHK_TRUE; break;
            default: {
                printf("%s%s%s", F_RED, W0004, NORMAL);
                return 2;
            }
        }
        if(IDrange == SHK_TRUE)
        {
            IDrange = SHK_FALSE;
            pars.endID = argIndex;
        }
        argIndex++;
    }
    return lastexec(tempID, argv);
}