/* Mystery carpet
 * Programmer: Taisto Tammilehto
 * Name: Taisto Tammilehto
 * Student ID: tuni.fi:151238789
 * User: kmtata
 * E-Mail: taisto.tammilehto@tuni.fi
 * */

/* Mystery carpet
 * Programmer: Taisto Tammilehto
 * Name: Taisto Tammilehto
 * Student ID: tuni.fi:151238789
 * User: kmtata
 * E-Mail: taisto.tammilehto@tuni.fi
 * */

#include "carpet.hh"

// Mapping between color characters and their corresponding Color enum values
std::map<char, Color> color_map = {
    {'R', RED},
    {'G', GREEN},
    {'B', BLUE},
    {'Y', YELLOW},
    {'W', WHITE}};

// Prints the given carpet to the console
void print_carpet(Color carpet[], int width, int height)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            switch (carpet[i * width + j])
            {
            case RED:
                std::cout << " R";
                break;
            case GREEN:
                std::cout << " G";
                break;
            case BLUE:
                std::cout << " B";
                break;
            case YELLOW:
                std::cout << " Y";
                break;
            case WHITE:
                std::cout << " W";
                break;
            }
        }
        std::cout << std::endl;
    }
}

// Searches the given carpet for the given pattern, and prints the locations
// of all matches to the console

int correct_dimensions = 2;
int search_pattern(Color pattern[], Color carpet[], int width, int height)
{
    int matches = 0;
    // Loop through each 2x2 block of the carpet
    for (int i = 0; i <= height - correct_dimensions; i++)
    {
        for (int j = 0; j <= width - correct_dimensions; j++)
        {
            bool match = true;
            // Check if the pattern matches the current block
            for (int k = 0; k < correct_dimensions; k++)
            {
                for (int l = 0; l < correct_dimensions; l++)
                {
                    if (pattern[k * correct_dimensions + l] != carpet[(i + k) * width + j + l])
                    {
                        match = false;
                        break;
                    }
                }
                if (!match)
                    break;
            }
            // If a match is found, increment the matches counter
            if (match)
            {
                matches++;
                std::cout << " - Found at (" << j + 1 << ", " << i + 1 << ")\n";
            }
        }
    }
    return matches;
}
