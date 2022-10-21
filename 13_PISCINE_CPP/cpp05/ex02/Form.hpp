/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:22:03 by minkim            #+#    #+#             */
/*   Updated: 2022/10/20 14:11:35 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORM_HPP
# define FORM_HPP

# include <iostream>
# include "Bureaucrat.hpp"

class Form {
 private:
    const std::string name;
    bool sign;
    const int grade_sign;
    const int grade_excute;

 public:
    Form();
    Form(std::string name, int grade_sign, int grade_execute);
    Form(const Form& obj);
    ~Form();
    Form& operator=(const Form& obj);

    class GradeTooHighException : public std::exception
    {
        const char * what(void) const throw();
    };
    class GradeTooLowException : public std::exception
    {
        const char * what(void) const throw();
    };
    class NotSignedException : public std::exception
    {
        const char * what(void) const throw();
    };
    
    const std::string& getName(void) const;
    const bool& getSign(void) const;
    const int& getGradeSign(void) const;
    const int& getGradeExcute(void) const;

    void beSigned(const Bureaucrat &bc);

    void setName(const std::string& name);

    virtual void execute(Bureaucrat const & executor) const = 0;
};

std::ostream &operator<<(std::ostream &out, const Form &f);

#endif
