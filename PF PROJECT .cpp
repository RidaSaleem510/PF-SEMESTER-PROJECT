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


int main() {
    const int rows = 10; // Number of rows in the puzzle grid
    const int cols = 10; // Number of columns in the puzzle grid
    const int wordCount = 10; // Total number of words in the puzzle

    // Puzzle grid and word list
    char puzzle[10][10]; // 2D array to store the puzzle grid
    string words[10]; // Array to store the words to find

    // Load the puzzle grid from a file
    if (!loadPuzzle("C:/Users/AL KHAIR COMPUTER/Desktop/sem proj/puzzle.txt", puzzle, rows, cols)) {
        cerr << "Error: Failed to load puzzle from file." << endl; // Display error if the file cannot be loaded
        return 1; // Exit the program with an error code
    }

    // Load the word list from a file
    if (!loadWords("C:/Users/AL KHAIR COMPUTER/Desktop/sem proj/word.txt", words, wordCount)) {
        cerr << "Error: Failed to load words from file." << endl; // Display error if the file cannot be loaded
        return 1; // Exit the program with an error code
    }

    bool foundWords[10] = {false};  // Array to track which words have been found
    int attempts[10] = {0};         // Array to track attempts for each word
    int wordsFound = 0;             // Counter for words found
    string guess;                   // Variable to store the user's guess
        bool exitGame = false;          // Flag to indicate if the game should end

    do {
        // Display the welcome message and puzzle instructions
        cout << "Welcome to the Animal Word Search Puzzle Game!\n";
        cout << "Here is your puzzle:\n";
        displayPuzzle(puzzle, rows, cols);  // Call function to display the puzzle
        cout << "Your task is to find the hidden words in the grid.\n";
        cout << "You can find the words in any order.\n";
        cout << "Each word has a maximum of 3 attempts.\n";
        cout << "Type 'EXIT' at any time to end the game.\n\n";

        wordsFound = 0;
        // Reset tracking arrays for a new game
        for (int i = 0; i < wordCount; ++i) {
            attempts[i] = 0;
            foundWords[i] = false;
        }

        // Main game loop where the player guesses words
        while (wordsFound < wordCount) {
            // Display hints for the player
            cout << "Hint: Word lengths: ";
            for (int i = 0; i < wordCount; ++i) {
                if (!foundWords[i]) {
                    cout << words[i].length() << " ";
                }
            }
            cout << endl;

            // Get user's guess
            cout << "Enter your guess: ";
            cin >> guess;

            // Handle exit condition if the user types "EXIT"
            if (toUpperCase(guess) == "EXIT") {
                cout << "You chose to end the game. Thanks for playing!\n";
                exitGame = true;
                break; // Break out of the game loop
            }

            // Process the guess to check if it's correct
            if (!guessWord(toUpperCase(guess), words, foundWords, attempts, wordCount, wordsFound)) {
                cout << "Incorrect!\n"; // If the guess is incorrect, notify the user
            }

            // Check if any word has reached 3 incorrect attempts
            for (int i = 0; i < wordCount; ++i) {
                if (attempts[i] >= 3 && !foundWords[i]) {
                    cout << "Three wrong attempts for a word. Ending game.\n";
                    endGame(wordsFound, wordCount); // End the game when 3 incorrect attempts are reached

                    // Ask if the user wants to retry the game
                    if (!askToRetry()) {
                        cout << "Thanks for playing! Goodbye.\n";
                        exitGame = true;
                    }
                    break;
                }
            }

            if (exitGame) break; // Exit the game loop if the player chose to quit
        }

        // Display the final results if the game ends
        if (wordsFound == wordCount && !exitGame) {
            cout << "Congratulations! You found all the words.\n";
        }
        endGame(wordsFound, wordCount); // Call endGame to show final results

    } while (!exitGame); // Loop for retrying the game if the user chooses to do so

    return 0; // Exit the program
}
    
    
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




