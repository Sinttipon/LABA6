#include <iostream> 
#include "tests.h"

void TestBitSequence_GetOperations()
{
    std::cout << "\nBitSequence Get" << std::endl;

    TEST("GetFirst непустой")
    {
        bool src[] = {true, false, true};
        BitSequence bs(src, 3);
        CHECK(bs.GetFirst() == Bit(true));
    }
    ENDTEST();

    TEST("GetFirst пустой")
    {
        BitSequence bs;
        CHECK_THROW(bs.GetFirst(), IndexOutOfRange);
    }
    ENDTEST();

    TEST("GetLast непустой")
    {
        bool src[] = {true, false, false};
        BitSequence bs(src, 3);
        CHECK(bs.GetLast() == Bit(false));
    }
    ENDTEST();

    TEST("GetLast пустой")
    {
        BitSequence bs;
        CHECK_THROW(bs.GetLast(), IndexOutOfRange);
    }
    ENDTEST();

    TEST("Get")
    {
        bool src[] = {true, false, true};
        BitSequence bs(src, 3);
        CHECK(bs.Get(0) == Bit(true));
    }
    ENDTEST();

    TEST("Get за границами")
    {
        bool src[] = {true, false};
        BitSequence bs(src, 2);
        CHECK_THROW(bs.Get(5), IndexOutOfRange);
    }
    ENDTEST();

    TEST("Get пустой")
    {
        BitSequence bs;
        CHECK_THROW(bs.Get(0), IndexOutOfRange);
    }
    ENDTEST();

    TEST("GetLength непустой")
    {
        bool src[] = {true, false, true, true};
        BitSequence bs(src, 4);
        CHECK(bs.GetLength() == 4);
    }
    ENDTEST();

    TEST("GetLength пустой")
    {
        BitSequence bs;
        CHECK(bs.GetLength() == 0);
    }
    ENDTEST();

    TEST("GetFirst и GetLast на единичный")
    {
        bool src[] = {true};
        BitSequence bs(src, 1);
        CHECK(bs.GetFirst() == bs.GetLast());
        CHECK(bs.GetLast() == Bit(true));
    }
    ENDTEST();
}

void TestBitSequence_Subsequence()
{
    TEST("полная последовательность")
    {
        bool src[] = {true, false, true, false};
        BitSequence bs(src, 4);
        Sequence<Bit> *sub = bs.GetSubsequence(0, 3);

        CHECK(sub->GetLength() == 4);
        CHECK(sub->Get(0) == Bit(true));
        CHECK(sub->Get(1) == Bit(false));
        CHECK(sub->Get(2) == Bit(true));
        CHECK(sub->Get(3) == Bit(false));

        delete sub;
    }
    ENDTEST();

    TEST("часть последовательности")
    {
        bool src[] = {true, false, true, false, true};
        BitSequence bs(src, 5);
        Sequence<Bit> *sub = bs.GetSubsequence(1, 3);

        CHECK(sub->GetLength() == 3);
        CHECK(sub->Get(0) == Bit(false));
        CHECK(sub->Get(1) == Bit(true));
        CHECK(sub->Get(2) == Bit(false));

        delete sub;
    }
    ENDTEST();

    TEST("один элемент")
    {
        bool src[] = {true, false, true};
        BitSequence bs(src, 3);
        Sequence<Bit> *sub = bs.GetSubsequence(1, 1);

        CHECK(sub->GetLength() == 1);
        CHECK(sub->Get(0) == Bit(false));

        delete sub;
    }
    ENDTEST();

    TEST("ошибка индексации")
    {
        bool src[] = {true, false, true};
        BitSequence bs(src, 3);
        CHECK_THROW(bs.GetSubsequence(2, 1), IndexOutOfRange);
    }
    ENDTEST();

    TEST("за границами")
    {
        bool src[] = {true, false};
        BitSequence bs(src, 2);
        CHECK_THROW(bs.GetSubsequence(0, 5), IndexOutOfRange);
    }
    ENDTEST();

    TEST("пустая")
    {
        BitSequence bs;
        CHECK_THROW(bs.GetSubsequence(0, 0), IndexOutOfRange);
    }
    ENDTEST();
}

void TestBitSequence_Append()
{
    TEST("добавление в конец")
    {
        bool src[] = {true, false};
        BitSequence bs(src, 2);
        Sequence<Bit> *newBs = bs.Append(Bit(true));

        CHECK(bs.GetLength() == 2);
        CHECK(newBs->GetLength() == 3);
        CHECK(newBs->Get(0) == Bit(true));
        CHECK(newBs->Get(1) == Bit(false));
        CHECK(newBs->Get(2) == Bit(true));

        delete newBs;
    }
    ENDTEST();

    TEST("добавление к пустой")
    {
        BitSequence bs;
        Sequence<Bit> *newBs = bs.Append(Bit(false));

        CHECK(newBs->GetLength() == 1);
        CHECK(newBs->Get(0) == Bit(false));

        delete newBs;
    }
    ENDTEST();
}

void TestBitSequence_Prepend()
{
    TEST("добавление в начало")
    {
        bool src[] = {false, true};
        BitSequence bs(src, 2);
        Sequence<Bit> *newBs = bs.Prepend(Bit(true));

        CHECK(bs.GetLength() == 2);
        CHECK(newBs->GetLength() == 3);
        CHECK(newBs->Get(0) == Bit(true));
        CHECK(newBs->Get(1) == Bit(false));
        CHECK(newBs->Get(2) == Bit(true));

        delete newBs;
    }
    ENDTEST();

    TEST("добавление к пустой")
    {
        BitSequence bs;
        Sequence<Bit> *newBs = bs.Prepend(Bit(true));

        CHECK(newBs->GetLength() == 1);
        CHECK(newBs->Get(0) == Bit(true));

        delete newBs;
    }
    ENDTEST();
}

void TestBitSequence_InsertAt()
{
    TEST("вставка в середину")
    {
        bool src[] = {true, false, true};
        BitSequence bs(src, 3);
        Sequence<Bit> *newBs = bs.InsertAt(Bit(false), 1);

        CHECK(bs.GetLength() == 3);
        CHECK(newBs->GetLength() == 4);
        CHECK(newBs->Get(0) == Bit(true));
        CHECK(newBs->Get(1) == Bit(false));
        CHECK(newBs->Get(2) == Bit(false));
        CHECK(newBs->Get(3) == Bit(true));

        delete newBs;
    }
    ENDTEST();

    TEST("вставка в начало")
    {
        bool src[] = {false, true};
        BitSequence bs(src, 2);
        Sequence<Bit> *newBs = bs.InsertAt(Bit(true), 0);

        CHECK(newBs->GetLength() == 3);
        CHECK(newBs->Get(0) == Bit(true));
        CHECK(newBs->Get(1) == Bit(false));
        CHECK(newBs->Get(2) == Bit(true));

        delete newBs;
    }
    ENDTEST();

    TEST("вставка в конец")
    {
        bool src[] = {true, false};
        BitSequence bs(src, 2);
        Sequence<Bit> *newBs = bs.InsertAt(Bit(true), 2);

        CHECK(newBs->GetLength() == 3);
        CHECK(newBs->Get(0) == Bit(true));
        CHECK(newBs->Get(1) == Bit(false));
        CHECK(newBs->Get(2) == Bit(true));

        delete newBs;
    }
    ENDTEST();

    TEST("за границами")
    {
        bool src[] = {true, false};
        BitSequence bs(src, 2);
        CHECK_THROW(bs.InsertAt(Bit(true), 3), IndexOutOfRange);
    }
    ENDTEST();
}

void TestBitSequence_Where()
{
    TEST("Where true")
    {
        bool src[] = {true, false, true, false, true};
        BitSequence bs(src, 5);
        Sequence<Bit> *result = bs.Where([](const Bit &x)
                                         { return x == Bit(true); });
        CHECK(result->GetLength() == 3);
        CHECK(result->Get(0) == Bit(true));
        CHECK(result->Get(1) == Bit(true));
        CHECK(result->Get(2) == Bit(true));
        delete result;
    }
    ENDTEST();

    TEST("Where false")
    {
        bool src[] = {true, false, true, false};
        BitSequence bs(src, 4);
        Sequence<Bit> *result = bs.Where([](const Bit &x)
                                         { return x == Bit(false); });
        CHECK(result->GetLength() == 2);
        CHECK(result->Get(0) == Bit(false));
        CHECK(result->Get(1) == Bit(false));
        delete result;
    }
    ENDTEST();

    TEST("нет совпадений")
    {
        bool src[] = {false, false, false};
        BitSequence bs(src, 3);
        Sequence<Bit> *result = bs.Where([](const Bit &x)
                                         { return x == Bit(true); });
        CHECK(result->GetLength() == 0);
        delete result;
    }
    ENDTEST();

    TEST("все совпадения")
    {
        bool src[] = {true, true, true};
        BitSequence bs(src, 3);
        Sequence<Bit> *result = bs.Where([](const Bit &x)
                                         { return x == Bit(true); });
        CHECK(result->GetLength() == 3);
        delete result;
    }
    ENDTEST();

    TEST("пустая")
    {
        BitSequence bs;
        Sequence<Bit> *result = bs.Where([](const Bit &x)
                                         { return x == Bit(true); });
        CHECK(result->GetLength() == 0);
        delete result;
    }
    ENDTEST();

    TEST("не меняет исходную")
    {
        bool src[] = {true, false, true};
        BitSequence bs(src, 3);
        Sequence<Bit> *result = bs.Where([](const Bit &x)
                                         { return x == Bit(true); });
        CHECK(bs.GetLength() == 3);
        CHECK(bs.Get(0) == Bit(true));
        delete result;
    }
    ENDTEST();
}

void TestBitSequence_Concat()
{
    TEST("дефолт")
    {
        bool s1[] = {true, false};
        bool s2[] = {true, true};
        BitSequence a(s1, 2);
        BitSequence b(s2, 2);
        Sequence<Bit> *result = a.Concat(&b);
        CHECK(a.GetLength() == 2);
        CHECK(result->GetLength() == 4);
        CHECK(result->Get(0) == Bit(true));
        CHECK(result->Get(1) == Bit(false));
        CHECK(result->Get(2) == Bit(true));
        CHECK(result->Get(3) == Bit(true));
        delete result;
    }
    ENDTEST();

    TEST("c пустой")
    {
        bool src[] = {true, false};
        BitSequence a(src, 2);
        BitSequence b;
        Sequence<Bit> *result = a.Concat(&b);
        CHECK(result->GetLength() == 2);
        CHECK(result->Get(0) == Bit(true));
        CHECK(result->Get(1) == Bit(false));
        delete result;
    }
    ENDTEST();

    TEST("пустая c непустой")
    {
        BitSequence a;
        bool src[] = {true, false};
        BitSequence b(src, 2);
        Sequence<Bit> *result = a.Concat(&b);
        CHECK(result->GetLength() == 2);
        CHECK(result->Get(0) == Bit(true));
        CHECK(result->Get(1) == Bit(false));
        delete result;
    }
    ENDTEST();

    TEST("две пустых")
    {
        BitSequence a, b;
        Sequence<Bit> *result = a.Concat(&b);
        CHECK(result->GetLength() == 0);
        delete result;
    }
    ENDTEST();

    TEST("с nullptr")
    {
        bool src[] = {true};
        BitSequence a(src, 1);
        Sequence<Bit> *result = a.Concat(nullptr);
        CHECK(result->GetLength() == 1);
        CHECK(result->Get(0) == Bit(true));
        delete result;
    }
    ENDTEST();

    TEST("не меняет исходные")
    {
        bool s1[] = {true};
        bool s2[] = {false, true};
        BitSequence a(s1, 1);
        BitSequence b(s2, 2);
        Sequence<Bit> *result = a.Concat(&b);
        CHECK(a.GetLength() == 1);
        CHECK(b.GetLength() == 2);
        delete result;
    }
    ENDTEST();
}

void TestBitSequence_Map()
{
    TEST("Map в Bit инверсия")
    {
        bool src[] = {true, false, true};
        BitSequence bs(src, 3);
        Sequence<Bit> *result = bs.Map<Bit>([](const Bit &x)
                                            { return ~x; });
        CHECK(result->GetLength() == 3);
        CHECK(result->Get(0) == Bit(false));
        CHECK(result->Get(1) == Bit(true));
        CHECK(result->Get(2) == Bit(false));
        delete result;
    }
    ENDTEST();

    TEST("Map в Bit всё в true")
    {
        bool src[] = {true, false, true};
        BitSequence bs(src, 3);
        Sequence<Bit> *result = bs.Map<Bit>([](const Bit &)
                                            { return Bit(true); });
        CHECK(result->GetLength() == 3);
        CHECK(result->Get(0) == Bit(true));
        CHECK(result->Get(1) == Bit(true));
        CHECK(result->Get(2) == Bit(true));
        delete result;
    }
    ENDTEST();

    TEST("Map в int 1 и 0")
    {
        bool src[] = {true, false, true};
        BitSequence bs(src, 3);
        Sequence<int> *result = bs.Map<int>([](const Bit &x)
                                            { return x == Bit(true) ? 1 : 0; });
        CHECK(result->GetLength() == 3);
        CHECK(result->Get(0) == 1);
        CHECK(result->Get(1) == 0);
        CHECK(result->Get(2) == 1);
        delete result;
    }
    ENDTEST();

    TEST("Map в string")
    {
        bool src[] = {true, false};
        BitSequence bs(src, 2);
        Sequence<std::string> *result = bs.Map<std::string>([](const Bit &x)
                                                            { return x == Bit(true) ? "yes" : "no"; });
        CHECK(result->GetLength() == 2);
        CHECK(result->Get(0) == "yes");
        CHECK(result->Get(1) == "no");
        delete result;
    }
    ENDTEST();

    TEST("Map пустая в Bit")
    {
        BitSequence bs;
        Sequence<Bit> *result = bs.Map<Bit>([](const Bit &x)
                                            { return ~x; });
        CHECK(result->GetLength() == 0);
        delete result;
    }
    ENDTEST();

    TEST("Map пустая в int")
    {
        BitSequence bs;
        Sequence<int> *result = bs.Map<int>([](const Bit &)
                                            { return 42; });
        CHECK(result->GetLength() == 0);
        delete result;
    }
    ENDTEST();

    TEST("Map не меняет исходную")
    {
        bool src[] = {true, false, true};
        BitSequence bs(src, 3);
        Sequence<Bit> *result = bs.Map<Bit>([](const Bit &x)
                                            { return ~x; });
        CHECK(bs.GetLength() == 3);
        CHECK(bs.Get(0) == Bit(true));
        CHECK(bs.Get(1) == Bit(false));
        CHECK(bs.Get(2) == Bit(true));
        delete result;
    }
    ENDTEST();

    TEST("Map один элемент")
    {
        bool src[] = {true};
        BitSequence bs(src, 1);
        Sequence<int> *result = bs.Map<int>([](const Bit &){ return 99; });
        CHECK(result->GetLength() == 1);
        CHECK(result->Get(0) == 99);
        delete result;
    }
    ENDTEST();
}

void TestBitSequence_Reduce()
{
    TEST("AND все true")
    {
        bool src[] = {true, true, true};
        BitSequence bs(src, 3);
        Bit result = bs.Reduce<Bit>([](const Bit &a, const Bit &x)
                                    { return a & x; }, Bit(true));
        CHECK(result == Bit(true));
    }
    ENDTEST();

    TEST("AND есть false")
    {
        bool src[] = {true, false, true};
        BitSequence bs(src, 3);
        Bit result = bs.Reduce<Bit>([](const Bit &a, const Bit &x)
                                    { return a & x; }, Bit(true));
        CHECK(result == Bit(false));
    }
    ENDTEST();

    TEST("OR есть true")
    {
        bool src[] = {false, false, true};
        BitSequence bs(src, 3);
        Bit result = bs.Reduce<Bit>([](const Bit &a, const Bit &x)
                                    { return a | x; }, Bit(false));
        CHECK(result == Bit(true));
    }
    ENDTEST();

    TEST("OR все false")
    {
        bool src[] = {false, false, false};
        BitSequence bs(src, 3);
        Bit result = bs.Reduce<Bit>([](const Bit &a, const Bit &x)
                                    { return a | x; }, Bit(false));
        CHECK(result == Bit(false));
    }
    ENDTEST();

    TEST("int подсчёт true")
    {
        bool src[] = {true, false, true, true, false};
        BitSequence bs(src, 5);
        int count = bs.Reduce<int>([](const int &a, const Bit &x)
                                   { return a + (x == Bit(true) ? 1 : 0); }, 0);
        CHECK(count == 3);
    }
    ENDTEST();

    TEST("int подсчёт false")
    {
        bool src[] = {true, false, true, false};
        BitSequence bs(src, 4);
        int count = bs.Reduce<int>([](const int &a, const Bit &x)
                                   { return a + (x == Bit(false) ? 1 : 0); }, 0);
        CHECK(count == 2);
    }
    ENDTEST();

    TEST("int сумма 1/0")
    {
        bool src[] = {true, false, true};
        BitSequence bs(src, 3);
        int sum = bs.Reduce<int>([](const int &a, const Bit &x)
                                 { return a + (x == Bit(true) ? 1 : 0); }, 0);
        CHECK(sum == 2);
    }
    ENDTEST();

    TEST("пустая Bit возвращает init")
    {
        BitSequence bs;
        Bit result = bs.Reduce<Bit>([](const Bit &a, const Bit &x)
                                    { return a | x; }, Bit(false));
        CHECK(result == Bit(false));
    }
    ENDTEST();

    TEST("пустая int возвращает init")
    {
        BitSequence bs;
        int result = bs.Reduce<int>([](const int &a, const Bit &)
                                    { return a + 1; }, 100);
        CHECK(result == 100);
    }
    ENDTEST();

    TEST("один элемент")
    {
        bool src[] = {true};
        BitSequence bs(src, 1);
        int result = bs.Reduce<int>([](const int &a, const Bit &x)
                                    { return a + (x == Bit(true) ? 1 : 0); }, 0);
        CHECK(result == 1);
    }
    ENDTEST();

    TEST("XOR всех")
    {
        bool src[] = {true, true, false, false};
        BitSequence bs(src, 4);
        Bit result = bs.Reduce<Bit>([](const Bit &a, const Bit &x)
                                    { return a ^ x; }, Bit(false));
        CHECK(result == Bit(false));
    }
    ENDTEST();

    TEST("не меняет исходную")
    {
        bool src[] = {true, false, true};
        BitSequence bs(src, 3);
        int result = bs.Reduce<int>([](const int &a, const Bit &)
                                    { return a + 1; }, 0);
        CHECK(bs.GetLength() == 3);
        CHECK(bs.Get(0) == Bit(true));
        CHECK(result == 3);
    }
    ENDTEST();
}

void TestBitSequence_And()
{
    TEST("And одинаковая длина")
    {
        bool s1[] = {true, true, false, false};
        bool s2[] = {true, false, true, false};
        BitSequence a(s1, 4), b(s2, 4);
        BitSequence *r = a.And(b);
        CHECK(r->GetLength() == 4);
        CHECK(r->Get(0) == Bit(true));
        CHECK(r->Get(1) == Bit(false));
        CHECK(r->Get(2) == Bit(false));
        CHECK(r->Get(3) == Bit(false));
        CHECK(r->ToString() == "1000");
        delete r;
    }
    ENDTEST();

    TEST("And все true")
    {
        bool s1[] = {true, true, true};
        bool s2[] = {true, true, true};
        BitSequence a(s1, 3), b(s2, 3);
        BitSequence *r = a.And(b);
        CHECK(r->ToString() == "111");
        delete r;
    }
    ENDTEST();

    TEST("And разная длина")
    {
        bool s1[] = {true, false};
        bool s2[] = {true, true, false};
        BitSequence a(s1, 2), b(s2, 3);
        BitSequence *r = a.And(b);
        CHECK(r->GetLength() == 2);
        CHECK(r->Get(0) == Bit(true));
        CHECK(r->Get(1) == Bit(false));
        delete r;
    }
    ENDTEST();

    TEST("And пустая и непустая")
    {
        bool s2[] = {true, false};
        BitSequence a, b(s2, 2);
        BitSequence *r = a.And(b);
        CHECK(r->GetLength() == 0);
        delete r;
    }
    ENDTEST();

    TEST("And обе пустые")
    {
        BitSequence a, b;
        BitSequence *r = a.And(b);
        CHECK(r->GetLength() == 0);
        delete r;
    }
    ENDTEST();

    TEST("And не меняет исходные")
    {
        bool s1[] = {true, false};
        bool s2[] = {true, true};
        BitSequence a(s1, 2), b(s2, 2);
        BitSequence *r = a.And(b);
        CHECK(a.GetLength() == 2);
        CHECK(a.Get(0) == Bit(true));
        CHECK(a.Get(1) == Bit(false));
        CHECK(b.GetLength() == 2);
        CHECK(b.Get(0) == Bit(true));
        CHECK(b.Get(1) == Bit(true));
        delete r;
    }
    ENDTEST();

    TEST("And один элемент")
    {
        bool s1[] = {true};
        bool s2[] = {false};
        BitSequence a(s1, 1), b(s2, 1);
        BitSequence *r = a.And(b);
        CHECK(r->GetLength() == 1);
        CHECK(r->Get(0) == Bit(false));
        delete r;
    }
    ENDTEST();
}

void TestBitSequence_Or()
{
    TEST("Or одинаковая длина")
    {
        bool s1[] = {true, true, false, false};
        bool s2[] = {true, false, true, false};
        BitSequence a(s1, 4), b(s2, 4);
        BitSequence *r = a.Or(b);
        CHECK(r->GetLength() == 4);
        CHECK(r->Get(0) == Bit(true));
        CHECK(r->Get(1) == Bit(true));
        CHECK(r->Get(2) == Bit(true));
        CHECK(r->Get(3) == Bit(false));
        CHECK(r->ToString() == "1110");
        delete r;
    }
    ENDTEST();

    TEST("Or все true")
    {
        bool s1[] = {true, true};
        bool s2[] = {false, false};
        BitSequence a(s1, 2), b(s2, 2);
        BitSequence *r = a.Or(b);
        CHECK(r->ToString() == "11");
        delete r;
    }
    ENDTEST();

    TEST("Or смешанные")
    {
        bool s1[] = {true, false};
        bool s2[] = {false, true};
        BitSequence a(s1, 2), b(s2, 2);
        BitSequence *r = a.Or(b);
        CHECK(r->ToString() == "11");
        delete r;
    }
    ENDTEST();

    TEST("Or разная длина")
    {
        bool s1[] = {true};
        bool s2[] = {false, true};
        BitSequence a(s1, 1), b(s2, 2);
        BitSequence *r = a.Or(b);
        CHECK(r->GetLength() == 1);
        CHECK(r->Get(0) == Bit(true));
        delete r;
    }
    ENDTEST();

    TEST("Or пустые")
    {
        BitSequence a, b;
        BitSequence *r = a.Or(b);
        CHECK(r->GetLength() == 0);
        delete r;
    }
    ENDTEST();

    TEST("Or не меняет исходные")
    {
        bool s1[] = {true, false};
        bool s2[] = {false, false};
        BitSequence a(s1, 2), b(s2, 2);
        BitSequence *r = a.Or(b);
        CHECK(a.Get(0) == Bit(true));
        CHECK(b.Get(1) == Bit(false));
        delete r;
    }
    ENDTEST();
}

void TestBitSequence_Xor()
{

    TEST("Xor одинаковая длина")
    {
        bool s1[] = {true, true, false, false};
        bool s2[] = {true, false, true, false};
        BitSequence a(s1, 4), b(s2, 4);
        BitSequence *r = a.Xor(b);
        CHECK(r->GetLength() == 4);
        CHECK(r->Get(0) == Bit(false));
        CHECK(r->Get(1) == Bit(true));
        CHECK(r->Get(2) == Bit(true));
        CHECK(r->Get(3) == Bit(false));
        CHECK(r->ToString() == "0110");
        delete r;
    }
    ENDTEST();

    TEST("Xor одинаковые дают 0")
    {
        bool s1[] = {true, false, true};
        bool s2[] = {true, false, true};
        BitSequence a(s1, 3), b(s2, 3);
        BitSequence *r = a.Xor(b);
        CHECK(r->ToString() == "000");
        delete r;
    }
    ENDTEST();

    TEST("Xor противоположные дают 1")
    {
        bool s1[] = {true, false, true};
        bool s2[] = {false, true, false};
        BitSequence a(s1, 3), b(s2, 3);
        BitSequence *r = a.Xor(b);
        CHECK(r->ToString() == "111");
        delete r;
    }
    ENDTEST();

    TEST("Xor все true")
    {
        bool s1[] = {true, true};
        bool s2[] = {true, true};
        BitSequence a(s1, 2), b(s2, 2);
        BitSequence *r = a.Xor(b);
        CHECK(r->ToString() == "00");
        delete r;
    }
    ENDTEST();

    TEST("Xor разная длина")
    {
        bool s1[] = {true, false, true};
        bool s2[] = {false, true};
        BitSequence a(s1, 3), b(s2, 2);
        BitSequence *r = a.Xor(b);
        CHECK(r->GetLength() == 2);
        CHECK(r->Get(0) == Bit(true));
        CHECK(r->Get(1) == Bit(true));
        delete r;
    }
    ENDTEST();

    TEST("Xor пустые")
    {
        BitSequence a, b;
        BitSequence *r = a.Xor(b);
        CHECK(r->GetLength() == 0);
        delete r;
    }
    ENDTEST();

    TEST("Xor не меняет исходные")
    {
        bool s1[] = {true, false};
        bool s2[] = {false, true};
        BitSequence a(s1, 2), b(s2, 2);
        BitSequence *r = a.Xor(b);
        CHECK(a.GetLength() == 2);
        CHECK(b.GetLength() == 2);
        delete r;
    }
    ENDTEST();
}

void TestBitSequence_Not()
{
    TEST("Not смешанные")
    {
        bool src[] = {true, false, true, false};
        BitSequence bs(src, 4);
        BitSequence *r = bs.Not();
        CHECK(r->GetLength() == 4);
        CHECK(r->Get(0) == Bit(false));
        CHECK(r->Get(1) == Bit(true));
        CHECK(r->Get(2) == Bit(false));
        CHECK(r->Get(3) == Bit(true));
        CHECK(r->ToString() == "0101");
        delete r;
    }
    ENDTEST();

    TEST("Not все true")
    {
        bool src[] = {true, true, true};
        BitSequence bs(src, 3);
        BitSequence *r = bs.Not();
        CHECK(r->ToString() == "000");
        delete r;
    }
    ENDTEST();

    TEST("Not пустая")
    {
        BitSequence bs;
        BitSequence *r = bs.Not();
        CHECK(r->GetLength() == 0);
        CHECK(r->ToString() == "");
        delete r;
    }
    ENDTEST();

    TEST("Not не меняет исходную")
    {
        bool src[] = {true, false};
        BitSequence bs(src, 2);
        BitSequence *r = bs.Not();
        CHECK(bs.GetLength() == 2);
        CHECK(bs.Get(0) == Bit(true));
        CHECK(bs.Get(1) == Bit(false));
        delete r;
    }
    ENDTEST();

    TEST("Not дважды")
    {
        bool src[] = {true, false, true};
        BitSequence bs(src, 3);
        BitSequence *r1 = bs.Not();
        BitSequence *r2 = r1->Not();
        CHECK(r2->ToString() == bs.ToString());
        delete r1;
        delete r2;
    }
    ENDTEST();
}

void RunAllBitSeqTests()
{
    std::cout << "Тесты BitSeq" << std::endl;

    TestBitSequence_GetOperations();
    TestBitSequence_Subsequence();
    TestBitSequence_Append();
    TestBitSequence_Prepend();
    TestBitSequence_InsertAt();
    TestBitSequence_Where();
    TestBitSequence_Concat();
    TestBitSequence_Map();
    TestBitSequence_Reduce();
    TestBitSequence_And();
    TestBitSequence_Or();
    TestBitSequence_Xor();
    TestBitSequence_Not();

    if (testsFailed == 0)
    {
        std::cout << "Все тесты успешно пройдены" << std::endl;
    }
    else
    {
        std::cout << "Есть непройденные тесты " << testsFailed << "шт" << std::endl;
    }
}