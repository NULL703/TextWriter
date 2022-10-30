/************************************************************************
文件读取模块。
Copyright (C) 2022 NULL_703, All rights reserved.
Created on 2022.9.3  16:30
Created by NULL_703
Last change time on 2022.10.29  19:59
************************************************************************/
#include <stdlib.h>
#include <filereader.h>
#include <main.h>

int textRead(const char* name)
{
    int charbuf = 32;    // Default character is space.
    int page = 0;
    FILE* textfile;
    if((textfile = fopen(name, "rb")) == NULL)
    {
        printf("%s%s%s", F_RED, W0006, NORMAL);
        return 1;
    }
    for(int i = 0; !feof(textfile); i++)
    {
        // 如果是第一次循环则跳过，因为在第一次循环的时候临时字符变量还是初始值，需要先从文件获取数据后才能输出。
        if(i > 0) putchar(charbuf);
        charbuf = fgetc(textfile);
        if(i % 1000 == 0 && i != 0)
        {
            page++;
            printf("Page #%d %d    %s", i / 1000, i, W0010);
            getchar();
            // 防止文件过大导致变量值溢出
            if(i >= 0xf4240) i = 1;
            if(page >= 0xf4240) page = 0;
        }
    }
    fclose(textfile);
    return 0;
}

int asciiRead(const char* name)
{
    char seqbuf[0xa];
    char tempchar = 32;
    int magicCount = 0;
    int page = 0;
    FILE* asciifile;
    if((asciifile = fopen(name, "r")) == NULL)
    {
        printf("%s%s%s", F_RED, W0006, NORMAL);
        return 1;
    }
    for(int i = 0; ; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            tempchar = fgetc(asciifile);
            if(tempchar == ',')
            {
                if(magicCount <= 1)
                {
                    magicCount++;
                    // 清除序列间的空格
                    fgetc(asciifile);
                }
                seqbuf[j] = '\0';
                break;
            }
            if(tempchar == EOF) return 0;
            seqbuf[j] = tempchar;
        }
        if(magicCount <= 1) continue;
        printf("%c", atoi(seqbuf));
        if(i % 1000 == 0)
        {
            page++;
            printf("Page #%d    %s", i / 1000, W0010);
            getchar();
            // 防止文件过大导致变量值溢出
            if(i >= 0xf4240) i = 1;
            if(page >= 0xf4240) page = 0;
        }
    }
    fclose(asciifile);
    return 0;
}