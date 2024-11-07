#ifndef QUICKSORT_H
#define QUICKSORT_H
#include "ISorter.h"
#include <iostream>
template <typename T, typename Comparator>
class QuickSort : public ISorter<T, Comparator> {
public:
    void Sort(ShrdPtr<Sequence<T>> sequence, Comparator comp) override {
        size_t n = sequence->GetLength();
        if (n > 0) { // <-- Добавлена проверка
            quickSort(sequence, 0, n - 1, comp);
        }
    }

private:
    size_t partition(ShrdPtr<Sequence<T>> sequence, size_t low, size_t high, Comparator comp) {
        T pivot = sequence->Get(high);
        size_t i = low - 1;

        for (size_t j = low; j < high; ++j) {
            if (comp(sequence->Get(j), pivot)) {
                ++i;
                // Corrected bounds check:
                if (i <= high) { // i should be within [low, high]
                    std::swap(sequence->Get(i), sequence->Get(j));
                } else {
                    // Handle error (throw or return)
                    throw std::runtime_error("Error in partition: i out of range");

                }
            }
        }

        // Corrected bounds check:
        if (i + 1 <= high) { // i+1 should be within [low, high+1] (it might be high + 1 after the loop)

            std::swap(sequence->Get(i + 1), sequence->Get(high));

        } else {
            // Handle error (throw or return)
            throw std::runtime_error("Error in partition: i + 1 out of range");
        }

        return i + 1;
    }

    void quickSort(ShrdPtr<Sequence<T>> sequence, size_t low, size_t high, Comparator comp) {
        // std::cout << "quickSort: low = " << low << ", high = " << high << std::endl;
        if (low < high) {
            size_t pi = partition(sequence, low, high, comp);
            // std::cout << "partition returned: pi = " << pi << std::endl;
            if (low < pi - 1) {
                quickSort(sequence, low, pi, comp);
            }
            if (pi < high) {
                quickSort(sequence, pi +1, high, comp);
            }
        }
    }
};
#endif //QUICKSORT_H
