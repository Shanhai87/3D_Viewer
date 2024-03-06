#include "model.h"

namespace s21 {

void Model::SetWire(std::vector<double> vertexes_wire) {
  vertexes_wire_ = vertexes_wire;
}
void Model::SetShade(std::vector<double> vertexes_shade) {
  vertexes_shade_ = vertexes_shade;
}
void Model::SetNormal(std::vector<double> normal_coords) {
  normal_coords_ = normal_coords;
}

void Model::SetFileName(std::string name) { filename_ = name; }

void Model::ParseFile(std::string filename) {
  command_ = new CommandParseFile(this, filename);
  command_->Execute();
  if (GetErrorMessage().empty()) {
    if (command_history_.size() > 0) ClearHistory(0);
    command_history_.push_back(command_);
    index_history_ = 0;
  } else {
    delete command_;
  }
}

void Model::Transform(double value, TransformType transform, Axis axis,
                      bool save) {
  if (!GetFilename().empty()) {
    command_ = new CommandTransform(this, value, transform, axis);
    command_->Execute();
    if (save) {
      if (index_history_ != command_history_.size() - 1) {
        ClearHistory(index_history_ + 1);
      }
      command_history_.push_back(command_);
      ++index_history_;
    } else {
      delete command_;
    }
  }
}

void Model::Redo(int count) {
  for (int i = 0; i < count && command_history_.size() &&
                  index_history_ < command_history_.size() - 1;
       ++i) {
    if (command_history_.size() &&
        index_history_ < command_history_.size() - 1) {
      command_ = command_history_[++index_history_];
      command_->Execute();
    }
  }
}

void Model::Undo(int count) {
  for (int i = 0;
       index_history_ > 0 && command_history_.size() > 0 && i < count; ++i) {
    if (index_history_ > 0 && command_history_.size() > 0) {
      command_ = command_history_[index_history_];
      command_->Cancel();
      --index_history_;
    }
  }
}

void Model::ClearHistory(size_t index) {
  if (index < command_history_.size()) {
    for (size_t i = command_history_.size() - 1; i >= index; --i) {
      delete command_history_[i];
      command_history_.pop_back();
      if (!i) {
        return;
      }
    }
  }
}

void Model::ReturnToBase() {
  if (command_history_.size() > 1) {
    ClearHistory(1);
    index_history_ = 0;
  }
  ReturnToBaseModel();
}

Model::~Model() {
  if (command_history_.size() > 0) ClearHistory(0);
}

std::string Model::GetFilename() { return filename_; }

std::string Model::GetErrorMessage() { return error_message_; }

size_t Model::GetCountVertexes() { return count_vertexes_; }

std::vector<double> &Model::GetWireVertexArray() { return vertexes_wire_; }

std::vector<double> &Model::GetShadeVertexArray() { return vertexes_shade_; }

std::vector<double> &Model::GetNormalArray() { return normal_coords_; }

std::vector<double> &Model::GetTextureArray() { return texture_coords_; }

std::vector<unsigned int> &Model::GetTextureIndexArray() {
  return texture_indexes_;
}
std::vector<double> &Model::GetWireTextureArray() { return textures_; }

std::vector<unsigned int> &Model::GetWireIndexArray() { return wire_indexes_; }

std::vector<unsigned int> &Model::GetShadeIndexArray() {
  return shade_indexes_;
}

void Model::ReturnToBaseModel() {
  normal_coords_ = normal_coords_base_;
  vertexes_wire_ = vertexes_wire_base_;
  vertexes_shade_ = vertexes_shade_base_;
}

int Model::GetScreenHeight() { return screen_height_; }

int Model::GetScreenWidth() { return screen_width_; }

void Model::SetErrorMessage(std::string error) { error_message_ = error; }

double Model::GetMaxCoordinate() { return max_coordinate_; }

void Model::SetVertexesVector(std::vector<double> input) {
  vertexes_wire_ = input;
}

void Model::SetScreenHeight(int height) { screen_height_ = height; }

void Model::SetScreenWidth(int width) { screen_width_ = width; }

void Model::MoveFunc(double move, Axis axes,
                     std::vector<double> &vector_to_move, size_t start,
                     size_t end) {
  for (size_t i = start + axes; i < end; i += 3) {
    vector_to_move[i] += move;
  }
}

void Model::MoveThread(double move, Axis axes,
                       std::vector<double> &vector_to_move) {
  int start = vector_to_move.size() / 6;
  while (start % 3 != 0) ++start;
  std::thread threads[6];
  for (int i = 0; i < 6; ++i) {
    threads[i] = std::thread(
        &s21::Model::MoveFunc, this, move, axes, std::ref(vector_to_move),
        start * i, (i == 5 ? vector_to_move.size() : (i + 1) * start));
  }
  for (int i = 0; i < 6; ++i) {
    threads[i].join();
  }
}

void Model::MoveVector(double move, Axis axes) {
  if (!move || move <= -100000 || move >= 100000) return;
  MoveThread(move, axes, vertexes_wire_);
  MoveThread(move, axes, vertexes_shade_);
}

void Model::RotateFunc(double rotate, int axes1, int axes2,
                       std::vector<double> &vector_to_rotate, size_t start,
                       size_t end) {
  for (size_t i = start; i < end; i += 3) {
    double v1 = vector_to_rotate[i + axes1] * cos(rotate) -
                vector_to_rotate[i + axes2] * sin(rotate);
    double v2 = vector_to_rotate[i + axes1] * sin(rotate) +
                vector_to_rotate[i + axes2] * cos(rotate);
    vector_to_rotate[i + axes1] = v1;
    vector_to_rotate[i + axes2] = v2;
  }
}

void Model::ThreadRotate(int axes1, int axes2, double rotate,
                         std::vector<double> &vector_to_rotate) {
  int start = vector_to_rotate.size() / 6;
  while (start % 3 != 0) ++start;
  std::thread threads[6];
  for (int i = 0; i < 6; ++i) {
    threads[i] =
        std::thread(&s21::Model::RotateFunc, this, rotate, axes1, axes2,
                    std::ref(vector_to_rotate), start * i,
                    (i == 5 ? vector_to_rotate.size() : (i + 1) * start));
  }
  for (int i = 0; i < 6; ++i) {
    threads[i].join();
  }
}

void Model::RotateVector(double rotate, Axis axes) {
  if (!rotate || rotate <= -100000 || rotate >= 100000) return;
  int axes1 = (axes + 1) % 3;
  int axes2 = (axes + 2) % 3;
  rotate = rotate * M_PI / 180;
  ThreadRotate(axes1, axes2, rotate, vertexes_wire_);
  ThreadRotate(axes1, axes2, rotate, vertexes_shade_);
  ThreadRotate(axes1, axes2, rotate, normal_coords_);
}

void Model::ScaleFunc(double scale, std::vector<double> &vector_to_scale,
                      size_t start, size_t end) {
  for (size_t i = start; i < end; ++i) {
    vector_to_scale[i] *= scale;
  }
}

void Model::ScaleThread(double scale, std::vector<double> &vector_to_scale) {
  int start = vector_to_scale.size() / 6;
  while (start % 3 != 0) ++start;
  std::thread threads[6];
  for (int i = 0; i < 6; ++i) {
    threads[i] = std::thread(
        &s21::Model::ScaleFunc, this, scale, std::ref(vector_to_scale),
        start * i, (i == 5 ? vector_to_scale.size() : (i + 1) * start));
  }
  for (int i = 0; i < 6; ++i) {
    threads[i].join();
  }
}

void Model::ScaleVector(double scale) {
  if (scale == 1 || scale <= 0 || scale >= 100000) return;
  ScaleThread(scale, vertexes_wire_);
  ScaleThread(scale, vertexes_shade_);
}

void Model::Init() {
  filename_ = "";
  error_message_ = "";
  count_vertexes_ = 0;
  screen_width_ = WIDTH;
  screen_height_ = HEIGHT;
  max_coordinate_ = 0;
  index_history_ = 0;
}

ParserErrors Model::ParseFileBase(std::string file) {
  Parser parser;
  ParserErrors status = parser.ParseFile(file);
  if (status == kSuccess) {
    filename_ = parser.GetFilename();
    error_message_ = parser.GetErrorMessage();
    count_vertexes_ = parser.GetCountVertexes();
    vertexes_wire_.swap(parser.GetWireVertexArray());
    vertexes_shade_.swap(parser.GetShadeVertexArray());
    textures_.swap(parser.GetWireTextureArray());
    texture_coords_.swap(parser.GetTextureArray());
    texture_indexes_.swap(parser.GetTextureIndexArray());
    wire_indexes_.swap(parser.GetWireIndexArray());
    shade_indexes_.swap(parser.GetShadeIndexArray());
    normal_coords_.swap(parser.GetNormalArray());
    normal_coords_base_ = normal_coords_;
    vertexes_wire_base_ = vertexes_wire_;
    vertexes_shade_base_ = vertexes_shade_;
    screen_width_ = parser.GetScreenWidth();
    screen_height_ = parser.GetScreenHeight();
    max_coordinate_ = parser.GetMaxCoordinate();
  } else {
    error_message_ = parser.GetErrorMessage();
  }
  return status;
}
}  // namespace s21
