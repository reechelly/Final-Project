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

// Get random match time
std::string getRandomTime() {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> hourDist(12, 19);
    std::uniform_int_distribution<int> minDist(0, 1);

    int hour = hourDist(rng);
    int minute = (minDist(rng) == 0) ? 0 : 45;  // Random minute 00 or 45
    std::stringstream ss;
    ss << std::setw(2) << std::setfill('0') << hour << ":"
       << std::setw(2) << std::setfill('0') << minute;
    return ss.str();
}
