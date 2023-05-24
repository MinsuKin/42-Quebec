/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 16:26:22 by minkim            #+#    #+#             */
/*   Updated: 2023/05/23 20:03:12 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "RPN.hpp"

bool is_operator(const std::string &token)
{
    return token == "+" || token == "-" || token == "*" || token == "/";
}

int perform_operation(const std::string &op, int a, int b)
{
    if (op == "+")
    {
        return a + b;
    }
    
    if (op == "-")
    {
        return a - b;
    }
    
    if (op == "*")
    {
        return a * b;
    }
    
    if (op == "/")
    {
        if (b == 0)
            throw std::runtime_error("Error: division by zero");
        return a / b;
    }
    
    throw std::runtime_error("Error: invalid operator");
}

int evaluate_rpn(const std::string &expr)
{
    std::istringstream iss(expr);
    std::string token;
    std::stack<int> values;

    while (iss >> token)
    {
        if (is_operator(token))
        {
            if (values.size() < 2)
                throw std::runtime_error("Error");
            int b = values.top();
            values.pop();
            int a = values.top();
            values.pop();
            int result = perform_operation(token, a, b);
            values.push(result);
        }
        else
        {
            int number;
            std::istringstream(token) >> number;
            values.push(number);
        }
    }

    if (values.size() != 1)
        throw std::runtime_error("Error");
    return values.top();
}
