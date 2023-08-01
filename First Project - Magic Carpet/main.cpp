/* Mystery carpet
 *
 * Tämä ohjelma tulostaa mysteerimaton käyttäjän
 * määräämillä tai satunnaisilla väreillä. Lisäksi
 * käyttäjä voi etsiä matosta 2x2 kuvioita ja
 * ohjelma tulostaa kuvioiden sijainnin matolla.
 *
 * Programmer: Taisto Tammilehto
 * Name: Taisto Tammilehto
 * Student ID: tuni.fi:151238789
 * User: kmtata
 * E-Mail: taisto.tammilehto@tuni.fi

 * */

#include "carpet.hh"
#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>
#include <map>
#include <random>
#include <ctime>

// Function to initialize the carpet randomly
void initializeRandomCarpet(Color *carpet, int width, int height, int seed)
{
    std::default_random_engine rand_gen(seed);
    std::uniform_int_distribution<int> distribution(0, 4);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            carpet[i * width + j] = static_cast<Color>(distribution(rand_gen));
        }
    }
}

// Function to initialize the carpet from user input
bool initializeInputCarpet(Color *carpet, int width, int height)
{
    std::string input;
    std::cout << "Input: ";
    std::cin >> input;

    // Check if the input length matches the carpet size
    if (input.length() != static_cast<std::string::size_type>(width * height))
    {
        std::cout << "Error: Wrong amount of colors." << std::endl;
        return false;
    }

    // Convert the input to uppercase
    std::transform(input.begin(), input.end(), input.begin(), ::toupper);

    // Map input colors to carpet colors
    for (std::string::size_type i = 0; i < input.length(); i++)
    {
        // Check if the input color is valid
        if (color_map.find(input[i]) == color_map.end())
        {
            std::cout << "Error: Unknown color." << std::endl;
            return false;
        }
        else
        {
            carpet[i] = color_map[input[i]];
        }
    }

    return true;
}

int main()
{
    // Get the dimensions of the carpet from the user
    int width, height;
    std::cout << "Enter carpet's width and height: ";
    std::cin >> width >> height;

    // Check if the carpet is too small for the pattern
    int maximum_dimensions = 2;
    if (width < maximum_dimensions || height < maximum_dimensions)
    {
        std::cout << "Error: Carpet cannot be smaller than pattern." << std::endl;
        return EXIT_FAILURE;
    }

    // Get input from the user to select how to initialize the carpet
    char carpet_input;
    do
    {
        std::cout << "Select start (R for random, I for input): ";
        std::cin >> carpet_input;
    } while (carpet_input != 'R' && carpet_input != 'I' && carpet_input != 'r' && carpet_input != 'i');

    // Create an array to store the colors of the carpet
    Color carpet[width * height];

    // Randomly initialize the carpet
    if (carpet_input == 'R' || carpet_input == 'r')
    {
        // Prompt the user for a seed value in the range 1-20
        int seed;
        do
        {
            std::cout << "Enter seed value (1-20): ";
            std::cin >> seed;
            if (seed < 1 || seed > 20)
            {
                std::cout << "Error: Wrong seed value." << std::endl;
            }
        } while (seed < 1 || seed > 20);

        // Randomly initialize the carpet using the provided seed
        initializeRandomCarpet(carpet, width, height, seed);
    }
    else
    {
        // Read the carpet from user input
        bool input_success = initializeInputCarpet(carpet, width, height);
        if (!input_success)
        {
            // If there was an error in the input, initialize the carpet randomly
            int seed = std::time(nullptr);
            initializeRandomCarpet(carpet, width, height, seed);
        }
    }

    // Print the carpet to the console
    print_carpet(carpet, width, height);

    while (true)
    {
        // Get the pattern to search for from the user
        char pattern_input[5];
        std::cout << "Enter 4 colors, or q to quit: ";
        std::cin >> pattern_input;

        // Check for invalid input
        if (std::cin.fail())
        {
            std::cout << "Error: Invalid input." << std::endl;
            continue;
        }

        // Exit the loop if the user enters 'q'
        if (pattern_input[0] == 'q')
        {
            break;
        }

        const unsigned long int correct_amount_of_colors = 4;
        Color pattern[correct_amount_of_colors];

        // Check if the user entered the correct amount of colors
        if (std::strlen(pattern_input) != correct_amount_of_colors)
        {
            std::cout << "Error: Wrong amount of colors." << std::endl;
            continue;
        }

        // Map input colors to pattern colors
        bool has_error = false;
        for (unsigned long int i = 0; i < correct_amount_of_colors; i++)
        {
            char c = std::toupper(pattern_input[i]);

            // Check if the input color is valid
            if (color_map.find(c) == color_map.end())
            {
                std::cout << "Error: Unknown color." << std::endl;
                has_error = true;
                break;
            }
            else
            {
                pattern[i] = color_map[c];
            }
        }

        // Continue to the next iteration of the loop if there was an error
        if (has_error)
        {
            continue;
        }

        // Search for the pattern in the carpet and print the results
        int matches = search_pattern(pattern, carpet, width, height);

        // If there are more than zero matches, print the corresponding message
        if (matches > 0)
        {
            std::cout << " = Matches found: " << matches << std::endl;
        }
        else
        {
            // There are no matches if the if-statement above isn't fulfilled
            std::cout << " = Matches found: 0" << std::endl;
        }
    }

    return EXIT_SUCCESS;
}
