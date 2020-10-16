#ifndef _AUTOMATO_H_
#define _AUTOMATO_H_

#include <Transition.hpp>
#include <State.hpp>
#include <vector>
#include <string>

class AutomatoFinito
{
private:
    int numStates;
    std::vector<State> states;
    std::string terminalSymbols;
    std::vector<int> acceptingStates;
    std::vector<int> initStates;
    bool isAFD;
    void setAcceptingStates(std::vector<int> acceptingStates);
    bool isValidSymbol(char ch);
    bool indexOutOfRange(int src, int dst);
    void insertTransition(int src, int dst, char ch);
    void insertTransitions(std::vector<Transition> transitions);
    void printTransition(); 
    bool validateChain(std::string str, int stateId, int currIdx); 
public:
    AutomatoFinito(int n, std::string terminalSymbols, std::vector<int> initStates, 
              std::vector<int> acceptingStates, std::vector<Transition> transitions);
    void runSimulation(std::vector<std::string> inputs);
    std::string getAutomataType();
};

#endif