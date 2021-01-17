CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD -g
EXEC = connect4
OBJECTS = main.o board.o humanPlayer.o controller.o textView.o playerTeam.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}
