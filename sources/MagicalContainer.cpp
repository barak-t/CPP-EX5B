#include "MagicalContainer.hpp"
#include <math.h>
#include <iostream>
using namespace std;

namespace ariel {

    bool MagicalContainer::is_prime(int num) {
        if(num <= 1) {
            return false;
        }
        for(int divider = 2; divider <= sqrt(num); divider++) {
            if(num % divider == 0) {
                return false;
            }
        }
        return true;
    }

    void MagicalContainer::add_to_sorted(int* num_ptr) {
        if(this->sorted_elements.empty()){
            this->sorted_elements.push_back(num_ptr);
        } else if(*(this->sorted_elements.at(0)) >= *(num_ptr)){
            this->sorted_elements.insert(this->sorted_elements.begin(), num_ptr);
        } else if(this->sorted_elements.size() == 1){
            this->sorted_elements.push_back(num_ptr);
        } else {
            size_t i;
            for(i=0; i < this->sorted_elements.size()-1; i++) {
                if(*(num_ptr) >= *(this->sorted_elements.at(i)) && *(num_ptr) <= *(this->sorted_elements.at(i+1))) {
                    break;
                }
            }

            this->sorted_elements.insert(this->sorted_elements.begin() + (int) i+1, num_ptr);
        }
    }

    MagicalContainer::MagicalContainer() {}

    MagicalContainer::~MagicalContainer() {
        for(size_t i=0; i<this->elements.size(); i++){
            free(this->elements.at(i));
        }
    }

    int MagicalContainer::size() {
        return this->elements.size();
    }
    bool comparePtrToInt(int* a, int* b) { return (*a < *b); }

    void MagicalContainer::addElement(int num) {
        int* num_ptr = new int(num);

        this->elements.push_back(num_ptr);
        this->add_to_sorted(num_ptr);
        if (this->is_prime(num)) {
            this->prime_elements.push_back(num_ptr);
        }
    }

    void MagicalContainer::removeElement(int num) {
        int* num_ptr = nullptr;
        for(size_t i=0; i< this->elements.size(); i++){
            if(*(this->elements.at(i)) == num){
                num_ptr = this->elements.at(i);
                break;
            }
        }
        if(num_ptr != nullptr){
            this->elements.erase(remove(this->elements.begin(), this->elements.end(), num_ptr), this->elements.end());
            this->sorted_elements.erase(remove(this->sorted_elements.begin(), this->sorted_elements.end(), num_ptr), this->sorted_elements.end());
            this->prime_elements.erase(remove(this->prime_elements.begin(), this->prime_elements.end(), num_ptr), this->prime_elements.end());
            free(num_ptr);
        } else {
            throw runtime_error("element is not exist");
        }
    }


    // BaseIterator
    MagicalContainer::BaseIterator::BaseIterator(MagicalContainer& magicalContainer): mc(&magicalContainer) {}
    int MagicalContainer::BaseIterator::operator*() const {
        return *(this->iter.operator*());
    }
    MagicalContainer::BaseIterator &MagicalContainer::BaseIterator::operator=(BaseIterator other) {
        if (this != &other) {
            throw runtime_error("different iterators");
        }
        this->vec = other.vec;
        this->location = other.location;
        this->iter = other.iter;
        this->mc = other.mc;
        return *this;
    }
    MagicalContainer::BaseIterator &MagicalContainer::BaseIterator::operator++() {
        if(this->location >= this->vec->size()) {
            throw runtime_error("Out of bounds");
        }
        this->iter.operator++();
        this->location++;
        return *this;
    }
    bool MagicalContainer::BaseIterator::operator==(const BaseIterator &other) const {
        if (this->mc != other.mc) {
            throw runtime_error("different MagicalContainer");
        }

        return this->vec == other.vec && this->location == other.location;
    }
    bool MagicalContainer::BaseIterator::operator!=(const BaseIterator &other) const {
        return !(this->operator==(other));
    }
    bool MagicalContainer::BaseIterator::operator<(BaseIterator other) const {
        return this->location < other.location;
    }
    bool MagicalContainer::BaseIterator::operator>(BaseIterator other) const {
        return this->location > other.location;
    }

    /* AscendingIterator */
    MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer& magicalContainer): MagicalContainer::BaseIterator(magicalContainer) {
        this->vec = &this->mc->sorted_elements;
        this->begin();
    }
    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::begin() {
        this->iter = this->vec->begin();
        this->location = 0;
        return *this;
    }
    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::end() {
        this->iter = this->vec->end();
        this->location = this->vec->size();
        return *this;
    }

    /* SideCrossIterator */
    MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer& magicalContainer): MagicalContainer::BaseIterator(magicalContainer) {
        this->vec = &this->mc->elements;
        this->begin();
    }
    int MagicalContainer::SideCrossIterator::operator*() {
        int value;
        if (this->get_s) {
            value = *(this->vec->at(this->s_index));
        } else {
            value = *(this->vec->at(this->e_index - 1));
        }
        return value;
    }
    MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator++() {
        if(this->s_index > this->e_index){
            throw runtime_error("Out of bounds");
        }
        if(this->get_s) {
            this->s_index++;
        } else {
            this->e_index--;
        }
        this->get_s = !this->get_s;
        this->location++;

        if(this->s_index >= this->e_index) {
            this->s_index = this->vec->size();
            this->e_index = 0;
        }
        return *this;
    }
    bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator &other) const {
        if (this->mc != other.mc) {
            throw runtime_error("different MagicalContainer");
        }

        return this->mc == other.mc && this->s_index == other.s_index && this->e_index == other.e_index;
    }

    MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::begin() {
        this->location = 0;

        this->s_index = 0;
        this->e_index = (size_t) this->vec->size();
        this->get_s = true;

        return *this;
    }
    MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::end() {
        this->s_index = this->vec->size();
        this->e_index = 0;

        return *this;
    }


    /* PrimeIterator */
    MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer& magicalContainer): MagicalContainer::BaseIterator(magicalContainer) {
        this->vec = &this->mc->prime_elements;
        this->begin();
    }
    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::begin() {
        this->iter = this->vec->begin();
        this->location = 0;
        return *this;
    }
    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::end() {
        this->iter = this->vec->end();
        this->location = this->vec->size();

        return *this;
    }
}
