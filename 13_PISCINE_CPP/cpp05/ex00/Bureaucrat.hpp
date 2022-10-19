/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 11:27:30 by minkim            #+#    #+#             */
/*   Updated: 2022/10/18 19:59:13 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP

# include <iostream>
# include <fstream>

class Bureaucrat {
 private:
    const std::string name;
    int grade;

 public:
    Bureaucrat();
    Bureaucrat(const Bureaucrat& obj);
    ~Bureaucrat();
    Bureaucrat& operator=(const Bureaucrat& obj);
    
    Bureaucrat(std::string name, int grade);

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
};

std::ostream &operator<<(std::ostream &out, const Bureaucrat &bc);

#endif
