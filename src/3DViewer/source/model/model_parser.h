#ifndef SRC_3DVIEWER_SOURCE_MODEL_MODEL_PARSER_H
#define SRC_3DVIEWER_SOURCE_MODEL_MODEL_PARSER_H

#include <sys/stat.h>

#include <cmath>
#include <fstream>
#include <sstream>
#include <iostream>
#include <set>
#include <string>
#include <thread>
#include <vector>

#include "../include/viewer.h"

namespace s21 {

class Parser {
 public:
  Parser() { Init(); }
  ~Parser() {}

  std::string GetFilename();
  std::string GetErrorMessage();
  size_t GetCountVertexes();
  std::vector<double> &GetWireVertexArray();
  std::vector<double> &GetShadeVertexArray();
  void SetVertexArray(std::vector<double> input);
  std::vector<unsigned int> &GetNormalIndexArray();

  std::vector<unsigned int> &GetTextureIndexArray();
  std::vector<double> &GetWireTextureArray();

  std::vector<double> &GetNormalArray();
  std::vector<double> &GetNormal();
  std::vector<double> &GetTextureArray();
  void SetVertexArrayToBase();
  std::vector<unsigned int> &GetWireIndexArray();
  std::vector<unsigned int> &GetShadeIndexArray();
  void SetErrorMessage(std::string error);
  double GetMaxCoordinate();
  double GetScreenWidth();
  double GetScreenHeight();
  void SetScreenWidth(int width);
  void SetScreenHeight(int height);
  void Init();
  ParserErrors ParseFile(std::string file);

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
  std::vector<unsigned int> normal_indexes_;
  std::vector<double> normal_coords_;
  std::vector<double> normals_;
  std::vector<double> vertexes_base_;
  double screen_width_;
  double screen_height_;
  double max_coordinate_;

  int IsFile(std::string &str);
  int CheckFileExtension(std::string &str);

  void Clear();

  void ReadFile(std::string &str,
                std::set<std::pair<unsigned int, unsigned int>> &indexes,
                int count, std::string check_line, ParserErrors &result);

  //  ParserErrors ReadFile(
  //      std::string &str,
  //      std::set<std::pair<unsigned int, unsigned int>> &indexes);

  ParserErrors ParseValues(
      std::string &str,
      std::set<std::pair<unsigned int, unsigned int>> &indexes);

  ParserErrors ParseFaceSlash(std::string &string, int &texture_index,
                              int &normal_index);

  ParserErrors AddWireTextureNormal(int value, int &index_to_add, size_t size,
                                    int other);
  void PushTextureIndexes(int texture_index, int first_texture_index, size_t i,
                          size_t size);
  void PushVectorValues(int first, int second, int third);
  void PushToSet(std::set<std::pair<unsigned int, unsigned int>> &indexes,
                 int first, int second);
  void CustomSplit(std::vector<std::string> &strings, std::string &str);

  double GetDoubleFromString(std::string &str);
  ParserErrors ParseTextureNormalVertex(std::vector<std::string> &strings,
                                        ParseType type);
  ParserErrors ParseFace(
      std::vector<std::string> &strings,
      std::set<std::pair<unsigned int, unsigned int>> &indexes);

  void CorrectFunc(double scaling, Dimentions &dimentions,
                   std::vector<double> &vector_to_correct);
  void CorrectVertexes();
  void SetMaxCoordinateFunc(double max, double min, double scaling);
  void SetDimentionsFunc(size_t i, double &max, double &min);
  void SetDimentions(Dimentions &dimentions);
  double SetScale(Dimentions &dimentions);
  void SetMaxCoordinate(double &scaling, Dimentions &dimentions);
  void PushFunc(std::vector<double> &to_vec, std::vector<double> &from_vec,
                int count, int value);
};
}  // namespace s21

#endif  // SRC_3DVIEWER_SOURCE_MODEL_MODEL_PARSER_H
