#include "instance.h"
#include "library.h"
#include "ppfile_iostream.h"

#include <ppapi/cpp/file_system.h>
#include <taglib/id3v2tag.h>
#include <taglib/mpegfile.h>

Library::Library(ClementineInstance* instance)
    : instance_(instance),
      callback_factory_(this),
      thread_(instance) {
}

void Library::Init() {
  thread_.Start();
}

void Library::AddDirectory(pp::FileSystem file_system,
                           const string& path,
                           const string& id) {
  thread_.message_loop().PostWork(
      callback_factory_.NewCallback(
          &Library::AddDirectoryImpl, file_system, path, id));
}

void Library::AddDirectoryImpl(int32_t result,
                               pp::FileSystem file_system,
                               const string& path,
                               const string& id) {
  pp::FileRef ref(file_system, path.c_str());
  ref.ReadDirectoryEntries(callback_factory_.NewCallbackWithOutput(
      &Library::ListCallback, ref));
}

void Library::ListCallback(int32_t result,
                           const std::vector<pp::DirectoryEntry>& entries,
                           pp::FileRef /* unused_ref */) {
  for (std::vector<pp::DirectoryEntry>::const_iterator it = entries.begin() ;
       it != entries.end() ; ++it) {
    const pp::DirectoryEntry& entry = *it;

    switch (entry.file_type()) {
      case PP_FILETYPE_DIRECTORY:
        // Recurse into this directory.
        entry.file_ref().ReadDirectoryEntries(
            callback_factory_.NewCallbackWithOutput(
                &Library::ListCallback, entry.file_ref()));
        break;
      case PP_FILETYPE_REGULAR: {
        instance_->LogToConsole(PP_LOGLEVEL_LOG, entry.file_ref().GetPath());
        std::unique_ptr<PPFileIOStream> stream(
            new PPFileIOStream(entry.file_ref(), instance_));
        if (!stream->Open()) {
          instance_->LogToConsole(PP_LOGLEVEL_LOG, "Failed to open file");
          continue;
        }

        TagLib::MPEG::File tag(stream.get(),
                               TagLib::ID3v2::FrameFactory::instance(),
                               TagLib::AudioProperties::Accurate);
        pp::VarDictionary dict;
        dict.Set("artist", tag.tag()->artist().to8Bit());
        dict.Set("title", tag.tag()->title().to8Bit());
        dict.Set("album", tag.tag()->album().to8Bit());
        dict.Set("path", entry.file_ref().GetPath());
        instance_->PostMessage(dict);
        break;
      }
      case PP_FILETYPE_OTHER:
        break;
    }
  }
}
