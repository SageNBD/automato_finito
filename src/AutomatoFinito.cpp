#include <vector>
#include <string>
#include <iostream>
#include "AutomatoFinito.hpp"

AutomatoFinito::AutomatoFinito(int n, std::string terminalSymbols, std::vector<int> initStates, 
          std::vector<int> acceptingStates, std::vector<Transition> transitions) 
{
    this->numStates = n;
    this->terminalSymbols = terminalSymbols;
    this->initStates = initStates;
    this->acceptingStates = acceptingStates;
    this->states = std::vector<State>(n);
    this->insertTransitions(transitions);
    this->setAcceptingStates(acceptingStates);
}

void AutomatoFinito::setAcceptingStates(std::vector<int> acceptingStates) 
{
    for (int i = 0; i < this->numStates; ++i) this->states[i].setFinal(false);
    for (auto u : acceptingStates) this->states[u].setFinal(true);
}

bool AutomatoFinito::isValidSymbol(char ch) 
{ 
    if (ch == '-') return true;
    for (auto u : this->terminalSymbols)
        if (ch == u) return true;
    std::cout << "ERRO: Caractér '" << ch << "' não é símbolo terminal." << '\n';
    return false;
}

bool AutomatoFinito::indexOutOfRange(int src, int dst) 
{
    if (src < 0 || src >= this->numStates || dst < 0 || dst >= this->numStates) 
    {
        std::cout << "ERRO: Índices não respeitam a numeração de estados." << '\n';
        return true;
    }
    return false;
}

void AutomatoFinito::insertTransition(int src, int dst, char ch) 
{
    if (!isValidSymbol(ch) || indexOutOfRange(src, dst)) return;
    this->states[src].insertTransition(Transition(src, dst, ch));
}

void AutomatoFinito::insertTransitions(std::vector<Transition> transitions) 
{
    for (int i = 0; i < (int)transitions.size(); ++i) 
    {
        Transition t = transitions[i];
        if (!isValidSymbol(t.edge) || indexOutOfRange(t.source, t.dest)) continue;
        this->states[t.source].insertTransition(t);
    }
}

void AutomatoFinito::printTransition() 
{
    for (auto u : this->states) 
    {
        for (int i = 0; i < (int)u.transitions.size(); ++i) 
        {
            Transition t = u.transitions[i];
            std::cout << "(" << t.source << ", " << t.dest << ", " << t.edge << ")" << '\n';
        }
    }
}

bool AutomatoFinito::validateChain(std::string str, int stateId, int currIdx) 
{
    if (currIdx >= (int)str.size()) 
        return this->states[stateId].getFinal();

    State currState = this->states[stateId];
    for (int i = 0; i < (int)currState.transitions.size(); ++i) 
    {
        Transition t = currState.transitions[i];
        if (t.edge == str[currIdx]) // Call next DFS phase
        { 
            if (validateChain(str, t.dest, currIdx + 1)) 
                return true;
        }
        else if (t.edge == '-') // Lambda porém tratar 
        {
            if (validateChain(str, t.dest, currIdx))
                return true;
        }
    }
    return false; // Didnt find transition that matched current chain symbol
}

void AutomatoFinito::runSimulation(std::vector<std::string> inputs) 
{
    for (auto chain : inputs) 
    {
        bool foundSolution = false;
        for (auto stateId : this->initStates)
        {
            if (validateChain(chain, stateId, 0))
            {
                foundSolution = true;
                break;
            }
        }
        std::cout << (foundSolution ? "aceita" : "rejeita") << '\n';
    }
}

std::string AutomatoFinito::getAutomataType() 
{ 
    return this->isAFD ? "Determinístico": "Não Determinístico"; 
}