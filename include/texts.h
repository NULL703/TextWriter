/************************************************************************
程序文本(English)。
Copyright (C) 2022-2023 NULL_703, All rights reserved.
Created on 2022.7.9  13:42
Created by NULL_703
Last change time on 2023.6.3  10:56
************************************************************************/
#ifndef TEXTWRITER_TEXTS_H
#define TEXTWRITER_TEXTS_H

#ifdef ZH_CN
    #include "texts_zh_CN.h"
#else
    #define W0001 "TextWriter V1.1.1, Copyright (C) 2022-2023 NULL_703, All rights reserved.\n"\
        "Usage: cmdtr [MainOption] [AttachOption] [AttachOption of parameter]\n"\
        "[--ascii] [-a]: Save as ascii number sequence.\n"\
        "[--text] [-t]: Save as text file.\n"\
        "[--read-as-ascii]: Read ascii number sequence file. (Read only)\n"\
        "[--read-as-text]: Read text file. (Read only)\n"\
        "[--help] [-h]: Show help infomation.\n"\
        "[--export-as-nse]: Export as number sequencefile.\n"\
        "[--export-as-ori]: Export as original data.\n"\
        "[--bufsize]: Set print to terminal of character amount, if parameter value is 0 them print all character to terminal from file.\n"\
        "[--unlimited]: Cancel inputfile of max size is 16MB of limited. (Only option [--export-as-nse] have this limited)\n"\
        "[--file2C]: Convert specifyed file as C source file.(Filesize limited cannot cancel)\n"\
        "[--nse2C]: Covert specifyed NSE file as C source file.\n"\
        "[-A] [--showall]: Show all content from file.\n"\
        "[-c] [--continue]: Continue-write specified file, must be used with [-a], [--ascii], [-t], [--text] and must be before these options.\n"\
        "[-b] [--batch]: Batch convert files, must be used with [--export-as-nse], [--export-as-ori], [--file2C], [--nse2C] and must be before these options.\n"
    #define W0002 "Error: Parameter too few! [E_1001]\n"
    #define W0003 "Error: Must have a parameter or option! [E_1002]\n"
    #define W0004 "Error: Invalid parameter or option! [E_1003]\n"
    #define W0005 "Please input outputfile name (Type `<` to skip):\n"
    #define W0006 "Error: File open failed! [E_2001]\n"
    #define W0007 "Warning: This filename of file already exists, please rename again. [W_2001]\n"
    #define W0008 "\033[1;37;46mPlease input your text:\033[m\n"
    #define W0009 "Warning: This option only open ascii number sequence file! [W_1001]\n"
    #define W0010 "Press <Enter> show next page...\033[m\n"
    #define W0011 "Error: Invalid file magic number. [E_2002]\n"
    #define W0012 "Warning: File of size get failed, export process not show. [W_2001]\n"
    #define W0013 "File export processing: \n"
    #define W0014 "Warning: Option usage invalid. [W_1002]\n"
    #define W0015 "Error: Must specify a filename. [E_1004]\n"
    #define W0016 "Warning: File too big, operation is stopped.(Maxsize: 16MB) [W_2002]\n"
    #define W0017 "File exporting...\n"
    #define W0018 "Error: This option must specify a value! [E_1005]\n"
    #define W0019 "Info: Operation finish! [I_1001]\n"
    #define W0020 "Error: Filename of length too long! [E_2003]\n"
    #define W0021 "Warning: Input file of size must less then 8MB, operation is stopped. [W_2002]\n"
    #define W0022 "Error: Cannot open specified directory. [E_2004]\n"
    #define W0023 "Error: Create filelist failed, return value is 8. [E_2005]\n"
    #define W0024 "Error: Internal error! [E_-1]\n"
    #define W0025 "Info: Specified file not exists, newfile is created.[I_2001]\n"
    #define W0026 "Error: ContinueWrite mode must specify a file and option. [E_1006]\n"
    #define W0027 "Warning: Skipped a empty file. [W_2003]\n"
    #define W0028 "Warning: OutputFile is exists, opertion is skipped. [W_2004]\n"
    #define W0029 "Converting file..."
    #define W0030 "Info: No file searched in this directory. [I_2002]\n"
#endif    // ZH_CN
#endif    // TEXTWRITER_TEXTS_H