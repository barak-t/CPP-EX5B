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
            this->sorted_elements.insert(this->sorted_elements.cbegin(), num_ptr);
        } else if(this->sorted_elements.size() == 1){
            this->sorted_elements.push_back(num_ptr);
        } else {
            for(size_t i=0; i < this->sorted_elements.size()-1; i++) {
                if(*(num_ptr) >= *(this->sorted_elements.at(i)) && *(num_ptr) <= *(this->sorted_elements.at(i+1))) {
                    this->sorted_elements.insert(this->sorted_elements.begin() + (int) i, num_ptr);
                    return;
                }
            }
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
//        this->sorted_elements.insert(num);
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
        cout << "size:" << this->elements.size() << endl;
        if(num_ptr != nullptr){
            this->elements.erase(remove(this->elements.begin(), this->elements.end(), num_ptr), this->elements.end());
            this->sorted_elements.erase(remove(this->sorted_elements.begin(), this->sorted_elements.end(), num_ptr), this->sorted_elements.end());
//        this->sorted_elements.erase(num_ptr);
            this->prime_elements.erase(remove(this->prime_elements.begin(), this->prime_elements.end(), num_ptr), this->prime_elements.end());
            free(num_ptr);
            cout << "after free size:" << this->elements.size() << endl;

        } else {
            throw runtime_error("element is not exist");
        }
    }


    /* AscendingIterator */
    MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer& magicalContainer): mc(magicalContainer) {}
    int MagicalContainer::AscendingIterator::operator*() const {
        return *(*(this->it));
    }
    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator++() {
        this->it.operator++();
        this->location++;
        return *this;
    }
    bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator &it) const {
        return this->it == it.it;
    }
    bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator &it) const {
        return !this->operator==(it);
    }
    bool MagicalContainer::AscendingIterator::operator<(AscendingIterator other) const {
        return this->operator*() < other.operator*();
    }
    bool MagicalContainer::AscendingIterator::operator>(AscendingIterator other) const {
        return this->operator*() > other.operator*();
    }
    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::begin() {
        this->it = this->mc.sorted_elements.begin();
        return *this;
    }
    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::end() {
        this->it = this->mc.sorted_elements.end();
        return *this;
    }

    /* SideCrossIterator */
    MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer& magicalContainer): mc(magicalContainer) {}
    int MagicalContainer::SideCrossIterator::operator*() const {
        return 1;
    }
    MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator++() {
        this->location++;
        return *this;
    }
    bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator &it) const {
        return true;
    }
    bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator &it) const {
        return !this->operator==(it);
    }
    bool MagicalContainer::SideCrossIterator::operator<(SideCrossIterator other) const {
        return this->operator*() < other.operator*();
    }
    bool MagicalContainer::SideCrossIterator::operator>(SideCrossIterator other) const {
        return this->operator*() > other.operator*();
    }
    MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::begin() {
        return *this;
    }
    MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::end() {
        return *this;
    }


    /* PrimeIterator */
    MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer& magicalContainer): mc(magicalContainer) {}
    int MagicalContainer::PrimeIterator::operator*() const {
        return *(*(this->it));
    }
    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++() {
        this->it.operator++();
        this->location++;
        return *this;
    }
    bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator &it) const {
        return this->it == it.it;
    }
    bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator &it) const {
        return !this->operator==(it);
    }
    bool MagicalContainer::PrimeIterator::operator<(PrimeIterator other) const {
        return this->operator*() < other.operator*();
    }
    bool MagicalContainer::PrimeIterator::operator>(PrimeIterator other) const {
        return this->operator*() > other.operator*();
    }
    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::begin() {
        this->it = this->mc.prime_elements.begin();
        return *this;
    }
    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::end() {
        this->it = this->mc.prime_elements.end();
        return *this;
    }


}
