#include <iostream>
#include <vector>
#include <string>
#include <utils.hpp>
#include <Transition.hpp>
#include <State.hpp>
#include <AutomatoFinito.hpp>

int main(int argc, char *argv[])
{
    int numStates = readNumStates();
    std::string terminalSymbols = readTerminalSymbols();
    std::string sigmaExtended = readExtendedSymbols();
    std::vector<int> acceptingStates = readAcceptingStates();
    std::vector<int> initStates(1, 0);
    std::vector<Transition> transitions = readTransitions();
    std::vector<std::string> chains = readChains();

    AutomatoFinito a = AutomatoFinito(
        numStates, terminalSymbols, sigmaExtended, initStates, acceptingStates, transitions);

    a.runSimulation(chains);

    return 0;
}