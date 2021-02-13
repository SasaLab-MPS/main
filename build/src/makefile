INCDIR := include	# ヘッダファイル置き場
SRCDIR := src		# ソースコード置き場
TARGET = main
OBJS = $(wildcard ./lib/*.o)
SRC = ../../src/main.cpp
HEADERS = $(wildcard ../../$(INCDIR)/*.hpp)
OUTDIR := build		# 出力先フォルダ

CC = g++
CFLAGS = -Wall -O2 -I $(HEADERS) -o

# ライブラリトファイルの作成
X : $(SRC)
	$(CC) $(CFLAGS) $^ $(OBJS)