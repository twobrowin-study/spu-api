/*
  base_structure.cpp
        - base structure class implementation

  Copyright 2019  Dubrovin Egor <dubrovin.en@ya.ru>
                    Aleksandr Kiryanenko <akiryanenko@mail.ru>
                    Alex Popov <alexpopov@bmstu.ru>
                    Bauman Moscow State Technical University

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "base_structure.hpp"

namespace SPU
{

/***************************************
  BaseStructure class implementation
***************************************/

/* Constructor from nothing */
BaseStructure::BaseStructure() :
  fops("/dev/" SPU_CDEV_NAME), power(0)
{
  adds_rslt_t result = adds();
  if (result.rslt == OK)
  {
    /* Set GSID */
    gsid = result.gsid;
  }
  else
  {
    throw CouldNotCreateStructure();
  }
}

/* Destructor */
BaseStructure::~BaseStructure()
{
  dels();
}

/* ADDS command execution */
adds_rslt_t BaseStructure::adds()
{
  /* Initialize ADDS command */
  adds_cmd_t adds =
      {
          .cmd = ADDS | P_FLAG
      };
  adds_rslt_t result;

  /* Execute ADDS command */
  result = fops.execute<adds_cmd_t, adds_rslt_t>(adds);

  return result;
}

/* DELS command execution */
dels_rslt_t BaseStructure::dels()
{
  /* Initialize DELS command */
  dels_cmd_t dels =
      {
          .cmd  = DELS | P_FLAG,
          .gsid = gsid
      };
  dels_rslt_t result;

  /* Execute DELS command */
  result = fops.execute<dels_cmd_t, dels_rslt_t>(dels);
  
  power = result.power;

  return result;
}

/* Get structure power */
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

/* Delete command execution */
status_t BaseStructure::del(key_t key, flags_t flags)
{
  /* Initialize DEL command */
  del_cmd_t del =
      {
          .cmd  = (cmd_t) ( DEL | flags ),
          .gsid = gsid,
          .key  = key
      };
  del_rslt_t result;

  /* Execute DEL command */
  result = fops.execute<del_cmd_t, del_rslt_t>(del);

  power = result.power;

  return result.rslt;
}

/* Search command execution */
pair_t BaseStructure::search(key_t key, flags_t flags)
{
  /* Initialize SRCH command */
  srch_cmd_t srch =
      {
          .cmd  = (cmd_t) ( SRCH | flags ),
          .gsid = gsid,
          .key  = key
      };
  srch_rslt_t result;

  /* Execute SRCH command */
  result = fops.execute<srch_cmd_t, srch_rslt_t>(srch);

  power = result.power;

  return { result.key, result.val, result.rslt };
}

/* Min command execution */
pair_t BaseStructure::min(flags_t flags)
{
  /* Initialize MIN command */
  min_cmd_t min =
      {
          .cmd  = (cmd_t) ( MIN | flags ),
          .gsid = gsid
      };
  min_rslt_t result;

  /* Execute MIN command */
  result = fops.execute<min_cmd_t, min_rslt_t>(min);

  power = result.power;

  return { result.key, result.val, result.rslt };
}

/* Max command execution */
pair_t BaseStructure::max(flags_t flags)
{
  /* Initialize MAX command */
  max_cmd_t max =
      {
          .cmd  = (cmd_t) ( MAX | flags ),
          .gsid = gsid
      };
  max_rslt_t result;

  /* Execute MAX command */
  result = fops.execute<max_cmd_t, max_rslt_t>(max);

  power = result.power;

  return { result.key, result.val, result.rslt };
}

/* Next command execution */
pair_t BaseStructure::next(key_t key, flags_t flags)
{
  /* Initialize NEXT command */
  next_cmd_t next =
      {
          .cmd  = (cmd_t) ( NEXT | flags ),
          .gsid = gsid,
          .key = key
      };
  next_rslt_t result;

  /* Execute NEXT command */
  result = fops.execute<next_cmd_t, next_rslt_t>(next);

  power = result.power;

  return { result.key, result.val, result.rslt };
}

/* Previous command execution */
pair_t BaseStructure::prev(key_t key, flags_t flags)
{
  /* Initialize PREV command */
  prev_cmd_t prev =
      {
          .cmd  = (cmd_t) ( PREV | flags ),
          .gsid = gsid,
          .key = key
      };
  prev_rslt_t result;

  /* Execute PREV command */
  result = fops.execute<prev_cmd_t, prev_rslt_t>(prev);

  power = result.power;

  return { result.key, result.val, result.rslt };
}

/* Next Smaler command execution */
pair_t BaseStructure::nsm(key_t key, flags_t flags)
{
  /* Initialize NSM command */
  nsm_cmd_t nsm =
      {
          .cmd  = (cmd_t) ( NSM | flags ),
          .gsid = gsid,
          .key = key
      };
  nsm_rslt_t result;

  /* Execute NSM command */
  result = fops.execute<nsm_cmd_t, nsm_rslt_t>(nsm);

  power = result.power;

  return { result.key, result.val, result.rslt };
}

/* Next Greater command execution */
pair_t BaseStructure::ngr(key_t key, flags_t flags)
{
  /* Initialize NGR command */
  ngr_cmd_t ngr =
      {
          .cmd  = (cmd_t) ( NGR | flags ),
          .gsid = gsid,
          .key = key
      };
  ngr_rslt_t result;

  /* Execute NGR command */
  result = fops.execute<ngr_cmd_t, ngr_rslt_t>(ngr);

  power = result.power;

  return { result.key, result.val, result.rslt };
}

} /* namespace SPU */