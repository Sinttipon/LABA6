#include "tests.h"
#include "../ADT/Vector.h"
#include "../Base/exceptions.hpp"
#include <iostream>
#include <cmath>
int testsFailed = 0;

void VectorGetTest()
{
    TEST("Get вектор")
    {
    int arr[]={1,2,3,4,5};
    Vector<int> t(arr,5);
    CHECK(t.GetLength()==5);
    CHECK(t.GetFirst() == 1);
    CHECK(t.GetLast() == 5);
    CHECK(t.Get(1) == 2);
    }
    ENDTEST();
}

void VectorGetSubsequence(){
    TEST("GetSubsequence вектор"){
    int arr[] = {1, 2, 3, 4, 5};
    Vector<int> t(arr, 5);
    Sequence<int> *sub1 = t.GetSubsequence(1, 3);
    CHECK(sub1->GetLength() == 3);
    CHECK(sub1->Get(0) == 2);
    CHECK(sub1->Get(2) == 4);
    delete sub1;
    }
    ENDTEST();
}

void VectorAppendPrepend(){
    TEST("Append и Prepend вектор")
    {
    int arr[] = {1, 2, 3, 4, 5};
    Vector<int> t(arr, 5);
    Sequence<int> *appended = t.Append(99);
    CHECK(appended->GetLength() == 6);
    CHECK(appended->Get(5) == 99);
    CHECK(t.GetLength() == 5); 
    delete appended;

    Sequence<int> *prepended = t.Prepend(0);
    CHECK(prepended->GetLength() == 6);
    CHECK(prepended->Get(0) == 0);
    CHECK(prepended->Get(1) == 1);
    CHECK(t.GetLength() == 5);
    delete prepended;
    }
    ENDTEST();
}

void VectorInsertAt(){
    TEST("InsertAt вектор"){
    int arr[] = {1, 2, 3, 4, 5};
    Vector<int> t(arr, 5);
    Sequence<int> *inserted = t.InsertAt(77, 2);
    CHECK(inserted->GetLength() == 6);
    CHECK(inserted->Get(2) == 77);
    CHECK(inserted->Get(4) == 4); 
    CHECK(t.GetLength() == 5);   
    delete inserted;
    }
    ENDTEST();
}

void VectorConcat(){
    TEST("Concat вектор"){
    int arr[] = {1, 2, 3, 4, 5};
    Vector<int> t(arr, 5);
    int arr2[] = {6, 7};
    Vector<int> t2(arr2, 2);

    Sequence<int> *concat = t.Concat(&t2);
    CHECK(concat->GetLength() == 7);
    CHECK(concat->Get(0) == 1);
    CHECK(concat->Get(5) == 6);
    CHECK(concat->Get(6) == 7);
    CHECK(t.GetLength() == 5); 
    delete concat;

    Sequence<int> *concatNull = t.Concat(nullptr);
    CHECK(concatNull->GetLength() == 5);
    delete concatNull;
    }
    ENDTEST();
}

void VectorAdd(){
    TEST("Add вектор")
    {
        int arrA[] = {1, 2, 3, 4, 5};
        int arrB[] = {5, 4, 3, 2, 1};
        Vector<int> tA(arrA, 5);
        Vector<int> tB(arrB, 5);

        Vector<int> tSum = tA.Add(tB);
        CHECK(tSum.GetLength() == 5);
        CHECK(tSum.Get(0) == 6);
        CHECK(tSum.Get(2) == 6);
        CHECK(tSum.Get(4) == 6);
    }
    ENDTEST();
}

void VectorMultiByScalar(){
    TEST("MultiByScalar вектор"){
        int arr[] = {1, 2, 3, 4, 5};
        Vector<int> t(arr, 5);
        Vector<int> tScaled = t.MultiByScalar(3);
        CHECK(tScaled.GetLength() == 5);
        CHECK(tScaled.Get(0) == 3);
        CHECK(tScaled.Get(4) == 15);
        CHECK(tScaled.GetLength() == 5);
    }
    ENDTEST();
}

void VectorNormTest(){
    TEST("Норма вектор"){
        int arr[] = {3, 4};
        Vector<int> t(arr, 2);
        double norm = t.Norm();
        CHECK(std::abs(norm - 5.0) < 1e-9);
    }
    ENDTEST();
}

void VectorScalarProductTest(){
    TEST("Скалярное произведение")
    {
        int a1[] = {1, 2, 3};
        int a2[] = {4, 5, 6};
        Vector<int> t1(a1, 3);
        Vector<int> t2(a2, 3);
        CHECK(t1.ScalarProduct(t2) == 32);
    }
    ENDTEST();
}

void VectorOperatorsTest1(){
    TEST("operator+ и operator*")
    {
        int a1[] = {1, 2, 3};
        int a2[] = {4, 5, 6};
        Vector<int> t1(a1, 3);
        Vector<int> t2(a2, 3);

        Vector<int> tSum = t1 + t2;
        CHECK(tSum.Get(0) == 5);
        CHECK(tSum.Get(2) == 9);

        Vector<int> tScaled = t1 * 10;
        CHECK(tScaled.Get(0) == 10);
        CHECK(tScaled.Get(2) == 30);
    }
    ENDTEST();
}

void VectorOperatorsTest2(){
    TEST("operator== и operator!=")
    {
        int a1[] = {1, 2, 3};
        int a2[] = {1, 2, 3};
        int a3[] = {1, 2, 4};
        Vector<int> t1(a1, 3);
        Vector<int> t2(a2, 3);
        Vector<int> t3(a3, 3);

        CHECK(t1 == t2);
        CHECK(!(t1 == t3));
        CHECK(t1 != t3);
        CHECK(!(t1 != t2));

        Vector<int> tShort(a1, 2);
        CHECK(t1 != tShort);
    }
    ENDTEST();
}

void VectorRangeTest()
{
    TEST("Range генерация диапазона")
    {
        auto t = Vector<int>::Range(1, 5);
        CHECK(t.GetLength() == 5);
        CHECK(t.Get(0) == 1);
        CHECK(t.Get(4) == 5);

        auto tNeg = Vector<int>::Range(-2, 2);
        CHECK(tNeg.GetLength() == 5);
        CHECK(tNeg.Get(0) == -2);
        CHECK(tNeg.Get(4) == 2);

        bool exceptionThrown = false;
        try {
            Vector<int>::Range(5, 1);
        } catch (const std::invalid_argument&) {
            exceptionThrown = true;
        } catch (...) {}
        
        CHECK(exceptionThrown);
    }
    ENDTEST();
}

void VectorAllSubsequencesTest() {
    TEST("AllSubsequences подмножества") {
        int arr[] = {1, 2, 3};
        Vector<int> t(arr, 3);
        auto* subs = t.AllSubsequences();
        CHECK(subs->GetLength() == 7);
        bool found12 = false;
        bool found13 = false;

        for (size_t i = 0; i < subs->GetLength(); ++i) {
            Vector<int>* sub = dynamic_cast<Vector<int>*>(subs->Get(i));
            if (sub->GetLength() == 2 && sub->Get(0) == 1 && sub->Get(1) == 2)
                found12 = true;
            if (sub->GetLength() == 2 && sub->Get(0) == 1 && sub->Get(1) == 3)
                found13 = true;
            delete sub;
        }
        CHECK(found12);
        CHECK(!found13);
        delete subs;
    }
    ENDTEST();
}

void RunAllVectorTests(){
    std::cout << "Тесты вектор" << std::endl;
    VectorGetTest();
    VectorGetSubsequence();
    VectorAppendPrepend();
    VectorInsertAt();
    VectorConcat();
    VectorAdd();
    VectorMultiByScalar();
    VectorNormTest();
    VectorScalarProductTest();
    VectorOperatorsTest1();
    VectorOperatorsTest2();
    VectorAllSubsequencesTest();
    VectorRangeTest();
    if (testsFailed == 0){
        std::cout << "Все тесты успешно пройдены" << std::endl;
    } else{
        std::cout << "Есть непройденные тесты " << testsFailed << "шт" << std::endl;
    }
}