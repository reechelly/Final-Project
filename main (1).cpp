#include <algorithm>
#include <random>
#include <iostream>
#include <unordered_set>
#include <vector>
#include <sstream>
#include <fstream>
#include <iomanip> // for setting time format

struct Team {
    std::string name;
    std::string stadium;
    std::string town;
};

// Read team data from a file
std::vector<Team> loadTeams(const std::string& filePath) {
    std::vector<Team> teamList;
    std::ifstream file(filePath);
    if (!file) {
        std::cout << "Can't open the file! Check path: " << filePath << std::endl;
        return teamList;
    }

    std::string line;
    std::getline(file, line); // Skip the header
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        Team t;
        std::getline(ss, t.name, ',');
        std::getline(ss, t.stadium, ',');
        std::getline(ss, t.town, ',');
        teamList.push_back(t);
    }
    file.close();
    return teamList;
}

