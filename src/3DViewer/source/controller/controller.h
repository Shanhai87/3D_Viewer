#ifndef SRC_3DVIEWER_SOURCE_CONTROLLER_CONTROLLER_H
#define SRC_3DVIEWER_SOURCE_CONTROLLER_CONTROLLER_H

#include <string>
#include <vector>

#include "../include/viewer.h"
#include "../model/model.h"

namespace s21 {

class Controller {
 public:
  Controller(Model *model) : model_(model) {}
  ~Controller() {}

  void ParseFile(std::string file_name);

  void MakeTransform(double value, TransformType transform,
                     Axis axis = Axis::kX, bool save = true);

  void ReturnToBase();
  void Redo();
  void Undo();
  void ShiftRedo();
  void ShiftUndo();
  void SetHeight(int height);

  void SetWidth(int width);

  void SetErrorMessage(std::string error);

  std::vector<double> &GetWireTextureArray();
  std::vector<unsigned int> &GetTextureIndexArray();
  std::vector<unsigned int> &GetWireIndexArray();
  std::vector<unsigned int> &GetShadeIndexArray();
  std::vector<double> &GetWireVertexArray();
  std::vector<double> &GetShadeVertexArray();
  std::vector<double> &GetNormalArray();
  std::vector<double> &GetTextureArray();

  std::string GetErrorMessage();
  size_t GetCountVertexes();
  int GetScreenWidth();
  int GetScreenHeight();
  std::string GetFilename();
  double GetMaxCoordinate();

 private:
  Model *model_;
};
}  // namespace s21

#endif  // SRC_3DVIEWER_SOURCE_CONTROLLER_CONTROLLER_H
