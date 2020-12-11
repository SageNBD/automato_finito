#include <vector>
#include <string>
#include <iostream>
#include <Transition.hpp>
#include <utils.hpp>

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

std::string readExtendedSymbols() {
    int numExtendedSymbols;
    std::cin >> numExtendedSymbols;
    std::string extendedSymbols = "";
    for (int i = 0; i < numExtendedSymbols; ++i) 
    {
        char ch;
        std::cin >> ch;
        extendedSymbols += ch;
    }

    return extendedSymbols;
}

std::vector<int> readInitStates() 
{
    int numInitStates;
    std::cin >> numInitStates;

    std::vector<int> initStates;
    for (int i = 0; i < numInitStates; ++i) 
    {
        initStates.push_back(i);
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
        char edgeRead, edgeWrite, direction;
        std::cin >> src >> edgeRead >> dest >> edgeWrite >> direction;
        transitions.push_back(Transition(src, dest, edgeRead, edgeWrite, direction));
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