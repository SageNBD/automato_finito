#include <Transition.hpp>

Transition::Transition(int src, int dst, char edgeRead, char edgeWrite, char direction) : 
            source(src), dest(dst), edgeRead(edgeRead), edgeWrite(edgeWrite), direction(direction) {}