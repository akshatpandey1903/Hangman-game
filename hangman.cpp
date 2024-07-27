#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <fstream>
#include <cctype>

std::vector<std::string> readWordsFromFile(const std::string& filename) {
    std::vector<std::string> wordList;
    std::ifstream file;
    file.open(filename);
    std::string line;

    while (std::getline(file, line)) {
        
        line.erase(std::find_if(line.rbegin(), line.rend(), [](unsigned char ch) {
            return !std::isspace(ch);
        }).base(), line.end());

        if (!line.empty()) {
            wordList.push_back(line);
        }
    }
    file.close();
    return wordList;
}

std::string chooseWord(const std::vector<std::string>& wordList) {
    int index = rand() % wordList.size();
    return wordList[index];
}

void displayGameState(const std::string& word, const std::string& guessedLetters) {
    for (char c : word) {
        if (std::isalpha(c)) {
            if (guessedLetters.find(std::tolower(c)) != std::string::npos) {
                std::cout << c << ' ';
            } else {
                std::cout << "_ ";
            }
        } else {
            std::cout << c << ' ';  
        }
    }
    std::cout << std::endl;
}

bool isWordGuessed(const std::string& word, const std::string& guessedLetters) {
    for (char c : word) {
        if (std::isalpha(c) && guessedLetters.find(std::tolower(c)) == std::string::npos) {
            return false;
        }
    }
    return true;
}

bool isGuessCorrect(const std::string& word, char guess) {
    return std::any_of(word.begin(), word.end(), [guess](char c) {
        return std::tolower(c) == std::tolower(guess);
    });
}

void updateGuessedLetters(std::string& guessedLetters, char guess) {
    if (guessedLetters.find(guess) == std::string::npos) {
        guessedLetters += guess;
    }
}

void displayHangman(int wrongGuesses) {
    static const std::vector<std::string> hangmanStates = {
        "  +---+\n      |\n      |\n      |\n      |\n      |\n=========",
        "  +---+\n  O   |\n      |\n      |\n      |\n      |\n=========",
        "  +---+\n  O   |\n  |   |\n      |\n      |\n      |\n=========",
        "  +---+\n  O   |\n /|   |\n      |\n      |\n      |\n=========",
        "  +---+\n  O   |\n /|\\  |\n      |\n      |\n      |\n=========",
        "  +---+\n  O   |\n /|\\  |\n /    |\n      |\n      |\n=========",
        "  +---+\n  O   |\n /|\\  |\n / \\  |\n      |\n      |\n========="
    };
    std::cout << hangmanStates[wrongGuesses] << std::endl;
}

int main() {
    std::vector<std::string> wordList = readWordsFromFile("movies.txt");
    if (wordList.empty()) {
        std::cerr << "Word list is empty or file not found!" << std::endl;
        return 1;
    }

    srand(static_cast<unsigned int>(time(0)));

    char playAgain;
    do {
        std::string word = chooseWord(wordList);
        std::string guessedLetters;
        int wrongGuesses = 0;
        const int maxWrongGuesses = 6;

        while (wrongGuesses < maxWrongGuesses && !isWordGuessed(word, guessedLetters)) {
            displayGameState(word, guessedLetters);
            displayHangman(wrongGuesses);

            std::cout << "Enter your guess: ";
            char guess;
            std::cin >> guess;
            guess = std::tolower(guess);

            if (isGuessCorrect(word, guess)) {
                std::cout << "Correct guess!" << std::endl;
                updateGuessedLetters(guessedLetters, guess);
            } else {
                std::cout << "Wrong guess!" << std::endl;
                ++wrongGuesses;
            }
        }

        if (isWordGuessed(word, guessedLetters)) {
            std::cout << "Congratulations! You've guessed the movie: " << word << std::endl;
        } else {
            std::cout << "You've been hanged! The movie was: " << word << std::endl;
        }

        std::cout << "Play again? (y/n): ";
        std::cin >> playAgain;
        playAgain = std::tolower(playAgain);
    } while (playAgain == 'y');


    return 0;
}
