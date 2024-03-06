#include "controller.h"

namespace s21 {

void Controller::ParseFile(std::string file_name) {
  model_->ParseFile(file_name);
}

void Controller::MakeTransform(double value, TransformType transform, Axis axis,
                               bool save) {
  model_->Transform(value, transform, axis, save);
}

void Controller::ReturnToBase() { model_->ReturnToBase(); }

std::vector<double> &Controller::GetWireTextureArray() {
  return model_->GetWireTextureArray();
}
std::vector<unsigned int> &Controller::GetTextureIndexArray() {
  return model_->GetTextureIndexArray();
}
std::vector<unsigned int> &Controller::GetWireIndexArray() {
  return model_->GetWireIndexArray();
}
std::vector<unsigned int> &Controller::GetShadeIndexArray() {
  return model_->GetShadeIndexArray();
}
std::vector<double> &Controller::GetWireVertexArray() {
  return model_->GetWireVertexArray();
}
std::vector<double> &Controller::GetShadeVertexArray() {
  return model_->GetShadeVertexArray();
}
std::vector<double> &Controller::GetNormalArray() {
  return model_->GetNormalArray();
}
std::vector<double> &Controller::GetTextureArray() {
  return model_->GetTextureArray();
}

std::string Controller::GetErrorMessage() { return model_->GetErrorMessage(); }
size_t Controller::GetCountVertexes() { return model_->GetCountVertexes(); }
int Controller::GetScreenWidth() { return model_->GetScreenWidth(); }
int Controller::GetScreenHeight() { return model_->GetScreenHeight(); }
std::string Controller::GetFilename() { return model_->GetFilename(); }
double Controller::GetMaxCoordinate() { return model_->GetMaxCoordinate(); }

void Controller::SetErrorMessage(std::string error) {
  model_->SetErrorMessage(error);
}

void Controller::ShiftRedo() { model_->Redo(SPEED); }

void Controller::ShiftUndo() { model_->Undo(SPEED); }

void Controller::Redo() { model_->Redo(1); }

void Controller::Undo() { model_->Undo(1); }

void Controller::SetHeight(int height) { model_->SetScreenHeight(height); }

void Controller::SetWidth(int width) { model_->SetScreenWidth(width); }

}  // namespace s21
