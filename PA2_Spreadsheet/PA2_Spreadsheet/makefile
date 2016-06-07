CXX=g++
CXXFlags= -std=c++11 -Wall -pedantic -Wno-long-long -O0 -ggdb
LD=G++
LDFLAGS=-lncurses

all: SpreadsheetSimulator

SpreadsheetSimulator: main.o CSpreadsheetSimulator.o CSheet.o CScreen.o CCell.o CString.o CNumber.o CExpression.o
	$(LD) $(LDFLAGS) main.o CSpreadsheetSimulator.o CSheet.o CScreen.o CCell.o CString.o CNumber.o CExpression.o -o SpreadsheetSimulator

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -g -o $@

clean:
	rm SpreadsheetSimulator *.o
