#include "PmergeMe.cpp"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Error" << std::endl;
        return 1;
    }

    std::vector<int> input_vec;
    for (int i = 1; i < argc; ++i)
    {
        int value;
        std::istringstream iss(argv[i]);
        iss >> value;
        if (value <= 0)
        {
            std::cerr << "Error" << std::endl;
            return 1;
        }
        input_vec.push_back(value);
    }

    std::deque<int> input_deq(input_vec.begin(), input_vec.end());

    std::cout << "Before: ";
    for (unsigned long i = 0; i < input_vec.size(); ++i)
        std::cout << input_vec[i] << " ";
    std::cout << std::endl;

    std::vector<int> sorted_vec = merge_insert_sort(input_vec);
    std::cout << "After: ";
    for (unsigned long i = 0; i < sorted_vec.size(); ++i)
        std::cout << sorted_vec[i] << " ";
    std::cout << std::endl;

    process_container(input_vec, "std::vector");
    process_container(input_deq, "std::deque");

    return 0;
}
