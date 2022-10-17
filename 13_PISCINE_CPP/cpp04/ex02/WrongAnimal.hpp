/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 11:56:00 by minkim            #+#    #+#             */
/*   Updated: 2022/10/16 11:57:26 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRONGANIMAL_HPP
# define WRONGANIMAL_HPP

# include <iostream>

class WrongAnimal {
 protected:
    std::string type;

 public:
    WrongAnimal();
    WrongAnimal(const WrongAnimal& obj);
    ~WrongAnimal();
    WrongAnimal& operator=(const WrongAnimal& obj);

    std::string getType(void) const;
    void makeSound(void) const;
};

#endif
