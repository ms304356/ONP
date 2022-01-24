/** @file */
#ifndef onp_h
#define onp_h
#include <vector>
#include <string>
#include <stack>

/** Wektor zmiennych typu string */
typedef std::vector<std::string> VeSt;

/** Wektor zmiennych typu double */
typedef std::vector<double> VeDb;

/** Wektor zmiennych typu char */
typedef std::vector<char> VeCh;

/** Stos zmiennych typu char */
typedef std::stack<char, VeCh> StaCh;

/** Stos zmiennych typu double */
typedef std::stack<double,VeDb> StaDb;

/** Zmienna, zawierająca domyślne nazwy plików wejścia/wyjścia */
extern const std::string defaults[];

/** Zmienna, zawierająca krótką informację o tym, jak użyć programu */
extern const std::string help;

/**
 * Funkcja, zwracająca priorytet operatoru.
 * @param o Operator
 * @return Priorytet operatoru
 */
int p(char o);

/**
 * Funcja, zwracjąca czy podany symbol jest operatorem
 * @param character Sprawdzany symbol
 * @return True, jeśli symbol jest operatorem, False, jeśli nie jest
 */
bool is_an_operator(char character);

/**
 * Funkcja, rozdzielająca string na wektor stringów (używając spacje)
 * @param input Rozdzielany string
 * @return Wektor stringów
 */
VeSt split(std::string input);

/**
 * Funkcja,  która oblicza wartość końcową wyrażenia w postaci ONP
 * @param input Wyrażenie w postaći ONP
 * @return Wynik końcowy wyrażenia
 */
std::string calculate(std::string input);

/**
 * Funkcja, przerabiająca wyrażenie w postaci normalnej na wyrażenie w postaci ONP
 * @param input Wyrażenie
 * @return Wyrażenie w postaci ONP
 */
std::string onp(std::string input);

/**
 * Funkcja, obrabiająca argumenty wejściowe programu
 * @param argc Ilość argumentów + 1
 * @param argv wskaźnik na tablicę argumentów
 * @return Wektor, zawierający wartości 3 argumentów + element dodatkowy ("help" lub "error")
 */
VeSt process_arguments(int argc, const char **argv);

#endif
