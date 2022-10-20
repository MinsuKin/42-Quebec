/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 19:00:42 by minkim            #+#    #+#             */
/*   Updated: 2022/10/20 11:20:43 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main(void)
{	
	// 1st test
	const Animal* j = new Dog(); 
	const Animal* i = new Cat();

	delete j;
	delete i; 


	// // 2nd test
	// const Animal *meta[4]; 

    // meta[0] = new Dog();
    // meta[1] = new Dog();
    // meta[2] = new Cat();
    // meta[3] = new Cat();

	// for (size_t i = 0; i < 4; i++)
	// {
	// 	delete meta[i];
	// }


	// // 3rd test
	// const Dog *dog = new Dog();
	// const Cat *cat = new Cat();
	// const Dog *copy_dog = new Dog(*dog);
	// const Cat *copy_cat = new Cat(*cat);

	// dog->getBrain()->setIdea(0, "Woof woof"); 
	// cat->getBrain()->setIdea(0, "Meow Meow");
	
	// std::cout << dog << std::endl;
	// std::cout << copy_dog << std::endl;
	// std::cout << cat << std::endl;
	// std::cout << copy_cat << std::endl;

	// std::cout << dog->getBrain()->getIdea(0) << std::endl;
	// std::cout << copy_dog->getBrain()->getIdea(0) << std::endl;
	// std::cout << cat->getBrain()->getIdea(0) << std::endl;
	// std::cout << copy_cat->getBrain()->getIdea(0) << std::endl;

	// delete dog;
	// delete copy_dog;
	// delete cat;
	// delete copy_cat;

	return 0;
}
