#include "FisherYatesShuffle.h"

void FisherYatesShuffle::Shuffle(int *arr, int n) {
    std::random_device rd;
    std::mt19937 gen(rd());

    for (int i = n - 1; i >= 1; i--)
    {
        std::uniform_int_distribution<> dist(0,i);
        int j = dist(gen);

        std::swap(arr[i], arr[j]);
    }
}
