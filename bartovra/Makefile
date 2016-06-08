CXX=g++
CXXFLAGS=-Wall -g -pedantic -Wno-long-long -O0 -ggdb -std=c++11
LDFLAGS=-lncurses
SRCS=src/main.cpp src/CSpreadsheetSimulator.cpp src/CScreen.cpp src/CSheet.cpp src/CCell.cpp src/CNumber.cpp src/CExpression.cpp src/CString.cpp
OBJS=$(subst .cpp,.o,$(SRCS))
EXEC=bartovra

all: doc compile

compile: $(OBJS)
	$(CXX)  $(CXXFLAGS) -o $(EXEC) $(OBJS) $(LDFLAGS)

main.o: src/main.cpp src/CSpreadsheetSimulator.hpp
CSpreadsheetSimulator.o: src/CSpreadsheetSimulator.cpp src/CSpreadsheetSimulator.hpp src/Sheet.hpp src/Screen.hpp

CCell.o: src/CCell.cpp src/CCell.hpp
CString.o: src/CString.cpp src/CString.hpp src/CCell.hpp
CNumber.o: src/CNumber.cpp src/CNumber.hpp src/CCell.hpp
CExpression.o: src/CExpression.cpp src/CExpression.hpp src/CCell.hpp

CSheet.o: src/CSheet.cpp src/CSheet.hpp src/CCell.hpp src/CString.hpp src/CNumber.hpp src/CExpression.hpp
CScreen.o: src/Screen.cpp src/Screen.hpp src/Sheet.hpp 


clean:
	rm -rf src/*.o bartovra doc

run:
	./bartovra

doc: $(OBJS)
	doxygen Doxyfile