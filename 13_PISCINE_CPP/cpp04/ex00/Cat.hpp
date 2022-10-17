/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 19:00:16 by minkim            #+#    #+#             */
/*   Updated: 2022/10/16 16:28:26 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAT_HPP
# define CAT_HPP

# include <iostream>
# include "Animal.hpp"

class Cat : public Animal {
 private:

 public:
    Cat();
    Cat(const Cat& obj);
    ~Cat();
    Cat& operator=(const Cat& obj);

    void makeSound(void) const;
};

#endif
