/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:55:30 by minkim            #+#    #+#             */
/*   Updated: 2022/10/13 17:29:14 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLAPTRAP_HPP
# define CLAPTRAP_HPP

# include <iostream>

class ClapTrap {
private:
   std::string name;
   unsigned int hit_points;
   unsigned int energy_points;
   unsigned int attack_damage;

public:
   ClapTrap(void);
   ClapTrap(std::string name);
   ClapTrap(const ClapTrap& ct);
   ~ClapTrap();
   ClapTrap& operator=(const ClapTrap& ct);

   void attack(const std::string& target);
   void takeDamage(unsigned int amount);
   void beRepaired(unsigned int amount);
};

#endif
