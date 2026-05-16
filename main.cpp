#include "Tests/tests.h"
#include <windows.h>
#include "Tests/VectorTest.h"
int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    RunAllVectorTests();
    return 0;
}