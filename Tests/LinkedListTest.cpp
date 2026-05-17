#include <iostream>
#include "tests.h"

void TestLinkedList_Construction()
{
    std::cout << "\nLinkedList создание" << std::endl;

    TEST("дефолт")
    {
        LinkedList<int> l;
        CHECK(l.GetLength() == 0);
    }
    ENDTEST();

    TEST("из массива")
    {
        int src[] = {1, 2, 3, 4, 5};
        LinkedList<int> l(src, 5);
        CHECK(l.GetLength() == 5);
        CHECK(l.GetFirst() == 1);
        CHECK(l.GetLast() == 5);
    }
    ENDTEST();

    TEST("копия")
    {
        int src[] = {10, 20, 30};
        LinkedList<int> a(src, 3);
        LinkedList<int> b(a);
        CHECK(b.GetLength() == 3);
        CHECK(b.GetFirst() == 10);
    }
    ENDTEST();
}

void TestLinkedList_GetOperations()
{
    std::cout << "\nLinkedList Get" << std::endl;

    TEST("GetFirst/GetLast")
    {
        int src[] = {1, 2, 3};
        LinkedList<int> l(src, 3);
        CHECK(l.GetFirst() == 1);
        CHECK(l.GetLast() == 3);
    }
    ENDTEST();

    TEST("по индексу")
    {
        int src[] = {10, 20, 30, 40, 50};
        LinkedList<int> l(src, 5);
        CHECK(l.Get(0) == 10);
        CHECK(l.Get(4) == 50);
    }
    ENDTEST();

    TEST("за границами")
    {
        LinkedList<int> l;
        CHECK_THROW(l.Get(0), IndexOutOfRange);
    }
    ENDTEST();
}

void TestLinkedList_AddOperations()
{
    std::cout << "\nLinkedList добавление" << std::endl;

    TEST("Append")
    {
        LinkedList<int> l;
        l.Append(42);
        CHECK(l.GetLength() == 1);
        CHECK(l.GetFirst() == 42);
    }
    ENDTEST();

    TEST("Prepend")
    {
        LinkedList<int> l;
        l.Prepend(42);
        CHECK(l.GetFirst() == 42);
    }
    ENDTEST();

    TEST("InsertAt")
    {
        int src[] = {1, 3};
        LinkedList<int> l(src, 2);
        l.InsertAt(2, 1);
        CHECK(l.Get(1) == 2);
    }
    ENDTEST();

    TEST("InsertAt за границами")
    {
        int src[] = {1, 2};
        LinkedList<int> l(src, 2);
        CHECK_THROW(l.InsertAt(99, 5), IndexOutOfRange);
    }
    ENDTEST();
}

void TestLinkedList_GetSubList()
{
    std::cout << "\nLinkedList GetSubList" << std::endl;

    TEST("подсписок из середины")
    {
        int src[] = {1, 2, 3, 4, 5};
        LinkedList<int> l(src, 5);
        LinkedList<int> *sub = l.GetSubList(1, 3);
        CHECK(sub->GetLength() == 3);
        CHECK(sub->Get(0) == 2);
        CHECK(sub->Get(2) == 4);
        delete sub;
    }
    ENDTEST();

    TEST("недопустимые индексы")
    {
        int src[] = {1, 2, 3};
        LinkedList<int> l(src, 3);
        CHECK_THROW(l.GetSubList(1, 5), IndexOutOfRange);
    }
    ENDTEST();
}

void TestLinkedList_Concat()
{
    std::cout << "\nLinkedList Concat" << std::endl;

    TEST("два списка")
    {
        int s1[] = {1, 2}, s2[] = {3, 4};
        LinkedList<int> a(s1, 2), b(s2, 2);
        LinkedList<int> *r = a.Concat(&b);
        CHECK(r->GetLength() == 4);
        CHECK(r->Get(0) == 1);
        CHECK(r->Get(3) == 4);
        delete r;
    }
    ENDTEST();

    TEST("с пустым")
    {
        int src[] = {1, 2, 3};
        LinkedList<int> a(src, 3), b;
        LinkedList<int> *r = a.Concat(&b);
        CHECK(r->GetLength() == 3);
        delete r;
    }
    ENDTEST();
}

void TestLinkedList_OperatorBracket()
{
    std::cout << "\nLinkedList operator[]" << std::endl;

    TEST("чтение/запись")
    {
        int src[] = {1, 2, 3};
        LinkedList<int> l(src, 3);
        CHECK(l[0] == 1);
        l[1] = 99;
        CHECK(l[1] == 99);
    }
    ENDTEST();

    TEST("за границами")
    {
        int src[] = {1, 2};
        LinkedList<int> l(src, 2);
        CHECK_THROW(l[5], IndexOutOfRange);
    }
    ENDTEST();
}

void TestLinkedList_Assignment()
{
    std::cout << "\nLinkedList присваивание" << std::endl;

    TEST("оператор =")
    {
        int src[] = {1, 2, 3};
        LinkedList<int> a(src, 3), b;
        b.Append(99);
        b = a;
        CHECK(b.GetLength() == 3);
        CHECK(b.Get(0) == 1);
    }
    ENDTEST();

    TEST("самоприсваивание")
    {
        int src[] = {1, 2, 3};
        LinkedList<int> l(src, 3);
        l = l;
        CHECK(l.GetLength() == 3);
    }
    ENDTEST();
}

void TestLinkedList_Iterator()
{
    std::cout << "\nLinkedList итераторы" << std::endl;

    TEST("обход итератором")
    {
        int src[] = {1, 2, 3};
        LinkedList<int> l(src, 3);
        int sum = 0;
        for (auto it = l.begin(); it != l.end(); ++it)
        {
            sum += *it;
        }
        CHECK(sum == 6);
    }
    ENDTEST();

    TEST("модификация через итератор")
    {
        int src[] = {1, 2, 3};
        LinkedList<int> l(src, 3);
        for (auto it = l.begin(); it != l.end(); ++it)
            *it = *it * 10;
        CHECK(l.Get(0) == 10);
        CHECK(l.Get(2) == 30);
    }
    ENDTEST();
}

void RunAllLinkListTests()
{
    std::cout << "Тесты LinkList" << std::endl;

    TestLinkedList_Construction();
    TestLinkedList_GetOperations();
    TestLinkedList_AddOperations();
    TestLinkedList_GetSubList();
    TestLinkedList_Concat();
    TestLinkedList_OperatorBracket();
    TestLinkedList_Assignment();
    TestLinkedList_Iterator();

    if (testsFailed == 0)
    {
        std::cout << "Все тесты успешно пройдены" << std::endl;
    }
    else
    {
        std::cout << "Есть непройденные тесты " << testsFailed << "шт" << std::endl;
    }
}