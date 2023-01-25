#include "Testing/Testing.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    Testing *test = new Testing("../Generated tests/", 20);

    test->StartGeneratingAndTestingSET("f", true);

    return 0;
}


