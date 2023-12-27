// ScoreManager.cpp
#include "ScoreManager.h"
#include "Score.h"
#include <iostream>
#include <vector>
#include <sstream>

void ScoreManager::saveScore(const Score& score) {
    std::ofstream file("../saves/scores.txt", std::ios::app);

    if (file.is_open()) {
        file << score.playerName << "-" << score.scoreValue << std::endl;
        file.close();
        std::cout << "Score saved successfully!" << std::endl;
    } else {
        std::cerr << "Unable to open the file for saving scores." << std::endl;
    }
}

std::vector<Score>* ScoreManager::loadScores() {
    std::vector<Score>* scores = new std::vector<Score>();

    std::ifstream file("../saves/scores.txt");

    if (file.is_open()) {
        std::cout<<"file opened\n";
        std::string line;
        while (std::getline(file, line)) {
            size_t delimiterPos = line.find('-');
            if (delimiterPos != std::string::npos) {
                std::string playerName = line.substr(0, delimiterPos);
                float scoreValue = std::stof(line.substr(delimiterPos + 1));

                scores->push_back(Score(playerName, scoreValue));
            }
        }
        file.close();
        std::cout << "Scores loaded successfully!" << std::endl;
    } else {
        std::cerr << "Unable to open the file for loading scores." << std::endl;
    }

    return scores;
}

