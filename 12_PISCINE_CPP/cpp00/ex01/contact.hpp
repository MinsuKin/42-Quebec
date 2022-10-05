/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 14:44:08 by minkim            #+#    #+#             */
/*   Updated: 2022/10/05 16:29:48 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <iostream>

class Contact
{
private:
    std::string info[5];
    std::string content[5];

public:
    Contact();
    ~Contact();

    void AddContent();
    void PrintContent();
    void PrintSearch();
};

#endif
