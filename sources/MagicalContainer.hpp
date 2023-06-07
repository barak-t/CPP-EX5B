#include <vector>
#include <set>

using namespace std;
namespace ariel {

    class MagicalContainer {

    private:
        vector<int*> elements;
        vector<int*> sorted_elements;
        vector<int*> prime_elements;

        bool is_prime(int num);
        void add_to_sorted(int*);

    public:
        MagicalContainer();
        void addElement(int);
        int size();
        void removeElement(int);
        ~MagicalContainer();

        class BaseIterator;
        class AscendingIterator;
        class SideCrossIterator;
        class PrimeIterator;

    };

    class MagicalContainer::BaseIterator {
    protected:
        int location = 0;
        vector<int*>::iterator it;
        MagicalContainer& mc;

    public:
        BaseIterator(MagicalContainer&);

        bool operator<(BaseIterator other) const;
        bool operator>(BaseIterator other) const;
        bool operator==(const BaseIterator &it) const;
        bool operator!=(const BaseIterator &it) const;
        BaseIterator& operator++(); //++iterator
        BaseIterator& operator++(int); //iterator++
        int operator*() const;
        BaseIterator& begin();
        BaseIterator& end();

    };


    class MagicalContainer::AscendingIterator: public BaseIterator{

    private:
        int location = 0;
        vector<int*>::iterator it;
        MagicalContainer& mc;

    public:
        AscendingIterator(MagicalContainer&);

        bool operator<(AscendingIterator other) const;
        bool operator>(AscendingIterator other) const;
        bool operator==(const AscendingIterator &it) const;
        bool operator!=(const AscendingIterator &it) const;
        AscendingIterator& operator++(); //++iterator
        AscendingIterator& operator++(int); //iterator++
        int operator*() const;
        AscendingIterator& begin();
        AscendingIterator& end();

    };


    class MagicalContainer::SideCrossIterator {

    private:
        int location = 0;
        MagicalContainer& mc;

    public:
        SideCrossIterator(MagicalContainer&);

        bool operator<(SideCrossIterator other) const;
        bool operator>(SideCrossIterator other) const;
        bool operator==(const SideCrossIterator &it) const;
        bool operator!=(const SideCrossIterator &it) const;
        SideCrossIterator& operator++(); //++iterator
        SideCrossIterator& operator++(int); //iterator++
        int operator*() const;
        SideCrossIterator& begin();
        SideCrossIterator& end();
    };


    class MagicalContainer::PrimeIterator {

    private:
        int location = 0;
        vector<int*>::iterator it;
        MagicalContainer& mc;

    public:
        PrimeIterator(MagicalContainer&);

        bool operator<(PrimeIterator other) const;
        bool operator>(PrimeIterator other) const;
        bool operator==(const PrimeIterator &it) const;
        bool operator!=(const PrimeIterator &it) const;
        PrimeIterator& operator++(); //++iterator
        int operator*() const;
        PrimeIterator& begin();
        PrimeIterator& end();
    };

}

