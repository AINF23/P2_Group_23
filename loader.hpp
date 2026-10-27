#pragma once
#include "classes.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>

using namespace std;

inline vector<string> splitTabs(const string& line) {
    vector<string> fields;
    size_t start = 0;
    while (true) {
        size_t pos = line.find('\t', start);
        if (pos == string::npos) {
            fields.push_back(line.substr(start));
            break;
        }
        fields.push_back(line.substr(start, pos - start));
        start = pos + 1;
    }
    return fields;
}

// minYear: drop shows that started before this. minVotes: drop shows with fewer votes.
inline vector<TVShow*> loadShows(const string& basicsPath,
                                 const string& ratingsPath,
                                 const string& episodePath,
                                 int minYear, int minVotes) {
    string line;

    // Pass 1: ratings
    unordered_map<string, pair<float, int>> ratings;
    ifstream rf(ratingsPath);
    if (!rf) { cerr << "Can't open " << ratingsPath << "\n"; return {}; }
    getline(rf, line);  // skip header
    while (getline(rf, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        auto f = splitTabs(line);
        if (f.size() < 3) continue;
        ratings[f[0]] = {stof(f[1]), stoi(f[2])};
    }

    // Pass 2: basics
    vector<TVShow*> shows;
    unordered_map<string, TVShow*> byId;
    ifstream bf(basicsPath);
    if (!bf) { cerr << "Can't open " << basicsPath << "\n"; return {}; }
    getline(bf, line);  // skip header
    while (getline(bf, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        auto f = splitTabs(line);
        if (f.size() < 9 || f[1] != "tvSeries") continue;
        if (f[5] == "\\N") continue;
        int year = stoi(f[5]);
        if (year < minYear) continue;

        // Unrated shows are kept (rating 0.0) unless they fail the vote check
        float rating = 0.0f;
        auto it = ratings.find(f[0]);
        if (it != ratings.end()) {
            if (it->second.second < minVotes) continue;
            rating = it->second.first;
        } else if (minVotes > 0) {
            continue;   // no votes at all, and a minimum was requested
        }

        TVShow* s = new TVShow;
        s->title = f[2];
        s->genre = (f[8] == "\\N") ? "" : f[8];   // e.g. "Drama,Crime,Thriller"
        s->rating = rating;
        s->year = year;
        s->episodes = 0;
        s->seasons = 0;
        byId[f[0]] = s;
        shows.push_back(s);
    }

    // Pass 3: episodes and seasons
    ifstream ef(episodePath);
    if (!ef) { cerr << "Can't open " << episodePath << "\n"; return shows; }
    getline(ef, line);  // skip header
    while (getline(ef, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        auto f = splitTabs(line);
        if (f.size() < 4) continue;
        auto it = byId.find(f[1]);
        if (it == byId.end()) continue;
        it->second->episodes++;
        if (f[2] != "\\N") {
            int season = stoi(f[2]);
            if (season > it->second->seasons) it->second->seasons = season;
        }
    }
    return shows;
}