/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:02:27 by minkim            #+#    #+#             */
/*   Updated: 2023/05/20 12:08:13 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <iomanip>
# include <vector>
# include <deque>
# include <sstream>
# include <algorithm>
# include <iterator>
# include <ctime>
# include <typeinfo>

template <typename Container>
Container merge_insert_sort(const Container &input);

template <typename Container>
void process_container(const Container &input, const std::string &container_name);

#endif
