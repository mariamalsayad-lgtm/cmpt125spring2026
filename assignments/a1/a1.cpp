// a1.cpp

/////////////////////////////////////////////////////////////////////////
//
// Student Info
// ------------
//
// Name         : <Mariam Alsayad>
// Student ID # : <301642886>
// SFU Email    : <maa298@sfu.ca>
// Platform     : <MacOS>
// Editor/IDE   : <vs code>
// Known Bugs   : <describe any bugs or issues you're aware of>
// Missing      : <describe any missing features you're aware of>
// Challenges   : <describe any challenges you faced>
// Help         : <what people and AI tools helped you? If you used AI, please cite the source.>
//
// Statement of Originality
// ------------------------
//
// All the code and comments below are my own original work. For any non-
// original work, I have provided citations above and in the comments with
// enough detail so that someone can see the exact source and extent of the
// borrowed work.
//
// In addition, I have not shared this work with anyone else, and I have not
// seen solutions from other students, tutors, websites, books, etc.
//
/////////////////////////////////////////////////////////////////////////

// ... write your code here ...
#include <iostream>
#include <stack>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

bool isOperator(string& input);
void preformOp(string& input, stack<double>& calc);
void preformunaryOp(string& input, stack<double>& calc);
bool unaryOp(string& input);
void preformCommand(string& line, stack<double>& calc);
bool command(string& line);

int main() {

stack <double> calc;

cout << "RPN Calculator (type 'h' for help, 'q' to quit) \n";

while(true){
    //getting input
    
    cout << ">> ";
    string line;
    getline(cin, line);

    // take the line and split words seperated by spaces by "" 
    // Help from Stack Overflow: explanation of how stringstream works in C++
    // URL: https://stackoverflow.com/questions/20594520/what-exactly-does-stringstream-do
   stringstream ss(line);

    // read one token at a time from the string stream and store it in 'line'
    // Help from Stack Overflow: how to loop through characters in an input stream
    // URL: https://stackoverflow.com/questions/36654327/how-to-loop-through-characters-in-stream-c
    while(ss >> line){
    
      try{
        double num;
         //check for numeric value
        
        if(stringstream(line) >> num){
         calc.push(num);
        }   
        // check for operator
        else if(isOperator(line)){
            preformOp(line, calc);
            cout << "Result: " << calc.top() << "\n";
        }
        else if(unaryOp(line)){
            preformunaryOp(line, calc);
            cout << "Result: " << calc.top() << "\n";
        }
        else if (command(line)) {
            preformCommand(line, calc);
            if (!calc.empty()) {
            cout << "Result: " << calc.top() << "\n";
        }
    }
}

catch(string& msg){
    cout << msg << '\n';
}
    
}
}
}


bool isOperator(string& input) {
    // create a list of operators
    vector<string> ops = {"-", "+", "*", "/"};
    for(int i = 0; i <4; i++ ){
        if(input == ops[i]) { 
            return true; }
    }
    return false;
}

void preformOp(string& input, stack<double>& calc){
    double lhs, rhs, result;

    if(calc.size() < 2){
        throw string("error: can't pop from an empty stack");
    }
     
    rhs = calc.top();
    calc.pop();
    lhs = calc.top();
    calc.pop();
    
    if (input == "-"){
        result = lhs - rhs;
    }
    else if (input == "+"){
        result = lhs + rhs;
    }
    else if (input == "/"){
        if (rhs == 0){
            cout << "Error: Division by zero. \n";
            calc.push(lhs);
            calc.push(rhs);
            return;
        }
        else{
            result = lhs/rhs;
        }
        
    }
    else if(input == "*"){
        result = lhs * rhs;
    }
    calc.push(result);
  
}



bool unaryOp(string& input) {
    if (input == "abs" || input == "sin" || input == "cos" || input == "sqrt" || 
    input == "dup" || input == "drop") {
       return true;
    }
    return false;
}

void preformunaryOp(string& input, stack<double>& calc){
    if (calc.empty()) {
        throw string ("Error: can't pop from empty stack");
    }
    else if (input == "abs"){
        double x = calc.top();
        if (x < 0) {;
        calc.pop();
        calc.push(x * -1);
        }
    }
    else if (input == "sin"){
        double x = calc.top();
        calc.pop();
        calc.push(sin(x));
    }
    else if (input == "cos") {
       double x = calc.top();
        calc.pop();
        calc.push(cos(x));
    }
    else if (input == "sqrt") {
       double x = calc.top();
       if (x < 0){
        cout << "error: can take a sqrt of a negative number";
       }
        calc.pop();
        calc.push(sqrt(x));
    }
    else if (input == "dup") {
    double x = calc.top();
        calc.push(x);
    }
    else if (input == "drop") {
        calc.pop();
    }
}

bool command(string& line) {
    if (line == "clear" || line == "print" || line == "help" || line == "quit" 
    || line == "c" || line == "p" || line == "h" || line == "?" || line =="q"){
        return true;
    }
    return false;
}

void preformCommand(string& line, stack<double>& calc){
    if (line == "clear" || line =="c") {
        while(!calc.empty()){
        calc.pop();
        }
    }
    else if (line == "print" || line == "p") {
        while(!calc.empty()){
            double x = calc.top();
            cout << x << "\n";
            calc.pop();
        }
    }
    else if( line == "help" || line == "h" || line == "?") {
        cout << "This is a postfix calculator: operators appear after their operands.e.g. 2 3 * + 1 evaluates to 7, the same as 1 + 2 * 3.\n";
    }
    else if (line == "quit" || line == "q") {
        cout << "Exiting the calculator. Goodbye! \n";
        exit(0);
    }
}

