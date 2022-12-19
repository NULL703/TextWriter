#************************************************************************
# 项目根目录下的主Makefile(Windows版本).
# Copyright (C) 2022 NULL_703. All rights reserved.
# Created on 2022.9.27  16:30
# Created by NULL_703
# Last change time on 2022.12.18  17:17
#*************************************************************************
cpp := g++
gc := gcc
cflag := -O2 -std=c99 -Wall -DZH_CN -fexec-charset=GBK -s -I ./include
flag := -O2 -std=c++11 -Wall -DZH_CN -fexec-charset=GBK -s -I ./include
bin := cmdtr.exe
lib := libformula.dll
obj := main.o cmdargs.o filereader.o writer.o convert.o
res := cmdtr.o

all: $(bin) $(lib)
	move $(bin) "./bin"

$(bin): $(lib) $(obj) $(res)
	$(gc) $(obj) $(res) -L. -lformula $(cflag) -o $(bin)
	del libformula.dll

$(lib): 
	make -C ./lib/libformula/ -f win32.make

$(obj): 
	make -C ./src -f win32.make progobj

$(res): cmdtr.rc
	windres -i cmdtr.rc -o $(res)

.PHONY: clean
clean:
	@echo "Deleting binary files..."
	make -C ./lib/libformula/ -f win32.make clean
	del *.o
	del "./bin"
	rmdir "bin"
	@echo "Finish!"