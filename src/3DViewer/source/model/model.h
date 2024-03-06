#ifndef SRC_3DVIEWER_SOURCE_MODEL_MODEL_H
#define SRC_3DVIEWER_SOURCE_MODEL_MODEL_H

#include <sys/stat.h>

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <thread>
#include <vector>

#include "../include/viewer.h"
#include "command.h"
#include "model_parser.h"

namespace s21 {

class Model {
 public:
  Model() { Init(); }
  ~Model();

  std::string GetFilename();
  std::string GetErrorMessage();
  size_t GetCountVertexes();
  std::vector<double> &GetWireVertexArray();
  std::vector<double> &GetShadeVertexArray();
  std::vector<double> &GetNormalArray();
  std::vector<double> &GetTextureArray();
  std::vector<unsigned int> &GetTextureIndexArray();
  std::vector<double> &GetWireTextureArray();
  std::vector<unsigned int> &GetWireIndexArray();
  std::vector<unsigned int> &GetShadeIndexArray();
  void SetErrorMessage(std::string error);
  double GetMaxCoordinate();
  void SetScreenHeight(int height);
  void SetVertexesVector(std::vector<double> input);
  void SetScreenWidth(int width);
  int GetScreenHeight();
  int GetScreenWidth();
  void ReturnToBaseModel();
  void Init();
  void MoveVector(double move, Axis axes);
  void RotateVector(double rotate, Axis axes);
  void ScaleVector(double scale);
  ParserErrors ParseFileBase(std::string file);

  void ReturnToBase();
  void ParseFile(std::string filename);
  void Transform(double value, TransformType transform, Axis axis = Axis::kX,
                 bool save = true);
  void Redo(int count);
  void Undo(int count);

  void SetWire(std::vector<double> vertexes_wire);
  void SetShade(std::vector<double> vertexes_shade);
  void SetNormal(std::vector<double> normal_coords);
  void SetFileName(std::string name);

 private:
  std::string filename_;
  std::string error_message_;
  size_t count_vertexes_;
  std::vector<double> vertexes_wire_;
  std::vector<double> vertexes_shade_;
  std::vector<double> textures_;
  std::vector<double> texture_coords_;
  std::vector<unsigned int> texture_indexes_;
  std::vector<unsigned int> wire_indexes_;
  std::vector<unsigned int> shade_indexes_;
  std::vector<double> normal_coords_;
  std::vector<double> normal_coords_base_;
  std::vector<double> vertexes_wire_base_;
  std::vector<double> vertexes_shade_base_;
  double screen_width_;
  double screen_height_;
  double max_coordinate_;

  void ScaleThread(double scale, std::vector<double> &vector_to_scale);

  void MoveThread(double move, Axis axes, std::vector<double> &vector_to_move);

  void ScaleFunc(double scale, std::vector<double> &vector_to_scale,
                 size_t start, size_t end);

  void ThreadRotate(int axes1, int axes2, double rotate,
                    std::vector<double> &vector_to_rotate);

  void RotateFunc(double rotate, int axes1, int axes2,
                  std::vector<double> &vector_to_rotate, size_t start,
                  size_t end);

  void MoveFunc(double move, Axis axes, std::vector<double> &vector_to_move,
                size_t start, size_t end);

  size_t index_history_;
  std::vector<Command *> command_history_;
  Command *command_;

  void ClearHistory(size_t index);
};
}  // namespace s21

#endif  // SRC_3DVIEWER_SOURCE_MODEL_MODEL_H
