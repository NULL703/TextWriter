#************************************************************************
# 项目根目录下的主Makefile.
# Copyright (C) 2022 NULL_703. All rights reserved.
# Created on 2022.7.9  12:44
# Created by NULL_703
# Last change time on 2022.10.29  21:38
#*************************************************************************
cpp := g++
gc := gcc
cflag := -O2 -std=c99 -Wall -s -I ./include
flag := -O2 -std=c++11 -Wall -s -I ./include
bin := cmdtr
lib := libformula.so
obj := main.o cmdargs.o filereader.o writer.o

all: $(bin) $(lib)
	mv $(bin) "./bin"

$(bin): $(lib) $(obj)
	$(gc) $(obj) -L. -lformula -lm $(cflag) -o $(bin)
	rm $(lib)

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