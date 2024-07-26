
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <fstream> 

std::vector<std::string> readWordsFromFile(const std::string& filename){
    std::vector<std::string> wordList;
    std::ifstream file(filename);
    std::string word;

    while(file >> word) {
        wordList.push_back(word);
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
}

int main() {
    
}