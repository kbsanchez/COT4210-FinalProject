# Automata Theory and Formal Languages - Final Project
#### Contributors:
- Keylin Sanchez
- Chuong Le
- Glenn Bravo
- Moinul Islam Munna
##### Project description here.
## How to compile
     make main
## How to run
    ./main
## Running examples
    % make main
    c++	main.cpp	-o main
    Number of states: 2
    Initial state: q0
    Final state: q1
    Add another final state?
    Enter 1 for yes, 0 for no: 0
    Number of transitions: 4
    
    Enter each transition in the form of {present state} {symbol} {next state}
    (Epsilon transitions can be denoted by using the symbol E)
    
    Transition 1: q0 0 q1
    Transition 2: q0 1 q0
    Transition 3: q1 0 q1
    Transition 4: q1 1 q0
    
    **********************************************************
        NFA table construction complete! Results below      
    **********************************************************
    
    NFA Transition Table:
    State   |0      |1      |E      |
    q0      |{q1}   |{q0}   |{ }    |
    *q1     |{q1}   |{q0}   |{ }    |
    
    *********************************************************
        NFA - to - DFA conversion complete! Results below    
    *********************************************************
    
    Initial state: {q0}
    Final State(s): {{q1}}
    
    DFA Transition Table:
    State   |0      |1      |
    {q0}    |{q1}   |{q0}   |
    *{q1}	|{q1}	|{q0}   |
    %

    
