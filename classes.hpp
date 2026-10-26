#pragma once
#include <string>
#include <vector>
#include "string_stuff.h"
#include <cctype> //used for the strings

using namespace std;
struct TVShow{
    string title = "";
    string genre = "";
    float rating = 0.0;
    int year = 2000;
    int seasons = 1;
    int episodes = 1;
    //add more later
};

struct Query{
    float ratingMin = 1.0;
    float ratingMax = 10.0;
    string titlePrefix = "";
    string genrePrefix = "";
    //might need more data later
    string sortAlgo = "quick";
    string sortBy = "rating";
    bool descending = false;
};

class Database{
    public:
        void loadData(const vector<TVShow*>& dataToLoad){
            data = dataToLoad;
        }
        vector<TVShow*> applyQuery(const Query& q){
            vector<TVShow*> result;
            for (int i = 0; i < data.size(); i++){
                if (data[i]->rating < q.ratingMin || data[i]->rating > q.ratingMax){
                    continue;
                }
                if (!checkPrefix(q.titlePrefix, data[i]->title)){
                    continue;
                }
                if (!checkPrefix(q.genrePrefix, data[i]->genre)){
                    continue;
                }
                //still more to code...
                result.push_back(data[i]);
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

		bool hasGenre(){
 			return true;}  //in p-p-progress
		string toLower(string s){
			for(int i =0; i <s.size(); i++){
				s[i] = tolower(s[i]);
			}
			return s;
         }
		//quick sort
		//heap sort
		//merge sort
};