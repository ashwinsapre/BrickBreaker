// ScoreManager.cpp
#include "ScoreManager.h"
#include "Score.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>


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
    auto scores = new std::vector<Score>();

    std::ifstream file("../saves/scores.txt");

    if (file.is_open()) {
        std::cout << "File opened\n";
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

    // Sort scores in ascending order (lower score is better)
    std::sort(scores->begin(), scores->end(), [](const Score& a, const Score& b) {
        return a.scoreValue < b.scoreValue;
    });

    return scores;
}

std::vector<Score>* ScoreManager::getTopScores(int count) {
    std::vector<Score>* scores = loadScores();
    if (!scores) {
        std::cerr << "Invalid input vector pointer." << std::endl;
        return nullptr;
    }
    // Get only the top 'count' scores
    if (count < scores->size()) {
        scores->resize(count);
    }

    return scores;
}


