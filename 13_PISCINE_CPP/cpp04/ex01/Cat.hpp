/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 19:00:16 by minkim            #+#    #+#             */
/*   Updated: 2022/10/16 17:23:41 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAT_HPP
# define CAT_HPP

# include <iostream>
# include "Animal.hpp"
# include "Brain.hpp"

class Cat : public Animal {
 private:
    Brain *brain;

 public:
    Cat();
    Cat(const Cat& obj);
    ~Cat();
    Cat& operator=(const Cat& obj);

    void makeSound(void) const;
    Brain *getBrain(void) const;
};

#endif
