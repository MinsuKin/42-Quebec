/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:22:03 by minkim            #+#    #+#             */
/*   Updated: 2022/10/18 17:22:41 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORM_HPP
# define FORM_HPP

# include <iostream>


class Form {
 private:

 public:
    Form();
    Form(const Form& obj);
    ~Form();
    Form& operator=(const Form& obj);
};

#endif
