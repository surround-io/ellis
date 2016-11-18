/*
 * @file err.hpp
 *
 * @brief Ellis error public C++ header.
 *
 * This is the C header for Ellis, which implements the standalone Ellis data
 * interaction routines.
 */

#pragma once
#ifndef ELLIS_ERR_HPP_
#define ELLIS_ERR_HPP_

#include <stdexcept>
#include <string>


namespace ellis {


enum class err_code {
  WRONG_TYPE = 4096,
  PARSING_ERROR = 4097,
  NOT_MERGED = 4098,
  PATH_ERROR = 4099,
};


#define MAKE_ELLIS_ERR(CODE, MSG) \
  err((int)CODE, __FILE__, __LINE__, (MSG))


class err : public std::runtime_error {

public:
  int m_code;
  std::string m_file;
  int m_line;

public:
  err(
      int code,
      const std::string &file,
      int line,
      const std::string &msg);
  err(const err &) = default;
  ~err();

  err& operator=(const err &) = default;

  /** Returns the machine-usable error code associated with the error.
   *
   * This value will be one of the normal errno values, such as EINVAL,
   * or one of the Ellis-defined values in err_code. Note that the value
   * will always be negative. */
  int code();

  /** Returns the filename of the location in the code that created the
   * error. */
  std::string file();

  /** Returns the line number of the location in the code that created the
   * error. */
  int line();

  /** Returns the human-readable message associated with the error.  */
  std::string msg();

  /** Return a summary string including code, file, line, and msg. */
  std::string summary();
};


}  /* namespace ellis */

#endif  /* ELLIS_ERR_HPP_ */
