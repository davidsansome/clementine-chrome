#include "ppfile_iostream.h"

#include <ppapi/c/ppb_file_io.h>
#include <ppapi/cpp/instance.h>

PPFileIOStream::PPFileIOStream(pp::FileRef ref, pp::InstanceHandle instance)
    : ref_(ref),
      instance_(instance),
      filename_(ref_.GetPath().AsString()),
      io_(instance),
      offset_(0) {
}

bool PPFileIOStream::Open() {
  int32_t open_result = io_.Open(
      ref_, PP_FILEOPENFLAG_READ, pp::BlockUntilComplete());
  if (open_result != PP_OK) {
    return false;
  }

  int32_t query_result = io_.Query(&info_, pp::BlockUntilComplete());
  if (query_result != PP_OK) {
    return false;
  }

  return true;
}
  
TagLib::FileName PPFileIOStream::name() const {
  return filename_.c_str();
}

TagLib::ByteVector PPFileIOStream::readBlock(ulong length) {
  if (length == 0 || length >= info_.size) {
    return TagLib::ByteVector::null;
  }

  TagLib::ByteVector ret((uint(length)));
  int64_t buf_offset = 0;
  int32_t bytes_read = 0;
  int32_t bytes_to_read = length;
  while (bytes_to_read > 0) {
    bytes_read = io_.Read(offset_,
                          &ret.data()[buf_offset],
                          ret.size() - buf_offset,
                          pp::BlockUntilComplete());
    if (bytes_read > 0) {
      buf_offset += bytes_read;
      offset_ += bytes_read;
      bytes_to_read -= bytes_read;
    } else if (bytes_read < 0) {
      // Error.
      return TagLib::ByteVector::null;
    } else {
      // EOF
      ret.resize(buf_offset);
      break;
    }
  }

  return ret;
}

void PPFileIOStream::writeBlock(const TagLib::ByteVector& data) {
}

void PPFileIOStream::insert(const TagLib::ByteVector& data,
                            ulong start,
                            ulong replace) {
}

void PPFileIOStream::removeBlock(ulong start, ulong length) {
}

bool PPFileIOStream::readOnly() const {
  return true;
}

bool PPFileIOStream::isOpen() const {
  return true;
}

void PPFileIOStream::seek(long offset, TagLib::IOStream::Position p) {
  switch (p) {
    case Beginning:
      offset_ = offset;
      break;
    case Current:
      offset_ += offset;
      break;
    case End:
      offset_ = info_.size + offset;
      break;
  }
}

long PPFileIOStream::tell() const {
  return offset_;
}

long PPFileIOStream::length() {
  return info_.size;
}

void PPFileIOStream::truncate(long length) {
}
