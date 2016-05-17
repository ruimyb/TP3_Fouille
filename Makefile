REP_HEADERS = ./headers
REP_SRC = ./src
REP_TESTS = ./tests
REP_OBJ = ./obj_src

EXE = prog.exe

CXX = gcc
CXXFLAGS = -Wall -Wextra -g -std=c99

.PHONY : all clean check

SRC = $(wildcard $(REP_SRC)/*.c)
OBJS = $(SRC:$(REP_SRC)/%.c=$(REP_OBJ)/%.o)

$(EXE) : $(OBJS)
	$(CXX) $(CXXFLAGS) -I $(REP_HEADERS) -o $@ $^

$(REP_OBJ) :
	mkdir -p $@

$(REP_OBJ)/%.o : $(REP_SRC)/%.c $(REP_OBJ)
	$(CXX) $(CXXFLAGS) -I $(REP_HEADERS) -o $@ -c $<

clean : 
	rm -f -r $(REP_OBJ) $(EXE)

check : 
	echo $(SRC)
	echo $(OBJS)
