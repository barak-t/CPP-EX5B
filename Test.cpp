#include "doctest.h"
#include <numeric>
#include <vector>
#include <random>
#include <iostream>

#include "sources/MagicalContainer.hpp"

using namespace std;
using namespace ariel;

TEST_CASE("test MagicalContainer operations") {
    MagicalContainer mc;
    mc.addElement(17);
    mc.addElement(2);
    mc.addElement(25);
    mc.addElement(9);
    mc.addElement(3);
    CHECK_EQ(mc.size(), 5);

    mc.removeElement(9);
    CHECK_EQ(mc.size(), 4);
    MagicalContainer::AscendingIterator ascIter(mc);
    for (auto it = ascIter.begin(); it != ascIter.end(); ++it) {
        CHECK_NE(9, *it);
    }

    mc.removeElement(25);
    CHECK_EQ(mc.size(), 3);

//    mc.removeElement(7); // not exists
    CHECK_EQ(mc.size(), 3);
}

TEST_CASE("test AscendingIterator sort") {
    // create shuffle vector with 1000 numbers
    vector<int> numbers(1000);
    iota(numbers.begin(), numbers.end(), 1);
    CHECK_EQ(numbers.size(), 1000);
    auto rng = default_random_engine {};
    shuffle(begin(numbers), end(numbers), rng);

    // Add the numbers to the MagicalContainer
    MagicalContainer mc;
    while(!numbers.empty()) {
        mc.addElement(numbers.back());
        numbers.pop_back();
    }
    CHECK_EQ(mc.size(), 1000);
    MagicalContainer::AscendingIterator ascIter(mc);
    int i = 1;
    for (auto it = ascIter.begin(); it != ascIter.end(); ++it) {
        CHECK_EQ(i++, *it);
    }
}

TEST_CASE("test SideCrossIterator") {
    // create vector with 100 numbers
    vector<int> numbers(100);
    iota(numbers.begin(), numbers.end(), 1);
    CHECK_EQ(numbers.size(), 100);

    // Add the numbers to the MagicalContainer
    MagicalContainer mc;
    for(size_t i=0; i < numbers.size(); i++) {
        mc.addElement(numbers.at(i));
    }
    CHECK_EQ(mc.size(), 100);

    MagicalContainer::SideCrossIterator crossIter(mc);
    int start = 1;
    int end = 100;
    bool first = true;
    for (auto it = crossIter.begin(); it != crossIter.end(); ++it) {
        if (first == true) {
            CHECK_EQ(start++, *it);
        } else {
            CHECK_EQ(end--, *it);
        }
        first = !first;
    }
}

TEST_CASE("test PrimeIterator") {
    // create vector with 20 numbers
    vector<int> numbers(20);
    iota(numbers.begin(), numbers.end(), 1);
    CHECK_EQ(numbers.size(), 20);


    // Add the numbers to the MagicalContainer
    MagicalContainer mc;
    for(size_t i=0; i < numbers.size(); i++) {
        mc.addElement(numbers.at(i));
    }
    CHECK_EQ(mc.size(), 20);
    mc.removeElement(5);
    CHECK_EQ(mc.size(), 19);

    vector<int> prime_nums{2, 3, 7, 11, 13, 17, 19}; // except 5
    MagicalContainer::PrimeIterator primeIter(mc);
    size_t prime_i = 0;
    for (auto it = primeIter.begin(); it != primeIter.end(); ++it) {
        CHECK_EQ(*it, prime_nums.at(prime_i++));
    }
}


TEST_CASE("test Iterators operators") {
    // create vector with 100 numbers
    vector<int> numbers(100);
    iota(numbers.begin(), numbers.end(), 1);
    CHECK_EQ(numbers.size(), 100);

    // Add the numbers to the MagicalContainer
    MagicalContainer mc;
    while(!numbers.empty()) {
        mc.addElement(numbers.back());
        numbers.pop_back();
    }
    CHECK_EQ(mc.size(), 100);
}
