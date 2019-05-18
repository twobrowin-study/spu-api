//
// Created by kiryanenko on 18.05.19.
//

#include "data_container_operators.h"

namespace SPU
{
    /* Check if all u32 from array is equal */
    template <typename T>
    bool operator== (const T &c1, const T &c2)
    {
        for(u8 i=0; i < arraySize(c1); i++) {
            if(c1[i] != c2[i]) {
                return false;
            }
        }
        return true;
    }

    /* Check if any u32 from array not equal */
    template <typename T>
    bool operator!= (const T &c1, const T &c2)
    {
        for(u8 i = 0; i < arraySize(c1); i++) {
            if (c1[i] != c2[i]) {
                return true;
            }
        }
        return false;
    }

    /* Check from head if u32 is more then other */
    template <typename T>
    bool operator>  (const T &c1, const T &c2)
    {
        auto size = arraySize(c1);
        for(u8 i = 1; i < size+1; i++) {
            if(c1[size - i] > c2[size - i]) {
                return true;
            }
        }
        return false;
    }

    /* Use other operators */
    template <typename T>
    bool operator>= (const T &c1, const T &c2)
    {
        return (c1 > c2) | (c1 == c2);
    }

    /* Check from head if all u32 is less then other */
    template <typename T>
    bool operator<  (const T &c1, const T &c2)
    {
        auto size = arraySize(c1);
        for (u8 i = 1; i < size + 1; i++) {
            if(c1[size - i] > c2[size - i]) {
                return false;
            }
        }
        return true;
    }

    /* Use other operators */
    template <typename T>
    bool operator<= (const T &c1, const T &c2)
    {
        return (c1 < c2) | (c1 == c2);
    }


    /* Invokes operator for all array */
    template <typename T>
    T operator+ (const T &c1, const T &c2)
    {
        T ret = {0};
        for (u8 i = 0; i < arraySize(c1); i++) {
            ret[i] = c1[i] + c2[i];
        }
        return ret;
    }

    /* префиксная версия возвращает значение после инкремента */
    template <class T>
    T & operator++ (T &c1)
    {
        ++c1[arraySize(c1) - 1];
        return c1;
    }

    /* постфиксная версия возвращает значение до инкремента */
    template <class T>
    const T operator++ (T &c1, int)
    {
        auto prev = c1;
        ++c1[arraySize(c1) - 1];
        return prev;
    }

    /* Invokes operator for all array */
    template <typename T>
    T operator- (const T &c1, const T &c2)
    {
        T ret = {0};
        for (u8 i = 0; i < arraySize(c1); i++) {
            ret[i] = c1[i] - c2[i];
        }
        return ret;
    }

    /* Invokes operator for all array */
    template <typename T>
    data_t operator& (const T &c1, const T &c2)
    {
        data_t ret = {0};
        for(u8 i=0; i<SPU_WEIGHT; i++)
        {
            ret[i] = c1[i] & c2[i];
        }
        return ret;
    }

/* Invokes operator for all array */
    data_t operator| (const data_t &c1, const data_t &c2)
    {
        data_t ret = {0};
        for (u8 i=0; i < arraySize(c1); i++) {
            ret[i] = c1[i] | c2[i];
        }
        return ret;
    }

/* Iterates and invokes shift with left part */
    data_t operator<< (const data_t &cont, const u8 &shift)
    {
        data_t ret = cont;
        if(shift > 0)
        {
            data_t work_cont = cont;
            u8 work_shift    = shift;
            size_t size      = sizeof(u32)*8;

            /* Shift array at all */
            u8 idx = 0;
            while(work_shift >= size)
            {
                work_cont[idx] = 0;
                idx++;
                for(u8 i=idx; i<SPU_WEIGHT; i++)
                {
                    work_cont[i] = cont[i-1];
                }
                work_shift -= size;
            }

            /* Shift every part of array */
            u32 left_part = 0;
            for(u8 i=0; i<SPU_WEIGHT; i++)
            {
                ret[i] = (work_cont[i] << work_shift) | left_part;
                left_part = work_cont[i] >> (size - work_shift);
            }
        }
        return ret;
    }

/* Iterates and invokes shift with left part */
    data_t operator>> (const data_t &cont, const u8 &shift)
    {
        data_t ret = cont;
        if(shift > 0)
        {
            data_t work_cont = cont;
            u8 work_shift    = shift;
            size_t size      = sizeof(u32)*8;

            /* Shift array at all */
            u8 idx = 1;
            while(work_shift >= size)
            {
                work_cont[SPU_WEIGHT-idx] = 0;
                idx++;
                for(u8 i=idx; i<SPU_WEIGHT+1; i++)
                {
                    work_cont[SPU_WEIGHT-i] = cont[SPU_WEIGHT-i+1];
                }
                work_shift -= size;
            }

            /* Shift every part of array */
            u32 left_part = 0;
            for(u8 i=1; i<SPU_WEIGHT+1; i++)
            {
                ret[SPU_WEIGHT-i] = (work_cont[SPU_WEIGHT-i] >> work_shift) | left_part;
                left_part = work_cont[SPU_WEIGHT-i] << (size - work_shift);
            }
        }
        return ret;
    }


}