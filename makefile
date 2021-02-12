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
CFLAGS = -Wall -O2 -I $(INCDIR)

#.PHONY: all clean
#all: $(TARGET)

# 実行ファイルの生成
#$(TARGET): $(OBJS)
#	$(CC) $(CFLAGS) -o $@ $^

# 出力先フォルダの作成(無い場合作成)
$(OUTDIR): 
	@if not exist $(OUTDIR) mkdir $(OUTDIR)

# オブジェクトファイルの作成
# $(OUTDIR)/%.o : $(SRCS)
#	if [ ! -e `dirname $@` ]; then mkdir -p `dirname $@`; fi
#	$(CC) $(CFLAGS) $^ $(HEADERS)