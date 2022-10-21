/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 11:27:30 by minkim            #+#    #+#             */
/*   Updated: 2022/10/20 13:08:23 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP

# include <iostream>

class Form;

class Bureaucrat {
 private:
    const std::string name;
    int grade;

 public:
    Bureaucrat();
    Bureaucrat(std::string name, int grade);
    Bureaucrat(const Bureaucrat& obj);
    ~Bureaucrat();
    Bureaucrat& operator=(const Bureaucrat& obj);
    

    class GradeTooHighException : public std::exception
    {
        const char * what(void) const throw();
    };
    class GradeTooLowException : public std::exception
    {
        const char * what(void) const throw();
    };
    
    std::string getName(void) const;
    int getGrade(void) const;
    void incrementGrade(void);
    void decrementGrade(void);

    void signForm(Form &f) const;

    void executeForm(Form const & form);
};

std::ostream &operator<<(std::ostream &out, const Bureaucrat &bc);

#endif
