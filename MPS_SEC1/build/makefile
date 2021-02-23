INCDIR := include	# ヘッダファイル置き場
SRCDIR := src		# ソースコード置き場
TARGET := main
SRCS := $(../src/main.cpp)
HEADERS := $(wildcard ../include/*.hpp)
AR := $(wildcard src/*.a)
OUTDIR := build		# 出力先フォルダ

CC = g++
CFLAGS = -Wall -O2 -o

# オブジェクトファイルの作成
$(TARGET) : $(SRCS)
	$(CC) $(CFLAGS) $@ $^ $(AR) $(HEADERS) 