/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 12:51:36 by minkim            #+#    #+#             */
/*   Updated: 2022/10/17 17:23:39 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CURE_HPP
# define CURE_HPP

# include <iostream>
# include "AMateria.hpp"

class Cure : public AMateria {
 private:
    
 public:
    Cure();
    Cure(const Cure& obj);
    ~Cure();
    Cure& operator=(const Cure& obj);

    AMateria* clone() const;
    void use(ICharacter& target);
};

#endif
