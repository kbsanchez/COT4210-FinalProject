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
    vector <string> allStates;
    vector<transition_t> transitions;
    vector< vector< vector <string> > > transitionTable;
} nfa_t;

void printNFA(nfa_t nfa);

int main() {

    int numStates = 0, numTransitions = 0, i = 0;
    bool Final = 0, exists = 0, in = 0, in2 = 0;
    nfa_t nfa;
    transition_t trans;
    string temp;

    cout << "Number of states: ";
    cin >> numStates;

    cout << "Initial state: ";
    cin >> nfa.initialState;

    nfa.allStates.push_back(nfa.initialState);

    while (Final == 0 && i < numStates){
        cout << "Final state: ";
        cin >> temp;
        
        nfa.finalStates.push_back(temp);
        nfa.allStates.push_back(nfa.finalStates[i]);

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
        for(int i = 0; i < nfa.allStates.size(); ++i){
            if (trans.presentState == nfa.allStates[i]){
                in = 1;
            }
        }
        for(int i = 0; i < nfa.allStates.size(); ++i){
            if (trans.nextState == nfa.allStates[i]){
                in2 = 1;
            }
        }
        if(exists == 0){
            nfa.symbols.push_back(trans.symbol);
        }
        if(in == 0){
            nfa.allStates.push_back(trans.presentState);
        }
        if(in2 == 0){
            nfa.allStates.push_back(trans.nextState);
        }

        nfa.transitions.push_back(trans);
        exists = 0, in = 0, in2 = 0;
    }

    printNFA(nfa);

    return 0;
}

void printNFA(nfa_t nfa){
    int captureIndex = -1, captureIndex2 = -1;
    vector< vector<string> > temp;
    int count = 0, count2 = 0;

    cout << "\nNFA Transition Table:\n";
    cout << "State\t|";
    for(int i = 0; i < nfa.symbols.size(); ++i){
        cout << "\t" << nfa.symbols[i] << "|";
    }

    for(int i = 0; i < nfa.allStates.size(); ++i){
        cout << "\n" << nfa.allStates[i] << "\t|";
        for(int j = 0; i < nfa.symbols.size(); ++j){
            for(int k = 0; k < nfa.transitions.size(); ++k){
                if(nfa.transitions[k].presentState == nfa.allStates[i] && nfa.transitions[k].symbol == nfa.symbols[j]){
                    captureIndex = k;
                    temp[j].push_back(nfa.transitions[k].nextState);
                    
                }
            }
            if(captureIndex >= 0){
                captureIndex2 = j;
                nfa.transitionTable[i][j].push_back(temp[j][count]);
                captureIndex = -1;
                count++;
            }
            else if(captureIndex < 0 && captureIndex2 < 0){
                temp[j].push_back(" ");
                nfa.transitionTable[i][j].push_back(temp[j][count]);
                count++;
            }
            
        }
        
        for(int j = 0; i < nfa.symbols.size(); ++j){
            cout << nfa.transitionTable[i][j][count-1] << "\t|";
        }
        captureIndex2 = -1;
    }
    
}