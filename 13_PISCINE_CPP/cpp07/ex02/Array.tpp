/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.tpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:15:21 by minkim            #+#    #+#             */
/*   Updated: 2022/10/25 20:28:54 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

template <typename T>
Array<T>::Array()
{
    std::cout << "Default constructor called" << std::endl;
    array = NULL;
    len = 0;
}

template <typename T>
Array<T>::Array(unsigned int n)
{
    std::cout << "Constructor called" << std::endl;
    if (n == 0)
    {
        array = NULL;
        len = 0;
    }
    else
    {
        array = new T[n];
        len = n;
    }
}

template <typename T>
Array<T>::Array(const Array& obj)
{
    std::cout << "Copy constructor called" << std::endl;
    if (obj.size() == 0)
        return;
    this->len = obj.size();
    this->array = new T[len];
    for (size_t i = 0; i < len; i++)
    {
        array[i] = obj[i];
    }
}

template <typename T>
Array<T>::~Array()
{
    std::cout << "Destructor called" << std::endl;
    if (array != NULL)
    {
        delete[] array;
        array = NULL;
        len = 0;
    }
}

template <typename T>
Array<T>& Array<T>::operator=(const Array<T>& obj)
{
    std::cout << "Copy assignment operator called" << std::endl;
    if (array != NULL)
    {
        delete[] array;
        array = NULL;
        len = 0;
    }
    this->len = obj.size();
    this->array = new T[len];
    for (size_t i = 0; i < len; i++)
    {
        array[i] = obj[i];
    }
    return *this;
}

template <typename T>
T& Array<T>::operator[] (std::size_t i)
{
    if (i >= len)
        throw std::out_of_range("OutOfRangeException");
    return array[i];
}

template <typename T>
const T& Array<T>::operator[] (std::size_t i) const
{
    if (i >= len)
        throw std::out_of_range("OutOfRangeException");
    return array[i];
}

template <typename T>
std::size_t Array<T>::size() const
{
    return this->len;
}
