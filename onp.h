//
// Created by Mykyta Shemechko.
//

#ifndef onp_h
#define onp_h
#include <vector>
#include <string>
#include <stack>

typedef std::vector<std::string> VeSt;

typedef std::vector<double> VeDb;

typedef std::vector<char> VeCh;

typedef std::stack<char, VeCh> StaCh;

typedef std::stack<double,VeDb> StaDb;

extern std::string defaults[];

extern std::string help;

int p(char c);

bool is_an_operator(char character);

VeSt split(std::string input);

std::string calculate(std::string input);

std::string onp(std::string input);

VeSt process_arguments(int argc, const char **argv);

#endif //onp_h
