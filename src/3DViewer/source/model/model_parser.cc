#include "model_parser.h"

namespace s21 {

int Parser::IsFile(std::string &str) {
  struct stat s;
  int result = 1;
  if (!stat(str.c_str(), &s)) {
    if (s.st_mode & 0040000) {
      str += " - Is a directory";
    } else if (s.st_mode & 0100000) {
      result = 0;
    } else {
      str += " - Is not a file";
    }
  } else {
    str += " - No such file or directory";
  }
  return result;
}

int Parser::CheckFileExtension(std::string &str) {
  int result = 1;
  if (str.length() > 4 && str.substr(str.length() - 4) == ".obj") {
    result = 0;
  }
  return result;
}

void Parser::ReadFile(std::string &str,
                      std::set<std::pair<unsigned int, unsigned int>> &indexes,
                      int count, std::string check_line, ParserErrors &result) {
  std::string line;
  std::ifstream in(str);
  unsigned int num = 0;
  ParserErrors result_tmp = kSuccess;
  if (in.is_open()) {
    while (std::getline(in, line) && !result_tmp) {
      ++num;
      if (line.length() > 3 && !line.compare(0, count, check_line)) {
        result_tmp = ParseValues(line, indexes);
      }
    }
    if (result_tmp) {
      str += " - Error in " + std::to_string(num) + " line";
    }
    in.close();
  } else {
    str += " - Is unreadable";
    result_tmp = kParsingError;
  }
  if (result_tmp != kSuccess) {
    result = kParsingError;
  }
}

ParserErrors Parser::ParseValues(
    std::string &str,
    std::set<std::pair<unsigned int, unsigned int>> &indexes) {
  std::vector<std::string> split_str;
  std::string temp = str.substr(2);
  ParserErrors result = kParsingError;
  CustomSplit(split_str, temp);
  if (str.at(0) == 'v' && str.at(1) == 't') {
    if (split_str.size() < 2) {
      result = kParsingError;
    } else {
      result = ParseTextureNormalVertex(split_str, kTexture);
    }
  } else if (split_str.size() < 3) {
    result = kParsingError;
  } else if (str.at(0) == 'v' && str.at(1) == 'n') {
    result = ParseTextureNormalVertex(split_str, kNormal);
  } else if (str.at(0) == 'v') {
    result = ParseTextureNormalVertex(split_str, kVertex);
  } else if (str.at(0) == 'f') {
    result = ParseFace(split_str, indexes);
  }
  return result;
}

void Parser::CustomSplit(std::vector<std::string> &strings, std::string &str) {
  int start_index = 0;
  int end_index;
  std::string temp;
  size_t size = str.size();
  size_t i = 0;
  if (i < size && isspace(str[i])) {
    while (i < size && isspace(str[i])) ++i;
    start_index = i;
  }
  for (; i <= size; ++i) {
    if (i == size || isspace(str[i])) {
      end_index = i;
      temp = str.substr(start_index, end_index - start_index);
      strings.push_back(temp);
      while (i < size && isspace(str[i])) ++i;
      start_index = i;
    }
  }
}

ParserErrors Parser::ParseTextureNormalVertex(std::vector<std::string> &strings,
                                              ParseType type) {
  ParserErrors result = kSuccess;
  double num;
  try {
    for (int i = 0; i < (type == kTexture ? 2 : 3); ++i) {
      num = stod(strings[i]);
      if (type == kTexture) {
        textures_.push_back(num);
      } else if (type == kNormal) {
        normals_.push_back(num);
      } else {
        vertexes_wire_.push_back(num);
      }
    }
    if (type == kVertex) {
      count_vertexes_++;
    }
  } catch (...) {
    result = kParsingError;
  }
  return result;
}

ParserErrors Parser::ParseFaceSlash(std::string &string, int &texture_index,
                                    int &normal_index) {
  ParserErrors result = kSuccess;
  int slash = 0;
  size_t size_str = string.size();
  for (size_t j = 0; j < size_str && result == kSuccess; ++j) {
    if (string[j] == '/' && ++slash) {
      if (++j < size_str) {
        if (slash == 1) {
          if (string[j] != '/') {
            int value = stoi(string.substr(j)) - 1;
            result =
                AddWireTextureNormal(value, texture_index, textures_.size(), 2);
          }
        } else if (slash == 2) {
          int value = stoi(string.substr(j)) - 1;
          result =
              AddWireTextureNormal(value, normal_index, normals_.size(), 3);
        }
      } else {
        result = kParsingError;
      }
    }
  }
  return result;
}

void Parser::PushFunc(std::vector<double> &to_vec,
                      std::vector<double> &from_vec, int count, int value) {
  if (!from_vec.empty()) {
    for (short i = 0; i < count; ++i) {
      to_vec.push_back(from_vec[count * value + i]);
    }
  }
}

void Parser::PushVectorValues(int first, int second, int third) {
  std::thread thread1(&s21::Parser::PushFunc, this, std::ref(vertexes_shade_),
                      std::ref(vertexes_wire_), 3, first);
  std::thread thread2(&s21::Parser::PushFunc, this, std::ref(normal_coords_),
                      std::ref(normals_), 3, second);
  std::thread thread3(&s21::Parser::PushFunc, this, std::ref(texture_coords_),
                      std::ref(textures_), 2, third);
  thread1.join();
  thread2.join();
  thread3.join();
  shade_indexes_.push_back(shade_indexes_.size());
}

void Parser::PushToSet(std::set<std::pair<unsigned int, unsigned int>> &indexes,
                       int first, int second) {
  if (second > first) {
    indexes.insert(std::pair(first, second));
  } else if (second < first) {
    indexes.insert(std::pair(second, first));
  }
}

ParserErrors Parser::AddWireTextureNormal(int value, int &index_to_add,
                                          size_t size, int other) {
  ParserErrors result = kSuccess;
  index_to_add = value;
  if (index_to_add < 0) {
    index_to_add += size / other + 1;
  }
  if (index_to_add >= static_cast<int>(size) / other) {
    result = kParsingError;
  }
  return result;
}

void Parser::PushTextureIndexes(int texture_index, int first_texture_index,
                                size_t i, size_t size) {
  if (i) {
    texture_indexes_.push_back(texture_index);
    texture_indexes_.push_back(texture_index);
  }
  if (!i || i == size - 1) {
    texture_indexes_.push_back(first_texture_index);
  }
}

ParserErrors Parser::ParseFace(
    std::vector<std::string> &strings,
    std::set<std::pair<unsigned int, unsigned int>> &indexes) {
  ParserErrors result = kSuccess;
  int num = 0, first_face_num = 0, first_pair_num = 0, texture_index = 0,
      first_texture_index = 0, normal_index = 0, first_normal_index = 0;
  size_t size = strings.size(), triple = 1;
  try {
    for (size_t i = 0; i < size && result == kSuccess; ++i, ++triple) {
      result = AddWireTextureNormal(stoi(strings[i]) - 1, num,
                                    vertexes_wire_.size(), 3);
      if (result == kSuccess) {
        result = ParseFaceSlash(strings[i], texture_index, normal_index);
      } else {
        break;
      }
      PushVectorValues(num, normal_index, texture_index);
      if (!i) {
        first_face_num = first_pair_num = num;
        first_normal_index = normal_index;
        first_texture_index = texture_index;
      } else {
        if (triple != 2 && triple < size) {
          PushVectorValues(first_face_num, first_normal_index,
                           first_texture_index);
          PushVectorValues(num, normal_index, texture_index);
        }
        PushToSet(indexes, num, first_pair_num);
        first_pair_num = num;
      }
      PushTextureIndexes(texture_index, first_texture_index, i, size);
    }
    PushToSet(indexes, num, first_face_num);
  } catch (...) {
    result = kParsingError;
  }
  return result;
}

void Parser::CorrectFunc(double scaling, Dimentions &dimentions,
                         std::vector<double> &vector_to_correct) {
  for (size_t i = 0; i < vector_to_correct.size(); ++i) {
    if (i % 3 == Axis::kX) {
      vector_to_correct[i] -= (dimentions.x_max + dimentions.x_min) / 2;
    } else if (i % 3 == Axis::kY) {
      vector_to_correct[i] -= (dimentions.y_max + dimentions.y_min) / 2;
    } else if (i % 3 == Axis::kZ) {
      vector_to_correct[i] -= (dimentions.z_max + dimentions.z_min) / 2;
    }
    vector_to_correct[i] *= scaling;
  }
}

void Parser::CorrectVertexes() {
  Dimentions dimentions;
  double scaling;
  SetDimentions(dimentions);
  scaling = SetScale(dimentions);
  std::thread thread1(&s21::Parser::CorrectFunc, this, scaling,
                      std::ref(dimentions), std::ref(vertexes_shade_));
  std::thread thread2(&s21::Parser::CorrectFunc, this, scaling,
                      std::ref(dimentions), std::ref(vertexes_wire_));
  thread1.join();
  thread2.join();
  SetMaxCoordinate(scaling, dimentions);
}

void Parser::SetDimentionsFunc(size_t i, double &max, double &min) {
  if (vertexes_wire_[i] > max) {
    max = vertexes_wire_[i];
  } else if (vertexes_wire_[i] < min) {
    min = vertexes_wire_[i];
  }
}

void Parser::SetDimentions(Dimentions &dimentions) {
  for (size_t i = 0; i < vertexes_wire_.size(); ++i) {
    if (i % 3 == Axis::kX) {
      SetDimentionsFunc(i, dimentions.x_max, dimentions.x_min);
    } else if (i % 3 == Axis::kY) {
      SetDimentionsFunc(i, dimentions.y_max, dimentions.y_min);
    } else if (i % 3 == Axis::kZ) {
      SetDimentionsFunc(i, dimentions.z_max, dimentions.z_min);
    }
  }
}

double Parser::SetScale(Dimentions &dimentions) {
  double scaling;
  double width = dimentions.x_max - dimentions.x_min;
  double height = dimentions.y_max - dimentions.y_min;
  if (width / height >= screen_width_ / screen_height_) {
    scaling = screen_width_ / width;
  } else {
    scaling = screen_height_ / height;
  }
  return scaling;
}

void Parser::SetMaxCoordinateFunc(double max, double min, double scaling) {
  double i = (max - min) * scaling / 2;
  if (max_coordinate_ < i) {
    max_coordinate_ = i;
  }
}

void Parser::SetMaxCoordinate(double &scaling, Dimentions &dimentions) {
  max_coordinate_ = (dimentions.x_max - dimentions.x_min) * scaling / 2;
  SetMaxCoordinateFunc(dimentions.y_max, dimentions.y_min, scaling);
  SetMaxCoordinateFunc(dimentions.z_max, dimentions.z_min, scaling);
}

std::string Parser::GetFilename() { return filename_; }

std::string Parser::GetErrorMessage() { return error_message_; }

size_t Parser::GetCountVertexes() { return count_vertexes_; }

void Parser::SetVertexArray(std::vector<double> input) {
  vertexes_wire_ = input;
}
std::vector<double> &Parser::GetWireVertexArray() { return vertexes_wire_; }
std::vector<double> &Parser::GetShadeVertexArray() { return vertexes_shade_; }
void Parser::SetVertexArrayToBase() { vertexes_wire_ = vertexes_base_; }
std::vector<unsigned int> &Parser::GetTextureIndexArray() {
  return texture_indexes_;
}
std::vector<double> &Parser::GetWireTextureArray() { return textures_; }
std::vector<unsigned int> &Parser::GetNormalIndexArray() {
  return normal_indexes_;
}
std::vector<double> &Parser::GetNormalArray() { return normal_coords_; }
std::vector<double> &Parser::GetTextureArray() { return texture_coords_; }

std::vector<double> &Parser::GetNormal() { return normals_; }

std::vector<unsigned int> &Parser::GetWireIndexArray() { return wire_indexes_; }
std::vector<unsigned int> &Parser::GetShadeIndexArray() {
  return shade_indexes_;
}

void Parser::SetErrorMessage(std::string error) { error_message_ = error; }

double Parser::GetMaxCoordinate() { return max_coordinate_; }
double Parser::GetScreenWidth() { return screen_width_; }
double Parser::GetScreenHeight() { return screen_height_; }
void Parser::SetScreenWidth(int width) { screen_width_ = width; }
void Parser::SetScreenHeight(int height) { screen_height_ = height; }

void Parser::Init() {
  filename_ = "";
  error_message_ = "";
  count_vertexes_ = 0;
  screen_width_ = WIDTH;
  screen_height_ = HEIGHT;
  max_coordinate_ = 0;
}

void Parser::Clear() {
  filename_.clear();
  error_message_.clear();
  count_vertexes_ = 0;
  vertexes_wire_.clear();
  vertexes_shade_.clear();
  textures_.clear();
  texture_coords_.clear();
  wire_indexes_.clear();
  shade_indexes_.clear();
  normal_indexes_.clear();
  normal_coords_.clear();
  normals_.clear();
  vertexes_base_.clear();
  max_coordinate_ = 0;
}

ParserErrors Parser::ParseFile(std::string file) {
  Clear();
  if (file.empty()) {
    return kEmptyFile;
  }
  std::set<std::pair<unsigned int, unsigned int>> indexes;
  size_t pos = file.find_last_of('/');
  ParserErrors result = kSuccess;
  if (!IsFile(file) && !CheckFileExtension(file)) {
    std::thread thread1(&s21::Parser::ReadFile, this, std::ref(file),
                        std::ref(indexes), 2, "v ", std::ref(result));
    std::thread thread2(&s21::Parser::ReadFile, this, std::ref(file),
                        std::ref(indexes), 3, "vt ", std::ref(result));
    std::thread thread3(&s21::Parser::ReadFile, this, std::ref(file),
                        std::ref(indexes), 3, "vn ", std::ref(result));
    thread1.join();
    thread2.join();
    thread3.join();
    ReadFile(file, indexes, 2, "f ", result);
  }
  if (result == kSuccess) {
    CorrectVertexes();
    filename_.clear();
    filename_ = file.substr(pos + 1);
    vertexes_base_.clear();
    vertexes_base_ = vertexes_wire_;
    wire_indexes_.clear();
    for (auto &it : indexes) {
      wire_indexes_.push_back(it.first);
      wire_indexes_.push_back(it.second);
    }
    error_message_.clear();
  } else {
    error_message_ = file.substr(pos + 1);
  }
  return result;
}
}  // namespace s21
