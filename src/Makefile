#************************************************************************
# 程序源代码目录下的Makefile.
# Copyright (C) 2022-2023 NULL_703. All rights reserved.
# Created on 2022.10.29  20:08
# Created by NULL_703
# Last change time on 2023.4.14  21:49
#*************************************************************************
cpp := g++
gc := gcc
cflag := -O2 -std=c99 -Wall -DZH_CN -s -I ../include -I ../lib/libformula/include
flag := -O2 -std=c++11 -Wall -DZH_CN -s -I ../include -I ../lib/libformula/include
obj := main.o cmdargs.o filereader.o writer.o convert.o fileselector.o

.PHONY: progobj
progobj: $(obj)
	mv *.o ../

%.o: %.c
	$(gc) -c $(cflag) $<

.PHONY: clean
clean:
	rm *.o