#ifndef CLEMENTINE_PPFILE_IOSTREAM_H_
#define CLEMENTINE_PPFILE_IOSTREAM_H_

#include "common.h"

#include <ppapi/cpp/file_io.h>
#include <ppapi/cpp/file_ref.h>
#include <ppapi/cpp/instance_handle.h>
#include <taglib/tiostream.h>

class PPFileIOStream : public TagLib::IOStream {
 public:
  PPFileIOStream(pp::FileRef ref, pp::InstanceHandle instance);

  bool Open();

  virtual TagLib::FileName name() const;
  virtual TagLib::ByteVector readBlock(ulong length);
  virtual void writeBlock(const TagLib::ByteVector& data);
  virtual void insert(const TagLib::ByteVector& data,
                      ulong start = 0,
                      ulong replace = 0);
  virtual void removeBlock(ulong start = 0, ulong length = 0);
  virtual bool readOnly() const;
  virtual bool isOpen() const;
  virtual void seek(long offset, TagLib::IOStream::Position p = Beginning);
  virtual long tell() const;
  virtual long length();
  virtual void truncate(long length);

 private:
  pp::FileRef ref_;
  pp::InstanceHandle instance_;
  
  string filename_;
  pp::FileIO io_;
  PP_FileInfo info_;

  long offset_;
};

#endif  // CLEMENTINE_PPFILE_IOSTREAM_H_
