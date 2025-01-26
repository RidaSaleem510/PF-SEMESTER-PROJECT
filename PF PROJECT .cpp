#include <iostream>
#include <string>
#include <fstream> // For file handling
#include <iomanip> // For centering text
#include <cctype> // For toupper

using namespace std;
// Function prototypes (declarations of functions used in the program)
void displayPuzzle(const char puzzle[10][10], int rows, int cols); // Function to display the puzzle grid
string toUpperCase(const string& str); // Function to convert a string to uppercase
bool guessWord(const string& guess, string* words, bool* foundWords, int* attempts, int wordCount, int& wordsFound); // Function to process user guesses
void endGame(int wordsFound, int totalWords); // Function to end the game and display results
bool askToRetry(); // Function to ask the user if they want to play again
bool loadPuzzle(const string& filename, char puzzle[10][10], int rows, int cols); // Function to load puzzle data from a file
bool loadWords(const string& filename, string* words, int wordCount); // Function to load the word list from a file

// Function to display the puzzle
void displayPuzzle(const char puzzle[10][10], int rows, int cols) {
    const int consoleWidth = 80; // Assume a standard console width
    int padding = (consoleWidth - (cols * 2 - 1)) / 2; // Adjust for spaces between letters

    // Loop to print each row of the puzzle
    for (int i = 0; i < rows; ++i) {
        cout << string(padding, ' '); // Add padding to center the puzzle
        for (int j = 0; j < cols; ++j) {
            cout << puzzle[i][j]; // Print the letter
            if (j < cols - 1) cout << " "; // Add space between letters
        }
        cout << endl;
    }
    cout << endl; // Add extra line at the end for clarity
}

// Convert a string to uppercase
string toUpperCase(const string& str) {
    string result = str; // Create a copy of the input string
    for (size_t i = 0; i < result.length(); ++i) { // Loop through each character
        result[i] = toupper(result[i]); // Convert the character to uppercase
    }
    return result; // Return the uppercase string
}

// Function to process a user's guess
bool guessWord(const string& guess, string* words, bool* foundWords, int* attempts, int wordCount, int& wordsFound) {
    for (int i = 0; i < wordCount; ++i) {
        if (!foundWords[i] && guess == words[i]) {
            cout << "Correct! You found the word: " << words[i] << "\n\n";
            foundWords[i] = true;  // Mark the word as found
            wordsFound++;          // Increment the count of found words
            return true;
        }
    }

    // If the guess is incorrect, update the attempts and notify the user
    for (int i = 0; i < wordCount; ++i) {
        if (!foundWords[i]) {
            attempts[i]++; // Increment the incorrect attempt count for the word
            cout << "Incorrect! " << (3 - attempts[i]) << " attempts left for this word.\n";
            break; // Exit after the first incorrect guess
        }
    }
    return false;
}
// End the game and display final results
void endGame(int wordsFound, int totalWords) {
    cout << "Game Over! You found " << wordsFound << " out of " << totalWords << " words.\n";
    cout << "Thanks for playing!\n";
}

// Function to ask if the user wants to retry the game
bool askToRetry() {
    string response;
    cout << "Do you want to try again? (yes/no): ";
    cin >> response;
    return toUpperCase(response) == "YES"; // Return true if the user chooses "yes"
}
// Load the puzzle grid from a file
bool loadPuzzle(const string& filename, char puzzle[10][10], int rows, int cols) {
    ifstream file(filename.c_str()); // Open the file
    if (!file.is_open()) return false; // Return false if the file cannot be opened

    for (int i = 0; i < rows; ++i) { // Loop through each row
        string line;
        getline(file, line); // Read a line from the file
        if (line.length() != cols) return false; // Ensure the line matches the column count

        for (int j = 0; j < cols; ++j) { // Loop through each column
            puzzle[i][j] = line[j]; // Assign the character to the puzzle grid
        }
    }

    file.close(); // Close the file
    return true; // Return true if the puzzle was loaded successfully
}

// Function to load words from a file
bool loadWords(const string& filename, string* words, int wordCount) {
    ifstream file(filename.c_str()); // Open the file for reading
    if (!file.is_open()) return false; // Return false if the file can't be opened

    // Read each word from the file
    for (int i = 0; i < wordCount; ++i) {
        if (!(file >> words[i])) return false; // Ensure there are enough words in the file
    }

    file.close(); // Close the file after reading
    return true;
}




