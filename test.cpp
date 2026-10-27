#include "classes.hpp"
#include "sorting.hpp"
#include <iostream>

int main(){
    Database db;

    TVShow* show1 = new TVShow;
    show1->rating = 5.7;
    show1->title = "Amazing Horse";
    show1->genre = "romance";

    TVShow* show2 = new TVShow;
    show2->rating = 6.4;
    show2->title = "Theoretical Physics";
    show2->genre = "scifi";

    TVShow* show3 = new TVShow;
    show3->rating = 9.5;
    show3->title = "Breaking Bad";
    show3->genre = "drama";

    vector<TVShow*> data = {show2, show1, show3};
    db.loadData(data);
    Query q;
    q.ratingMin = 6;
    q.ratingMax = 5;
    q.titlePrefix = "";

    vector<TVShow*> filteredData = db.applyQuery(q);
    for (int i = 0; i < filteredData.size(); i++){
        if (i != filteredData.size() - 1){
            cout << filteredData[i]->title << ", ";
        }
        else{
            cout << filteredData[i]->title << endl;
        }
    }

    vector<int> unsorted = {7, 4, 3, 9, 16, 32, 2};
    bool (*compare)(const int&, const int&) = [](const int &a, const int& b){return a < b;};
    vector<int> sorted = mergeSort(unsorted, compare);

    for (int i = 0; i < sorted.size(); i++){
        if (i != sorted.size() - 1){
            cout << sorted[i] << ", ";
        }
        else{
            cout << sorted[i] << endl;
        }
    }
}