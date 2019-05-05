
#g++ config.cc datamanage.cc linkedclient.cc  socketevent.cc main.cc -I../inc/   -o dzpserver


CC :=g++
FLAGS = -g

DIR_INCLUDE := ../inc
DIR_SOURCE := ../src
DIR_OBJS := ../obj
DIR_EXEC := ./
EXEC_NAME :=dzp_server

CPPSOURCE := $(wildcard $(DIR_SOURCE)/*.cc )
OBJS := $(patsubst $(DIR_SOURCE)/%.cc, $(DIR_OBJS)/%.o, $(CPPSOURCE) )

all: makeobjdir $(DIR_EXEC)/$(EXEC_NAME)

makeobjdir:
        mkdir -p DIR_OBJS
        @echo $(CPPSOURCE)
        @echo $(OBJS)

$(DIR_EXEC)/$(EXEC_NAME): $(OBJS)
        $(CC) -I$(DIR_INCLUDE) $^ -o $@

$(DIR_OBJS)/%.o:$(DIR_SOURCE)/%.cc
        $(CC) $(FLAGS) -I$(DIR_INCLUDE) -c $< -o $@

clean:
        rm -f $(DIR_OBJS)/*.o
