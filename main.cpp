//
//  main.cpp
//  Semester
//
//  Created by Mykyta Shemechko.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <stack>
#include <cmath>
#include <cctype>

using namespace std;

string defaults[] = {"input.txt","onp_output.txt","calculated_output.txt"};
string input_filename = defaults[0];
string onp_output_filename = defaults[1];
string calculated_output_filename = defaults[2];
string help = "\n"
              "\nThis is a programme by Mykyta Shemechko"
              "\nIt converts expressions to ONP and calculates their results."
              "\nTo use this programme set an input using \"-i\" argument. "
              "\nYou can also set outputs (\"-o\" and \"-w\")."
              "\n\"-o\" is used to set an output for the converted expression."
              "\n\"-w\" is used to set an output for the calculated result."
              "\nDefault input filename is \"input.txt\""
              "\nDefault outputs are \"onp_output.txt\" and \"calculated_output.txt\" respectively."
              "\n";



int p(char c)
{
    switch (c)
    {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
    }
    return 0;
}


bool is_an_operator(char character) {
    switch (character) {
        case '*':
        case '/':
        case '+':
        case '-':
        case '^':
            return 1;
        default:
            return 0;
    }
}

vector<string> split(string input) {
    string temp = "";
    vector<string> output;
    for (int i = 0; i < input.size(); i++) {
        if (input[i] == ' ') {
            output.push_back(temp);
            temp = "";
        }
        else {
            temp += input[i];
        }
    }
    output.push_back(temp);
    return output;
}


string calculate(string input) {
    vector<string> expression = split(input);
    stack<double, vector<double>> stos;
    double a;
    double b;
    for (int i = 0; i < expression.size(); i++) {
        if (isdigit(expression[i][0])) {
            stos.push(stod(expression[i]));
        }
        else if (is_an_operator(expression[i][0])) {
            a = stos.top();
            stos.pop();
            b = stos.top();
            stos.pop();
            switch (expression[i][0]) {
                case '*':
                    stos.push(b * a);
                    break;
                case '/':
                    stos.push(b / a);
                    break;
                case '+':
                    stos.push(b + a);
                    break;
                case '-':
                    stos.push(b - a);
                    break;
                case '^':
                    stos.push(pow(b, a));
                    break;
            }

            //cout << endl << b << " " << expression[i] << " " << a << " = " << stos.top() << endl;
        }
    }


    string output_string;
    output_string = to_string(stos.top());
    for (int i = 0; i < 3; i++) { output_string.pop_back(); }
    return output_string;
}

string onp(string input) {
    stack<char, vector<char>> stos;
    vector<char> output;
    for (int i = 0; i < input.size(); i++) {
        if (isdigit(input[i])) {
            output.push_back(input[i]);
        }
        else if (is_an_operator(input[i])) {
            if (!stos.empty()) {
                while (!stos.empty()&&(!(p(stos.top()) == 3 || p(input[i]) > p(stos.top())))) {
                    output.push_back(' ');
                    output.push_back(stos.top());
                    stos.pop();
                }
            }
            stos.push(input[i]);
            output.push_back(' ');
        }
        else if (input[i] == '(') {
            stos.push(input[i]);
        }
        else if (input[i] == ')') {

            while (stos.top() != '(') {
                output.push_back(' ');
                output.push_back(stos.top());
                stos.pop();
            }
            stos.pop();
        }
    }
    while (!stos.empty()) {
        output.push_back(' ');
        output.push_back(stos.top());
        stos.pop();
    }
    string output_string(output.begin(), output.end());
    return output_string;
}

bool process_argument(string argument, string contents){
    if (argument[0] == '-'){
        switch (argument[1]) {
            case 'i':
                input_filename = contents;
                return false;
            case 'o':
                onp_output_filename = contents;
                return false;
            case 'w':
                calculated_output_filename = contents;
                return false;
        }
    }
    cout << "Error. Argument " << argument << " is wrong.";
    return true;
}

int main(int argc, const char* argv[]) {


    vector<string> converted_expressions;
    string inputLine;
    fstream input;
    fstream onp_output;
    fstream calculated_output;
    string expression, calculated_expression;




    switch (argc) {
        case 3:
            if (process_argument(argv[1], argv[2])) {
                return 2;
            }
            break;
        case 5:
            if (process_argument(argv[1], argv[2]) || process_argument(argv[3], argv[4])) {
                return 2;
            }
            break;
        case 7:
            if (process_argument(argv[1], argv[2]) || process_argument(argv[3], argv[4]) || process_argument(argv[5], argv[6])) {
                return 2;
            }
            break;
        default:
            cout << help;
            return 1;
    }

    input.open(input_filename);
    onp_output.open(onp_output_filename,ios::out|fstream::trunc);
    calculated_output.open(calculated_output_filename, ios::out|fstream::trunc);

    while (getline(input, inputLine)) {
        expression = onp(inputLine);
        converted_expressions.push_back(expression);
        onp_output << expression << endl;
    }
    for (int i = 0; i < converted_expressions.size(); i++) {
        calculated_expression = calculate(converted_expressions[i]);
        calculated_output << calculated_expression << endl;
    }

    input.close();
    onp_output.close();
    calculated_output.close();

    return 0;
}