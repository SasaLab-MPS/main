# INCDIR := include	# ヘッダファイル置き場
# SRCDIR := src		# ソースコード置き場
TARGET = main
OBJS = $(wildcard ./src/lib/*.o)
SRC = ../src/main.cpp
HEADERS = ../include/inputs.hpp ../include/functions.hpp
OUTDIR := build		# 出力先フォルダ

CC = g++
CFLAGS = -Wall -O2 -o

# ライブラリトファイルの作成
$(TARGET) : $(SRC)
	$(CC) $(CFLAGS) $@ $^ $(HEADERS) $(OBJS)