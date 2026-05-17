#include "Tests/tests.h"
#include <windows.h>
#include "Tests/VectorTest.h"
#include "Tests/BitSeqTest.h"
#include "Tests/DynamicArrayTest.h"
#include "Tests/LinkedListTest.h"
#include "Tests/ListSeqTest.h"
int testsFailed = 0;
int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    RunAllVectorTests();
    RunAllBitSeqTests();
    RunAllDynArrTests();
    RunAllLinkListTests();
    RunAllListSeqTests();
    return 0;
}