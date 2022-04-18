#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

typedef struct transition_t {
    string presentState;
    string symbol;
    string nextState;
} transition_t;

typedef struct nfa_t {
    string initialState;
    vector <string> finalStates;
    vector <string> symbols;
    vector<transition_t> transitions;
    vector< vector< vector <string> > > transitionTable;
} nfa_t;

void printNFA(nfa_t nfa);

int main() {

    int numStates = 0, numTransitions = 0, i = 0;
    bool Final = 0, exists = 0;
    nfa_t nfa;
    transition_t trans;
    string temp;

    cout << "Number of states: ";
    cin >> numStates;

    cout << "Initial state: ";
    cin >> nfa.initialState;

    while (Final == 0 && i < numStates){
        cout << "Final state: ";
        cin >> temp;
        
        nfa.finalStates.push_back(temp);

        ++i;
        if(i < numStates){
            cout << "Add another final state?\nEnter 0 for yes, 1 for no: ";
            cin >> Final;
        }
    }

    cout << "Number of transitions: ";
    cin >> numTransitions;

    cout << "\nEnter each transition in the form of {present state} {symbol} {next state}\n\n";

    for (int j = 0; j < numTransitions; ++j){
        cout << "Transition " << j+1 << ": ";
        cin >> trans.presentState >> trans.symbol >> trans.nextState;
        for(int i = 0; i < nfa.symbols.size(); ++i){
            if (trans.symbol == nfa.symbols[i]){
                exists = 1;
            }
        }
        if(exists == 0){
            nfa.symbols.push_back(trans.symbol);
        }

        nfa.transitions.push_back(trans);
    }

    printNFA(nfa);

    return 0;
}

void printNFA(nfa_t nfa){
    cout << "\nNFA Transition Table:\n";
    cout << "State\t|";
    for(int i = 0; i < nfa.symbols.size(); ++i){
        cout << "\t" << nfa.symbols[i] << "|";
    }

    for(int j = 0; j < nfa.transitions.size(); j++){

        //cout << "\n" << nfa.transitions[j].presentState << "\t|";
    }

    
}