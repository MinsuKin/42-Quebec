/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 12:27:55 by minkim            #+#    #+#             */
/*   Updated: 2022/10/08 15:10:06 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANB_HPP
# define HUMANB_HPP

#include <iostream>
#include "Weapon.hpp"

class HumanB
{
private:
    Weapon *wp;
    std::string name;
    
public:
    HumanB(std::string name);
    ~HumanB(void);

    void attack(void) const;
    void setWeapon(Weapon &wp);
};

#endif
