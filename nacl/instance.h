#ifndef CLEMENTINE_INSTANCE_H_
#define CLEMENTINE_INSTANCE_H_

#include "ppapi/cpp/instance.h"
#include "ppapi/cpp/var.h"

#include <memory>

class Library;

class ClementineInstance : public pp::Instance {
 public:
  explicit ClementineInstance(PP_Instance instance);
  virtual ~ClementineInstance();

  virtual bool Init(uint32_t argc,
                    const char* argn[],
                    const char* argv[]);

  virtual void HandleMessage(const pp::Var& var_message);

 private:
  std::unique_ptr<Library> library_;
};

#endif  // CLEMENTINE_INSTANCE_H_
