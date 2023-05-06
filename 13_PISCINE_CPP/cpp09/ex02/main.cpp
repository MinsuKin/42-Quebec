#include <iostream>
#include <vector>

void ftExit(void)
{
    std::cout << "Error" << std::endl;
    exit(EXIT_FAILURE);
}

int main(int argc, char const *argv[])
{
    std::vector<int> list;

    if (argc < 2)
        ftExit();

    for (int i = 1; i < argc; i++)
    {
        list.push_back(argv[i]);
    }
    // value1 = strtol(src,&pos,10);//10진수로 계산

    return 0;
}
