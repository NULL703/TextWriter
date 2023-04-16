#************************************************************************
# 项目根目录下的主Makefile.
# Copyright (C) 2022-2023 NULL_703. All rights reserved.
# Created on 2022.7.9  12:44
# Created by NULL_703
# Last change time on 2023.4.16  10:58
#*************************************************************************
cpp := g++
gc := gcc
cflag := -O2 -std=c99 -Wall -DZH_CN -s -I ./include
flag := -O2 -std=c++11 -Wall -DZH_CN -s -I ./include
bin := cmdtr
lib := libformula.so
obj := main.o cmdargs.o filereader.o writer.o convert.o fileselector.o

all: $(bin) $(lib)
	mv $(bin) "./bin"

$(bin): $(lib) $(obj)
	mkdir ./bin
	cp ./lib/libformula/bin/libformula.so ./bin
	$(gc) $(obj) -L. -lformula -lm $(cflag) -o $(bin)

$(lib): 
	make -C ./lib/libformula/

$(obj): 
	make -C ./src progobj

.PHONY: clean
clean:
	@echo "Deleting binary files..."
	make -C ./lib/libformula/ clean
	rm *.o
	rm -rf ./bin
	@echo "Finish!"