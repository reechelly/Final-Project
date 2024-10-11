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

// Create all the matchups "mine"
void makeFixtures(const std::vector<Team>& teams, std::vector<std::tuple<Team, Team, int, std::string>>& matches) {
    std::vector<std::pair<Team, Team>> games;

    // Home and away matches
    for (size_t i = 0; i < teams.size(); ++i) {
        for (size_t j = i + 1; j < teams.size(); ++j) {
            games.push_back({teams[i], teams[j]});
            games.push_back({teams[j], teams[i]});
        }
    }

    // Shuffle the games
    std::random_device rd;
    std::mt19937 rng(rd());
    std::shuffle(games.begin(), games.end(), rng);

    int week = 1;
    while (!games.empty()) {
        std::unordered_set<std::string> busyTeams;
        std::vector<std::pair<Team, Team>> thisWeekGames;

        for (auto it = games.begin(); it != games.end();) {
            const Team& home = it->first;
            const Team& away = it->second;

            if (busyTeams.find(home.name) == busyTeams.end() &&
                busyTeams.find(away.name) == busyTeams.end()) {
                thisWeekGames.push_back(*it);
                busyTeams.insert(home.name);
                busyTeams.insert(away.name);
                it = games.erase(it);
                if (thisWeekGames.size() == 2) break;  // Limit 2 games per week
            } else {
                ++it;
            }
        }

        // Add games with random time
        for (const auto& game : thisWeekGames) {
            std::string matchTime = getRandomTime();
            matches.push_back(std::make_tuple(game.first, game.second, week, matchTime));
        }
        ++week;
    }
}
void saveToCSV(const std::string& fileName, const std::vector<std::tuple<Team, Team, int, std::string>>& matches) {
    std::ofstream outFile(fileName);
    
if (!outFile) {
    std::cerr << "Oops! Couldn't write to file: " << fileName << std::endl;
    return;
}

outFile << "WEEK: HOME TEAM x AWAY TEAM @ TOWN - STADIUM: TIME\n";
for (const auto& match : matches) {
    const Team& home = std::get<0>(match);
    const Team& away = std::get<1>(match);
    int week = std::get<2>(match);
    const std::string& time = std::get<3>(match);

    outFile << week << ": "
            << home.name << " x "
            << away.name << " @ "
            << home.stadium << " - "
            << home.town << " => "
            << time << "\n";
}
}

