#pragma once
#include <concepts>
#include <cstddef>

/**
 * @brief Поддержка операций с векторами
 */
template <typename T>
concept number = requires(T t) {
    { t + t } -> std::same_as<T>; 
    { t - t } -> std::same_as<T>; 
    { t * t } -> std::same_as<T>; 
};

/**
 * @brief Аналогичные методы/итераторы/индексация как у sequence или dyArr
 */
template <typename Container>
concept vectorizable = requires(Container c, size_t idx) {
    { c[idx] };                               
    { c.GetLength() } -> std::same_as<size_t>; 
    { c.begin() };                             
    { c.end() };                              
};

/**
 * @brief Для сортировки поиска и сравнения векторов
 */
template <typename T>
concept comparable = requires(T a, T b) {
    { a == b } -> std::convertible_to<bool>;
    { a != b } -> std::convertible_to<bool>;
    { a < b } -> std::convertible_to<bool>;
    { a > b } -> std::convertible_to<bool>;
};

/**
 * @brief Хеш-сумма
 */
template <typename T>
concept hashable = requires(T t) {
    { std::hash<T>{}(t) } -> std::convertible_to<size_t>;
};