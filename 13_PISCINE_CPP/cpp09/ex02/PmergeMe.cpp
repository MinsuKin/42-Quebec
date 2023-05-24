/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:02:16 by minkim            #+#    #+#             */
/*   Updated: 2023/05/23 20:08:16 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

template <typename Container>
Container merge_insert_sort(const Container &input)
{
    if (input.size() <= 1)
    {
        return input;
    }

    // Use insertion sort if the size of the list is less than 6
    if (input.size() <= 5)
    {
        Container result = input;
        typename Container::iterator it;
        for (it = result.begin() + 1; it != result.end(); ++it)
        {
            int key = *it;
            typename Container::iterator j = it;
            while (j != result.begin() && *(j - 1) > key)
            {
                // Shift elements greater than the key to the right
                *j = *(j - 1);
                --j;
            }
            // Place the key at its correct position
            *j = key;
        }
        return result;
    }

    // Split the input into two halves
    Container left_half(input.begin(), input.begin() + input.size() / 2);
    Container right_half(input.begin() + input.size() / 2, input.end());

    // Recursively sort the two halves
    left_half = merge_insert_sort(left_half);
    right_half = merge_insert_sort(right_half);

    // Merge the sorted halves
    Container sorted;
    typename Container::iterator left_iter = left_half.begin();
    typename Container::iterator right_iter = right_half.begin();

    while (left_iter != left_half.end() || right_iter != right_half.end())
    {
        if (left_iter == left_half.end())
        {
            // If all elements from the left half have been merged, append the remaining elements from the right half
            sorted.insert(sorted.end(), right_iter, right_half.end());
            break;
        }
        else if (right_iter == right_half.end())
        {
            // If all elements from the right half have been merged, append the remaining elements from the left half
            sorted.insert(sorted.end(), left_iter, left_half.end());
            break;
        }
        else if (*left_iter <= *right_iter)
        {
            // If the current element from the left half is smaller or equal, append it to the sorted list
            sorted.push_back(*left_iter);
            ++left_iter;
        }
        else
        {
            // // If the current element from the right half is smaller, append it to the sorted list
            sorted.push_back(*right_iter);
            ++right_iter;
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

    std::cout << "Time to process a range of " << input.size() << " elements with " << container_name << " : " << std::fixed << std::setprecision(6) << duration << " μs" << std::endl;
}
