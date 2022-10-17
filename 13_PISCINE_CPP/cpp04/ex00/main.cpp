/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 19:00:42 by minkim            #+#    #+#             */
/*   Updated: 2022/10/16 17:39:44 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main(void)
{// Class before 'const' -> all member functions must have 'const' after function name
    const Animal* meta = new Animal();
    const Animal* j = new Dog();
    const Animal* i = new Cat();
    const WrongAnimal* wrong = new WrongCat(); // 'virtual' not used

    std::cout << j->getType() << " " << std::endl;
    std::cout << i->getType() << " " << std::endl;
    // std::cout << meta->getType() << " " << std::endl;

    i->makeSound();
    j->makeSound();
    meta->makeSound();
    
    std::cout << wrong->getType() << " " << std::endl; // Does not use WrongCat's function
    wrong->makeSound(); // Does not use WrongCat's function

    delete meta;
    delete j;
    delete i;
    delete wrong; // WrongCat destructor does not get called

    return 0;
}
