#include <State.hpp>

State::State() : isFinal(false) {}

void State::setFinal(bool val)
{
    isFinal = val;
}

bool State::getFinal()
{
    return isFinal;
}

void State::insertTransition(Transition t)
{
    transitions.push_back(t);
}