/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 15:08:50 by minkim            #+#    #+#             */
/*   Updated: 2022/10/20 22:18:54 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERN_HPP
# define INTERN_HPP

# include <iostream>
# include "ShrubberyCreationForm.hpp"
# include "RobotomyRequestForm.hpp"
# include "PresidentialPardonForm.hpp"

class Intern {
 private:

 public:
    Intern();
    Intern(const Intern& obj);
    ~Intern();
    Intern& operator=(const Intern& obj);

    class NameNotFoundException : public std::exception
    {
        const char * what(void) const throw();
    };

    Form *makeForm(const std::string& name, const std::string& target);
};

#endif
