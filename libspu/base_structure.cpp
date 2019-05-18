//
// Created by kiryanenko on 18.05.19.
//

#include "base_structure.h"

namespace SPU
{
    /***************************************
      BaseStructure class implementation
    ***************************************/

    /* Constructor from nothing */
    BaseStructure::BaseStructure() :
            fops("/dev/" SPU_CDEV_NAME), power(0)
    {
        adds_rslt_t result = createStructure();
        if (result.rslt == OK) {
            /* Create GSID */
            gsid = result.gsid;
        } else {
            throw CouldNotCreateStructure();
        }
    }

    /* Destructor witch DELS SPU structure */
    BaseStructure::~BaseStructure()
    {
        dels_rslt_t result = deleteStructure();
        power = result.power;
    }

    adds_rslt_t BaseStructure::createStructure() {
        /* Initialize ADDS command */
        adds_cmd_t adds = {.cmd = ADDS | P_FLAG};
        /* Execute ADDS command */
        return fops.execute<adds_cmd_t, adds_rslt_t>(adds);
    }

    dels_rslt_t BaseStructure::deleteStructure() {
        /* Initialize DELS command */
        dels_cmd_t dels = {
            .cmd  = DELS | P_FLAG,
            .gsid = gsid
        };
        /* Execute DELS command */
        return fops.execute<dels_cmd_t, dels_rslt_t>(dels);
    }

    /* Insert command execution */
    u32 BaseStructure::get_power()
    {
        return this->power;
    }

    /* Insert command execution */
    status_t BaseStructure::insert(key_t key, value_t value, flags_t flags)
    {
        /* Initialize INS command */
        ins_cmd_t ins =
                {
                        .cmd  = (cmd_t) ( INS | flags ),
                        .gsid = gsid,
                        .key  = key,
                        .val  = value
                };
        ins_rslt_t result;

        /* Execute INS command */
        result = fops.execute<ins_cmd_t, ins_rslt_t>(ins);

        power = result.power;

        return result.rslt;
    }

    /* Mass vectorized insert command execution */
    status_t BaseStructure::insert(InsertVector insert_vector, flags_t flags)
    {
        for(auto ex : insert_vector)
        {
            status_t status = insert(ex.key, ex.value, flags);
            if(status != OK)
            {
                return status;
            }
        }
        return OK;
    }

    /* Delete command execution */
    status_t BaseStructure::del(key_t key, flags_t flags)
    {
        /* Initialize INS command */
        del_cmd_t del =
                {
                        .cmd  = (cmd_t) ( DEL | flags ),
                        .gsid = gsid,
                        .key  = key
                };
        del_rslt_t result;

        /* Execute del command */
        result = fops.execute<del_cmd_t, del_rslt_t>(del);

        power = result.power;

        return result.rslt;
    }

    /* Search command execution */
    pair_t BaseStructure::search(key_t key, flags_t flags)
    {
        /* Initialize INS command */
        srch_cmd_t srch =
                {
                        .cmd  = (cmd_t) ( SRCH | flags ),
                        .gsid = gsid,
                        .key  = key
                };
        srch_rslt_t result;

        /* Execute srch command */
        result = fops.execute<srch_cmd_t, srch_rslt_t>(srch);

        power = result.power;

        return { result.key, result.val, result.rslt };
    }

    /* Min command execution */
    pair_t BaseStructure::min(flags_t flags)
    {
        /* Initialize INS command */
        min_cmd_t min =
                {
                        .cmd  = (cmd_t) ( MIN | flags ),
                        .gsid = gsid
                };
        min_rslt_t result;

        /* Execute min command */
        result = fops.execute<min_cmd_t, min_rslt_t>(min);

        power = result.power;

        return { result.key, result.val, result.rslt };
    }

    /* Max command execution */
    pair_t BaseStructure::max(flags_t flags)
    {
        /* Initialize INS command */
        max_cmd_t max =
                {
                        .cmd  = (cmd_t) ( MAX | flags ),
                        .gsid = gsid
                };
        max_rslt_t result;

        /* Execute max command */
        result = fops.execute<max_cmd_t, max_rslt_t>(max);

        power = result.power;

        return { result.key, result.val, result.rslt };
    }

    /* Next command execution */
    pair_t BaseStructure::next(key_t key, flags_t flags)
    {
        /* Initialize INS command */
        next_cmd_t next =
                {
                        .cmd  = (cmd_t) ( NEXT | flags ),
                        .gsid = gsid,
                        .key = key
                };
        next_rslt_t result;

        /* Execute next command */
        result = fops.execute<next_cmd_t, next_rslt_t>(next);

        power = result.power;

        return { result.key, result.val, result.rslt };
    }

    /* Previous command execution */
    pair_t BaseStructure::prev(key_t key, flags_t flags)
    {
        /* Initialize INS command */
        prev_cmd_t prev =
                {
                        .cmd  = (cmd_t) ( PREV | flags ),
                        .gsid = gsid,
                        .key = key
                };
        prev_rslt_t result;

        /* Execute prev command */
        result = fops.execute<prev_cmd_t, prev_rslt_t>(prev);

        power = result.power;

        return { result.key, result.val, result.rslt };
    }

    /* Next Smaler command execution */
    pair_t BaseStructure::nsm(key_t key, flags_t flags)
    {
        /* Initialize INS command */
        nsm_cmd_t nsm =
                {
                        .cmd  = (cmd_t) ( NSM | flags ),
                        .gsid = gsid,
                        .key = key
                };
        nsm_rslt_t result;

        /* Execute nsm command */
        result = fops.execute<nsm_cmd_t, nsm_rslt_t>(nsm);

        power = result.power;

        return { result.key, result.val, result.rslt };
    }

    /* Next Greater command execution */
    pair_t BaseStructure::ngr(key_t key, flags_t flags)
    {
        /* Initialize INS command */
        ngr_cmd_t ngr =
                {
                        .cmd  = (cmd_t) ( NGR | flags ),
                        .gsid = gsid,
                        .key = key
                };
        ngr_rslt_t result;

        /* Execute ngr command */
        result = fops.execute<ngr_cmd_t, ngr_rslt_t>(ngr);

        power = result.power;

        return { result.key, result.val, result.rslt };
    }

    gsid_t BaseStructure::get_gsid() {
        return gsid;
    }
}