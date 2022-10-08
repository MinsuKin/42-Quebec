/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:41:24 by minkim            #+#    #+#             */
/*   Updated: 2022/10/08 13:44:35 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>

int main(int ac, char *av[])
{
    std::ifstream in;
    std::ofstream out;
    std::string filename;
    std::string line;
    std::string s1;
    std::string s2;

    if (ac != 4)
    {
        std::cout << "Error - need 3 inputs" << std::endl;
        return 1;
    }
    
    filename = av[1];
    in.open(filename);
    if (!in.is_open()) 
    {
        std::cout << "Error - cannot open input file" << std::endl;
        return 1;
    }
    
    out.open(filename + ".replace");
    if (!out.is_open()) 
    {
        std::cout << "Error - cannot open output file" << std::endl;
        return 1;
    }

    s1 = av[2];
    s2 = av[3];
    while (true)
    {
        std::getline(in, line);

        size_t pos = 0;
        while (true)
        {
            pos = line.find(s1, pos); // pos == starting position
            if (pos == std::string::npos) // cannot find anymore (npos == -1)
                break;
            line.erase(pos, s1.length());
            line.insert(pos, s2);
            pos += s2.length();
        }
        out << line;
        if (in.eof())
            break;
        out << std::endl;
    }
    return 0;
}
