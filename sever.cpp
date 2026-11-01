#include "httplib.h"
#include "classes.hpp"
#include "loader.hpp"
#include "sever.h"
#include <chrono>
#include <iostream>

string escapeJson(const string &text) {  //so the titles dont break the json
    string result = "";
    for (int i =0; i < text.size(); i++){
        if (text[i] == '"' || text[i] == '\\') {
            result += '\\';
        }
        result += text[i];
    }
    return result;
}

//reads name = value fro url
float getFloat(const httplib::Request &req, const string &name, float fallback) {
    if (!req.has_param(name)) return fallback;
    try {
        return stof(req.get_param_value(name));
    }
    catch (...) {
        return fallback;
    }
}

string getText(const httplib::Request &req, const string &name, const string &fallback) {
    if (!req.has_param(name)) return fallback;
    return req.get_param_value(name);
}



int main() {
    cout << "testing" <<endl;
    vector<TVShow*> shows = loadShows("../data/title.basics.tsv","../data/title.ratings.tsv", "../data/title.episode.tsv", 2000,1000);
    cout << "Loaded " <<shows.size() << " shows" << endl;

    Database db;
    db.loadData(shows);

    httplib::Server server;
    server.set_mount_point("/", "../web");

    server.Get("/api/search", [&](const httplib::Request & req, httplib::Response &res) {
       Query q;
        q.ratingMin = getFloat(req, "ratingMin", 1.0);
        q.ratingMax = getFloat(req, "ratingMax", 10.0);
        q.titlePrefix = getText(req, "titlePrefix", "");
        q.genrePrefix = getText(req, "genre", "");
        q.sortBy = getText(req, "sortBy", "rating");
        q.sortAlgo = getText(req, "sortAlgo", "quick");
        q.descending = (getText(req, "descending", "false") == "true");
        //q.yearMin  q.yearMax  q.seasonsMax

        auto start = chrono::steady_clock::now();
        vector<TVShow*> results = db.applyQuery(q);
        auto end = chrono::steady_clock::now();
        double sortMs = chrono::duration<double,milli> (end-start).count();

        //makie the jason
        string json = "{\"sortMs\":" + to_string(sortMs) + ",\"total\":" + to_string(results.size()) + ",\"shows\":[";
        for (int i =0; i < results.size() && i < 25; i++) {  //top 25 results
            TVShow* s = results[i];
            if (i>0) json += ",";
            json += "{ \"title\":\"" + escapeJson(s->title)+ "\"," +
                "\"year\":" + to_string(s->year) + "," +
                    "\"rating\":"  + to_string(s->rating) + "," +
                        "\"seasons\":" + to_string(s->seasons) + "," +
                            "\"episodes\":" + to_string(s->episodes) + "," +
                                "\"genre\":\"" + escapeJson(s->genre)  + "\"}";
        }
        json += "]}";
        res.set_content(json, "application/json");
    });
    cout << "open browser test" <<endl;
    server.listen("localhost", 8080); 
}