INCDIR := include	# ヘッダファイル置き場
SRCDIR := src		# ソースコード置き場
LIBDIR := lib		# いろんな関数の置き場
HEADERS = $(wildcard ../../$(INCDIR)/*.hpp)
SRCS = $(wildcard *.cpp)
OUTDIR := ../../build/src/lib		# 出力先ディレクトリ

CC = g++
CFLAGS = -Wall -O2 -c

# オブジェクトファイルの作成
#$(OUTDIR)%.o: %.cpp
#	@[-d $(OUTDIR)]
#	$(CC) $(CFLAGS) $@ $^ $(HEADERS)

#$(OUTDIR)/%.o: $(SRCS)
#	$(CC) $(CFLAGS) $< $@ $(HEADERS)

obj : $(SRCS)
	$(CC) $(CFLAGS) $^ $(HEADERS)