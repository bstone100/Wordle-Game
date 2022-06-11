#include "WordleGame.h"
#include <fstream>
#include <string>
#include <set>
#include <iostream>

WordleGame::WordleGame(const std::string& filename) {
    std::fstream file;
    file.open(filename, std::ios::in);
    std::string temp;
    do {
        getline(file, temp);
        dictionary.insert(temp);
    } while (temp != "");
}
void WordleGame::select_key(int index) {
    int point = index % (dictionary.size() - 1);
    std::set<std::string>::iterator it = dictionary.begin();
    std::advance(it, point);
    key = *it;
}
std::string WordleGame::score(const std::string& input) {
    std::string result = "-----";
    std::string keyCopy;
    done = false;
    if (dictionary.find(input) == dictionary.end()) {
        return "not in dictionary";
    } else if (input == key) {
        done = true;
        return "*****";
    } else {
        for (int i = 0; i < 5; i++) {
            if (input[i] == key[i]) {
                result[i] = '*';
            } else {
                keyCopy += key[i];
            }
        }
        for (int i = 0; i < 5; i++) {
            if (result[i] != '*') {
                std::size_t found = keyCopy.find(input[i]);
                if (found != std::string::npos) {
                    result[i] = '+';
                    keyCopy.erase(keyCopy.begin() + found);
                } else {
                    result[i] = '-';
                }
            }
            
        }
    }
    return result;
}
bool WordleGame::over(void) const {
    return done;
}
