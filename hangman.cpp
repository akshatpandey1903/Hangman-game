#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <fstream> 
#include <cctype>

std::string toLowerCase(const std::string& word){
    std::string lower;
    for(char c : word){
        lower += std::tolower(c);
    }
    return lower;
}

std::vector<std::string> readWordsFromFile(const std::string& filename){
    std::vector<std::string> wordList;
    std::ifstream file(filename);
    std::string word;

    while(file >> word) {
        wordList.push_back(toLowerCase(word));
    }

    return wordList;
}

std::string chooseWord(const std::vector<std::string>& wordList) {
    int index = rand() % wordList.size();
    return wordList[index];
}

void displayGameState(const std::string& word, const std::string& guessedLetters) {
    for(char c : word){
        if(guessedLetters.find(c) != std::string::npos){
            std::cout << c << ' ';
        }else{
            std::cout << "_ ";
        }
    }
    std::cout << std::endl;
}

bool isWordGuessed(const std::string& word, const std::string& guessedLetters){
    for(char c : word){
        if(guessedLetters.find(c) == std::string::npos){
            return false;
        }
    }
    return true;
}

bool isGuessCorrect(const std::string& word, char guess){
    return word.find(guess) != std::string::npos;
}

void updateGuessedLetters(std::string& guessedLetters, char guess){
    guessedLetters += guess;
}

void displayHangman(int wrongGuesses) {
    static const std::vector<std::string> hangmanstates = {
        "  +---+\n      |\n      |\n      |\n      |\n      |\n=========",
        "  +---+\n  O   |\n      |\n      |\n      |\n      |\n=========",
        "  +---+\n  O   |\n  |   |\n      |\n      |\n      |\n=========",
        "  +---+\n  O   |\n /|   |\n      |\n      |\n      |\n=========",
        "  +---+\n  O   |\n /|\\  |\n      |\n      |\n      |\n=========",
        "  +---+\n  O   |\n /|\\  |\n /    |\n      |\n      |\n=========",
        "  +---+\n  O   |\n /|\\  |\n / \\  |\n      |\n      |\n========="
    };
    std::cout << hangmanstates[wrongGuesses] << std::endl;
}

int main() {
    std::vector<std::string> wordList = readWordsFromFile ("movies.txt");
    if (wordList.empty()){
        std::cerr << "Word List is empty or File not Found!!" << std::endl;
        return 1;
    }

    srand(static_cast<unsigned int>(time(0)));
    
    char playAgain;
    do{
        std::string word = chooseWord(wordList);
        std::string guessedLetters;
        int wrongGuesses = 0;
        const int maxWrongGuesses = 6;

        while(wrongGuesses < maxWrongGuesses && !isWordGuessed(word, guessedLetters)){
            displayGameState(word, guessedLetters);
            displayHangman(wrongGuesses);

            std::cout << "Enter your guess: ";
            char guess;
            std::cin >> guess;
            guess = tolower(guess);

            if(isGuessCorrect(word, guess)){
                std::cout << "Guess is correct :)" << std::endl;
                updateGuessedLetters(guessedLetters, guess);
            }else{
                std::cout << "Incorrect Guess :(" << std::endl;
                ++wrongGuesses;
            }
        }

        if(isWordGuessed(word, guessedLetters)){
            std::cout << "Congrats!! You've guessed the word: " << word << std::endl;
        }else{
            std::cout << "Unluckyy, You've been hanged! The word was: " << word << std::endl;
        }

        std::cout << "Do you wanna play again? (y/n): ";
        std::cin >> playAgain;
        playAgain = tolower(playAgain);
    }while(playAgain == 'y');

    return 0;
}