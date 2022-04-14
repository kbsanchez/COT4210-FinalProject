#include <iostream>
#include <string>
#include <list>

using namespace std;

typedef struct transition_t {
    string presentState;
    string symbol;
    string nextState;
} transition_t;

typedef struct nfa_t {
    string initialState;
    string finalStates[10];
    list<transition_t> transitions;
} nfa_t;

int main() {

    int numStates = 0, numTransitions = 0, i = 0;
    bool Final = 0;
    nfa_t nfa;
    transition_t trans;

    cout << "Number of states: ";
    cin >> numStates;

    cout << "Initial state: ";
    cin >> nfa.initialState;

    while (Final == 0 && i < numStates){
        cout << "Final state: ";
        cin >> nfa.finalStates[i];

        cout << "Add another final state?\nEnter 0 for yes, 1 for no: ";
        cin >> Final;
        ++i;
    }

    cout << "Number of transitions: ";
    cin >> numTransitions;

    cout << "\nEnter each transition in the form of {present state} {symbol} {next state}\n\n";

    for (int j = 0; j < numTransitions; ++j){
        cout << "Transition " << j+1 << ": ";
        cin >> trans.presentState >> trans.symbol >> trans.nextState;

        nfa.transitions.push_back(trans);
    }

    return 0;
}