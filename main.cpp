// Shreya Gogini
// p5.cpp
// Description:main file that calls the methods, and runs the program

#include "queue.h"
#include "stack.h"
#include <iostream>

using namespace std;

// OpId is an enum (short for enumeration). Enums assign names
// to integer values, allowing us to map things to a set of
// integer identifiers
enum OpId {
    BAD  = 0, // Does not correspond to any operation
    ADD  = 1,
    SUB  = 2,
    MUL  = 3,
    DIV  = 4,
    TOP  = 5,
    POP  = 6,
    DUP  = 7,
    COND = 8,
    ENQ  = 9,
    DEQ  = 10,
    SAVE = 11,
    LOAD = 12,
    END  = 1024
};

// To represent the mapping between operations and their string
// representation, we will make this helper struct to act as an
// entry in our list of mappings
struct Operation {
    std::string name;
    OpId        id;
};

// The mapping of operation string representations to their
// integer id
Operation const OPERATIONS[] = {
    {"add", ADD},
    {"sub", SUB},
    {"mul", MUL},
    {"div", DIV},
    {"top", TOP},
    {"pop", POP},
    {"dup", DUP},
    {"cond", COND},
    {"enq", ENQ},
    {"deq", DEQ},
    {"save", SAVE},
    {"load", LOAD},
    {"end", END},
};

// The number of entries in the operation id mapping, calculated
// by taking the quotient of the total size of the mapping by
// the size of each entry.
int const OPERATION_COUNT = sizeof(OPERATIONS) / sizeof(Operation);

// desc : Maps token strings to ther corresponding operation IDs, if
//        possible.
// pre  : None
// post : If the input token corresponds to a valid string representation
//        for an operation, the corresponding OpId value is returned. If
//        no such matching exists, OpId::BAD is returned instead
OpId token_to_operation_id(string token) {
    for (int i = 0; i < OPERATION_COUNT; i++) {
        // Linear search through entries until a match is found...
        if (OPERATIONS[i].name == token) {
            return OPERATIONS[i].id;
        }
    }
    // ... or until we run out of entries
    return OpId::BAD;
}

// desc : Returns true if and only if the input string represents a non-empty
//        string consisting only of roman numerals.
// pre  : None
// post : None, aside from description
bool is_numeric(string token) {
    int size = token.size();
    // In the odd case we get an empty string, we count it as *not* an integer
    if (size == 0) {
        return false;
    }
    // Iterate through token, double-checking that the character values are only
    // in the valid range for digits
    for (int i = 0; i < size; i++) {
        if (token[i] < '0' || token[i] > '9') {
            return false;
        }
    }
    return true;
}

// desc : based on user input, token in analyzed and sent to the correct method
// pre  : called by main and the stack/queue exists, token is passed
// post : runs the command in the switch based on user input
void evaluate(Stack &active_stack, Queue &active_queue, string token) {
    if (is_numeric(token)) {
        // Convert the token to its integer value
        int value = stoi(token);
        active_stack.push(value);
    } else {
        // It is advised you use the provided OpId enumeration and id mapping
        // functions to switch between your function calls. Of course, not all
        // operations must be handled here, since the end/save/load operations
        // have special requirements that are easier to meet in the main
        // function
        switch (token_to_operation_id(token)) {
        case OpId::ADD:
            active_stack.add();
            break;
        case OpId::SUB:
            active_stack.sub();
            break;
        case OpId::MUL:
            active_stack.mul();
            break;
        case OpId::DIV:
            active_stack.div();
            break;
        case OpId::TOP:
            active_stack.top_output();
            break;
        case OpId::POP:
            active_stack.pop();
            break;
        case OpId::DUP:
            active_stack.dup();
            break;
        case OpId::COND:
            active_stack.cond();
            break;
        case OpId::ENQ:
            active_queue.enqueue(active_stack.pop());
            break;
        case OpId::DEQ:
            active_stack.push(active_queue.dequeue());
            break;
        case OpId::LOAD:
        case OpId::SAVE:
        case OpId::END:
            break;
        // The case below should happen if an invalid id (like OpId::BAD) is
        // yielded by the id mapping function
        case OpId::BAD:
        default:
            cout << "Unrecognized token '" << token << "'\n";
        }
    }
}

// desc : main function to create the objects and run the program
// pre  : classes are initialized
// post : all memory is deallocated once program ends
int main() {
    Stack active_stack;
    Queue active_queue;
    Stack save_stack;
    Queue save_queue;
   
    // we may want to put something additional here to allow
    // us to save and load the active stack and queue.
    string token;
    bool done = false;
    while ((!done) && (cin >> token)) {
        if (token == "end") {
            // To get the automatic memory cleanup from the Stack/Queue
            // destructors, we must terminate by returning normally from main
            done = true;
        } else if (token == "save") {
            save_stack = active_stack;
            save_queue = active_queue;
           
        } else if (token == "load") {
            active_stack = save_stack;
            active_queue = save_queue;
           
        } else {
            // to prevent main from becoming too large/complex, we delegate the
            // evaluation of "non-special" operations to a separate function
            try{
            evaluate(active_stack, active_queue, token);
            }
            catch (const runtime_error& e){
                cerr << "Runtime error occured: " << e.what() << endl;
            }
        }
        /*
        //if you want to see the progression of the stacks and queues through the
        //program, this prints the table
        cout << "\n Active Stack: {";
        active_stack.display();
        cout << "}";
        cout << "\n Save Stack: {";
        save_stack.display(); 
        cout << "}";
        cout << "\n Active Queue: {";
        active_queue.display();
        cout << "}";
        cout << "\n Save Queue: {";
        save_queue.display();
        cout << "}";
        cout << endl;*/
    }
}
 
