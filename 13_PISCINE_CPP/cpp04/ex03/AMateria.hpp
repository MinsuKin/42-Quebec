/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 20:02:40 by minkim            #+#    #+#             */
/*   Updated: 2022/10/17 17:20:18 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AMATERIA_HPP
# define AMATERIA_HPP

# include <iostream>

class ICharacter;

class AMateria {
 protected:
    std::string type;

 public:
    AMateria();
    AMateria(std::string const &type);
    AMateria(const AMateria& obj);
    virtual ~AMateria();
    AMateria& operator=(const AMateria& obj);

    std::string const &getType() const;
    
    virtual AMateria* clone() const = 0;
    virtual void use(ICharacter& target);
};

#endif
