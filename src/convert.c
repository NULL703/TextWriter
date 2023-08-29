/************************************************************************
文件转换模块。
Copyright (C) 2022-2023 NULL_703, All rights reserved.
Created on 2022.11.1  19:40
Created by NULL_703
Last change time on 2023.8.29  16:24
************************************************************************/
#include <main.h>
#include <ctype.h>
#include <convert.h>

FILE* exportfile;
SHK_BOOL firstFlag = SHK_TRUE;
int outputCharCount = 0;
unsigned int filesize = 0;
char varName[0x20] = "V__";

char* getVarname(const char* origname)
{
    int vnameIndex = 0;
    int dirlever = shk_chcount(origname, '\\') + shk_chcount(origname, '/');
    while(dirlever > 0)
    {
        if(origname[vnameIndex] == '\\' || origname[vnameIndex] == '/') dirlever--;
        vnameIndex++;
    }
    for(int i = 3; i < 0x20; i++, vnameIndex++)
    {
        if(!isalpha(origname[vnameIndex])) break;
        varName[i] = origname[vnameIndex];
    }
    return varName;
}

SHK_BOOL normalNSEMagicNumCheck(const char* magicNum)
{
    if(shk_scmp(magicNum, "07, 03,") == SHK_FALSE)
    {
        printf("%s%s%s", F_RED, W0011, NORMAL);
        return SHK_FALSE;
    }
    return SHK_TRUE;
}

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

unsigned int fileSizeof(const char* filename)
{
    FILE* tf;
    if((tf = fopen(filename, "r")) == NULL) return -1;
    fseek(tf, 0, SEEK_END);
    filesize = ftell(tf);
    fclose(tf);
    return filesize;
}

SHK_BOOL ishex(char ch)
{
    if(((ch >= 'a' && ch <= 'f') || (ch >= 'A' && ch <= 'F'))
        || (ch >= '0' && ch <= '9')) return SHK_TRUE;
    return SHK_FALSE;
}

int asciiExport(FILE* file, const char* filename, const char* outputFilename, 
                SHK_BOOL bigfile, SHK_BOOL batchMode)
{
    char tempbuf = 32;    // Default character is space.
    int loop = 0;
    SHK_BOOL first = SHK_TRUE;
    filesize = fileSizeof(filename);
    if(access(outputFilename, 0) != -1)
    {
        printf("%s%s%s", F_YELLOW, W0028, NORMAL);
        return 0;
    }
    if(filesize > 0x1000000 && bigfile == SHK_FALSE)
    {
        printf("%s%s%s", F_YELLOW, W0016, NORMAL);
        return 16;
    }
    file = openInputFile(filename);
    if(!openfile_cv(outputFilename, "a")) return 1;
    if(filesize > 0x280000) printf("%s%s", F_LIGHT_BLUE, W0013);
    fprintf(exportfile, "07, 03");
    while(1)
    {
        loop++;
        if(first == SHK_TRUE)
        {
            first = SHK_FALSE;
            continue;
        }
        if(((loop * 100) / filesize) % 4 == 0 && filesize > 0x280000)
            procressBarDrawer(filesize, loop);
        tempbuf = fgetc(file);
        if(feof(file)) break;
        fprintf(exportfile, ", %d", (int)tempbuf);
    }
    printf("%s", NORMAL);    // 恢复为终端的默认字体
    if(!batchMode) printf("%s%s%s", F_LIGHT_BLUE, W0019, NORMAL);
    fclose(file);
    fclose(exportfile);
    return 0;
}

int restoreNSEfile(FILE* file, const char* filename, const char* outputFilename, SHK_BOOL batchMode)
{
    char magicNum[8];
    char tempbuf[0xa];
    char ch = 0;
    file = openInputFile(filename);
    int loop = 0;
    int tempint = 0;
    if(access(outputFilename, 0) != -1)
    {
        printf("%s%s%s", F_YELLOW, W0028, NORMAL);
        return 0;
    }
    if(!openfile_cv(outputFilename, "ab")) return 1;
    for(int i = 0; i < 7; i++)
        magicNum[i] = fgetc(file);
    magicNum[7] = '\0';
    if(normalNSEMagicNumCheck(magicNum) == SHK_FALSE)
    {
        fclose(file);    fclose(exportfile);
        remove(outputFilename);
        return 3;
    }
    if(!batchMode) printf("%s", W0017);
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
                if(!batchMode) printf("%s%s%s", F_LIGHT_BLUE, W0019, NORMAL);
                return 0;
            }
            tempbuf[i] = ch;
        }
        fgetc(file);
        tempint = atoi(tempbuf);
        fwrite(&tempint, sizeof(char), 1, exportfile);
    }
    if(!batchMode) printf("%s%s%s", F_LIGHT_BLUE, W0019, NORMAL);
    fclose(file);
    fclose(exportfile);
    return 0;
}

int exportC_Style_Array(FILE* file, const char* filename, const char* outfile, SHK_BOOL batchMode)
{
    char tempbuf = 32;
    file = openInputFile(filename);
    int dataitem = 0;
    SHK_BOOL first = SHK_TRUE;
    if(access(outfile, 0) != -1)
    {
        printf("%s%s%s", F_YELLOW, W0028, NORMAL);
        return 0;
    }
    if(!openfile_cv(outfile, "a")) return 1;
    // 此功能对输入文件的大小限制为8MB，且不能使用附加选项解除
    if(fileSizeof(filename) > 0x800000)
    {
        printf("%s%s%s", F_YELLOW, W0021, NORMAL);
        return 16;
    }
    // 导出的C样式文件头
    fprintf(exportfile, C_STYLE_HEAD, getVarname(outfile), fileSizeof(filename));
    // 文件正文
    while(1)
    {
        tempbuf = fgetc(file);
        if(feof(file)) break;
        if(!first) fprintf(exportfile, ",");
        if(first) first = SHK_FALSE;
        if(dataitem >= 0x10)
        {
            fprintf(exportfile, "\n");
            dataitem = 0;
        }
        fprintf(exportfile, "%-4d", (int)tempbuf);
        dataitem++;
    }
    // 导出的C样式文件结尾
    fprintf(exportfile, C_STYLE_TAIL);
    if(!batchMode) printf("%s%s%s", F_LIGHT_BLUE, W0019, NORMAL);
    fclose(file);
    fclose(exportfile);
    return 0;
}

int nse2C_Style_Array(FILE* file, const char* filename, const char* outfile, SHK_BOOL batchMode)
{
    int dataitem = 0;
    char tempchar = 0;
    char magicNum[8];
    file = openInputFile(filename);
    if(access(outfile, 0) != -1)
    {
        printf("%s%s%s", F_YELLOW, W0028, NORMAL);
        return 0;
    }
    if(!openfile_cv(outfile, "a")) return 1;
    // 魔数检查
    for(int i = 0; i < 7; i++)
        magicNum[i] = fgetc(file);
    magicNum[7] = '\0';
    if(normalNSEMagicNumCheck(magicNum) == SHK_FALSE)
    {
        fclose(file);    fclose(exportfile);
        remove(outfile);
        return 3;
    }
    fprintf(exportfile, C_STYLE_HEAD, getVarname(outfile), (int)fileSizeof(filename) / 2);
    fgetc(file);    // 去除正文序列前剩余的一个空格
    // 将源nse文件的序列写入数组，但每隔16个数据项会写入一个换行符
    while(1)
    {
        tempchar = fgetc(file);
        if(tempchar == ',') dataitem++;
        if(feof(file)) break;
        if(dataitem >= 0x10)
        {
            fprintf(exportfile, "%c\n", tempchar);
            fgetc(file);    // 去除将会出现在行首的空格
            dataitem = 0;
            continue;
        }
        fprintf(exportfile, "%c", tempchar);
    }
    fprintf(exportfile, C_STYLE_TAIL);
    if(!batchMode) printf("%s%s%s", F_LIGHT_BLUE, W0019, NORMAL);
    fclose(file);
    fclose(exportfile);
    return 0;
}

int blockHEX_Converter(FILE* origfile, const char* filename, const char* outfile, SHK_BOOL batmode)
{
    char ch = 0;
    origfile = openInputFile(filename);
    if(access(outfile, 0) != -1)
    {
        printf("%s%s%s", F_YELLOW, W0028, NORMAL);
        return 0;
    }
    if(!openfile_cv(outfile, "a")) return 1;
    while(1)
    {
        ch = fgetc(origfile);
        if(feof(origfile)) break;
        fprintf(exportfile, "%.2x", (int)ch & 0xff);
    }
    if(!batmode) printf("%s%s%s", F_LIGHT_BLUE, W0019, NORMAL);
    fclose(origfile);
    fclose(exportfile);
    return 0;
}

void getseq(FILE* file, char* seq, SHK_BOOL* EOF_mark)
{
    for(int i = 0; i < 2; i++)
    {
        seq[i] = fgetc(file);
        if(feof(file))
        {
            *EOF_mark = SHK_TRUE;
            break;
        }
        if(!ishex(seq[i]))
        {
            seq[i] = '\0';
            i--; continue;
        }
    }
}

int blockHEX_Deconverter(FILE* hexfile, const char* filename, const char* outfile, SHK_BOOL batmode)
{
    SHK_BOOL EOFmark = SHK_FALSE;
    int tdata = 0;
    char HEXbuf[3] = "";
    hexfile = openInputFile(filename);
    if(access(outfile, 0) != -1)
    {
        printf("%s%s%s", F_YELLOW, W0028, NORMAL);
        return 0;
    }
    if(fileSizeof(filename) % 2 != 0) printf("%s%s", F_YELLOW, W0032);
    if(!openfile_cv(outfile, "ab")) return 1;
    while(1)
    {
        getseq(hexfile, HEXbuf, &EOFmark);
        if(EOFmark) break;
        tdata = shk_HexToDec(HEXbuf);
        fwrite(&tdata, sizeof(char), 1, exportfile);
    }
    if(!batmode) printf("%s%s%s", F_LIGHT_BLUE, W0019, NORMAL);
    fclose(hexfile);
    fclose(exportfile);
    return 0;
}