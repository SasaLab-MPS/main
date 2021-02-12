# http://nao-bamboo.hatenablog.com/entry/2015/09/11/175832
PROGNAME := main	# 生成したい実行ファイル
INCDIR := include
SRCDIR := src
LIBDIR := lib
HEADERS = $(wildcard $(INCDIR)/*.hpp)
OUTDIR := build		# 出力フォルダ
TARGET := $(OUTDIR)/$(PROGNAME)
SRCS := $(wildcard $(SRCDIR)/*.cpp) $(wildcard $(SRCDIR)/$(LIBDIR)/*.cpp)
OBJS := $(addprefix $(OUTDIR)/,$(patsubst %.cpp,%.o,$(SRCS)))
#$(warning $(OBJS))

CC = g++
CFLAGS = -Wall -O2

