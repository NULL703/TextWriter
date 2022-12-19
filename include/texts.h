/************************************************************************
程序文本(English)。
Copyright (C) 2022 NULL_703, All rights reserved.
Created on 2022.7.9  13:42
Created by NULL_703
Last change time on 2022.12.19  16:54
************************************************************************/
#ifndef TEXTWRITER_TEXTS_H
#define TEXTWRITER_TEXTS_H

#ifdef ZH_CN
    #include "texts_zh_CN.h"
#else
    #define W0001 "TextWriter V1.0.1, Copyright (C) 2022 NULL_703, All rights reserved.\n"\
        "Usage: cmdtr [--ascii] [-a] [--text] [-t] [--read-as-ascii] [--read-as-text] [--help] [-h] "\
        "[--export-as-nse] [--export-as-ori]\n"\
        "[--ascii] [-a]: Save as ascii number sequence.\n"\
        "[--text] [-t]: Save as text file.\n"\
        "[--read-as-ascii]: Read ascii number sequence file. (Read only)\n"\
        "[--read-as-text]: Read text file. (Read only)\n"\
        "[--help] [-h]: Show help infomation.\n"\
        "[--export-as-nse]: Export as number sequencefile.\n"\
        "[--export-as-ori]: Export as original data.\n"
    #define W0002 "Error: Parameter too few! [E_1001]\n"
    #define W0003 "Error: Must have a parameter or option! [E_1002]\n"
    #define W0004 "Error: Invalid parameter or option! [E_1003]\n"
    #define W0005 "Please input outputfile name (Type `<` to skip):\n"
    #define W0006 "Error: File open failed! [E_2001]\n"
    #define W0007 "Warning: This filename of file already exists, please rename again. [W_2001]\n"
    #define W0008 "Please input your text:\n"
    #define W0009 "Warning: This option only open ascii number sequence file! [W_1001]\n"
    #define W0010 "\n\033[1;34m Press any key show next page...\033[m\n"
    #define W0011 "Error: Invalid file magic number. [E_2002]\n"
    #define W0012 "Warning: File of size get failed, export process not show. [W_2001]\n"
    #define W0013 "File export processing: \n"
    #define W0014 "Warning: Option usage invalid. [W_1002]\n"
    #define W0015 "Error: Must specify a filename. [E_1004]\n"
    #define W0016 "Warning: File too big, option is stopped. [W_2002]\n"
    #define W0017 "File exporting...\n"
#endif    // ZH_CN
#endif    // TEXTWRITER_TEXTS_H