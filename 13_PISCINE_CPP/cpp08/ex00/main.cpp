/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 18:29:55 by minkim            #+#    #+#             */
/*   Updated: 2022/10/27 21:37:56 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "easyfind.hpp"
#include <vector>
#include <deque>

int main()
{
    int fibo[] = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89 };
    std::vector<int> vec(fibo, fibo + sizeof(fibo) / sizeof(int));
    std::deque<int> deq(fibo, fibo + sizeof(fibo) / sizeof(int));

    try
    {
        int idx;

        std::vector<int>::iterator v_itr = easyfind(vec, 1);
        std::deque<int>::iterator d_itr = easyfind(deq, 89);

        idx = std::distance(vec.begin(), v_itr);
        std::cout << "Vector : Found " << *v_itr << ", " << idx + 1 << "nd element, vec[" << idx << "]" << std::endl;

        idx = d_itr - deq.begin(); // doesn't work for <list>
        std::cout << "Deque : Found " << *d_itr << ", " << idx + 1 << "th element, deq[" << idx << "]" << std::endl;
    
        easyfind(vec, 100); // fail to find
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}
