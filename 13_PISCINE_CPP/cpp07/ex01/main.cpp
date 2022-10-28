/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:14:28 by minkim            #+#    #+#             */
/*   Updated: 2022/10/26 18:28:58 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iter.hpp"

int main(void)
{
    int fibonacci[] = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89 };
    std::string last_name[] = { "Kim", "Lee", "Park", "Choi", "Han", "Son" };

    // iter<int>(fibonacci, 12, ftPrint<int>);
    iter(fibonacci, 12, ftPrint); // skipping '<type>' is allowed
    std::cout << std::endl;

    iter(last_name, 6, ftPrint);
    std::cout << std::endl;

    return 0;
}
