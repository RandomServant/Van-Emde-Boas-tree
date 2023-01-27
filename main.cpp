#include "Testing/Testing.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

/*
    Testing *test = new Testing("../Generated tests/", 20);
    //test->StartGeneratingAndTestingVEB("f", true);
    //test->StartGeneratingAndTestingSET("f", true);
    //test->StartGeneratingAndTestingUNSET("f", true);
*/

    Testing *test = new Testing("../Tests/", 12);
    test->StartTesting();

    return 0;
}


