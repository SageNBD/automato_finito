#ifndef _UTILS_H_
#define _UTILS_H_

#include <string>
#include <vector>
#include "Transition.hpp"

int readNumStates();
std::string readTerminalSymbols();
std::string readExtendedSymbols();
std::vector<int> readInitStates();
std::vector<int> readAcceptingStates();
std::vector<Transition> readTransitions();
std::vector<std::string> readChains();

#endif