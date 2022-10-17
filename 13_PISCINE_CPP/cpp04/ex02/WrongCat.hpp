/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 11:55:56 by minkim            #+#    #+#             */
/*   Updated: 2022/10/16 12:01:43 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRONGCAT_HPP
# define WRONGCAT_HPP

# include <iostream>
# include "WrongAnimal.hpp"

class WrongCat : public WrongAnimal {
 private:

 public:
    WrongCat();
    WrongCat(const WrongCat& obj);
    ~WrongCat();
    WrongCat& operator=(const WrongCat& obj);

    std::string getType(void) const;
    void makeSound(void) const;
};

#endif
