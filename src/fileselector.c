/************************************************************************
多文件选择模块。
Copyright (C) 2023 NULL_703, All rights reserved.
Created on 2023.3.2  21:50
Created by NULL_703
Last change time on 2023.4.5  12:32
************************************************************************/
#include <main.h>
#include <convert.h>
#include <fileselector.h>
// 如果在Visual Studio环境下编译此项目，请在编译时添加宏定义"__MSVC"。
#ifdef __MSVC
    #include <windows.h>
#else
    #include <dirent.h>
    DIR* dirs = NULL;
    struct dirent* dent = NULL;
#endif    // __MSVC

FOBJ* head = NULL;     FOBJ* node = NULL;    FOBJ* prev = NULL;
char ofilename[0xff] = "";

int addMainFilename(const char* origfilename, int count)
{
    if(shk_strlen(origfilename) + shk_strlen(".nse") >= 0xff)
    {
        printf("%s%s%s", F_RED, W0020, NORMAL);
        exit(4);
    }
    while(count < shk_strlen(origfilename))
    {
        ofilename[count] = origfilename[count];
        count++;
    }
    return count;
}

const char* del_NSE_Extname(const char* fname)
{
    int extnameSec = shk_chcount(fname, '.');
    for(int i = 0, j = 0; fname[i] != '\0'; i++)
    {
        ofilename[i] = fname[i];
        if(fname[i] == '.') j++;
        if(extnameSec >= 1 && j == (extnameSec - 1)) break;
    }
    return ofilename;
}

const char* add_C_Extname(const char* origfilename)
{
    int charcount = 0;
    charcount = addMainFilename(origfilename, charcount);
    ofilename[charcount++] = '.'; ofilename[charcount++] = 'c';
    return ofilename;
}

const char* add_NSE_Extname(const char* origfilename)
{
    int charcount = 0;
    charcount = addMainFilename(origfilename, charcount);
    ofilename[charcount++] = '.';
    ofilename[charcount++] = 'n'; ofilename[charcount++] = 's'; ofilename[charcount++] = 'e';
    ofilename[charcount++] = '\0'; 
    return ofilename;
}

SHK_BOOL givename(const char* gfilename, FOBJ* mnode)
{
    int index = 0;
    while(1)
    {
        if(gfilename[index] == '\0' || gfilename[index] == '\n') break;
        if(index == 0xff) return SHK_FALSE;
        mnode->fname[index] = gfilename[index];
        index++;
    }
    mnode->fname[index] = '\0';
    return SHK_TRUE;
}

SHK_BOOL addfile(const char* afilename, unsigned int fileID, SHK_BOOL haveExtname)
{
    if(fileID == 0)
    {
        head = (FOBJ*)malloc(sizeof(FOBJ));
        if(givename(afilename, head) == SHK_FALSE) return SHK_FALSE;
        head->haveExtname = haveExtname;
        head->ID = fileID;
        prev = head;
        return SHK_TRUE;
    }
    node = (FOBJ*)malloc(sizeof(FOBJ));
    if(givename(afilename, node) == SHK_FALSE) return SHK_FALSE;
    prev->haveExtname = haveExtname;
    node->ID = fileID;
    prev->nextobj = node;
    prev = node;
    return SHK_TRUE;
}

int execFileConvert(int option, SHK_BOOL allowBigfile, int bufsize)
{
    FILE* infile = NULL;
    int errcode = 0;
    while(1)
    {
        if(fileSizeof(head->fname) == 0)
        {
            printf("%s%s%s (fname=%s, fid=%d)\n", F_YELLOW, W0027, NORMAL, head->fname, head->ID);
            head = head->nextobj;
            continue;
        }
        printf("%s (fname=%s, fid=%d)\n", W0029, head->fname, head->ID);
        switch(option)
        {
            case OPT_TONSE: 
                errcode = asciiExport(infile, head->fname, add_NSE_Extname(head->fname), allowBigfile, SHK_TRUE); break;
            case OPT_TODAT: errcode = restoreNSEfile(infile, head->fname, add_NSE_Extname(head->fname), SHK_TRUE); break;
            case OPT_TOC: exportC_Style_Array(infile, head->fname, add_C_Extname(head->fname), SHK_TRUE); break;
            case OPT_NSETOC: nse2C_Style_Array(infile, head->fname, add_C_Extname(head->fname), SHK_TRUE); break;
            default: printf("%s%s%s", F_RED, W0024, NORMAL); return -1;
        }
        if(head->ID == prev->ID) break;
        head = head->nextobj;
        infile = NULL;
        if(errcode != 0) return errcode;
    }
    printf("%s%s%s", F_LIGHT_BLUE, W0019, NORMAL);
    return 0;
}

#ifdef __MSVC
// MSVC编译环境的代码块
int batchSelectFilenames(const char* dirname, int option, SHK_BOOL allowBigfile, int bufsize)
{
    WIN32_FIND_DATA findData;
    HANDLE hError;
    SHK_BOOL extnameStatus = SHK_FALSE;
    int fileID = 0;
    hError = FindFirstFile(strcat((char*)dirname, "\\*"), &findData);
    if(hError == INVALID_HANDLE_VALUE)
    {
        printf("%s%s%s", F_RED, W0022, NORMAL);
        return 1;
    }
    while(FindNextFile(hError, &findData))
    {
        if(findData.dwFileAttributes == 32)
        {
            if(shk_chcount(findData.cFileName, '.') > 0) extnameStatus = SHK_TRUE;
            if(!addfile(findData.cFileName, fileID, extnameStatus))
            {
                printf("%s%s%s", F_RED, W0023, NORMAL);
                return 1;
            }else{
                fileID++;
            }
        }
    }
    prev->nextobj = NULL;
    return execFileConvert(option, allowBigfile, bufsize);
}
#else
// GCC编译环境的代码块
int batchSelectFilenames(const char* dirname, int option, SHK_BOOL allowBigfile, int bufsize)
{
    int fileID = 0;
    SHK_BOOL extnameStatus = SHK_FALSE;
    if((dirs = opendir(dirname)) == NULL)
    {
        printf("%s%s%s", F_RED, W0022, NORMAL);
        return 1;
    }
    while(1)
    {
        dent = readdir(dirs);
        if(dent == NULL) break;
        if(dent->d_type == 0)
        {
            if(shk_chcount(dent->d_name, '.') > 0) extnameStatus = SHK_TRUE;
            if(!addfile(dent->d_name, fileID, extnameStatus))
            {
                printf("%s%s%s", F_RED, W0023, NORMAL);
                return 1;
            }else{
                fileID++;
            }
        }
        extnameStatus = SHK_FALSE;
    }
    prev->nextobj = NULL;
    return execFileConvert(option, allowBigfile, bufsize);
}
#endif    // __MSVC