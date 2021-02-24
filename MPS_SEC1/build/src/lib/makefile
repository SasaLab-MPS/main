INCDIR := include	# ヘッダファイル置き場
SRCDIR := src		# ソースコード置き場
LIBDIR := lib		# いろんな関数の置き場
HEADERS = $(wildcard ../../../include/*.hpp)
SRCS = $(wildcard ../../../src/lib/*.cpp)
OUTDIR := build		# 出力先フォルダ

CC = g++
CFLAGS = -Wall -O2 -c

# オブジェクトファイルの作成
obj : $(SRCS)
	$(CC) $(CFLAGS) $^ $(HEADERS)