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
        MagicalContainer& operator=(MagicalContainer&&) noexcept = default;
        MagicalContainer& operator=(const MagicalContainer&) noexcept = default;
        MagicalContainer(MagicalContainer&& other) noexcept = default;
        MagicalContainer(const MagicalContainer& other) = default;

        class BaseIterator;
        class AscendingIterator;
        class SideCrossIterator;
        class PrimeIterator;

    };

    class MagicalContainer::BaseIterator {
    protected:
        int location = 0;
        vector<int*>* vec;
        vector<int*>::iterator iter;
        MagicalContainer* mc;

    public:
        BaseIterator(MagicalContainer&);

        BaseIterator& operator=(BaseIterator other);
        bool operator<(BaseIterator other) const;
        bool operator>(BaseIterator other) const;
        bool operator==(const BaseIterator &other) const;
        bool operator!=(const BaseIterator &other) const;
        BaseIterator& operator++(); //++iterator
        int operator*() const;

    };

    class MagicalContainer::AscendingIterator: public MagicalContainer::BaseIterator {
    public:
        AscendingIterator(MagicalContainer&);
        AscendingIterator& begin();
        AscendingIterator& end();
    };


    class MagicalContainer::SideCrossIterator: public MagicalContainer::BaseIterator {
    private:
        size_t s_index, e_index;
        bool get_s = true;
    public:
        SideCrossIterator(MagicalContainer&);
        SideCrossIterator& begin();
        SideCrossIterator& end();
        int operator*();
        SideCrossIterator &operator++();
        bool operator==(const SideCrossIterator &other) const;
    };


    class MagicalContainer::PrimeIterator: public MagicalContainer::BaseIterator {
    public:
        PrimeIterator(MagicalContainer&);
        PrimeIterator& begin();
        PrimeIterator& end();
    };

}

