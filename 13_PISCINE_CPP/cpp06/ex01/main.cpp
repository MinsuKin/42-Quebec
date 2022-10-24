/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 14:28:22 by minkim            #+#    #+#             */
/*   Updated: 2022/10/24 16:03:55 by minkim           ###   ########.fr       */
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
	Data *decode;
	uintptr_t ptr;

	data.name = "Serialization";
	std::cout << data.name << std::endl;

    // encode
    std::cout << &data << std::endl;
	ptr = serialize(&data);
	std::cout << ptr << std::endl;

    // decode
	decode = deserialize(ptr);
    std::cout << decode << std::endl;
	std::cout << decode->name << std::endl;

	return (0);
}