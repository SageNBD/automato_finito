#ifndef _AUTOMATO_H_
#define _AUTOMATO_H_

#include <Transition.hpp>
#include <State.hpp>
#include <vector>
#include <string>
#include <map>

class MaquinaTuring
{
private:
    int numStates;
    std::vector<State> states;
    std::string terminalSymbols;
    std::string sigmaExtended;
    std::vector<int> acceptingStates;
    std::vector<int> initStates;
    bool bIsAFD;
    void setAcceptingStates(std::vector<int> acceptingStates);
    bool isValidSymbol(char ch);
    bool indexOutOfRange(int src, int dst);
    void insertTransition(int src, int dst, char chR, char chW, char D);
    void insertTransitions(std::vector<Transition> transitions);
    void printTransition();
    bool isValidChain(std::string str, int stateId, int currIdx);
    std::map<char, int> directionMap = {
        {'R', 1},
        {'L', -1},
        {'S', 0}};

public:
    MaquinaTuring(int n, std::string terminalSymbols, std::string sigmaExtended, std::vector<int> initStates,
                  std::vector<int> acceptingStates, std::vector<Transition> transitions);
    void runSimulation(std::vector<std::string> inputs);
    std::string getAutomataType();
};

#endif