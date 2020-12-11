#ifndef _TRANSITION_HPP_
#define _TRANSITION_HPP_

/*
    q x q' y D
*/
class Transition
{
public:
    int source;      // q
    int dest;        // q1
    char edgeRead;   // x
    char edgeWrite;  // y
    char direction;  // D

    Transition(int src, int dst, char edgeRead, char edgeWrite, char direction);
};

#endif