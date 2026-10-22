#include <vector>

#pragma once
using namespace std;

template <typename T>
vector<T> heapSort(const vector<T>& data, bool (*comparison)(const T&, const T&)){
    
}

template <typename T>
vector<T> mergeSort(const vector<T>& data, bool (*comparison)(const T&, const T&)){
    if (data.size() <= 1){
        return data;
    }
    int midpoint = data.size() / 2;
    vector<T> result;
    vector<T> vec1 = mergeSort(vector<T>(data.begin(), data.begin() + midpoint + data.size() % 2), comparison);
    vector<T> vec2 = mergeSort(vector<T>(data.rbegin(), data.rbegin() + midpoint), comparison);
    while (vec1.size() > 0 && vec2.size() > 0){
        if (comparison(vec1[0], vec2[0])){
            result.push_back(vec1[0]);
            vec1.erase(vec1.begin());
        }
        else{
            result.push_back(vec2[0]);
            vec2.erase(vec2.begin());
        }
    }
    if (vec1.size() == 0){
        result.insert(result.end(), vec2.begin(), vec2.end());
    }
    if (vec2.size() == 0){
        result.insert(result.end(), vec1.begin(), vec1.end());
    }
    return result;
}

template <typename T>
vector<T> quickSort(const vector<T>& data, bool (*comparison)(const T&, const T&)){
    
}