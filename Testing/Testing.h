/*
    Этот заголовочный файл содержит библиотеку с++ с реализацией
    тестирующей системы для алгоритма "Дерево ван Эмде Боасса"

    Также он наследует все функции библиотеки TestsGenerator.h

    Подключение:
    #include "Testing.h"

    Создание тестирующей системы:
    Testing *название = new Testing();

    Начать тестирование:
    название->StartTesting();

    Подробная инструкция по ссылке Подробнее по ссылке github.com/RandomServant/Van-Emde-Boas-tree
*/

#ifndef VAN_EMDEBOAS_TREE_TESTING_H
#define VAN_EMDEBOAS_TREE_TESTING_H

#include "TestsGenerator.h"

class Testing : TestsGenerator {

public:;
    Testing(std::string URL, int count);

    void StartTesting();
    void StartGeneratingAndTestingVEB(std::string function, bool random) override;
    void StartGeneratingAndTestingSET(std::string function, bool random) override;
    void StartGeneratingAndTestingUNSET(std::string function, bool random) override;
};


#endif //VAN_EMDEBOAS_TREE_TESTING_H
