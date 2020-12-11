#include <vector>
#include <string>
#include <iostream>
#include <AutomatoFinito.hpp>

AutomatoFinito::AutomatoFinito(int n, std::string terminalSymbols, std::string sigmaExtended, std::vector<int> initStates, 
          std::vector<int> acceptingStates, std::vector<Transition> transitions) 
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
 * bool AutomatoFinito::setAcceptingStates(std::vector<int> acceptingStates)
 * 
 * Initially sets every state isFinal flag to false
 * Then, loops through the acceptingStates vector, and given the state id,
 * sets the correspondent state flag isFinal to true
 * 
 * @param   std::vector<int>    acceptingStates     vector containing all state ids
 * @return  void
 */
void AutomatoFinito::setAcceptingStates(std::vector<int> acceptingStates) 
{
    for (int i = 0; i < this->numStates; ++i) this->states[i].setFinal(false);
    for (auto u : acceptingStates) this->states[u].setFinal(true);
}

/**
 * bool AutomatoFinito::isValidSymbol(char ch)
 * 
 * Check if a symbol is terminal by looping through the terminalSymbols vector
 * 
 * @param   char    ch    destination edge id
 * @return  bool    valid or not
 */
bool AutomatoFinito::isValidSymbol(char ch) 
{ 
    if (ch == '-') return true;
    for (auto u : this->terminalSymbols)
        if (ch == u) return true;
    std::cout << "ERRO: Caractér '" << ch << "' não é símbolo terminal." << '\n';
    return false;
}

/**
 * bool AutomatoFinito::indexOutOfRange(int src, int dest)
 * 
 * Checks if the source and destination Ids of an edge are valid, that is,
 * it respects the interval [0, numStates - 1]
 * 
 * @param   int     src     source edge id
 * @param   int     dest    destination edge id
 * @return  bool    valid or not
 */
bool AutomatoFinito::indexOutOfRange(int src, int dst) 
{
    if (src < 0 || src >= this->numStates || dst < 0 || dst >= this->numStates) 
    {
        std::cout << "ERRO: Índices não respeitam a numeração de estados." << '\n';
        return true;
    }
    return false;
}

/**
 * void AutomatoFinito::insertTransition(Transition transition)
 * 
 * Insert a single transition in the automata, checking if the data
 * is respects the automata constraints
 * 
 * @param   Transition     transition     Automata edge
 * @return  void
 */
void AutomatoFinito::insertTransition(int src, int dst, char chR, char chW, char D) 
{
    if (!isValidSymbol(chR) || !isValidSymbol(chW) || indexOutOfRange(src, dst)) return;
    this->states[src].insertTransition(Transition(src, dst, chR, chW, D));
}

/**
 * void AutomatoFinito::insertTransitions(std::vector<Transition> transitions)
 * 
 * For every Transition object containing the data of an edge, check if
 * the data is valid (not out of bounds or is terminal character) and 
 * pushes it to the transition vector of the source state.
 * 
 * @param   std::vector<Transition>     transitions     Automata edges
 * @return  void
 */
void AutomatoFinito::insertTransitions(std::vector<Transition> transitions) 
{
    for (int i = 0; i < (int)transitions.size(); ++i) 
    {
        Transition t = transitions[i];
        if (!isValidSymbol(t.edgeWrite) || !isValidSymbol(t.edgeWrite) || indexOutOfRange(t.source, t.dest)) continue;
        this->states[t.source].insertTransition(t);
    }
}

/**
 * void AutomatoFinito::printTrasition()
 * 
 * Print each transition of all the states in the automata 
 */
void AutomatoFinito::printTransition() 
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
 * void AutomatoFinito::isValidChain(std::string str, int stateId, int currIdx)
 * 
 * Determines if a chain is valid by running a DFS on the automata. 
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
bool AutomatoFinito::isValidChain(std::string str, int stateId, int currIdx) 
{
    if (currIdx >= (int)str.size()) {
        str.push_back('B');
    }
    
    if(currIdx < 0) {
        currIdx += 1;
        str = "B" + str; 
    } 

    State currState = this->states[stateId];
    // Test all transitions of 'stateId'
    for (int i = 0; i < (int)currState.transitions.size(); ++i) 
    {
        Transition t = currState.transitions[i];
        // Call next DFS phase
        if (t.edgeRead == str[currIdx]) {
            // update tape
            str[currIdx] = t.edgeWrite;
            if(isValidChain(str, t.dest, currIdx + this->directionMap[t.direction])) 
            {
                return true;
            }
            // restore tape
            str[currIdx] = t.edgeRead;
        }
        // Lambda 
        // else if (t.edgeRead == '-' && isValidChain(str, t.dest, currIdx))
        // {
        //     return true;
        // }
    }
    return false; // Didnt find transition that matched current chain symbol
}

/**
 * void AutomatoFinito::runSimulation(std::vector<std::string> inputs)
 * 
 * For each user input string, determines if the current chain is valid
 * by calling the isValidChain() function.
 * If the automata is non-deterministic, call the validation function
 * for every initial state.
 * 
 * @param std::vector<std::string>  inputs  chains to be determined
 * @return  none    prints a message that indicates whether the chain is valid or not
 */
void AutomatoFinito::runSimulation(std::vector<std::string> inputs) 
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
 * std::string AutomatoFinito::getAutomataType()
 * 
 * Returns whether automata is deterministic or non-deterministic
 * 
 * @return std::string  automataType    Deterministic or Non-Deterministic
 */
std::string AutomatoFinito::getAutomataType() 
{ 
    return this->bIsAFD ? "Determinístico": "Não Determinístico"; 
}