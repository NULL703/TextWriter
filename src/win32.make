#************************************************************************
# 程序源代码目录下的Makefile(Windows版本).
# Copyright (C) 2022 NULL_703. All rights reserved.
# Created on 2022.10.8  20:52
# Created by NULL_703
# Last change time on 2022.10.8  22:11
#*************************************************************************
cpp := g++
gc := gcc
cflag := -O2 -std=c99 -Wall -s -I ../include
flag := -O2 -std=c++11 -Wall -s -I ../include
obj := main.o cmdargs.o filereader.o writer.o

.PHONY: progobj
progobj: $(obj)
	move "*.o" "../"

%.o: %.c
	$(gc) -c $(cflag) $<

.PHONY: clean
clean:
	del *.o