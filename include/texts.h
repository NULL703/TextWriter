/************************************************************************
程序文本(English)。
Copyright (C) 2022 NULL_703, All rights reserved.
Created on 2022.7.9  13:42
Created by NULL_703
Last change time on 2022.9.22  18:40
************************************************************************/
#ifndef TEXTWRITER_TEXTS_H
#define TEXTWRITER_TEXTS_H
    #define W0001 "TextWriter V0.0.1, Copyright (C) 2022 NULL_703, All rights reserved.\n"\
        "Usage: txtwr [--ascii] [-a] [--text] [-t] [--read-as-ascii] [--read-as-text] [--help] [-h]\n"\
        "[--ascii] [-a]: Save as ascii number sequence.\n"\
        "[--text] [-t]: Save as text file.\n"\
        "[--read-as-ascii]: Read ascii number sequence file. (Read only)\n"\
        "[--read-as-text]: Read text file. (Read only)\n"\
        "[--help] [-h]: Show help infomation.\n"
    #define W0002 "Error: Parameter too more! [E_1001]\n"
    #define W0003 "Error: Must have a parameter! [E_1002]\n"
    #define W0004 "Error: Invalid parameter! [E_1003]\n"
    #define W0005 "Please input outputfile name (Type `<` to skip):\n"
    #define W0006 "Error: File open failed! [E_2001]\n"
    #define W0007 "Worning: This filename of file already exists, please rename again. [W_2001]\n"
    #define W0008 "Please input your text:\n"
    #define W0009 "Worning: This option only open ascii number sequence file! [W_1001]\n"
    #define W0010 "\nPress any key show next page...\n"
#endif    // TEXTWRITER_TEXTS_H