#include <iostream>
#include <random>
#include <utility>

using namespace std;

const int N = 1000;

class Sorter
{
    int arr[N];
    int size;

public:
    Sorter(const int source[], int n)
    {
        size = n;
        for (int i = 0; i < size; ++i)
            arr[i] = source[i];
    }

    size_t BubbleSort()
    {
        size_t iterations = 0;

        for (int n = size; n > 1; )
        {
            int last_swap = 0;

            for (int j = 1; j < n; ++j)
            {
                ++iterations;

                if (arr[j - 1] > arr[j])
                {
                    swap(arr[j - 1], arr[j]);
                    last_swap = j;
                }
            }

            if (last_swap == 0) break;
            n = last_swap;
        }

        return iterations;
    }

    size_t SelectionSort()
    {
        size_t iterations = 0;

        for (int i = 0; i < size - 1; ++i)
        {
            int min_index = i;

            for (int j = i + 1; j < size; ++j)
            {
                ++iterations;

                if (arr[j] < arr[min_index])
                    min_index = j;
            }

            if (min_index != i)
                swap(arr[i], arr[min_index]);
        }

        return iterations;
    }

    size_t InsertionSort()
    {
        size_t iterations = 0;

        for (int i = 1; i < size; ++i)
        {
            int key = arr[i];
            int j = i;

            while (j > 0)
            {
                ++iterations;

                if (arr[j - 1] <= key)
                    break;

                arr[j] = arr[j - 1];
                --j;
            }

            arr[j] = key;
        }

        return iterations;
    }

    bool IsSorted() const
    {
        for (int i = 1; i < size; ++i)
            if (arr[i - 1] > arr[i])
                return false;
        return true;
    }
};

int main()
{
    int original[N];

    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> distribution(0, 9999);
    for (int i = 0; i < N; ++i)
        original[i] = distribution(generator);

    Sorter bubble(original, N);
    Sorter selection(original, N);
    Sorter insertion(original, N);

    size_t bubble_count = bubble.BubbleSort();
    size_t selection_count = selection.SelectionSort();
    size_t insertion_count = insertion.InsertionSort();

    cout << "Bubble sort:    " << bubble_count << " comparisons"
         << (bubble.IsSorted() ? "" : " (NOT sorted!)") << endl;
    cout << "Selection sort: " << selection_count << " comparisons"
         << (selection.IsSorted() ? "" : " (NOT sorted!)") << endl;
    cout << "Insertion sort: " << insertion_count << " comparisons"
         << (insertion.IsSorted() ? "" : " (NOT sorted!)") << endl;

    cout << endl;
    cout << "Selection vs Bubble:    " << selection_count << " vs " << bubble_count << endl;
    cout << "Selection vs Insertion: " << selection_count << " vs " << insertion_count << endl;

    const char * best = "Bubble sort";
    size_t best_count = bubble_count;
    if (selection_count < best_count) { best = "Selection sort"; best_count = selection_count; }
    if (insertion_count < best_count) { best = "Insertion sort"; best_count = insertion_count; }

    cout << "Fewest comparisons: " << best << " (" << best_count << ")" << endl;

    return 0;
}