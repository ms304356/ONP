#include <vector>
#include <string>
#include <cmath>
#include <cctype>
#include "onp.h"

std::string defaults[] = {"input.txt","onp_output.txt","calculated_output.txt"};

std::string help = "\n"
                   "\nProgram napisał Mykyta Shemechko."
                   "\nTen program konwertuje dowolne wyrażenia arytmetyczne do wyrażenia w ONP i oblicza wartość końcową."
                   "\nWejście ustawia się argumentem \"-i\". "
                   "\nWyjścia ustawia się argumentami \"-o\" i \"-w\"."
                   "\n\"-o\" ustawia plik wyjściowy dla skonwertowanego wyrażenia."
                   "\n\"-w\" ustawia plik wyjściowy dla wartości końcowej."
                   "\nDomyślny plik wejściowy to \"input.txt\"."
                   "\nDomyślne pliki wyjjściowe to \"onp_output.txt\" i \"calculated_output.txt\""
                   "\n";

int p(char o)
{
    switch (o)
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
    VeSt expression = split(input); // Wyrażenie rozdielone na wektor stringów
    StaDb stos; // Stos obliczeniowy
    double a, b; // Zmienne dla obliczenia
    for (int i = 0; i < expression.size(); i++) {
        if (isdigit(expression[i][0])) {
            stos.push(stod(expression[i]));
        } // Jeśli liczba, daj na stos
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
        } // Jeśli operator, wykonać działanie na dwoch ostatnich liczbach ze stosu
    }


    std::string output_string; // String wyjściowy
    output_string = std::to_string(stos.top());
    for (int i = 0; i < 3; i++) { output_string.pop_back(); } // Usuń 3 ostatnie miejsca po przecinku
    return output_string;
}

std::string onp(std::string input) {
    StaCh stos; // Stos dla operatorów
    VeCh output; // Wyjście
    for (int i = 0; i < input.size(); i++) {
        if (isdigit(input[i])) {
            output.push_back(input[i]);
        } // Jeśli liczba, daj na wyjście
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
        } // Jeśli operator, daj na stos, uwzględnij priorytety
        else if (input[i] == '(') {
            stos.push(input[i]);
        } // Jeśli nawias otwarty, daj na stos
        else if (input[i] == ')') {

            while (stos.top() != '(') {
                output.push_back(' ');
                output.push_back(stos.top());
                stos.pop();
            }
            stos.pop(); // Usuń nawias zamknięty
        } // Jeśli nawias zamknięty, daj wszystkie operatory do nawiasu zamkniętego na wyjście
    }
    while (!stos.empty()) {
        output.push_back(' ');
        output.push_back(stos.top());
        stos.pop();
    } // Jeśli na końcu na stosie zostały jakieś operatory, wypisz na wyjście
    std::string output_string(output.begin(), output.end()); // Zrób stringa z wektora stringów
    return output_string;
}


VeSt process_arguments(int argc, const char **argv){
    VeSt output = {"","","",""}; // Wyjście ma 4 elementy: 3 argumenty i element doddatkowy
    for (int i = 1; i < argc; i++){
        if(argv[i][0]=='-') {
            if (argv[i][1] == 'i') output[0] = argv[i + 1];
            else if (argv[i][1] == 'o') output[1] = argv[i + 1];
            else if (argv[i][1] == 'w') output[2] = argv[i + 1];
            else {output[3] = "error"; return output;} // Jeśli argument jest nieznany, wyświetl błąd
        }
    }
    if (output[0] == "" && output[1] == "" && output[2] == ""){
        output[3] = "help";
    } // Jeśli argumentów nie ma, wyświetl instrukcję do programu.
    return output;
}