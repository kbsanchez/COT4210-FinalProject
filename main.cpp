#include <iostream>
#include <cstdio>
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
    vector<string> finalStates;
    vector<string> symbols;
    vector<string> allStates;
    vector<transition_t> transitions;
    unordered_map<string, unordered_map<string, vector<string> > > nfaTable;
} nfa_t;

typedef struct dfaState_t {
    bool marked;
    vector<string> states;
    unordered_map<string, string> moves;
} dfaState_t;

void constructNFATable(nfa_t nfa);
void convertNFAtoDFA(nfa_t nfa);
void printDFA(nfa_t nfa);

int main() {

    int numStates = 0, numTransitions = 0, i = 0;
    bool Final = 1, exists = 0, in = 0, in2 = 0;
    nfa_t nfa;
    transition_t trans;
    string temp;

    cout << "Number of states: ";
    cin >> numStates;

    cout << "Initial state: ";
    cin >> nfa.initialState;

    nfa.allStates.push_back(nfa.initialState);

    while (Final == 1 && i < numStates){
        cout << "Final state: ";
        cin >> temp;
        
        nfa.finalStates.push_back(temp);
        for(int r = 0; r < nfa.allStates.size(); ++r){
            if(temp == nfa.allStates[r]){
                in = 1;
            }
        }
        // if(in == 0)
        //     nfa.allStates.push_back(nfa.finalStates[i]);

        ++i;
        if(i < numStates){
            cout << "Add another final state?\nEnter 1 for yes, 0 for no: ";
            cin >> Final;
        }
        in = 0;
    }

    cout << "Number of transitions: ";
    cin >> numTransitions;

    cout << "\nEnter each transition in the form of {present state} {symbol} {next state}\n"
    << "(Epsilon transitions can be denoted by using the symbol E)\n\n";

    for (int j = 0; j < numTransitions; ++j){
        cout << "Transition " << j+1 << ": ";
        cin >> trans.presentState >> trans.symbol >> trans.nextState;
        for(int i = 0; i < nfa.symbols.size(); ++i){
            if (trans.symbol == nfa.symbols[i]){
                exists = 1;
            }
        }
        if(!exists && trans.symbol != "E"){
            nfa.symbols.push_back(trans.symbol);
        }

        for(int i = 0; i < nfa.allStates.size(); ++i){
            if (trans.presentState == nfa.allStates[i]){
                in = 1;
            }
        }
        if(!in){
            nfa.allStates.push_back(trans.presentState);
        }

        for(int i = 0; i < nfa.allStates.size(); ++i){
            if (trans.nextState == nfa.allStates[i]){
                in2 = 1;
            }
        }
        if(!in2){
            nfa.allStates.push_back(trans.nextState);
        }

        nfa.transitions.push_back(trans);
        exists = 0, in = 0, in2 = 0;
    }
        
    nfa.symbols.push_back("E");

    constructNFATable(nfa);
    convertNFAtoDFA(nfa);

    return 0;
}

void constructNFATable(nfa_t nfa){
    bool found = 0;
    vector<string> temp;
    unordered_map<string, vector<string> > temp2;

    cout << endl << "**********************************************************" << endl
    << "      NFA table construction complete! Results below      " << endl
    << "**********************************************************" << endl << endl;

    cout << "\nNFA Transition Table:\n";
    cout << "State\t|";
    for(int i = 0; i < nfa.symbols.size(); ++i){
        cout << nfa.symbols[i] << "\t|";
    }

    for(int i = 0; i < nfa.allStates.size(); ++i){

        cout << endl << nfa.allStates[i] << "\t|";

        for(int j = 0; j < nfa.symbols.size(); ++j){
            for(int k = 0; k < nfa.transitions.size(); ++k){
                if(nfa.transitions[k].symbol == nfa.symbols[j]){
                    if(nfa.transitions[k].presentState == nfa.allStates[i]){
                        found = 1;
                        temp.push_back(nfa.transitions[k].nextState);
                    }
                }
                
            }
            if(!found){
                temp.push_back(" ");
            }

            temp2.insert(make_pair<string, vector<string> >(nfa.symbols[j], temp));
            found = 0;

            cout << "{";
            for(int r = 0; r < temp.size(); r++){
                cout << temp[r];
                if((r+1) != temp.size()){
                    cout << ", ";
                }
            }
            cout << "}\t|";

            temp.clear();
        }
        
        nfa.nfaTable.insert(make_pair<string, unordered_map<string, vector<string> > >(nfa.allStates[i], temp2));
        
        temp2.clear();
        
    }

    cout << endl;
    
}

void convertNFAtoDFA(nfa_t nfa){
    printDFA(nfa);

}

void printDFA(nfa_t nfa){
    cout << endl << "*********************************************************" << endl
    << "    NFA - to - DFA conversion complete! Results below    " << endl
    << "*********************************************************" << endl << endl;
    
    cout << "Initial state: " << endl;
    cout << "Final State(s): " << endl;

    cout << "\nDFA Transition Table:\n";
    cout << "State\t|";
    for(int i = 0; i < nfa.symbols.size()-1; ++i){
        cout << nfa.symbols[i] << "\t|";
    }

    cout << endl;
}