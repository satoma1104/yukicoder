# ビルドする問題に応じて値を変える
TARGET=prob246

CXX=g++
SRC=$(TARGET).cc
OBJ=$(SRC:.cc=.o)
WARNING=-Wall -pedantic-errors -Werror
OPT=-O2
CXXFLAGS=$(OPT) $(WARNING)

$(TARGET): $(OBJ)
	$(CXX) -o $@ $?

test:
	$(MAKE) $(TARGET) CPPFLAGS=-DTEST

debug:
	$(MAKE) $(TARGET) OPT=-g

debugtest:
	$(MAKE) $(TARGET) CPPFLAGS=-DTEST OPT=-g

clean:
	rm -rf *.exe *.o *.stackdump
