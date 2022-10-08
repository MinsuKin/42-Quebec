/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 12:26:53 by minkim            #+#    #+#             */
/*   Updated: 2022/10/08 15:10:26 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEAPON_HPP
# define WEAPON_HPP

#include <iostream>

class Weapon
{
private:
    std::string type;

public:
    Weapon(std::string type);
    ~Weapon(void);

    // https://love-every-moment.tistory.com/91
    // 'const' after a function name -> Only READ variables in class, does not change their values.
    // 'const' before a function name -> Make the return value as a literal, cannot change.
    const std::string &getType(void) const;
    void setType(std::string type);
};

#endif
