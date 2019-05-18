//
// Created by kiryanenko on 18.05.19.
//

#ifndef GRAPH_API_DATA_CONTAINER_OPERATORS_H
#define GRAPH_API_DATA_CONTAINER_OPERATORS_H

#include <glob.h>
#include "spu.h"


namespace SPU
{
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
    extern data_t operator+ (const data_t &c1, const data_t &c2);
    extern gsid_t operator+ (const gsid_t &c1, const gsid_t &c2);
    /* префиксная версия возвращает значение после инкремента */
    extern data_t & operator++(data_t &c1);
    extern gsid_t & operator++(gsid_t &c1);
    /* постфиксная версия возвращает значение до инкремента */
    extern const data_t operator++ (const data_t &c1, int);
    extern const gsid_t operator++ (const gsid_t &c1, int);
    /* Invokes operator for all array */
    data_t operator- (const data_t &c1, const data_t &c2);
    gsid_t operator- (const gsid_t &c1, const gsid_t &c2);
    /* Invokes operator for all array */
    data_t operator& (const data_t &c1, const data_t &c2);
    gsid_t operator& (const gsid_t &c1, const gsid_t &c2);
    /* Invokes operator for all array */
    data_t operator| (const data_t &c1, const data_t &c2);
    gsid_t operator| (const gsid_t &c1, const gsid_t &c2);
    /* Iterates and invokes shift with left part */
    data_t operator<< (data_t &cont, const u8 &shift);
    /* Iterates and invokes shift with left part */
    data_t operator>> (data_t &cont, const u8 &shift);

}


#endif //GRAPH_API_DATA_CONTAINER_OPERATORS_H
