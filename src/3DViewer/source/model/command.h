#ifndef SRC_3DVIEWER_SOURCE_CONTROLLER_COMMAND_H
#define SRC_3DVIEWER_SOURCE_CONTROLLER_COMMAND_H

#include <iostream>

#include "../include/viewer.h"
namespace s21 {
class Model;
class Command {
 public:
  virtual ~Command(){};
  virtual void Execute() = 0;
  virtual void Cancel() = 0;

 protected:
  Command(Model *model) : model_(model){};
  Model *model_;
};

class CommandParseFile : public Command {
 public:
  CommandParseFile(Model *model, std::string file)
      : Command(model), new_filename_(file) {}

  void Execute();

  void Cancel();

 private:
  std::string new_filename_;
  std::string old_filename_;
};

class CommandTransform : public Command {
 public:
  CommandTransform(Model *model, double value, TransformType transform,
                   Axis axis = Axis::kX);

  ~CommandTransform() {}

  void Execute();

  void Cancel();

 private:
  double value_;
  TransformType transform_;
  Axis axis_;
};

}  // namespace s21

#endif  // SRC_3DVIEWER_SOURCE_CONTROLLER_COMMAND_H
