/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 19:00:27 by minkim            #+#    #+#             */
/*   Updated: 2022/10/16 12:18:26 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMAL_HPP
# define ANIMAL_HPP

# include <iostream>

class Animal {
 protected:
    std::string type;

 public:
    Animal();
    Animal(const Animal& obj);
    virtual ~Animal();
    Animal& operator=(const Animal& obj);

    std::string getType(void) const;
    virtual void makeSound(void) const;
};

#endif
