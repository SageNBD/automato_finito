#ifndef _TRANSITION_HPP_
#define _TRANSITION_HPP_

class Transition
{
public:
    int source;
    int dest;
    char edge;

    Transition(int src, int dst, char edge);
};

#endif