/************************************************************************
程序内部接口（标头文件）。
Copyright (C) 2022-2023 NULL_703, All rights reserved.
Created on 2022.7.9  13:04
Created by NULL_703
Last change time on 2023.4.14  21:57
************************************************************************/
#ifndef TEXTWRITER_MAIN_H
#define TEXTWRITER_MAIN_H

#include <unistd.h>
#ifdef __WIN32
    #define access _access
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <formulas.h>
#include "Colors.h"
#include "texts.h"

int argsProcess(int argc, const char** argv);
#endif    // TEXTWRITER_MAIN_H