#include <iostream>
#include "tests.h"

void TestListSequence_GetOperations()
{
    TEST("GetFirst непустой")
    {
        int src[] = {10, 20, 30};
        MutableListSequence<int> seq(src, 3);
        CHECK(seq.GetFirst() == 10);
    }
    ENDTEST();

    TEST("GetFirst пустая")
    {
        MutableListSequence<int> seq;
        CHECK_THROW(seq.GetFirst(), IndexOutOfRange);
    }
    ENDTEST();

    TEST("GetLast непустой")
    {
        int src[] = {10, 20, 30};
        MutableListSequence<int> seq(src, 3);
        CHECK(seq.GetLast() == 30);
    }
    ENDTEST();

    TEST("GetLast пустая")
    {
        MutableListSequence<int> seq;
        CHECK_THROW(seq.GetLast(), IndexOutOfRange);
    }
    ENDTEST();

    TEST("Get за границами")
    {
        int src[] = {1, 2};
        MutableListSequence<int> seq(src, 2);
        CHECK_THROW(seq.Get(5), IndexOutOfRange);
    }
    ENDTEST();

    TEST("Get пустая")
    {
        MutableListSequence<int> seq;
        CHECK_THROW(seq.Get(0), IndexOutOfRange);
    }
    ENDTEST();

    TEST("GetLength непустой")
    {
        int src[] = {1, 2, 3, 4};
        MutableListSequence<int> seq(src, 4);
        CHECK(seq.GetLength() == 4);
    }
    ENDTEST();

    TEST("GetLength пустая")
    {
        MutableListSequence<int> seq;
        CHECK(seq.GetLength() == 0);
    }
    ENDTEST();
}

void TestListSequence_GetSubsequence()
{
    TEST("GetSubsequence с начала")
    {
        int src[] = {1, 2, 3, 4, 5};
        ImmutableListSequence<int> seq(src, 5);
        Sequence<int> *sub = seq.GetSubsequence(0, 2);
        CHECK(sub->GetLength() == 3);
        CHECK(sub->Get(0) == 1);
        CHECK(sub->Get(1) == 2);
        CHECK(sub->Get(2) == 3);
        delete sub;
    }
    ENDTEST();

    TEST("GetSubsequence из середины")
    {
        int src[] = {10, 20, 30, 40, 50};
        ImmutableListSequence<int> seq(src, 5);
        Sequence<int> *sub = seq.GetSubsequence(1, 3);
        CHECK(sub->GetLength() == 3);
        CHECK(sub->Get(0) == 20);
        CHECK(sub->Get(1) == 30);
        CHECK(sub->Get(2) == 40);
        delete sub;
    }
    ENDTEST();

    TEST("GetSubsequence вся последовательность")
    {
        int src[] = {1, 2, 3};
        ImmutableListSequence<int> seq(src, 3);
        Sequence<int> *sub = seq.GetSubsequence(0, 2);
        CHECK(sub->GetLength() == 3);
        CHECK(sub->Get(0) == 1);
        CHECK(sub->Get(2) == 3);
        delete sub;
    }
    ENDTEST();

    TEST("GetSubsequence один элемент")
    {
        int src[] = {5, 10, 15};
        ImmutableListSequence<int> seq(src, 3);
        Sequence<int> *sub = seq.GetSubsequence(1, 1);
        CHECK(sub->GetLength() == 1);
        CHECK(sub->Get(0) == 10);
        delete sub;
    }
    ENDTEST();

    TEST("GetSubsequence start больше end")
    {
        int src[] = {1, 2, 3};
        ImmutableListSequence<int> seq(src, 3);
        CHECK_THROW(seq.GetSubsequence(2, 0), IndexOutOfRange);
    }
    ENDTEST();

    TEST("GetSubsequence end за границами")
    {
        int src[] = {1, 2};
        ImmutableListSequence<int> seq(src, 2);
        CHECK_THROW(seq.GetSubsequence(0, 5), IndexOutOfRange);
    }
    ENDTEST();

    TEST("GetSubsequence start за границами")
    {
        int src[] = {1, 2};
        ImmutableListSequence<int> seq(src, 2);
        CHECK_THROW(seq.GetSubsequence(3, 5), IndexOutOfRange);
    }
    ENDTEST();

    TEST("GetSubsequence пустая")
    {
        ImmutableListSequence<int> seq;
        CHECK_THROW(seq.GetSubsequence(0, 0), IndexOutOfRange);
    }
    ENDTEST();
}

void TestListSequence_Append()
{
    TEST("Append к пустой Immutable")
    {
        ImmutableListSequence<int> seq;
        Sequence<int> *result = seq.Append(42);
        CHECK(seq.GetLength() == 0);
        CHECK(result->GetLength() == 1);
        CHECK(result->Get(0) == 42);
        delete result;
    }
    ENDTEST();

    TEST("Append несколько раз")
    {
        ImmutableListSequence<int> seq;
        Sequence<int> *r1 = seq.Append(1);
        Sequence<int> *r2 = r1->Append(2);
        Sequence<int> *r3 = r2->Append(3);
        CHECK(r3->GetLength() == 3);
        CHECK(r3->Get(0) == 1);
        CHECK(r3->Get(1) == 2);
        CHECK(r3->Get(2) == 3);
        delete r1;
        delete r2;
        delete r3;
    }
    ENDTEST();
}

void TestListSequence_Prepend()
{
    TEST("Prepend к непустой Immutable")
    {
        int src[] = {2, 3};
        ImmutableListSequence<int> seq(src, 2);
        Sequence<int> *result = seq.Prepend(1);
        CHECK(seq.GetLength() == 2);
        CHECK(seq.GetFirst() == 2);
        CHECK(result->GetLength() == 3);
        CHECK(result->Get(0) == 1);
        CHECK(result->Get(1) == 2);
        CHECK(result->Get(2) == 3);
        delete result;
    }
    ENDTEST();

    TEST("Prepend к пустой Immutable")
    {
        ImmutableListSequence<int> seq;
        Sequence<int> *result = seq.Prepend(99);
        CHECK(seq.GetLength() == 0);
        CHECK(result->GetLength() == 1);
        CHECK(result->Get(0) == 99);
        delete result;
    }
    ENDTEST();

    TEST("Prepend несколько раз")
    {
        int src[] = {3};
        ImmutableListSequence<int> seq(src, 1);
        Sequence<int> *r1 = seq.Prepend(2);
        Sequence<int> *r2 = r1->Prepend(1);
        CHECK(r2->GetLength() == 3);
        CHECK(r2->Get(0) == 1);
        CHECK(r2->Get(1) == 2);
        CHECK(r2->Get(2) == 3);
        delete r1;
        delete r2;
    }
    ENDTEST();
}

void TestListSequence_InsertAt()
{
    TEST("InsertAt в начало Immutable")
    {
        int src[] = {2, 3};
        ImmutableListSequence<int> seq(src, 2);
        Sequence<int> *result = seq.InsertAt(1, 0);
        CHECK(seq.GetLength() == 2);
        CHECK(result->GetLength() == 3);
        CHECK(result->Get(0) == 1);
        CHECK(result->Get(1) == 2);
        CHECK(result->Get(2) == 3);
        delete result;
    }
    ENDTEST();

    TEST("InsertAt в середину Immutable")
    {
        int src[] = {1, 3};
        ImmutableListSequence<int> seq(src, 2);
        Sequence<int> *result = seq.InsertAt(2, 1);
        CHECK(result->GetLength() == 3);
        CHECK(result->Get(0) == 1);
        CHECK(result->Get(1) == 2);
        CHECK(result->Get(2) == 3);
        delete result;
    }
    ENDTEST();

    TEST("InsertAt в конец Immutable")
    {
        int src[] = {1, 2};
        ImmutableListSequence<int> seq(src, 2);
        Sequence<int> *result = seq.InsertAt(3, 2);
        CHECK(result->GetLength() == 3);
        CHECK(result->Get(0) == 1);
        CHECK(result->Get(1) == 2);
        CHECK(result->Get(2) == 3);
        delete result;
    }
    ENDTEST();

    TEST("InsertAt в пустую")
    {
        ImmutableListSequence<int> seq;
        Sequence<int> *result = seq.InsertAt(42, 0);
        CHECK(result->GetLength() == 1);
        CHECK(result->Get(0) == 42);
        delete result;
    }
    ENDTEST();

    TEST("InsertAt за границами")
    {
        int src[] = {1, 2};
        ImmutableListSequence<int> seq(src, 2);
        CHECK_THROW(seq.InsertAt(99, 5), IndexOutOfRange);
    }
    ENDTEST();
}

void TestListSequence_Concat()
{
    TEST("Concat две непустых")
    {
        int s1[] = {1, 2};
        int s2[] = {3, 4};
        ImmutableListSequence<int> a(s1, 2), b(s2, 2);
        Sequence<int> *result = a.Concat(&b);
        CHECK(a.GetLength() == 2);
        CHECK(b.GetLength() == 2);
        CHECK(result->GetLength() == 4);
        CHECK(result->Get(0) == 1);
        CHECK(result->Get(1) == 2);
        CHECK(result->Get(2) == 3);
        CHECK(result->Get(3) == 4);
        delete result;
    }
    ENDTEST();

    TEST("Concat c пустой")
    {
        int src[] = {1, 2, 3};
        ImmutableListSequence<int> a(src, 3), b;
        Sequence<int> *result = a.Concat(&b);
        CHECK(result->GetLength() == 3);
        CHECK(result->Get(0) == 1);
        delete result;
    }
    ENDTEST();

    TEST("Concat пустая c непустой")
    {
        ImmutableListSequence<int> a;
        int src[] = {1, 2};
        ImmutableListSequence<int> b(src, 2);
        Sequence<int> *result = a.Concat(&b);
        CHECK(result->GetLength() == 2);
        CHECK(result->Get(0) == 1);
        delete result;
    }
    ENDTEST();

    TEST("Concat две пустых")
    {
        ImmutableListSequence<int> a, b;
        Sequence<int> *result = a.Concat(&b);
        CHECK(result->GetLength() == 0);
        delete result;
    }
    ENDTEST();

    TEST("Concat с nullptr")
    {
        int src[] = {42};
        ImmutableListSequence<int> a(src, 1);
        Sequence<int> *result = a.Concat(nullptr);
        CHECK(result->GetLength() == 1);
        CHECK(result->Get(0) == 42);
        delete result;
    }
    ENDTEST();
}

void TestListSequence_Where()
{
    TEST("Where на четные")
    {
        int src[] = {1, 2, 3, 4, 5, 6};
        ImmutableListSequence<int> seq(src, 6);
        Sequence<int> *result = seq.Where([](const int &x)
                                          { return x % 2 == 0; });
        CHECK(result->GetLength() == 3);
        CHECK(result->Get(0) == 2);
        CHECK(result->Get(1) == 4);
        CHECK(result->Get(2) == 6);
        delete result;
    }
    ENDTEST();

    TEST("Where нет совпадений")
    {
        int src[] = {1, 3, 5};
        ImmutableListSequence<int> seq(src, 3);
        Sequence<int> *result = seq.Where([](const int &x)
                                          { return x > 10; });
        CHECK(result->GetLength() == 0);
        delete result;
    }
    ENDTEST();

    TEST("Where все подходят")
    {
        int src[] = {2, 4, 6};
        ImmutableListSequence<int> seq(src, 3);
        Sequence<int> *result = seq.Where([](const int &x)
                                          { return x % 2 == 0; });
        CHECK(result->GetLength() == 3);
        delete result;
    }
    ENDTEST();

    TEST("Where пустая")
    {
        ImmutableListSequence<int> seq;
        Sequence<int> *result = seq.Where([](const int &x)
                                          { return x > 0; });
        CHECK(result->GetLength() == 0);
        delete result;
    }
    ENDTEST();

    TEST("Where не меняет исходную")
    {
        int src[] = {1, 2, 3};
        ImmutableListSequence<int> seq(src, 3);
        Sequence<int> *result = seq.Where([](const int &x)
                                          { return x > 1; });
        CHECK(seq.GetLength() == 3);
        CHECK(seq.Get(0) == 1);
        delete result;
    }
    ENDTEST();
}

void TestListSequence_Map()
{
    TEST("Map умножение")
    {
        int src[] = {1, 2, 3};
        ImmutableListSequence<int> seq(src, 3);
        Sequence<int> *result = seq.Map<int>([](const int &x)
                                             { return x * 10; });
        CHECK(result->GetLength() == 3);
        CHECK(result->Get(0) == 10);
        CHECK(result->Get(1) == 20);
        CHECK(result->Get(2) == 30);
        delete result;
    }
    ENDTEST();

    TEST("Map в строку")
    {
        int src[] = {1, 2};
        ImmutableListSequence<int> seq(src, 2);
        Sequence<std::string> *result = seq.Map<std::string>([](const int &x)
                                                             { return "x" + std::to_string(x); });
        CHECK(result->GetLength() == 2);
        CHECK(result->Get(0) == "x1");
        CHECK(result->Get(1) == "x2");
        delete result;
    }
    ENDTEST();

    TEST("Map пустая")
    {
        ImmutableListSequence<int> seq;
        Sequence<int> *result = seq.Map<int>([](const int &x)
                                             { return x * 2; });
        CHECK(result->GetLength() == 0);
        delete result;
    }
    ENDTEST();

    TEST("Map не меняет исходную")
    {
        int src[] = {1, 2, 3};
        ImmutableListSequence<int> seq(src, 3);
        Sequence<int> *result = seq.Map<int>([](const int &x)
                                             { return x * 100; });
        CHECK(seq.GetLength() == 3);
        CHECK(seq.Get(0) == 1);
        delete result;
    }
    ENDTEST();
}

void TestListSequence_Reduce()
{
    TEST("Reduce сумма")
    {
        int src[] = {1, 2, 3, 4, 5};
        ImmutableListSequence<int> seq(src, 5);
        int result = seq.Reduce<int>([](const int &a, const int &x)
                                     { return a + x; }, 0);
        CHECK(result == 15);
    }
    ENDTEST();

    TEST("Reduce произведение")
    {
        int src[] = {1, 2, 3, 4};
        ImmutableListSequence<int> seq(src, 4);
        int result = seq.Reduce<int>([](const int &a, const int &x)
                                     { return a * x; }, 1);
        CHECK(result == 24);
    }
    ENDTEST();

    TEST("Reduce с init")
    {
        int src[] = {1, 2, 3};
        ImmutableListSequence<int> seq(src, 3);
        int result = seq.Reduce<int>([](const int &a, const int &x)
                                     { return a + x; }, 10);
        CHECK(result == 16);
    }
    ENDTEST();

    TEST("Reduce пустая возвращает init")
    {
        ImmutableListSequence<int> seq;
        int result = seq.Reduce<int>([](const int &a, const int &x)
                                     { return a + x; }, 50);
        CHECK(result == 50);
    }
    ENDTEST();

    TEST("Reduce не меняет исходную")
    {
        int src[] = {1, 2, 3};
        ImmutableListSequence<int> seq(src, 3);
        int result = seq.Reduce<int>([](const int &a, const int &x)
                                     { return a + x; }, 0);
        CHECK(seq.GetLength() == 3);
        CHECK(seq.Get(0) == 1);
        CHECK(result == 6);
    }
    ENDTEST();
}

void RunAllListSeqTests()
{
    std::cout << "Тесты ListSeq" << std::endl;

    TestListSequence_GetOperations();
    TestListSequence_GetSubsequence();
    TestListSequence_Append();
    TestListSequence_Prepend();
    TestListSequence_InsertAt();
    TestListSequence_Concat();
    TestListSequence_Where();
    TestListSequence_Map();
    TestListSequence_Reduce();

    if (testsFailed == 0)
    {
        std::cout << "Все тесты успешно пройдены" << std::endl;
    }
    else
    {
        std::cout << "Есть непройденные тесты " << testsFailed << "шт" << std::endl;
    }
}