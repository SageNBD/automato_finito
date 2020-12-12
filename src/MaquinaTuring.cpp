#include <vector>
#include <string>
#include <iostream>
#include <MaquinaTuring.hpp>

MaquinaTuring::MaquinaTuring(
    int n,
    std::string terminalSymbols,
    std::string sigmaExtended,
    std::vector<int> initStates,
    std::vector<int> acceptingStates,
    std::vector<Transition> transitions)
{
    this->numStates = n;
    this->terminalSymbols = terminalSymbols;
    this->sigmaExtended = sigmaExtended;
    this->initStates = initStates;
    this->bIsAFD = (int)initStates.size() == 1;
    this->acceptingStates = acceptingStates;
    this->states = std::vector<State>(n);
    this->insertTransitions(transitions);
    this->setAcceptingStates(acceptingStates);
}

/**
 * bool MaquinaTuring::setAcceptingStates(std::vector<int> acceptingStates)
 * 
 * Initially sets every state isFinal flag to false
 * Then, loops through the acceptingStates vector, and given the state id,
 * sets the correspondent state flag isFinal to true
 * 
 * @param   std::vector<int>    acceptingStates     vector containing all state ids
 * @return  void
 */
void MaquinaTuring::setAcceptingStates(std::vector<int> acceptingStates)
{
    for (int i = 0; i < this->numStates; ++i)
        this->states[i].setFinal(false);
    for (auto u : acceptingStates)
        this->states[u].setFinal(true);
}

/**
 * bool MaquinaTuring::isValidSymbol(char ch)
 * 
 * Check if a symbol is terminal by looping through the terminalSymbols vector
 * 
 * @param   char    ch    destination edge id
 * @return  bool    valid or not
 */
bool MaquinaTuring::isValidSymbol(char ch)
{
    return ch != ' ';
}

/**
 * bool MaquinaTuring::indexOutOfRange(int src, int dest)
 * 
 * Checks if the source and destination Ids of an edge are valid, that is,
 * it respects the interval [0, numStates - 1]
 * 
 * @param   int     src     source edge id
 * @param   int     dest    destination edge id
 * @return  bool    valid or not
 */
bool MaquinaTuring::indexOutOfRange(int src, int dst)
{
    if (src < 0 || src >= this->numStates || dst < 0 || dst >= this->numStates)
    {
        std::cout << "ERRO: Índices não respeitam a numeração de estados. " << src << " " << dst << '\n';
        return true;
    }
    return false;
}

/**
 * void MaquinaTuring::insertTransition(Transition transition)
 * 
 * Insert a single transition in the turing machine, checking if the data
 * is respects the turing machine constraints
 * 
 * @param   Transition     transition     turing machine edge
 * @return  void
 */
void MaquinaTuring::insertTransition(int src, int dst, char chR, char chW, char D)
{
    if (!isValidSymbol(chR) || !isValidSymbol(chW) || indexOutOfRange(src, dst))
        return;
    this->states[src].insertTransition(Transition(src, dst, chR, chW, D));
}

/**
 * void MaquinaTuring::insertTransitions(std::vector<Transition> transitions)
 * 
 * For every Transition object containing the data of an edge, check if
 * the data is valid (not out of bounds or is terminal character) and 
 * pushes it to the transition vector of the source state.
 * 
 * @param   std::vector<Transition>     transitions     turing machine edges
 * @return  void
 */
void MaquinaTuring::insertTransitions(std::vector<Transition> transitions)
{
    for (int i = 0; i < (int)transitions.size(); ++i)
    {
        Transition t = transitions[i];
        if (!isValidSymbol(t.edgeWrite) || !isValidSymbol(t.edgeWrite) || indexOutOfRange(t.source, t.dest))
            continue;
        this->states[t.source].insertTransition(t);
    }
}

/**
 * void MaquinaTuring::printTrasition()
 * 
 * Print each transition of all the states in the turing machine 
 */
void MaquinaTuring::printTransition()
{
    for (auto u : this->states)
    {
        for (int i = 0; i < (int)u.transitions.size(); ++i)
        {
            Transition t = u.transitions[i];
            std::cout << "(" << t.source << ", " << t.edgeRead << ", " << t.dest << ", " << t.edgeWrite << ", " << t.direction << ")\n";
        }
    }
}

/**
 * void MaquinaTuring::isValidChain(std::string str, int stateId, int currIdx)
 * 
 * Determines if a chain is valid by running a DFS on the turing machine. 
 * Given a state 's' and the current character 'ch' of the chain, check if there is a possible
 * path that matches 'ch' and the transitions that start from 's'.
 * If so, recursively call isValidChain(), incrementing the index and using one of the 
 * states that are adjacent to 's'.
 * 
 * @param   std::string   str         string representing the chain
 * @param   int           stateId     current state id
 * @param   int           currIdx     current index of chain
 * @return  bool          isValid     chain validation
 */
bool MaquinaTuring::isValidChain(std::string str, int stateId, int currIdx)
{
    // Chegou no estado de aceitação, retornar
    if (stateId == this->acceptingStates[0])
        return true;

    if (currIdx >= (int)str.size())
    {
        str.push_back('B');
        currIdx = str.length() - 1;
    }
    else if (currIdx < 0)
    {
        str = "B" + str;
        currIdx = 0;
    }

    State currState = this->states[stateId];
    // Test all transitions of 'stateId'
    for (int i = 0; i < (int)currState.transitions.size(); ++i)
    {
        Transition t = currState.transitions[i];
        // Call next DFS phase
        if (t.edgeRead == str[currIdx])
        {
            // update tape
            str[currIdx] = t.edgeWrite;
            if (isValidChain(str, t.dest, currIdx + this->directionMap[t.direction]))
            {
                return true;
            }
            // restore tape
            str[currIdx] = t.edgeRead;
        }
    }

    return false; // Didnt find transition that matched current chain symbol
}

/**
 * void MaquinaTuring::runSimulation(std::vector<std::string> inputs)
 * 
 * For each user input string, determines if the current chain is valid
 * by calling the isValidChain() function.
 * If the turing machine is non-deterministic, call the validation function
 * for every initial state.
 * 
 * @param std::vector<std::string>  inputs  chains to be determined
 * @return  none    prints a message that indicates whether the chain is valid or not
 */
void MaquinaTuring::runSimulation(std::vector<std::string> inputs)
{
    for (auto chain : inputs)
    {
        bool foundSolution = false;
        for (auto stateId : this->initStates)
        {
            if (isValidChain(chain, stateId, 0))
            {
                foundSolution = true;
                break;
            }
        }
        std::cout << (foundSolution ? "aceita" : "rejeita") << '\n';
    }
}

/**
 * std::string MaquinaTuring::getturing machineType()
 * 
 * Returns whether turing machine is deterministic or non-deterministic
 * 
 * @return std::string  turing machineType    Deterministic or Non-Deterministic
 */
std::string MaquinaTuring::getAutomataType()
{
    return this->bIsAFD ? "Determinístico" : "Não Determinístico";
}