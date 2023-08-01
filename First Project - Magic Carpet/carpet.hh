/* Mystery carpet
 * The purpose of this header file is to define
 * the interface for the Carpet class and to provide
 * any necessary includes or declarations.
 * Programmer: Taisto Tammilehto
 * Name: Taisto Tammilehto
 * Student ID: tuni.fi:151238789
 * User: kmtata
 * E-Mail: taisto.tammilehto@tuni.fi
 * */

#ifndef CARPET_HH
#define CARPET_HH

#include <iostream>
#include <string>
#include <map>
#include <cstdlib>
#include <ctime>

// Define an enumeration for the possible colors in a carpet.
enum Color
{
    RED,
    GREEN,
    BLUE,
    YELLOW,
    WHITE
};

// Declare a function for printing a carpet to the console.
void print_carpet(Color carpet[], int width, int height);

// Declare a function for searching for a pattern in a carpet.
int search_pattern(Color pattern[], Color carpet[], int width, int height);

// Declare an external map that maps characters to colors.
extern std::map<char, Color> color_map;

#endif // CARPET_HH
