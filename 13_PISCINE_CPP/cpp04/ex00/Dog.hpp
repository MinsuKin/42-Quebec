/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 19:00:35 by minkim            #+#    #+#             */
/*   Updated: 2022/10/16 16:28:29 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOG_HPP
# define DOG_HPP

# include <iostream>
# include "Animal.hpp"

class Dog : public Animal {
 private:

 public:
    Dog();
    Dog(const Dog& obj);
    ~Dog();
    Dog& operator=(const Dog& obj);

    void makeSound(void) const;
};

#endif
