/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:02:16 by minkim            #+#    #+#             */
/*   Updated: 2023/05/19 17:24:31 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "PmergeMe.hpp"

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
            // Shift elements greater than the key to the right
            int key = *it;
            typename Container::iterator j = it - 1;
            while (j >= result.begin() && *j > key)
            {
                *(j + 1) = *j;
                --j;
            }
            // Place the key at its correct position
            *(j + 1) = key;
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
            // If the current element from the right half is smaller, find the correct position to insert it
            typename Container::iterator next_right = right_iter;
            while (next_right != right_half.end() && *next_right < *left_iter)
            {
                ++next_right;
            }
            // Append the range of elements from right_iter to next_right to the sorted list
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

    std::cout << "Time to process a range of " << input.size() << " elements with " << container_name << " : " << std::fixed << std::setprecision(6) << duration << " μs" << std::endl;
}
