# 参考：http://boysenberrypi.hatenadiary.jp/entry/2014/03/15/113703
INCDIR := ./include	# ヘッダファイル置き場
SRCDIR := ./src		# ソースコード置き場
LIBDIR := ./lib		# いろんな関数の置き場
HEADERS = $(wildcard $(INCDIR)/*.hpp)
SRCS = $(wildcard $(SRCDIR)/$(LIBDIR)/*.cpp)
OUTDIR := ./build/src/lib		# 出力先ディレクトリ

CC = g++
CFLAGS = -Wall -O2

$(OUTDIR)/%.o: $(SRCDIR)/%.cpp
	@if [! -d $(OUTDIR)]; \
		then echo "mkdir -p $(OBJ_DIR)"; mkdir -p $(OBJ_DIR); \
      	fi
	$(CC) $(CFLAGS) $(HEADERS) -o $@ -c $<
