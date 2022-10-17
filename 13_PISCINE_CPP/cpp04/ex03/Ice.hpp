/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 12:51:50 by minkim            #+#    #+#             */
/*   Updated: 2022/10/17 17:23:57 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ICE_HPP
# define ICE_HPP

# include <iostream>
# include "AMateria.hpp"

class Ice : public AMateria {
 private:

 public:
    Ice();
    Ice(const Ice& obj);
    ~Ice();
    Ice& operator=(const Ice& obj);

    AMateria* clone() const;
    void use(ICharacter& target);
};

#endif
