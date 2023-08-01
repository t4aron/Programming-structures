/*
 * Library Management System
 * Date: March 15, 2023
 *
 * This program reads library data from a file
 * and allows users to interact with the data
 * using various commands, such as listing libraries,
 * displaying library material,listing books by author,
 * and checking for reservable and loanable books.
 * This program was created in Microsoft Visual Studio, which allows
 * the code to be formatted into a more aesthetic look automatically. The IDE
 * choice also allowed me to insert a CSV file to easily test the program.
 *
 * Name: Taisto Tammilehto
 * Student ID: tuni.fi:151238789
 * User: kmtata
 * E-Mail: taisto.tammilehto@tuni.fi
 *
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iterator>
#include <map>
#include <set>
#include <limits>

using namespace std;

struct Book
{
    string author;
    string title;
    int reservations = 0;
};

void print_libraries(const map<string, map<string, vector<Book>>> &libraries)
{
    /*
     * Function: print_libraries
     * Parameters: const map<string, map<string, vector<Book>>>& libraries
     * Purpose: Prints the names of all libraries in the given data structure.
     */
    for (const auto &library : libraries)
    {
        cout << library.first << endl;
    }
}

void print_material(const string &library_name, const map<string,
                                                          map<string, vector<Book>>> &libraries)
{
    /*
     * Function: print_material
     * Parameters: const string& library_name, const map<string,
     * map<string, vector<Book>>>& libraries
     * Purpose: Prints all books of given library and an error
     * message if library is unknown.
     */
    auto library_iter = libraries.find(library_name);

    if (library_iter != libraries.end())
    {
        for (const auto &author : library_iter->second)
        {
            for (const auto &book : author.second)
            {
                cout << author.first << ": " << book.title << endl;
            }
        }
    }
    else
    {
        cout << "Error: unknown library" << endl;
    }
}

void print_books(const string &library_name, const string &author, const map<string, map<string, vector<Book>>> &libraries)
{
    /*
     * Function: print_books
     * Parameters: const string& library_name, const string& author,
     * const map<string, map<string, vector<Book>>>& libraries
     * Purpose: Prints all books by given author in given library.
     * Also prints reservation status and title for book.
     */

    auto library_iter = libraries.find(library_name);

    if (library_iter != libraries.end())
    {
        auto author_iter = library_iter->second.find(author);
        if (author_iter != library_iter->second.end())
        {
            for (const auto &book : author_iter->second)
            {
                cout << book.title << " --- ";
                if (book.reservations == 0)
                {
                    cout << "on the shelf" << endl;
                }
                else
                {
                    cout << book.reservations << " reservations" << endl;
                }
            }
        }
        else
        {
            cout << "Error: unknown author" << endl;
        }
    }
    else
    {
        cout << "Error: unknown library" << endl;
    }
}

void print_reservable(const string &author, const string &title,
                      const map<string, map<string, vector<Book>>> &libraries)
{
    /*
     * Function: print_reservable
     * Parameters: const string& author, const string& title,
     * const map<string, map<string, vector<Book>>>& libraries
     * Purpose: Prints libraries for a given book/author
     * if reservable and let's the user know if
     * a book is not found from any library.
     */

    int min_reservations = numeric_limits<int>::max();
    // Initialize the minimum reservations to the maximum possible value
    vector<string> library_names;
    // Store the names of libraries with the minimum reservations
    bool book_found = false;
    // Flag to indicate if the book is found in any library

    // Iterate through each library
    for (const auto &library : libraries)
    {
        auto author_iter = library.second.find(author);
        if (author_iter != library.second.end())
        {
            // Check if the author is found in the library
            // Iterate through each book by the author
            for (const auto &book : author_iter->second)
            {
                if (book.title == title)
                { // Check if the book title matches
                    book_found = true;
                    // Update the minimum reservations and
                    // the corresponding library names
                    if (book.reservations < min_reservations &&
                        book.reservations != 100)
                    {
                        min_reservations = book.reservations;
                        library_names.clear();
                        library_names.push_back(library.first);
                    }
                    else if (book.reservations == min_reservations)
                    {
                        library_names.push_back(library.first);
                    }
                }
            }
        }
    }

    // Print the appropriate message based on the search result
    if (!book_found)
    {
        cout << "Book is not a library book" << endl;
    }
    else if (min_reservations == 100)
    {
        cout << "Book is not reservable from any library" << endl;
    }
    else if (min_reservations == numeric_limits<int>::max())
    {
        cout << "Book is not reservable from any library" << endl;
    }
    else if (min_reservations == 0)
    {
        cout << "on the shelf" << endl;
        for (const auto &library_name : library_names)
        {
            cout << "--- " << library_name << endl;
        }
    }
    else
    {
        cout << min_reservations << " reservations" << endl;
        for (const auto &library_name : library_names)
        {
            cout << "--- " << library_name << endl;
        }
    }
}

void print_loanable(const map<string, map<string, vector<Book>>> &libraries)
{
    /*
     * Function: print_loanable
     * Parameters: const map<string, map<string, vector<Book>>>& libraries
     * Purpose: Prints a list of all loanable books.
     */
    map<string, std::set<string>> loanable_books;

    for (const auto &library : libraries)
    {
        for (const auto &author : library.second)
        {
            for (const auto &book : author.second)
            {
                if (book.reservations == 0)
                {
                    loanable_books[author.first].insert(book.title);
                }
            }
        }
    }

    for (const auto &author : loanable_books)
    {
        for (const auto &title : author.second)
        {
            cout << author.first << ": " << title << endl;
        }
    }
}

bool book_compare(const Book &a, const Book &b)
{
    /*
     * Function: book_compare
     * Parameters: const Book& a, const Book& b
     * Purpose: Compares 2 book objects
     * Usage: This function is typically used
     * as a comparator in sorting algorithms.
     * This function was partly inspired by https://www.geeksforgeeks.org/
     */
    if (a.author == b.author)
    {
        return a.title < b.title;
    }
    return a.author < b.author;
}

void summary(const string &library, const unordered_map<string,
                                                        unordered_map<string, Book>> &libraries)
{
    /*
     * Function: summary
     * Parameters: const string& library, const unordered_map<string,
     * unordered_map<string, Book>>& libraries
     * Purpose: Prints a summary of available books in an alphabetical order.
     */
    auto lib_iter = libraries.find(library);
    if (lib_iter != libraries.end())
    {
        vector<Book> books;
        for (const auto &book_entry : lib_iter->second)
        {
            books.push_back(book_entry.second);
        }
        sort(books.begin(), books.end(), book_compare);
        for (const Book &book : books)
        {
            cout << book.author << ": " << book.title << endl;
        }
    }
    else
    {
        cout << "Error: unknown library" << endl;
    }
}

void author_info(const string &library, const string &author,
                 const unordered_map<string, unordered_map<string, Book>> &libraries)
{
    /*
     * Function: author_info
     * Parameters: const string& library, const string& author,
     * const unordered_map<string, unordered_map<string, Book>>& libraries
     * Purpose: This function displays the book title and status of reservation.
     * Also an error message is implemented.
     */

    auto lib_iter = libraries.find(library);
    if (lib_iter != libraries.end())
    {
        // Check if the library exists
        bool author_found = false;
        // Flag to indicate if the author is found in the library
        for (const auto &book_entry : lib_iter->second)
        {
            const Book &book = book_entry.second;
            if (book.author == author)
            {
                // Check if the book author matches
                author_found = true;
                cout << book.title << " --- ";
                if (book.reservations == 0)
                {
                    cout << "on the shelf";
                    // Book is available on the shelf
                }
                else
                {
                    cout << book.reservations << " reservations";
                    // Display the number of reservations
                }
                cout << endl;
            }
        }
        if (!author_found)
        {
            cout << "Error: unknown author" << endl;
            // The author is not found in the library
        }
    }
    else
    {
        cout << "Error: unknown library" << endl;
        // The library is not found
    }
}

bool operator==(const Book &a, const Book &b)
{
    return a.author == b.author && a.title == b.title;
}

int main()
{
    /*
     * Function: main
     * Purpose: Stores data from a CSV input file and defines a command interface.
     *          Supports commands that allow the user to interact with the data,
     *          such as checking the availability of books in different libraries.
     */

    string input_file;
    cout << "Input file: ";
    cin >> input_file;

    // Open the input file
    ifstream file(input_file);
    if (!file.is_open())
    {
        cout << "Error: input file cannot be opened" << endl;
        return EXIT_FAILURE;
    }

    // Read data from the input file and store it in the libraries data structure
    map<string, map<string, vector<Book>>> libraries;
    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string library, author, title, reservations_str;

        // Read and process input based on the delimiter (; or ,)
        if (line.find(';') != string::npos)
        {
            getline(ss, library, ';');
            getline(ss, author, ';');
            getline(ss, title, ';');
            getline(ss, reservations_str, ';');
        }
        else if (line.find(',') != string::npos)
        {
            getline(ss, library, ',');
            getline(ss, author, ',');
            getline(ss, title, ',');
            getline(ss, reservations_str, ',');
        }
        else
        {
            cout << "Error: unknown delimiter" << endl;
            return EXIT_FAILURE;
        }

        // Check for empty fields
        if (library.empty() || author.empty() || title.empty() || reservations_str.empty())
        {
            cout << "Error: empty field" << endl;
            return EXIT_FAILURE;
        }

        // Convert reservations_str to an integer
        int reservations = (reservations_str == "on-the-shelf") ? 0 : stoi(reservations_str);

        // Create a book object and add it to the libraries data structure
        Book book = {author, title, reservations};
        libraries[library][author].push_back(book);
    }
    file.close();

    cin.ignore();
    // Process commands entered by the user
    string command;
    while (true)
    {
        cout << "lib> ";
        getline(cin, command);

        stringstream cmd_stream(command);
        string cmd;
        cmd_stream >> cmd;

        // Check the user command and perform the corresponding action
        if (cmd == "quit" || cmd == "exit")
        {
            break;
        }
        else if (cmd == "libraries")
        {
            // Print the list of libraries
            print_libraries(libraries);
        }
        else if (cmd == "material")
        {
            string library_name;
            if (cmd_stream >> library_name)
            {
                // Print the list of materials in a specific library
                print_material(library_name, libraries);
            }
            else
            {
                cout << "Error: wrong number of parameters" << endl;
            }
        }
        else if (cmd == "books")
        {
            string library_name, author;
            if (cmd_stream >> library_name >> ws)
            {
                // Extract the author parameter (with possible spaces)
                getline(cmd_stream, author);
                if (!author.empty())
                {
                    // Print the list of books by a specific author in a specific library
                    print_books(library_name, author, libraries);
                }
                else
                {
                    cout << "Error: wrong number of parameters" << endl;
                }
            }
            else
            {
                cout << "Error: wrong number of parameters" << endl;
            }
        }
        else if (cmd == "reservable")
        {
            string author, title;
            cmd_stream >> author;

            // Check if the title has double quotes around it
            if (cmd_stream.peek() == ' ')
            {
                cmd_stream.ignore(1, ' ');
            }

            if (cmd_stream.peek() == '\"')
            {
                // Extract the title parameter enclosed in double quotes
                getline(cmd_stream.ignore(), title, '\"');
            }
            else
            {
                getline(cmd_stream, title);
            }

            // Check if author and title are not empty, then call the function
            if (!author.empty() && !title.empty())
            {
                // Print the availability of a specific book for reservation
                print_reservable(author, title, libraries);
            }
            else
            {
                cout << "Error: wrong number of parameters" << endl;
            }
        }
        else if (cmd == "loanable")
        {
            // Print the list of books available for loan
            print_loanable(libraries);
        }
        else
        {
            cout << "Error: unknown command" << endl;
        }
    }
}
