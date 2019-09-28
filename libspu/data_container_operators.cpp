////
//// Created by kiryanenko on 18.05.19.
////
//
#include "data_container_operators.h"
//
namespace SPU
{
    /* Check if all u32 from array is equal */
    bool operator== (const data_t &c1, const data_t &c2) { return cmpContainers(c1, c2) == 0; }
    bool operator== (const gsid_t &c1, const gsid_t &c2) { return cmpContainers(c1, c2) == 0; }
    /* Check if any u32 from array not equal */
    bool operator!= (const data_t &c1, const data_t &c2) { return cmpContainers(c1, c2) != 0; }
    bool operator!= (const gsid_t &c1, const gsid_t &c2) { return cmpContainers(c1, c2) != 0; }
    /* Check from head if u32 is more then other */
    bool operator>  (const data_t &c1, const data_t &c2) { return cmpContainers(c1, c2) > 0; }
    bool operator>  (const gsid_t &c1, const gsid_t &c2) { return cmpContainers(c1, c2) > 0; }
    /* Use other operators */
    bool operator>= (const data_t &c1, const data_t &c2) { return cmpContainers(c1, c2) >= 0; }
    bool operator>= (const gsid_t &c1, const gsid_t &c2) { return cmpContainers(c1, c2) >= 0; }
    /* Check from head if all u32 is less then other */
    bool operator<  (const data_t &c1, const data_t &c2) { return cmpContainers(c1, c2) < 0; }
    bool operator<  (const gsid_t &c1, const gsid_t &c2) { return cmpContainers(c1, c2) < 0; }
    /* Use other operators */
    bool operator<= (const data_t &c1, const data_t &c2) { return cmpContainers(c1, c2) <= 0; }
    bool operator<= (const gsid_t &c1, const gsid_t &c2) { return cmpContainers(c1, c2) <= 0; }
    /* Invokes operator for all array */
    data_t operator+ (const data_t &c1, const data_t &c2) { return addContainers(c1, c2); }
    gsid_t operator+ (const gsid_t &c1, const gsid_t &c2) { return addContainers(c1, c2); }
    /* Invokes operator for all array */
    data_t operator- (const data_t &c1, const data_t &c2) { return subContainers(c1, c2); }
    gsid_t operator- (const gsid_t &c1, const gsid_t &c2) { return subContainers(c1, c2); }
    /* префиксная версия возвращает значение после инкремента */
    data_t & operator++(data_t &c1) { return incContainer(c1); }
    gsid_t & operator++(gsid_t &c1) { return incContainer(c1); }
    /* постфиксная версия возвращает значение до инкремента */
    const data_t operator++ (data_t &c1, int) {
        auto prev = c1;
        incContainer(c1);
        return prev;
    }
    const gsid_t operator++ (gsid_t &c1, int) {
        auto prev = c1;
        incContainer(c1);
        return prev;
    }
    /* префиксная версия возвращает значение после декремента */
    data_t & operator--(data_t &c1) { return incContainer(c1); }
    gsid_t & operator--(gsid_t &c1) { return incContainer(c1); }
    /* постфиксная версия возвращает значение до декремента */
    const data_t operator-- (data_t &c1, int) {
        auto prev = c1;
        decContainer(c1);
        return prev;
    }
    const gsid_t operator-- (gsid_t &c1, int) {
        auto prev = c1;
        decContainer(c1);
        return prev;
    }
    /* Invokes operator for all array */
    data_t operator& (const data_t &c1, const data_t &c2) { return andContainers(c1, c2); }
    gsid_t operator& (const gsid_t &c1, const gsid_t &c2) { return andContainers(c1, c2); }
    /* Invokes operator for all array */
    data_t operator| (const data_t &c1, const data_t &c2) { return orContainers(c1, c2); }
    gsid_t operator| (const gsid_t &c1, const gsid_t &c2) { return orContainers(c1, c2); }


    /// Iterates and invokes shift with left part
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