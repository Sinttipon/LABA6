#pragma once
#include "../Base/exceptions.hpp"
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
    
    Vector &operator=(const Vector &other)
    {
        if (this != &other)
        {
            this->data = other.data;
        }
        return *this;
    }
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

    double Norm() const{
        double sum = 0.0;
        for (size_t i = 0; i < GetLength(); ++i){
            T val = Get(i);
            if constexpr (std::is_same_v<T, std::complex<double>> || std::is_same_v<T, std::complex<float>>){
                sum+= std::norm(val);
            }else{
                sum+=static_cast<double>(val*val);
            }
        }
        return std::sqrt(sum);
    }

    T ScalarProduct(const Vector<T>& other) const{
        if (GetLength() != other.GetLength()){
            throw DimensionMismatchException("Vector::ScalarProduct: размер " + std::to_string(GetLength()) + 
                " != " + std::to_string(other.GetLength()));
        }
        T result = T{};
        for (size_t i = 0; i < GetLength(); ++i){
            result = result + (Get(i) * other.Get(i));
        }
        return result;
    }

    Vector<T> operator+ (const Vector<T>& other) const {
        return Add(other);
    }
    Vector<T> operator* (T scalar) const {
        return MultiByScalar(scalar);
    }
    bool operator== (const Vector<T>& other) const {
        if (GetLength() != other.GetLength()) return false;
        for (size_t i = 0; i < GetLength(); ++i){
            if (Get(i) != other.Get(i)) return false;
        }
        return true;
    }
    bool operator!=(const Vector<T>& other) const {
        return !(*this == other);
    }

    static Vector<int> Range (int start, int end){
        if (start > end) throw std::invalid_argument("Для range start > end");
        size_t count = static_cast<size_t>(end - start + 1);
        int *tmp= new int[count];
        for (size_t i = 0; i < count; ++i){
            tmp[i] = static_cast<int>(start + i);
        }
        Vector<int> res(tmp, count);
        delete[] tmp;
        return res;
    }

    Sequence<Vector<T>*> *Boolean() const {
        size_t n = GetLength();
        if (n > 20) throw std::overflow_error("Boolean слишком много элементов");
        size_t total = 1ULL << n;
        auto *res = new MutableArraySequence<Vector<T> *>();
        for (size_t mask = 0; mask < total; ++mask)
        {
            auto *subset = new MutableArraySequence<T>();
            for (size_t i = 0; i < n; ++i)
            {
                if (mask & (1ULL << i))
                    subset->AppendInternal(Get(i));
            }
            res->AppendInternal(new Vector<T>(subset));
            delete subset;
        }
        return res;
    }

    Sequence<Vector<T>*> *AllSubsequences() const {
        size_t n = GetLength();
        auto *res = new MutableArraySequence<Vector<T> *>();
        res->AppendInternal(new Vector<T>()); 
        for (size_t start = 0; start < n; ++start)
        {
            for (size_t len = 1; len <= n - start; ++len)
            {
                auto *sub = new MutableArraySequence<T>();
                for (size_t i = start; i < start + len; ++i)
                    sub->AppendInternal(Get(i));
                res->AppendInternal(new Vector<T>(sub));
                delete sub;
            }
        }
        return res;
    }
};