#include <ellis/stream/cpp_input_stream.hpp>

#include <ellis/core/err.hpp>
#include <ellis_private/using.hpp>

namespace ellis {

cpp_input_stream::cpp_input_stream(std::istream &is) : m_is(is) {
}

bool cpp_input_stream::next_input_buf(byte **buf, size_t *bytecount) {
  if (m_pos < m_avail) {
    /* We have some leftover buffer from earlier.  Return that. */
    goto give_buffer;
  }

  /* No more bytes in current block?  Then try to get another one. */
  if (! m_is) {
    // TODO: check fail bits?
    // TODO: not PARSING_ERROR
    m_err.reset(new MAKE_ELLIS_ERR(PARSING_ERROR, "end of file"));
    return false;
  }

  m_pos = 0;
  m_is.read((char*)m_buf, sizeof(m_buf));
  m_avail = (int)m_is.gcount();
  if (m_avail <= 0) {
    // TODO: check fail bits?
    // TODO: not PARSING_ERROR
    m_err.reset(new MAKE_ELLIS_ERR(PARSING_ERROR, "end of file"));
    return false;
  }

give_buffer:
  *buf = m_buf + m_pos;
  *bytecount = m_avail - m_pos;
  /* Treat input as consumed unless put_back is called. */
  m_pos = m_avail;
  return true;
}

void cpp_input_stream::put_back(size_t bytecount) {
  m_pos = m_avail - bytecount;
}

unique_ptr<err> cpp_input_stream::extract_input_error() {
  return std::move(m_err);
}


}  /* namespace ellis */
