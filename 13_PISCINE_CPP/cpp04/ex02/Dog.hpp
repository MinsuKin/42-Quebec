/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 19:00:35 by minkim            #+#    #+#             */
/*   Updated: 2022/10/16 17:23:35 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOG_HPP
# define DOG_HPP

# include <iostream>
# include "Animal.hpp"
# include "Brain.hpp"

class Dog : public Animal {
 private:
    Brain *brain;

 public:
    Dog();
    Dog(const Dog& obj);
    ~Dog();
    Dog& operator=(const Dog& obj);

    void makeSound(void) const;
    Brain *getBrain(void) const;
};

#endif
