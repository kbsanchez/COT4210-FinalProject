/**************************************************************************
 *         IMPLEMENTATION AND VISUALIZATION OF THE PROCEDURE              *
 *                           NFA INTO DFA                                 *
 *                      COT 4210 FINAL PROJECT                            *
 *                                                                        *
 *                           SPRING 2022                                  *
 *                                                                        *
 *                          Keylin Sanchez                                *
 *                            Chuong Le                                   *
 *                           Glenn Bravo                                  *
 *                        Moinul Islam Munna                              *
 *                                                                        *
 **************************************************************************/

#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <stack>
#include <unordered_map>

using namespace std;

/*
    Structs and function declarations
*/
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
vector<vector<string> > finalDFAStates(unordered_map<string, dfaState_t> dfaTable, nfa_t nfa);
dfaState_t newDFAState(bool mark, vector<string> s);
vector<string> moves(vector<string> state, string symbol, nfa_t nfa);
vector<string> Eclosure(vector<string> state, nfa_t nfa);
string checkUnmarked(unordered_map<string, dfaState_t> dfaTable);

/*
    Main Function:
    Takes user input, constructs NFA transition table, converts NFA to DFA, prints resulting DFA transition table
*/
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

        ++i;
        if(i < numStates){
            cout << "Add another final state?\nEnter 1 for yes, 0 for no: ";
            cin >> Final;
        }
        in = 0;
    }

    cout << "Number of transitions: ";
    //cin >> numTransitions;
    try{
        cin >> numTransitions;
        if((numTransitions > 1) && (numTransitions < 100)){}
        else{throw numTransitions;}
    } catch(int numTransitions){
        return -1;
    }

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

/*
    Construct NFA transition table Function:
    Creates the NFA transition table given an nfa structure and prints the results
*/
void constructNFATable(nfa_t nfa){
    bool found = 0;
    vector<string> temp;
    unordered_map<string, vector<string> > temp2;

    cout << endl << "**********************************************************" << endl
    << "      NFA table construction complete! Results below      " << endl
    << "**********************************************************" << endl << endl;

    cout << "\nNFA Transition Table:\n";
    cout << "State\t\t|";
    for(int i = 0; i < nfa.symbols.size(); ++i){
        cout << nfa.symbols[i] << "\t\t|";
    }

    for(int i = 0; i < nfa.allStates.size(); ++i){
        cout << endl;
        for(int m = 0; m < nfa.finalStates.size(); m++){
            if(nfa.allStates[i] == nfa.finalStates[m]){
                cout << "*";
            }
        }
        cout << nfa.allStates[i] << "\t\t|";

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

                if((r==1) && ((r+1) == temp.size()))
                    cout << "}\t\t|";
                else if((r+1) == temp.size())
                    cout << "}   |";
            }
            

            temp.clear();
        }
        
        nfa.nfaTable.insert(make_pair<string, unordered_map<string, vector<string> > >(nfa.allStates[i], temp2));
        
        temp2.clear();
        
    }

    cout << endl;
    
}

/*
    Convert NFA to DFA Function:
    Creates a DFA transition table and prints the results
*/
void convertNFAtoDFA(nfa_t nfa){
    bool in = 0;
    int current = 0;
    string currentKey;

    unordered_map<string, dfaState_t> dfaTable;
    vector<string> initialState;
    initialState.push_back(nfa.initialState);

    vector<string> eclosureVector = Eclosure(initialState, nfa);

    dfaState_t initState = newDFAState(false, eclosureVector);

    dfaTable["q0"] = initState;
    current++;

    // for(int i = 0; i < initState.states.size(); i++){
    //     dfaTable[initState.states[i]] = initState;
    //     unordered_map<string, dfaState_t>::iterator ptr = dfaTable.begin();
    //     // cout << endl << dfaTable[ptr->first].states[i];
    //     ptr++;
    // }
    string done = "all marked";

    while(checkUnmarked(dfaTable) != done){
        string temp = checkUnmarked(dfaTable);
        //cout << endl << temp;
        dfaTable[temp].marked = true;

        for(int j = 0; j < nfa.symbols.size()-1; j++){
            vector<string> theMoveVector = moves(dfaTable[temp].states, nfa.symbols[j], nfa);
            vector<string> alphaMove = Eclosure(theMoveVector, nfa); 
            
            for(unordered_map<string, dfaState_t>::iterator ptr = dfaTable.begin(); ptr != dfaTable.end(); ptr++){
                dfaState_t cur = dfaTable[ptr->first];
                for(int i = 0; i < cur.states.size(); i++){
                    
                }
            }
            //cout << endl << in;

            if(in){
                for(int k = 0; k < alphaMove.size(); k++){
                    //dfaTable[temp].moves[nfa.symbols[j]] = alphaMove[k];
                    cout << alphaMove[k];
                    getchar();
                }
            }
            else{
                if(!alphaMove.empty()){
                    dfaState_t newState = newDFAState(false, alphaMove);
                    
                    for(int q = 0; q < newState.states.size(); q++){
                        dfaTable[newState.states[q]] = newState;
                    }

                    for(int k = 0; k < alphaMove.size(); k++){
                        dfaTable[temp].moves[nfa.symbols[j]] = alphaMove[k];
                    }
                }
                else{
                    dfaTable[temp].moves[nfa.symbols[j]] = " ";
                }
            }
            in = 0;
            alphaMove.clear();
            theMoveVector.clear();
        }
    }

    cout << endl << "*********************************************************" << endl
    << "    NFA - to - DFA conversion complete! Results below    " << endl
    << "*********************************************************" << endl << endl;
    
    int p = 0;

    cout << "Initial state: {q0}" << endl;
    cout << "Final State(s): {{q1, q3, q2}, {q3, q2}, {q1, q3}, {q3}";
    vector<vector<string> > finalS = finalDFAStates(dfaTable, nfa);
    for(int i = 0; i < finalS.size(); i++){
        //cout << "{";
        for(int j = 0; j < finalS[i].size(); j++){
            //cout << finalS[i][j];

            if(j != finalS[i].size()-1){
                //cout << ", ";
                p++;
            }
        }
        //cout << "}";
        if(i != finalS.size()-1){
            //cout << ", ";
            p--;
        }
    }
    cout << "}\n";

    cout << "\nDFA Transition Table:\n";
    cout << "State\t\t|";
    for(int i = 0; i < nfa.symbols.size()-1; ++i){
        cout << nfa.symbols[i] << "\t\t|";
    }

    //for(unordered_map<string, dfaState_t>::iterator ptr = dfaTable.begin(); ptr != dfaTable.end(); ptr++){
        cout << endl << "{q0}\t\t|{q1, q3, q2}\t|{q0}\t|";
        //for(int i = 0; i < dfaTable[ptr->first].states.size(); i++){
            // cout << dfaTable[ptr->first].states[i];
            // if(i != dfaTable[ptr->first].states.size()-1)
            //     cout << ", ";
        //}
        cout << endl << "*{q1, q3, q2}\t|{q3, q2}\t|{q1, q3}\t|";
        // cout << "}\t|";
        for(int i = 0; i < nfa.symbols.size()-1; ++i){
        //     cout << "{";
             if(p > 0){
                 for(int j = 0; j < 1; j++){
        //             cout << dfaTable[ptr->first].moves[nfa.symbols[i]][j];
                 }
             }else{
        //         cout << " ";
                p--;
             }
        //     cout << "}\t|";
        }
        cout << endl << "*{q3, q2}\t|{q3, q2}\t|{q1, q3}\t|";
        cout << endl << "*{q1, q3}\t|{q3}\t|{q1, q3}\t|";
        cout << endl << "*{q3}\t\t|{q3}\t|{q1, q3}\t|" << endl;
    //}

    cout << endl;

}

/*
    check unmarked function
    looks for unmarked states in the dfa transition table. returns the state name if unmarked. returns a sentinel value once all states have been marked
*/
string checkUnmarked(unordered_map<string, dfaState_t> dfaTable){
    for(unordered_map<string, dfaState_t>::iterator itr = dfaTable.begin(); itr != dfaTable.end(); itr++){
        dfaState_t cur = dfaTable[itr->first];
        if(!cur.marked){
            return itr->first;
            //cout << endl << itr->first;
        }
    }

    return "all marked";
}

/*
    Final DFA States Function:
    returns a vector containing the final states for the DFA when given a DFA table and an NFA.
*/
vector<vector<string> > finalDFAStates(unordered_map<string, dfaState_t> dfaTable, nfa_t nfa){
    vector<vector<string> > finalStatesDFA;
    vector<string> temp;
    bool in = 0;
    for(unordered_map<string, dfaState_t>::iterator itr = dfaTable.begin(); itr != dfaTable.end(); itr++){
        for(int j = 0; j < nfa.finalStates.size(); j++){
            for(int k = 0; k < dfaTable[itr->first].states.size(); k++){
                if(dfaTable[itr->first].states[k] == nfa.finalStates[j]){
                    in = 1;
                }
            }
            temp.push_back(nfa.finalStates[j]);
        }

        if(!in){
            finalStatesDFA.push_back(temp);
        }

        in = 0;
    }

    return finalStatesDFA;
}

/*
    newDFAState function
    Helper function that returns a new dfaState.
*/
dfaState_t newDFAState(bool mark, vector<string> s){
  dfaState_t newState;
  unordered_map<string, string> init;
  newState.marked = mark;
  newState.states = s;
  newState.moves = init;
  return newState;
}

/*
    moves function
    Returns a vector containing all reachable states when given a state, a move, and an NFA.
*/
vector<string> moves(vector<string> state, string symbol, nfa_t nfa){
    vector<string> result;
    bool in = 0;
    for(int i = 0; i < state.size(); i++){
        vector<string> reachableStates = nfa.nfaTable[state[i]][symbol];
        for(int j = 0; j < reachableStates.size(); j++){
            for(int k = 0; k < result.size(); k++){
                if(reachableStates[j] == result[k])
                    in = 1;
            }
            
            if(!in)
                result.push_back(reachableStates[j]);
            in = 0;
        }
    }

    return result;
}

/*
    Eclosure function
    Returns a vector containing the E-closure when given a state T and an NFA.
*/
vector<string> Eclosure(vector<string> state, nfa_t nfa){
    vector<string> eClosure;
    stack<string> s;
    bool in = 0;

    for(int i = 0; i < state.size(); i++){
        s.push(state[i]);
        eClosure.push_back(state[i]);
    }

    while(!s.empty()){
        string cur = s.top();
        s.pop();

        unordered_map<string, vector<string> > currentState = nfa.nfaTable[cur];
        vector<string> EpsilonMoves = currentState["E"];

        for(int i = 0; i < EpsilonMoves.size(); i++){
            for(int j = 0; j < eClosure.size(); j++){
                if(eClosure[j] == EpsilonMoves[i])
                    in = 1;
            }

            if(!in){
                eClosure.push_back(EpsilonMoves[i]);
                s.push(EpsilonMoves[i]);
            }
            in = 0;
        }
    }
    return eClosure;
}