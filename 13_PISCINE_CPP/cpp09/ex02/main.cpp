#include <iostream>
#include <iomanip>
#include <vector>
#include <deque>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <ctime>
#include <typeinfo>

template <typename Container>
Container merge_insert_sort(const Container &input)
{
    if (input.size() <= 1)
    {
        return input;
    }

    Container left_half(input.begin(), input.begin() + input.size() / 2);
    Container right_half(input.begin() + input.size() / 2, input.end());

    left_half = merge_insert_sort(left_half);
    right_half = merge_insert_sort(right_half);

    Container sorted;
    typename Container::iterator left_iter = left_half.begin();
    typename Container::iterator right_iter = right_half.begin();

    while (left_iter != left_half.end() || right_iter != right_half.end())
    {
        if (left_iter == left_half.end())
        {
            sorted.insert(sorted.end(), right_iter, right_half.end());
            break;
        }
        else if (right_iter == right_half.end())
        {
            sorted.insert(sorted.end(), left_iter, left_half.end());
            break;
        }
        else if (*left_iter <= *right_iter)
        {
            sorted.push_back(*left_iter);
            ++left_iter;
        }
        else
        {
            typename Container::iterator next_right = right_iter;
            while (next_right != right_half.end() && *next_right < *left_iter)
            {
                ++next_right;
            }
            sorted.insert(sorted.end(), right_iter, next_right);
            right_iter = next_right;
        }
    }

    return sorted;
}

template <typename Container>
void process_container(const Container &input, const std::string &container_name)
{
    std::clock_t start = std::clock();
    Container sorted = merge_insert_sort(input);
    double duration = static_cast<double>(std::clock() - start) / CLOCKS_PER_SEC;

    std::cout << "Time to process a range of " << input.size() << " elements with " << container_name
              << " : " << std::fixed << std::setprecision(6) << duration << " μs" << std::endl;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Error" << std::endl;
        return 1;
    }

    std::vector<int> input_vec;
    for (int i = 1; i < argc; ++i)
    {
        int value;
        std::istringstream iss(argv[i]);
        iss >> value;
        if (value <= 0)
        {
            std::cerr << "Error" << std::endl;
            return 1;
        }
        input_vec.push_back(value);
    }

    std::deque<int> input_deq(input_vec.begin(), input_vec.end());

    std::cout << "Before: ";
    std::copy(input_vec.begin(), input_vec.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    std::vector<int> sorted_vec = merge_insert_sort(input_vec);
    std::cout << "After: ";
    std::copy(sorted_vec.begin(), sorted_vec.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    process_container(input_vec, "std::vector");
    process_container(input_deq, "std::deque");

    return 0;
}
