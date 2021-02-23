INCDIR := include	# ヘッダファイル置き場
SRCDIR := src		# ソースコード置き場
LIBDIR := lib		# いろんな関数の置き場
OBJS = $(wildcard ./lib/*.o)
OUTDIR := build		# 出力先フォルダ

CC = ar
CFLAGS = r

# オブジェクトファイルの作成
libfuncs.a : $(OBJS)
	$(CC) $(CFLAGS) $@ $^