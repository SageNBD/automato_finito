#ifndef _STATE_H_
#define _STATE_H_

#include <Transition.hpp>
#include <vector>

class State
{
public:
    std::vector<Transition> transitions;
    bool isFinal;

    void setFinal(bool val);
    void insertTransition(Transition t);
    bool getFinal();
    State();
};

#endif