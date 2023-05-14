# include "PmergeMe.hpp"

template <typename Container>
void insertion_sort(Container& input, int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        typename Container::value_type key = input[i];
        int j = i - 1;
        while (j >= left && input[j] > key) {
            input[j + 1] = input[j];
            j--;
        }
        input[j + 1] = key;
    }
}

template <typename Container>
void merge(Container& input, int left, int mid, int right) {
    Container temp(right - left + 1);
    int i = left;
    int j = mid + 1;
    int k = 0;

    while (i <= mid && j <= right) {
        if (input[i] <= input[j]) {
            temp[k++] = input[i++];
        } else {
            temp[k++] = input[j++];
        }
    }

    while (i <= mid) {
        temp[k++] = input[i++];
    }

    while (j <= right) {
        temp[k++] = input[j++];
    }

    for (i = left; i <= right; i++) {
        input[i] = temp[i - left];
    }
}

template <typename Container>
void merge_insert_sort(Container& input, int left, int right, int size) {
    if (left >= right) {
        return;
    }

    if (right - left + 1 <= size) {
        insertion_sort(input, left, right);
        return;
    }

    int mid = (left + right) / 2;
    merge_insert_sort(input, left, mid, size);
    merge_insert_sort(input, mid + 1, right, size);
    merge(input, left, mid, right);
}

template <typename Container>
Container merge_insert_sort(const Container &input)
{
    if (input.size() <= 1)
    {
        return input;
    }

    // Use insertion sort if the size of the list is less than 6
    if (input.size() <= 5)
    {
        Container result = input;
        typename Container::iterator it;
        for (it = result.begin() + 1; it != result.end(); ++it) {
            typename Container::value_type key = *it;
            typename Container::iterator j = it - 1;
            while (j >= result.begin() && *j > key) {
                *(j + 1) = *j;
                --j;
            }
            *(j + 1) = key;
        }
        return result;
    }

    Container left_half(input.begin(), input.begin() + input.size() / 2);
    Container right_half(input.begin() + input.size() / 2, input.end());

    left_half = merge_insert_sort(left_half);
    right_half = merge_insert_sort(right_half);

    Container sorted;
    typename Container::iterator left_iter = left_half.begin();
    typename Container::iterator right_iter = right_half.begin();

    while (left_iter != left_half.end() || right_iter != right_half.end())
    {
        if (left_iter == left_half.end())
        {
            sorted.insert(sorted.end(), right_iter, right_half.end());
            break;
        }
        else if (right_iter == right_half.end())
        {
            sorted.insert(sorted.end(), left_iter, left_half.end());
            break;
        }
        else if (*left_iter <= *right_iter)
        {
            sorted.push_back(*left_iter);
            ++left_iter;
        }
        else
        {
            typename Container::iterator next_right = right_iter;
            while (next_right != right_half.end() && *next_right < *left_iter)
            {
                ++next_right;
            }
            sorted.insert(sorted.end(), right_iter, next_right);
            right_iter = next_right;
        }
    }

    return sorted;
}

template <typename Container>
void process_container(const Container &input, const std::string &container_name)
{
    std::clock_t start = std::clock();
    Container sorted = merge_insert_sort(input);
    double duration = static_cast<double>(std::clock() - start) / CLOCKS_PER_SEC;

    std::cout << "Time to process a range of " << input.size() << " elements with " << container_name
              << " : " << std::fixed << std::setprecision(6) << duration << " μs" << std::endl;
}
