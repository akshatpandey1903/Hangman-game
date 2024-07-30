#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <fstream>
#include <cctype> 

std::vector<std::string> readWordsFromFile(const std::string& category) {
    std::vector<std::string> wordList;
    std::string filename = category + ".txt";
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        // Convert the entire line to lowercase
        std::transform(line.begin(), line.end(), line.begin(), ::tolower);
        wordList.push_back(line);
    }

    return wordList;
}

std::vector<std::string> listCategories(){
    return {"Movies", "Games", "Animals", "Countries"};
}

std::string chooseCategory() {
    std::vector<std::string> categories = listCategories();
    std::cout << "Choose a category:\n";
    for(size_t i{}; i<categories.size(); ++i){
        std::cout << i + 1 << ". " << categories[i] << std::endl;
    }

    int choice;
    std::cin >> choice;
    return categories[choice - 1];
}

std::string chooseWord(const std::vector<std::string>& wordList) {
    int index = rand() % wordList.size();
    return wordList[index];
}

void displayGameState(const std::string& word, const std::string& guessedLetters, const std::string category) {
    std::cout << "Category: " << category << std::endl;
    for (char c : word) {
        if (!std::isalpha(c) || guessedLetters.find(c) != std::string::npos) {
            std::cout << c << ' '; // Display the character if guessed or if it is not an alphabet (e.g., space, punctuation)
        } else {
            std::cout << "_ ";
        }
    }
    std::cout << std::endl;
}

bool isWordGuessed(const std::string& word, const std::string& guessedLetters) {
    for (char c : word) {
        if (std::isalpha(c) && guessedLetters.find(c) == std::string::npos) {
            return false;
        }
    }
    return true;
}

bool isGuessCorrect(const std::string& word, char guess) {
    return word.find(guess) != std::string::npos;
}

void updateGuessedLetters(std::string& guessedLetters, char guess) {
    guessedLetters += guess;
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
    srand(static_cast<unsigned int>(time(0)));
    
    std::string category;
    std::vector<std::string> wordList;

    char playAgain;
    do {
        category = chooseCategory();
        wordList = readWordsFromFile(category);
        
        if(wordList.empty()){
            std::cerr << "Word list is empty or File could not be found for the chosen category: " << category << std::endl;
            std::cout << "Would you like to choose another category? (y/n): ";
            char tryAgain;
            std::cin >> tryAgain;
            if(towlower(tryAgain) != 'y'){
                break;
            } 
            continue;
        }

        std::string word = chooseWord(wordList);
        std::string guessedLetters;
        int wrongGuesses = 0;
        const int maxWrongGuesses = 6;

        while (wrongGuesses < maxWrongGuesses && !isWordGuessed(word, guessedLetters)) {
            displayGameState(word, guessedLetters, category);
            displayHangman(wrongGuesses);

            std::cout << "Enter your guess: ";
            char guess;
            std::cin >> guess;
            guess = tolower(guess);

            if (isGuessCorrect(word, guess)) {
                std::cout << "Correct guess!" << std::endl;
                updateGuessedLetters(guessedLetters, guess);
            } else {
                std::cout << "Wrong guess!" << std::endl;
                ++wrongGuesses;
            }
        }

        if (isWordGuessed(word, guessedLetters)) {
            std::cout << "Congratulations! You've guessed the word: " << word << std::endl;
        } else {
            std::cout << "You've been hanged! The word was: " << word << std::endl;
        }

        std::cout << "Play again? (y/n): ";
        std::cin >> playAgain;
        if(tolower(playAgain) != 'y'){
            break;
        }
    } while (true);

    std::cout << "\nThanks for Playing =)\n";
    return 0;
}
