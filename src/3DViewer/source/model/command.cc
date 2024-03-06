#include "command.h"

#include "model.h"

namespace s21 {

CommandTransform::CommandTransform(Model *model, double value,
                                   TransformType transform, Axis axis)
    : Command(model), value_(value), transform_(transform), axis_(axis) {}

void CommandParseFile::Execute() {
  old_filename_ = "";
  model_->ParseFileBase(new_filename_);
}

void CommandParseFile::Cancel() { model_->ParseFileBase(old_filename_); }

void CommandTransform::Execute() {
  if (transform_ == kMove) {
    model_->MoveVector(value_, axis_);
  } else if (transform_ == kRotate) {
    model_->RotateVector(value_, axis_);
  } else {
    model_->ScaleVector(value_);
  }
}

void CommandTransform::Cancel() {
  if (transform_ == kMove) {
    model_->MoveVector(-1 * value_, axis_);
  } else if (transform_ == kRotate) {
    model_->RotateVector(-1 * value_, axis_);
  } else {
    model_->ScaleVector(1 / value_);
  }
}

}  // namespace s21
