//
// Created by kiryanenko on 18.05.19.
//

#include "libspu.h"


namespace SPU
{
    /* Convert GSID to string */
    std::string to_string(gsid_t gsid)
    {
        char buf[100];
        snprintf(buf, sizeof(buf), GSID_FORMAT, GSID_VAR(gsid));
        return std::string(buf);
    }

    /* Convert data container to string */
    std::string to_string(struct data_container data, bool hex)
    {
        std::string ret;
        for(u8 i=1; i<SPU_WEIGHT+1; i++)
        {
            char buf[100];

            if(hex)
            {
                snprintf(buf, sizeof(buf), "0x%08x-", data[SPU_WEIGHT-i]);
            }
            else // Decimal
            {
                snprintf(buf, sizeof(buf), "%d-", data[SPU_WEIGHT-i]);
            }

            ret += buf;
        }
        return ret.substr(0, ret.size()-1);
    }

    /* Convert result into string */
    std::string to_string(status_t status)
    {
        /* Check if status is OK */
        if(status == OK)
        {
            return "OK";
        }

        std::string ret;

        /* If status is not OK find all parts */
        if(status & ERR)
        {
            ret += "ERR & ";
        }

        if(status & QERR)
        {
            ret += "QERR & ";
        }

        if(status & OERR)
        {
            ret += "OERR & ";
        }

        return ret.substr(0, ret.size()-3);
    }

    /* Convert key : value pair with status into string */
    std::string to_string(pair_t pair, bool hex)
    {
        return to_string(pair.status) + " : " + to_string(pair.key, hex) + " : " + to_string(pair.value, hex);
    }
}