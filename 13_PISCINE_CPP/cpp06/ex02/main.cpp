/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 18:30:51 by minkim            #+#    #+#             */
/*   Updated: 2022/10/24 19:29:03 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"

int main(void)
{
    Base *ptr = generate();
    identify(ptr);
    delete ptr;

    Base *ref = generate();
    identify(*ref);
    delete ref;
    
    return 0;
}