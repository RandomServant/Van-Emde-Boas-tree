/*
    Этот заголовочный файл содержит библиотеку с++ с реализацией алгоритма перестановки Фишера-Йетса"

    Подключение:
    #include "FisherYatesShuffle.h"

    Использование алгоритма перестановки:
    FisherYatesShuffle::Shuffle(массив, количество перестановок);

    Создание массива с перестановкой или без:
    FisherYatesShuffle::GenerateArray(Размер, true или false)
*/

#ifndef CHART_PY_FISHERYATESSHUFFLE_H
#define CHART_PY_FISHERYATESSHUFFLE_H

#include <iostream>
#include <random>

class FisherYatesShuffle {
public:
    static void Shuffle(int *arr, int n);
    static int *GenerateArray(int n, bool random);
};


#endif //CHART_PY_FISHERYATESSHUFFLE_H
