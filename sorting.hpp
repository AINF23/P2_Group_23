#include <vector>

#pragma once
using namespace std;

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
    vector<T> items = data;

}

//heap sort
template <typename T>
void heapify(vector<T> &v, int heapSize, int parent, bool(*comparison)(const T&, const T&)){
    int largest = parent;
    int leftChild = 2*parent+1;
    int rightChild = 2*parent +2;
    if (leftChild < heapSize && comparison(v[largest], v[leftChild])) {
        largest = leftChild;
    }
    if (rightChild < heapSize && comparison(v[largest], v[rightChild])) {
       largest = rightChild;
   }
    if (largest != parent) {
        swap(v[parent], v[largest]);
        heapify(v,heapSize, largest, comparison);
    }
}

template <typename T>
vector<T> heapSort(const vector<T> &data, bool (*comparison)(const T&, const T&)) {
    vector<T> result = data;
    int n = result.size();
    for (int i =n/2-1; i >= 0; i--) {
        heapify(result, n, i, comparison);
    }
    for (int end = n-1; end >0; end--) {
        swap(result[0], result[end]);
        heapify(result,end,0,comparison);
    }
    return result;
}