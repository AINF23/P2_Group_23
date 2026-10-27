//
// Created by ivass on 10/20/2026.
//

#include "classes.hpp"
#include "loader.hpp"
#include <iostream>

void printShow(const TVShow* s) {
    cout << s->title << " (" << s->year << ")\n"
         << "  Genres: " << s->genre << "\n"
         << "  Rating: " << s->rating << "\n"
         << "  Seasons: " << s->seasons << ", Episodes: " << s->episodes << "\n";
}

int main() {
    // Loading shows, change last two parameters for minYear and minVotes
    vector<TVShow*> shows = loadShows("../data/title.basics.tsv",
                                      "../data/title.ratings.tsv",
                                      "../data/title.episode.tsv",
                                      2000, 1000);

    //Example of loading every show above 8.5 rating
    /*
    Database db;
    db.loadData(shows);

    Query q;
    q.ratingMin = 8.5;
    q.ratingMax = 10;

    vector<TVShow*> top = db.applyQuery(q);
    for (TVShow* s : top) printShow(s);
    */

    //Looking for Loki
    for (TVShow* s : shows) {
        if (s->title == "Loki") printShow(s);
    }

}