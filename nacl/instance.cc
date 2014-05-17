#include "common.h"
#include "instance.h"
#include "library.h"

#include "ppapi/cpp/var_dictionary.h"


ClementineInstance::ClementineInstance(PP_Instance instance)
    : pp::Instance(instance),
      library_(new Library(this)) {
}

ClementineInstance::~ClementineInstance() {
}

bool ClementineInstance::Init(uint32_t argc,
                              const char* argn[],
                              const char* argv[]) {
  library_->Init();
  return true;
}

void ClementineInstance::HandleMessage(const pp::Var& message) {
  if (!message.is_dictionary()) {
    LogToConsole(PP_LOGLEVEL_ERROR, "Received non-dictionary message");
    return;
  }

  pp::VarDictionary dict(message);
  pp::Var method_name_var = dict.Get("method");
  if (!method_name_var.is_string()) {
    LogToConsole(PP_LOGLEVEL_ERROR, "Message did not contain 'method'");
    return;
  }

  string method_name = method_name_var.AsString();
  if (method_name == "Library.AddDirectory") {
    pp::FileSystem fs(dict.Get("fileSystem").AsResource());
    string id(dict.Get("id").AsString());
    string path(dict.Get("path").AsString());

    library_->AddDirectory(fs, path, id);
  }
}
