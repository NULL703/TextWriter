/************************************************************************
程序选项解析模块。
Copyright (C) 2022 NULL_703, All rights reserved.
Created on 2022.7.9  13:20
Created by NULL_703
Last change time on 2022.10.9  13:01
************************************************************************/
#include <main.h>
#include <writer.h>
#include <filereader.h>

#define READFILE_ARGS 3
const char propts[0xa][0x20] = {
    "", "--ascii", "-a","--text", "-t", "--read-as-ascii", "--read-as-text", "--help", "-h"
};

int argsMatch(const char* args)
{
    int arrayPointer = 0;
    while(arrayPointer != 0xa)
    {
        if(strcmp(args, propts[arrayPointer]) == 0) return arrayPointer;
        arrayPointer++;
    }
    return -1;
}

int argsProcess(int argc, const char** argv)
{
    // if(argc > 2)
    // {
    //     printf("%s%s%s", F_RED, W0002, NORMAL);
    //     return 1;
    // }
    switch(argsMatch(argv[1]))
    {
        case 0: printf("%s%s%s", F_RED, W0003, NORMAL); return 1;
        case 1:
        case 2: return asciiWriter();
        case 3:
        case 4: return textWriter();
        case 5: {
            if(argc != READFILE_ARGS)
            {
                printf("%s%s%s", F_RED, W0002, NORMAL);
                return 1;
            }
            return asciiRead(argv[2]);
            break;
        }
        case 6: {
            if(argc != READFILE_ARGS)
            {
                printf("%s%s%s", F_RED, W0002, NORMAL);
                return 1;
            }
            return textRead(argv[2]);
            break;
        }
        case 7:
        case 8: printf("%s", W0001); break;
        default: {
            printf("%s%s%s", F_RED, W0004, NORMAL);
            return 2;
        }
    }
    return 0;
}