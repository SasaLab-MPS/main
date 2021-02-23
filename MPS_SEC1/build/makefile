INCDIR := include	# ヘッダファイル置き場
LIBDIR := -L/src		# ソースコード置き場
TARGET := main
SRC := ../src/main.cpp
OBJS := $(wildcard src/lib/*.o)
HEADERS := $(wildcard ../include/*.hpp)
# LIB := -lfuncs
# OUTDIR := build		# 出力先フォルダ

CC = g++
CFLAGS = -Wall -O2 -o

# オブジェクトファイルの作成
# $(TARGET) : $(SRCS)
#	$(CC) $(CFLAGS) $@ $(LIBDIR) $(LIB) $^ $(HEADERS) 

# 実行ファイルの作成
$(TARGET) : $(SRC)
	$(CC) $(CFLAGS) $@ $^ $(OBJS) $(HEADERS)