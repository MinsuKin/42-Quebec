/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 12:25:39 by minkim            #+#    #+#             */
/*   Updated: 2022/10/16 17:21:50 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRAIN_HPP
# define BRAIN_HPP

# include <iostream>
# include <sstream>

class Brain {
 private:
    std::string ideas[100];

 public:
    Brain();
    Brain(const Brain& obj);
    ~Brain();
    Brain& operator=(const Brain& obj);

    std::string getIdea(const int& i) const;
    void setIdea(const int& i, std::string idea);
};

#endif
