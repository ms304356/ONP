//
//  main.cpp
//  ONP
//
//  Mykyta Shemechko
//

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "onp.h"

int main(int argc, const char* argv[]) {
    VeSt converted_expressions;
    std::fstream input, onp_output, calculated_output;
    std::string inputLine;
    VeSt arguments = process_arguments(argc,argv);
    if (arguments[3] == "error") {std::cout<<std::endl<<"Użyto nieznanego argumentu."<<help;return 2;}
    else if (arguments[3] == "help"){std::cout<<help; return 1;}
    input.open(arguments[0] == "" ? defaults[0] : arguments[0] );
    onp_output.open(arguments[1]=="" ? defaults[1] : arguments[1],std::ios::out|std::fstream::trunc);
    calculated_output.open(arguments[2]=="" ? defaults[2] : arguments[2], std::ios::out|std::fstream::trunc);

    while (getline(input, inputLine)) {
        converted_expressions.push_back(onp(inputLine));
        onp_output << converted_expressions[converted_expressions.size()-1] << std::endl;
        calculated_output << calculate(converted_expressions[converted_expressions.size()-1]) << std::endl;
    }

    input.close();
    onp_output.close();
    calculated_output.close();

    return 0;
}