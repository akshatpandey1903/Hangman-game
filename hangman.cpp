
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