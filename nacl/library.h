#ifndef CLEMENTINE_LIBRARY_H_
#define CLEMENTINE_LIBRARY_H_

#include "common.h"

#include "ppapi/cpp/directory_entry.h"
#include "ppapi/cpp/file_system.h"
#include "ppapi/utility/completion_callback_factory.h"
#include "ppapi/utility/threading/simple_thread.h"

class ClementineInstance;


class Library {
 public:
  explicit Library(ClementineInstance* instance);

  void Init();

  void AddDirectory(pp::FileSystem file_system,
                    const string& path,
                    const string& id);

 private:
  void AddDirectoryImpl(int32_t result,
                        pp::FileSystem file_system,
                        const string& path,
                        const string& id);

  void ListCallback(int32_t result,
                    const std::vector<pp::DirectoryEntry>& entries,
                    pp::FileRef /* unused_ref */);

  ClementineInstance* instance_;

  pp::CompletionCallbackFactory<Library> callback_factory_;
  pp::SimpleThread thread_;
};

#endif  // CLEMENTINE_LIBRARY_H_
