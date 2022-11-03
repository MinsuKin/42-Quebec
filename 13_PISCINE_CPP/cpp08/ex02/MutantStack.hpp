/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 14:59:44 by minkim            #+#    #+#             */
/*   Updated: 2022/10/31 10:53:24 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTANTSTACK_HPP
# define MUTANTSTACK_HPP

# include <iostream>
# include <stack>

template <typename T>
class MutantStack : public std::stack<T> {
 public:
    MutantStack() {};
    MutantStack(const MutantStack& obj) {*this = obj;};
    ~MutantStack() {};
    MutantStack& operator=(const MutantStack& obj) {*this = obj; return (*this);};

	typedef typename MutantStack<T>::stack::container_type::iterator iterator;
	iterator begin() {return this->c.begin();};
	iterator end() {return this->c.end();}

	typedef typename MutantStack<T>::stack::container_type::reverse_iterator reverse_iterator;
	reverse_iterator rbegin() {return this->c.rbegin();}
	reverse_iterator rend() {return this->c.rend();}

	typedef typename MutantStack<T>::stack::container_type::const_iterator const_iterator;
	const_iterator cbegin() {return this->c.cbegin();}
	const_iterator cend() {return this->c.cend();}

	typedef typename MutantStack<T>::stack::container_type::const_reverse_iterator const_reverse_iterator;
	const_iterator crbegin() {return this->c.crbegin();}
	const_iterator crend() {return this->c.crend();}
};

#endif
