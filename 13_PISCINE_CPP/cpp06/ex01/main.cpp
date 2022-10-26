/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 14:28:22 by minkim            #+#    #+#             */
/*   Updated: 2022/10/26 17:33:59 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

struct Data
{
	std::string name;
};

uintptr_t serialize(Data* ptr)
{
	return(reinterpret_cast<uintptr_t>(ptr));
}

Data* deserialize(uintptr_t raw)
{
	return(reinterpret_cast<Data *>(raw));
}

int main(void)
{
	Data data;
	Data *data_ptr;
	uintptr_t ptr;

	data.name = "Serialization";
	std::cout << data.name << std::endl;

	// ptr to unsigned long
    std::cout << &data << std::endl;
	ptr = serialize(&data);
	std::cout << ptr << std::endl;

	// unsigned long to ptr
	data_ptr = deserialize(ptr);
    std::cout << data_ptr << std::endl;
	std::cout << data_ptr->name << std::endl;

	return (0);
}