/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:58:42 by minkim            #+#    #+#             */
/*   Updated: 2022/10/05 20:21:07 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Zombie.hpp"

int	main(void)
{
    Zombie zb("Zombie");
    Zombie *newzb = newZombie("newZombie");

    randomChump("random");
    zb.announce();
    newzb->announce();

    delete newzb;
    return (0);
}