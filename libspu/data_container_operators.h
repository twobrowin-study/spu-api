//
// Created by kiryanenko on 18.05.19.
//

#ifndef GRAPH_API_DATA_CONTAINER_OPERATORS_H
#define GRAPH_API_DATA_CONTAINER_OPERATORS_H

#include <glob.h>
#include <type_traits>
#include "spu.h"

using namespace std;

namespace SPU
{
    template<class T>
    int cmpContainers(T &c1, T &c2)
    {
        for(u8 i=0; i < arraySize(c1); i++) {
            if (c1[i] != c2[i]) {
                return c1[i] < c2[i] ? -1 : 1;
            }
        }
        return 0;
    }

    template <typename T>
    T addContainers (T &c1, T &c2)
    {
        typename std::remove_const<T>::type ret = {0};
        for (u8 i = 0; i < arraySize(c1); i++) {
            ret[i] = c1[i] + c2[i];
        }
        return ret;
    }

    template <typename T>
    T subContainers (T &c1, T &c2)
    {
        typename std::remove_const<T>::type ret = {0};
        for (u8 i = 0; i < arraySize(c1); i++) {
            ret[i] = c1[i] - c2[i];
        }
        return ret;
    }

    /// префиксная версия возвращает значение после инкремента
    template <class T>
    T & incContainer (T &c1)
    {
        // FIXME инкремирует для последнего элемента
        ++c1[arraySize(c1) - 1];
        return c1;
    }

    /// префиксная версия возвращает значение после дикремента
    template <class T>
    T & decContainer (T &c1)
    {
        // FIXME декремирует для последнего элемента
        --c1[arraySize(c1) - 1];
        return c1;
    }

    /// Побитовое И
    template <typename T>
    T andContainers (const T &c1, const T &c2)
    {
        typename std::remove_const<T>::type ret = {0};
        for(u8 i = 0; i < arraySize(c1); i++) {
            ret[i] = c1[i] & c2[i];
        }
        return ret;
    }

    /// Побитовое ИЛИ
    template <typename T>
    T orContainers (T &c1, T &c2)
    {
        typename std::remove_const<T>::type ret = {0};
        for (u8 i = 0; i < arraySize(c1); i++) {
            ret[i] = c1[i] | c2[i];
        }
        return ret;
    }


    /* Check if all u32 from array is equal */
    bool operator== (const data_t &c1, const data_t &c2);
    bool operator== (const gsid_t &c1, const gsid_t &c2);
    /* Check if any u32 from array not equal */
    bool operator!= (const data_t &c1, const data_t &c2);
    bool operator!= (const gsid_t &c1, const gsid_t &c2);
    /* Check from head if u32 is more then other */
    bool operator>  (const data_t &c1, const data_t &c2);
    bool operator>  (const gsid_t &c1, const gsid_t &c2);
    /* Use other operators */
    bool operator>= (const data_t &c1, const data_t &c2);
    bool operator>= (const gsid_t &c1, const gsid_t &c2);
    /* Check from head if all u32 is less then other */
    bool operator<  (const data_t &c1, const data_t &c2);
    bool operator<  (const gsid_t &c1, const gsid_t &c2);
    /* Use other operators */
    bool operator<= (const data_t &c1, const data_t &c2);
    bool operator<= (const gsid_t &c1, const gsid_t &c2);
    /* Invokes operator for all array */
    data_t operator+ (const data_t &c1, const data_t &c2);
    gsid_t operator+ (const gsid_t &c1, const gsid_t &c2);
    /* Invokes operator for all array */
    data_t operator- (const data_t &c1, const data_t &c2);
    gsid_t operator- (const gsid_t &c1, const gsid_t &c2);
    /* префиксная версия возвращает значение после инкремента */
    data_t & operator++(data_t &c1);
    gsid_t & operator++(gsid_t &c1);
    /* постфиксная версия возвращает значение до инкремента */
    const data_t operator++ (data_t &c1, int);
    const gsid_t operator++ (gsid_t &c1, int);
    /* префиксная версия возвращает значение после декремента */
    data_t & operator--(data_t &c1);
    gsid_t & operator--(gsid_t &c1);
    /* постфиксная версия возвращает значение до декремента */
    const data_t operator-- (data_t &c1, int);
    const gsid_t operator-- (gsid_t &c1, int);
    /* Invokes operator for all array */
    data_t operator& (const data_t &c1, const data_t &c2);
    gsid_t operator& (const gsid_t &c1, const gsid_t &c2);
    /* Invokes operator for all array */
    data_t operator| (const data_t &c1, const data_t &c2);
    gsid_t operator| (const gsid_t &c1, const gsid_t &c2);

    /// Iterates and invokes shift with left part
    data_t operator<< (const data_t &cont, const u8 &shift);
    /* Iterates and invokes shift with left part */
    data_t operator>> (const data_t &cont, const u8 &shift);
}


#endif //GRAPH_API_DATA_CONTAINER_OPERATORS_H
