#pragma once
#include <string>
#include <vector>
#include <ctime>
#include <algorithm>
#include <cctype>
#include "sorting.hpp"

using namespace std;

struct TVShow{
    string title = "";
    string genre = "";
    float rating = 0.0;
    int year = 2000;
    int seasons = 1;
    int episodes = 1;
};

struct Query{
    float ratingMin = 1.0;
    float ratingMax = 10.0;
    int yearMin = 0;
    int yearMax = 3000;
    int seasonMin = 0;
    int seasonMax = 10000;
    int episodeMin = 0;
    int episodeMax = 10000;
    string titlePrefix = "";
    string genrePrefix = "";
    string sortAlgo = "merge";
    string sortBy = "rating";
    bool descending = false;
};

class Database{
    public:
        double duration = 0;
        void loadData(const vector<TVShow*>& dataToLoad){
            data = dataToLoad;
        }
        vector<TVShow*> applyQuery(const Query& q){
            clock_t startTime = clock();
            vector<TVShow*> result;
            for (int i = 0; i < data.size(); i++){
                if (data[i]->rating < q.ratingMin || data[i]->rating > q.ratingMax){
                    continue;
                }
                string data_title = data[i]->title;
                transform(data_title.begin(), data_title.end(), data_title.begin(), [](unsigned char c){
                    return tolower(c);
                });
                if (!checkPrefix(q.titlePrefix, data_title)){
                    continue;
                }
                if (!checkPrefix(q.genrePrefix, data[i]->genre)){
                    continue;
                }
                if (data[i]->year < q.yearMin || data[i]->year > q.yearMax){
                    continue;
                }
                if (data[i]->seasons < q.seasonMin || data[i]->seasons > q.seasonMax){
                    continue;
                }
                if (data[i]->episodes < q.episodeMin || data[i]->episodes > q.episodeMax){
                    continue;
                }
                result.push_back(data[i]);
            }

            bool (*compareUsed)(TVShow*&, TVShow*&);
            if (q.sortBy == "rating"){
                compareUsed = compareRating;
            }
            if (q.sortBy == "title"){
                compareUsed = compareTitle;
            }
            if (q.sortBy == "year"){
                compareUsed = compareYear;
            }
            if (q.sortBy == "episode" || q.sortBy == "episodes"){
                compareUsed = compareEpisode;
            }
            if (q.sortBy == "season" || q.sortBy == "seasons"){
                compareUsed = compareSeason;
            }

            if (q.sortAlgo == "merge"){
                result = mergeSort(result, compareUsed);
            }
            if (q.sortAlgo == "heap"){
                result = heapSort(result, compareUsed);
            }
            if (q.sortAlgo == "quick"){
                result = quickSort(result, compareUsed);
            }
            clock_t endTime = clock();
            duration = double(endTime - startTime) / CLOCKS_PER_SEC;
            if (q.descending){
                reverse(result.begin(), result.end());
            }
            return result;
        }
    private:
        vector<TVShow*> data;
        bool checkPrefix(string prefix, string s){
            for (int i = 0; i < prefix.size(); i++){
                if (prefix[i] != s[i]){
                    return false;
                }
            }
            return true;
        }
        bool (*compareTitle)(TVShow*&, TVShow*&) = [](TVShow* &a, TVShow* &b){return a->title < b->title;};
        bool (*compareRating)(TVShow*&, TVShow*&) = [](TVShow* &a, TVShow* &b){return a->rating < b->rating;};
        bool (*compareEpisode)(TVShow*&, TVShow*&) = [](TVShow* &a, TVShow* &b){return a->episodes < b->episodes;};
        bool (*compareYear)(TVShow*&, TVShow*&) = [](TVShow* &a, TVShow* &b){return a->year < b->year;};
        bool (*compareSeason)(TVShow*&, TVShow*&) = [](TVShow* &a, TVShow* &b){return a->seasons < b->seasons;};
};