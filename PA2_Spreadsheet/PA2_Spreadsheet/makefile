CXX=g++
CXXFlags= -Wall -pedantic -std=c++11
LD=G++
LDFLAGS=-lncurses

all: SpreadsheetSimulator

SpreadsheetSimulator: main.o CSpreadsheetSimulator.o CSheet.o CScreen.o CCell.o CString.o CNumber.o CExpression.o
	$(LD) $(LDFLAGS) main.o CSpreadsheetSimulator.o CSheet.o CScreen.o CCell.o CString.o CNumber.o CExpression.o -o SpreadsheetSimulator

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(LDFLAGS)

clean:
	rm SpreadsheetSimulator *.o
