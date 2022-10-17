/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 20:02:44 by minkim            #+#    #+#             */
/*   Updated: 2022/10/17 18:00:03 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AMateria.hpp"
#include "Ice.hpp"
#include "Cure.hpp"
#include "Character.hpp"
#include "MateriaSource.hpp"

int main(void)
{
    // 1st test
    IMateriaSource* src = new MateriaSource();
    src->learnMateria(new Ice());
    src->learnMateria(new Cure());

    ICharacter* me = new Character("me");

    AMateria* tmp;
    tmp = src->createMateria("ice");
    me->equip(tmp);
    tmp = src->createMateria("cure");
    me->equip(tmp);

    ICharacter* bob = new Character("bob");

    me->use(0, *bob);
    me->use(1, *bob);

    delete bob;
    delete me;
    delete src;

    // // 2nd test
	// IMateriaSource* src = new MateriaSource();
	// ICharacter* me = new Character("me");
	// ICharacter* bob = new Character("bob");
	// AMateria* tmp_ice = NULL;
	// AMateria* tmp_cure = NULL;
	
	// src->learnMateria(new Ice());
	// src->learnMateria(new Cure());
	// tmp_ice = src->createMateria("ice");
	// me->equip(tmp_ice);
	// tmp_cure = src->createMateria("cure");
	// me->equip(tmp_cure);
	// me->use(0, *bob);
	// me->use(1, *bob);
	// me->unequip(0);
	// me->unequip(1);
	// delete tmp_ice;
	// tmp_ice = NULL;
	// delete tmp_cure;
	// tmp_cure = NULL;
	// delete bob;
	// delete me;
	// delete src;

    return 0;
}
