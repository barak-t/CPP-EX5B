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
        char type;
        int location = 0;
        vector<int*>* vec;
        vector<int*>::iterator iter;
        MagicalContainer* mc;
        void check_same_container(BaseIterator other) const;
        void check_same_type(BaseIterator other) const;

    public:
        BaseIterator(MagicalContainer&, char type);
        ~BaseIterator() = default;

        BaseIterator& operator=(BaseIterator other);
        bool operator<(BaseIterator other) const;
        bool operator>(BaseIterator other) const;
        bool operator==(const BaseIterator &other) const;
        bool operator!=(const BaseIterator &other) const;
        BaseIterator& operator++(); //++iterator
        int operator*() const;
        BaseIterator& begin();
        BaseIterator& end();

    };

    class MagicalContainer::AscendingIterator: public MagicalContainer::BaseIterator {
    public:
        AscendingIterator(MagicalContainer&);
    };

    class MagicalContainer::PrimeIterator: public MagicalContainer::BaseIterator {
    public:
        PrimeIterator(MagicalContainer&);
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
}

