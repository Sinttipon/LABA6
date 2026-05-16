#pragma once
#include "../Base/Sequence.h"
#include "../Collections/ArraySequence.h"
#include "../Base/concepts.hpp"
#include <cmath>
#include <complex>
#include <stdexcept>
#include <functional>

template <typename T>
class Vector: public Sequence<T>{
private:
    MutableArraySequence<T> data;
public:
    Vector(): data() {}
    Vector(const T* items, size_t count): data(items,count){}
    Vector(const Sequence<T>* seq): data(){
        if (seq){
            for (size_t i = 0; i < seq->GetLength(); i++){
                const_cast<MutableArraySequence<T>&>(data).AppendInternal(seq->Get(i));}
        }

    }
    Vector(const Vector& other): data(other.data){}
    ~Vector() override = default;


    T Get(size_t index) const override{
        return data.Get(index);
    }
    size_t GetLength() const override{
        return data.GetLength();
    }
    T GetFirst() const override{
        return data.GetFirst();
    }
    T GetLast() const override{
        return data.GetLast();
    }
    Sequence<T>* GetSubsequence(size_t startIndex, size_t endIndex) const override{
        return data.GetSubsequence(startIndex, endIndex);
    }
    Sequence<T>* Append(const T& item) const override{
        Vector<T>* newVec = new Vector<T>(*this);
        const_cast<MutableArraySequence<T>&>(newVec->data).AppendInternal(item);
        return newVec;
    }
    Sequence<T>* Prepend(const T& item) const override{
        Vector<T> *newVec = new Vector<T>(*this);
        const_cast<MutableArraySequence<T> &>(newVec->data).PrependInternal(item);
        return newVec;
    }
    Sequence<T>* InsertAt(const T& item, size_t index) const override{
        Vector<T>* newVec = new Vector<T>(*this);
        const_cast<MutableArraySequence<T>&>(newVec->data).InsertAtInternal(item,index);
        return newVec;
    }
    Sequence<T>* Concat(const Sequence<T>* other) const override{
        Vector<T>* newVec = new Vector<T>(*this);
        if (other){
            for (size_t i=0; i<other->GetLength(); i++){
                const_cast<MutableArraySequence<T>&>(newVec->data).AppendInternal(other->Get(i));
            }
        }
        return newVec;
    }
    Sequence<T>* Where(std::function<bool(const T&)> predicate) const override{
        return data.Where(predicate);
    }


    Vector<T> Add(const Vector<T>& other) const{
        if (GetLength() != other.GetLength()){
            throw DimensionMismatchException("Vector::Add: ожидался размер " + std::to_string(GetLength()) + 
        " получен " + std::to_string(other.GetLength())
    );
        }

        Vector<T> result;
        for (size_t i = 0; i < GetLength(); ++i){
            const_cast<MutableArraySequence<T>&>(result.data).AppendInternal(Get(i) +other.Get(i));
        }
        return result;

    };
    Vector<T> MultiByScalar(T scalar) const{
        Vector<T> result;
        for (size_t i = 0; i < GetLength(); ++i){
            const_cast<MutableArraySequence<T>&>(result.data).AppendInternal(Get(i)*scalar);
        }
        return result;
    };
};