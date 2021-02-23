INCDIR := include	# ヘッダファイル置き場
SRCDIR := src		# ソースコード置き場
LIBDIR := lib		# いろんな関数の置き場
SRCS := $(wildcard ../src/main.cpp)
HEADERS := $(wildcard ../$(INCDIR)/*.hpp)
AR := $(wildcard src/*.a)
OUTDIR := build		# 出力先フォルダ

CC = g++
CFLAGS = -Wall -O2 -o

# オブジェクトファイルの作成
main : $(SRCS)
	$(CC) $(CFLAGS) $^ -l $(AR) $(HEADERS) 