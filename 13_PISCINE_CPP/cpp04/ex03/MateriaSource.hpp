/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 12:41:37 by minkim            #+#    #+#             */
/*   Updated: 2022/10/17 16:58:15 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIASOURCE_HPP
# define MATERIASOURCE_HPP

# include "IMateriaSource.hpp"

class MateriaSource : public IMateriaSource {
 private:
    AMateria *slot[4];

 public:
    MateriaSource();
    MateriaSource(const MateriaSource& obj);
    ~MateriaSource();
    MateriaSource& operator=(const MateriaSource& obj);

    void learnMateria(AMateria* m);
    AMateria* createMateria(std::string const &type);
};

#endif
