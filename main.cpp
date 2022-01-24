/** @file */
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "onp.h"

int main(int argc, const char* argv[]) {
    VeSt converted_expressions; // Tu będą wszystkie zkonwertowane wyrażenia
    std::fstream input, onp_output, calculated_output; // Zmienne plików wejścia/wyjścia
    VeSt arguments = process_arguments(argc,argv); // Obróbka argumentów
    if (arguments[3] == "error") {std::cout<<std::endl<<"Użyto nieznanego argumentu."<<help;return 2;} // Użyto nieznanego argumentu
    else if (arguments[3] == "help"){std::cout<<help; return 1;} // Nie znaleziono argumentów, wyświetlenie instrukcji

    // Otwarcie plików wejścia/wyjścia
    input.open(arguments[0] == "" ? defaults[0] : arguments[0] );
    if (!input.is_open()) {std::cout<<std::endl<<"Taki plik wejściowy nie istnieje."<<help; return 2;} // Plik nie został poprawnie otwarty
    // Używany jest fstream::trunc, żeby wyczyścić plik, jeśli już istnieje
    onp_output.open(arguments[1]=="" ? defaults[1] : arguments[1],std::ios::out|std::fstream::trunc);
    calculated_output.open(arguments[2]=="" ? defaults[2] : arguments[2], std::ios::out|std::fstream::trunc);

    std::string inputLine; // Zmienna dla odczytanej linii
    while (getline(input, inputLine)) {
        converted_expressions.push_back(onp(inputLine)); // Odczytywanie linii z wejścia
        onp_output << converted_expressions[converted_expressions.size()-1] << std::endl; // Zapis wyrażenia w ONP do wyjścia
        calculated_output << calculate(converted_expressions[converted_expressions.size()-1]) << std::endl; // Zapis wyniku końcowego do wyjścia
    }

    // Zamknięcie plików wejścia/wyjśćia
    input.close();
    onp_output.close();
    calculated_output.close();

    return 0; // Program wykonał się bezbłędnie
}