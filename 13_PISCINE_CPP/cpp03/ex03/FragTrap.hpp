/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 19:56:50 by minkim            #+#    #+#             */
/*   Updated: 2022/10/14 21:08:36 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRAGTRAP_HPP
# define FRAGTRAP_HPP

# include <iostream>
# include "ClapTrap.hpp"

class FragTrap : virtual public ClapTrap {
private:

public:
    FragTrap();
    FragTrap(std::string name);
    FragTrap(const FragTrap& ft);
    ~FragTrap();
    FragTrap& operator=(const FragTrap& ft);

    void highFivesGuys(void);
};

#endif
