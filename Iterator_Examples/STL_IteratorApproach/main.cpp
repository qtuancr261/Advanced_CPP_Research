/*
 * Author: tuantq3
 * File: %{Cpp:License:FileName}
 *
 * Created on 26/4/2020
 */
#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>
#include "NumericRange.h"

template <typename Iter>
void testSwapMyITer(Iter A, Iter B) {
    //     tmp = *A; what's tmp ? we dont know until an instance of the template is created
    // value_type alias must be declared in Iter class
    typename Iter::value_type tmp = *A;
    // This solution has limitations
    // STL algorithms work with pointers as well as iterators
    // Iter may be int*, or event ClassA* , the compiler wont understand what's int*::value_type, ClassA*::value_type
    // iterator_traits is a perfect template for solving this problem
    *A = *B;
    *B = tmp;
}
/* -> STL Approach with iterator_traits
 * -> definiton for type alias only
 * template <class _Iterator>
 * struct iterator_traits
 * typedef typename _Iterator::iterator_category iterator_category
 * typedef typename _Iterator::value_type        value_type
 * typedef typename _Iterator::difference_type   difference_type
 * typedef typename _Iterator::pointer           pointer
 * typedef typename _Iterator::reference         reference
 * -> mapping between the type alias names in this template
 * and the types used to create an iterator template instance
 *
 * -> difference_type: value result from the difference between two iterators of type _Iterator
 * -> iterator_category: one of the iterator category tag class
 * type: input_iterator_tag, output_iterator_tag,forward_iterator_tag, bidirectional_iterator_tag,
 * or random_access_iterator_tag
 * -> An iterator class that conforms to the STL requirements must def all these type alias
 * although for the output iters, all aliases except the iterator_category alias can be def as void
 * -> std::iterator_traits<std::string>::value_type is std::string::value_type
 */
template <typename Iter>
void testSwapSTLIter(Iter A, Iter B) {
    typename std::iterator_traits<Iter>::value_type tmp = *A;
    *A = *B;
    *B = tmp;
}
// The iterator template
class MyIter : public std::iterator<std::random_access_iterator_tag, int> {
public:
    MyIter() = default;
};
int main() {
    using namespace std::rel_ops;

    std::vector<std::string> strS{"tuan", "thieu", "2020", "STL"};
    testSwapSTLIter(strS.begin(), strS.begin() + 2);  // type deduced
    testSwapSTLIter(std::begin(strS), std::begin(strS) + 2);
    NumericRange<int> range{10, 5, 20};
    NumericIterator<int> first{range.begin()};
    NumericIterator<int> last{range.end()};
    // output the range
    std::copy(first, last, std::ostream_iterator<int>(std::cout, "-"));
    // cal sum
    std::cout << std::endl << "Sum: " << std::accumulate(first, last, 0);
    // init container from range
    NumericRange<double> rangeD{1000.0, 0.5, 10};
    std::vector<double> numD{rangeD.begin(), rangeD.end()};
    for (auto num : numD) {
        std::cout << "D: " << num << " - ";
    }

    return 0;
}
