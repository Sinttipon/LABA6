#pragma once
#include <iostream>
#include <cassert>
#include <string>
#include <functional>

#include "../Collections/DynamicArray.hpp"
#include "../Collections/ListSequence.h"
#include "../Collections/LinkedList.hpp"
#include "../Collections/BitSequence.h"
#include "../Base/exceptions.hpp"
#include "../Base/Option.hpp"
#define TEST(name)                                    \
    do                                                \
    {                                                 \
        std::cout << "  Тест: " << name << std::endl; \
        try

#define ENDTEST()                                                       \
    catch (const MYException &e)                                        \
    {                                                                   \
        std::cout << "НЕ ПРОЙДЕН: " << e.whatErr() << std::endl;        \
        ++testsFailed;                                                  \
    }                                                                   \
    catch (const std::exception &e)                                     \
    {                                                                   \
        std::cout << "НЕ ПРОЙДЕН: " << e.what() << std::endl;           \
        ++testsFailed;                                                  \
    }                                                                   \
    catch (...)                                                         \
    {                                                                   \
        std::cout << "НЕ ПРОЙДЕН: неизвестное исключение" << std::endl; \
        ++testsFailed;                                                  \
    }                                                                   \
    }                                                                   \
    while (0)

#define CHECK(cond)                                                    \
    do                                                                 \
    {                                                                  \
        if (!(cond))                                                   \
        {                                                              \
            throw TestFailedException("Проверка не пройдена: " #cond); \
        }                                                              \
    } while (0)

#define CHECK_THROW(expr, exc_type)                                                               \
    do                                                                                            \
    {                                                                                             \
        bool caught = false;                                                                      \
        try                                                                                       \
        {                                                                                         \
            expr;                                                                                 \
        }                                                                                         \
        catch (const exc_type &)                                                                  \
        {                                                                                         \
            caught = true;                                                                        \
        }                                                                                         \
        catch (...)                                                                               \
        {                                                                                         \
        }                                                                                         \
        if (!caught)                                                                              \
        {                                                                                         \
            throw TestFailedException("Ожидалось исключение " #exc_type ", но оно не выброшено"); \
        }                                                                                         \
    } while (0)
void RunAllTests();