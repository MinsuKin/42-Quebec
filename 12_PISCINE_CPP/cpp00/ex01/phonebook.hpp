/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phonebook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 13:49:59 by minkim            #+#    #+#             */
/*   Updated: 2022/10/05 16:29:34 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include <iostream>
#include "contact.hpp"

class PhoneBook
{
private:
    Contact contacts[8];
    int     index;

public:
    PhoneBook();
    ~PhoneBook();

    void AddContact();
    int PrintAll();
    int Search();
};

#endif
