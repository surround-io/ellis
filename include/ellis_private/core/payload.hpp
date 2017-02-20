/*
 * @file ellis_private/core/payload.hpp
 *
 * @brief payload -- refcounted payload for ellis nodes.
 *
 */

#pragma once
#ifndef ELLIS_PRIVATE_CORE_PAYLOAD_HPP_
#define ELLIS_PRIVATE_CORE_PAYLOAD_HPP_

#include <ellis/core/node.hpp>
#include <stdint.h>
#include <string>
#include <unordered_map>
#include <vector>

namespace ellis {


namespace payload_types {
  using arr_t = std::vector<node>;
  using map_t = std::unordered_map<std::string, node>;
  using bin_t = std::vector<byte>;
  using str_t = std::string;
  using refcount_t = unsigned;
}


/** Used to store refcount and underlying container type. */
struct payload {
 /** The refcount for the underlying container. */
  payload_types::refcount_t m_refcount;
  union {
    payload_types::arr_t m_arr;
    payload_types::map_t m_map;
    payload_types::bin_t m_bin;
    payload_types::str_t m_str;
  };
};


}  /* namespace ellis */

#endif  /* ELLIS_PRIVATE_CORE_PAYLOAD_HPP_ */
