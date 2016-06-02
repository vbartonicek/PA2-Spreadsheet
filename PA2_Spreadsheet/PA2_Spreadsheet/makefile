CXX=g++
CXXFlags=-Wall -pedantic -lncurses
LD=G++
LDFLAGS=-Wall -pedantic -lncurses

all: SpreadsheetSimulator

SpreadsheetSimulator: main.o CSpreadsheetSimulator.o CSheet.o CScreen.o
	$(LD) $(LDFLAGS) main.o CSpreadsheetSimulator.o CSheet.o CScreen.o -o SpreadsheetSimulator

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm SpreadsheetSimulator *.o
