#include "Testing/Testing.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    Testing *test = new Testing("../Generated tests/", 3);

    test->GenerateTests();
    test->StartTests();

    return 0;
}


