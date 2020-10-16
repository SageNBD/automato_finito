#include <iostream>
#include <vector>
#include <string>
#include "utils.hpp"
#include "Transition.hpp"
#include "State.hpp"
#include "AutomatoFinito.hpp"

int main(int argc, char *argv[]) 
{
    int numStates = readNumStates();
    std::string terminalSymbols = readTerminalSymbols();
    std::vector<int> initStates = readInitStates();
    std::vector<int> acceptingStates = readAcceptingStates();
    std::vector<Transition> transitions = readTransitions();
    std::vector<std::string> chains = readChains();

    AutomatoFinito a = AutomatoFinito(
        numStates, terminalSymbols, initStates, acceptingStates, transitions
    );

    a.runSimulation(chains);

    return 0;
}