#include <vector>
#include <string>
#include <iostream>
#include "Transition.hpp"
#include "utils.hpp"

int readNumStates()
{
    int numStates;

    std::cin >> numStates;
    getchar();

    return numStates;
}

std::string readTerminalSymbols()
{
    int numTerminalSymbols;
    std::cin >> numTerminalSymbols;
    std::string terminalSymbols = "";
    for (int i = 0; i < numTerminalSymbols; ++i) 
    {
        char ch;
        std::cin >> ch;
        terminalSymbols += ch;
    }

    return terminalSymbols;
}

std::vector<int> readInitStates() 
{
    int numInitStates;
    std::cin >> numInitStates;

    std::vector<int> initStates;
    if (numInitStates == 1) 
    {
        initStates.push_back(0);
    }
    else 
    {
        for (int i = 0; i < numInitStates; ++i) 
        {
            int x; 
            std::cin >> x;
            initStates.push_back(x);
        }
    }

    return initStates;
}

std::vector<int> readAcceptingStates()
{
    int numAcceptingStates;
    std::cin >> numAcceptingStates;

    std::vector<int> acceptingStates;
    for (int i = 0; i < numAcceptingStates; ++i) 
    {
        int x; 
        std::cin >> x;
        acceptingStates.push_back(x);
    }

    return acceptingStates;
}

std::vector<Transition> readTransitions()
{
    int numTransitions; 
    std::cin >> numTransitions;

    std::vector<Transition> transitions;
    for (int i = 0; i < numTransitions; ++i) 
    {
        int src, dest;
        char edge;
        std::cin >> src >> edge >> dest;
        transitions.push_back(Transition(src, dest, edge));
    }

    return transitions;
}

std::vector<std::string> readChains()
{
    int numChains;
    std::cin >> numChains;

    std::vector<std::string> chains;
    for (int i = 0; i < numChains; ++i) 
    {
        std::string str;
        std::cin >> str;
        chains.push_back(str);
    }

    return chains;
}