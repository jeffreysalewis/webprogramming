#pragma once

#include <string>
#include <list>
#include <vector>
#include <algorithm>
#include "HashmapInterface.h"

using namespace std;
const size_t INITIAL_CAPACITY = 10;
const double MAX_LOAD = 0.8;

template <class T>
class Hashmap : public HashmapInterface {
private:
    vector<list<T>>* data = new vector<list<T>>(INITIAL_CAPACITY);
    vector<list<string>>* keys = new vector<list<string>>(INITIAL_CAPACITY);
    size_t capacity = INITIAL_CAPACITY;
    size_t m_size = 0;
    // put any private data members or methods here
    size_t hashfun(T & val) {
        unsigned char * itr = (unsigned char *) &val;
        size_t sum = 0;
        for(size_t i = 0; i < sizeof(val); i++) {
            sum = sum * 31 + *itr;
            itr++;
        }
        return sum;
    }

    void grow() {
        vector<list<T>> * old = data;
        size_t oldsize = capacity;
        capacity = capacity * 2 - 1;
        data = new vector<list<T>>(capacity);
        keys = new vector<list<string>>(capacity);
        m_size = 0;
        for(int a = 0; a < oldsize; a++) {
            if(old[a].size != 0) {
                for(T val : old[a]) {
                    insert(val);
                }
            }
        }
        delete old;
    }

public:
    Hashmap() {
        // implement your constructor here
    }

    ~Hashmap() override {
        delete data;
        // implement your destructor here
    }

    void insert(std::string key, int value) override {
        size_t hashcode = hashfun(key);
        size_t index = hashcode % capacity;
        if(data->at(index)->size() == 0) {
            keys->at(index).push_back(key);
            data->at(index).push_back(value);
        } else {
            if(count(keys->at(index).begin(), keys->at(index).end(), value)) {
                
            }
//            for(string k: data->at(index).begin()) {
//
//            }
        }
        data[index].push_back(value);
        m_size++;
        if(static_cast<double>(m_size / capacity) > MAX_LOAD) {
            grow();
        }
        return;
        // implement insert here
    }

    bool contains(const std::string &key) const override {
        size_t index = hashfun(key) % capacity;
        if(data[index].size() != 0) {
            if(count(data[index].begin(), data[index].end(), key) != 0) {
                return true;
            }
        }
        return false;
        // implement contains here
    }

    int get(const std::string &key) const override {
        // implement get here
    }

    int &operator[](const std::string& key) override {
        // implement operator[] here
    }

    bool remove(const std::string &key) override {
        if(!contains(key)) {
            return false;
        }
        size_t index = hashfun(key) % capacity;
        data[index]. remove(key);
        m_size--;
        return true;
        // implement remove here
    }

    void clear() override {
        delete [] data;
        // implement clear here
    }
    
    int numBuckets() const override {
        // implement numBuckets here
    }

    int size() const override {
        return m_size;
        // implement size here
    }
};
