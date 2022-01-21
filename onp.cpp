//
// Created by Mykyta Shemechko.
//
#include <vector>
#include <string>
#include <cmath>
#include <cctype>
#include "onp.h"

std::string defaults[] = {"input.txt","onp_output.txt","calculated_output.txt"};

std::string help = "\n"
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

VeSt split(std::string input) {
    std::string temp = "";
    VeSt output;
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


std::string calculate(std::string input) {
    VeSt expression = split(input);
    StaDb stos;
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
        }
    }


    std::string output_string;
    output_string = std::to_string(stos.top());
    for (int i = 0; i < 3; i++) { output_string.pop_back(); }
    return output_string;
}

std::string onp(std::string input) {
    StaCh stos;
    VeCh output;
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
    std::string output_string(output.begin(), output.end());
    return output_string;
}


VeSt process_arguments(int argc, const char **argv){
    VeSt output = {"","","",""};
    for (int i = 1; i < argc; i++){
        if(argv[i][0]=='-') {
            if (argv[i][1] == 'i') output[0] = argv[i + 1];
            else if (argv[i][1] == 'o') output[1] = argv[i + 1];
            else if (argv[i][1] == 'w') output[2] = argv[i + 1];
        }
    }
    if (output[0] == "" && output[1] == "" && output[2] == ""){
        output[3] = "help";
    }
    return output;
}