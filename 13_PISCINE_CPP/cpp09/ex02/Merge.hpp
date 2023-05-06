#ifndef MERGE_HPP
# define MERGE_HPP

# include <iostream>


class Merge {
 private:
    /* data */
 public:
    Merge(/* args */);
    Merge(const Merge& obj);
    ~Merge();
    Merge& operator=(const Merge& obj);
};

#endif

Merge::Merge(/* args */) {}
Merge::Merge(const Merge& obj) {}
Merge::~Merge() {}
Merge& Merge::operator=(const Merge& obj) {}
