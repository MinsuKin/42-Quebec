/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 18:29:33 by minkim            #+#    #+#             */
/*   Updated: 2022/10/15 13:25:06 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCAVTRAP_HPP
# define SCAVTRAP_HPP

# include <iostream>
# include "ClapTrap.hpp"

# define SCAVTRAP_ENERGY_POINTS 50

class ScavTrap : virtual public ClapTrap {
private:

public:
    ScavTrap();
    ScavTrap(std::string name);
    ScavTrap(const ScavTrap& st);
    ScavTrap& operator=(const ScavTrap& st);
    ~ScavTrap();

    void attack(const std::string& target);
    void guardGate();
};

#endif
