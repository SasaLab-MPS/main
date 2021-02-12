INCDIR := include	# ヘッダファイル置き場
SRCDIR := src		# ソースコード置き場
LIBDIR := lib		# いろんな関数の置き場
HEADERS = $(wildcard ../../$(INCDIR)/*.hpp)
SRCS = $(wildcard *.cpp)

CC = g++
CFLAGS = -Wall -O2 -c

obj : $(SRCS)
	$(CC) $(CFLAGS) $^ $(HEADERS)