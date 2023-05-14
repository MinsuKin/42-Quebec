#ifndef PMEAGEME_HPP
# define PMEAGEME_HPP

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
