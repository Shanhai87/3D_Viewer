#include <gtest/gtest.h>

#include "../source/controller/controller.h"

TEST(RotateTests, RotateX) {
  s21::Model model;
  std::vector<double> vector1 = {0,  1, 0, -1, 0,  -1, 1, 0,
                                 -1, 1, 0, 1,  -1, 1,  1};
  model.SetWire(vector1);
  model.SetShade(vector1);
  model.SetNormal(vector1);
  vector1 = {0, -1, 0, -1, 0, 1, 1, 0, 1, 1, 0, -1, -1, -1, -1};
  model.SetFileName("123.obj");
  model.Transform(180, s21::kRotate, s21::kX, true);
  //  model.RotateVector(180, s21::kX);
  auto it_1 = model.GetWireVertexArray().begin();
  auto it_2 = model.GetShadeVertexArray().begin();
  auto it_3 = model.GetNormalArray().begin();
  auto it_1_end = model.GetWireVertexArray().end();
  auto it_2_end = model.GetShadeVertexArray().end();
  auto it_3_end = model.GetNormalArray().end();
  for (auto it_check = vector1.begin();
       it_check != vector1.end() && it_1 != it_1_end && it_2 != it_2_end &&
       it_3 != it_3_end;
       ++it_check, ++it_1, ++it_2, ++it_3) {
    EXPECT_NEAR(*it_1, *it_check, 1e-6);
    EXPECT_NEAR(*it_2, *it_check, 1e-6);
    EXPECT_NEAR(*it_3, *it_check, 1e-6);
  }
}

TEST(RotateTests, RotateY) {
  s21::Model model;
  std::vector<double> vector1 = {0,  1, 0, -1, 0,  -1, 1, 0,
                                 -1, 1, 0, 1,  -1, 1,  1};
  model.SetWire(vector1);
  model.SetShade(vector1);
  model.SetNormal(vector1);
  model.RotateVector(180, s21::kY);
  vector1 = {0, 1, 0, 1, 0, 1, -1, 0, 1, -1, 0, -1, 1, 1, -1};
  auto it_1 = model.GetWireVertexArray().begin();
  auto it_2 = model.GetShadeVertexArray().begin();
  auto it_3 = model.GetNormalArray().begin();
  auto it_1_end = model.GetWireVertexArray().end();
  auto it_2_end = model.GetShadeVertexArray().end();
  auto it_3_end = model.GetNormalArray().end();
  for (auto it_check = vector1.begin();
       it_check != vector1.end() && it_1 != it_1_end && it_2 != it_2_end &&
       it_3 != it_3_end;
       ++it_check, ++it_1, ++it_2, ++it_3) {
    EXPECT_NEAR(*it_1, *it_check, 1e-6);
    EXPECT_NEAR(*it_2, *it_check, 1e-6);
    EXPECT_NEAR(*it_3, *it_check, 1e-6);
  }
}

TEST(RotateTests, RotateZ) {
  s21::Model model;
  std::vector<double> vector1 = {0,  1, 0, -1, 0,  -1, 1, 0,
                                 -1, 1, 0, 1,  -1, 1,  1};
  model.SetWire(vector1);
  model.SetShade(vector1);
  model.SetNormal(vector1);
  model.RotateVector(180, s21::kZ);
  vector1 = {0, -1, 0, 1, 0, -1, -1, 0, -1, -1, 0, 1, 1, -1, 1};
  auto it_1 = model.GetWireVertexArray().begin();
  auto it_2 = model.GetShadeVertexArray().begin();
  auto it_3 = model.GetNormalArray().begin();
  auto it_1_end = model.GetWireVertexArray().end();
  auto it_2_end = model.GetShadeVertexArray().end();
  auto it_3_end = model.GetNormalArray().end();
  for (auto it_check = vector1.begin();
       it_check != vector1.end() && it_1 != it_1_end && it_2 != it_2_end &&
       it_3 != it_3_end;
       ++it_check, ++it_1, ++it_2, ++it_3) {
    EXPECT_NEAR(*it_1, *it_check, 1e-6);
    EXPECT_NEAR(*it_2, *it_check, 1e-6);
    EXPECT_NEAR(*it_3, *it_check, 1e-6);
  }
}

TEST(Scale, ScaleUp) {
  s21::Model model;
  std::vector<double> vector1 = {0,  1, 0, -1, 0,  -1, 1, 0,
                                 -1, 1, 0, 1,  -1, 1,  1};
  model.SetWire(vector1);
  model.SetShade(vector1);
  model.SetNormal(vector1);
  model.SetFileName("123.obj");
  model.Transform(2, s21::kScale);
  vector1 = {0, 2, 0, -2, 0, -2, 2, 0, -2, 2, 0, 2, -2, 2, 2};
  auto it_1 = model.GetWireVertexArray().begin();
  auto it_2 = model.GetShadeVertexArray().begin();
  auto it_3 = model.GetNormalArray().begin();
  auto it_1_end = model.GetWireVertexArray().end();
  auto it_2_end = model.GetShadeVertexArray().end();
  auto it_3_end = model.GetNormalArray().end();
  for (auto it_check = vector1.begin();
       it_check != vector1.end() && it_1 != it_1_end && it_2 != it_2_end &&
       it_3 != it_3_end;
       ++it_check, ++it_1, ++it_2, ++it_3) {
    EXPECT_NEAR(*it_1, *it_check, 1e-6);
    EXPECT_NEAR(*it_2, *it_check, 1e-6);
  }
}

TEST(Scale, ScaleDown) {
  s21::Model model;
  std::vector<double> vector1 = {0,  2, 0, -2, 0,  -2, 2, 0,
                                 -2, 2, 0, 2,  -2, 2,  2};
  model.SetWire(vector1);
  model.SetShade(vector1);
  model.SetNormal(vector1);
  model.ScaleVector(0.5);
  vector1 = {0, 1, 0, -1, 0, -1, 1, 0, -1, 1, 0, 1, -1, 1, 1};
  auto it_1 = model.GetWireVertexArray().begin();
  auto it_2 = model.GetShadeVertexArray().begin();
  auto it_3 = model.GetNormalArray().begin();
  auto it_1_end = model.GetWireVertexArray().end();
  auto it_2_end = model.GetShadeVertexArray().end();
  auto it_3_end = model.GetNormalArray().end();
  for (auto it_check = vector1.begin();
       it_check != vector1.end() && it_1 != it_1_end && it_2 != it_2_end &&
       it_3 != it_3_end;
       ++it_check, ++it_1, ++it_2, ++it_3) {
    EXPECT_NEAR(*it_1, *it_check, 1e-6);
    EXPECT_NEAR(*it_2, *it_check, 1e-6);
  }
}

TEST(Move, MoveX) {
  s21::Model model;
  std::vector<double> vector1 = {0,  1, 0, -1, 0,  -1, 1, 0,
                                 -1, 1, 0, 1,  -1, 1,  1};
  model.SetWire(vector1);
  model.SetShade(vector1);
  model.SetNormal(vector1);
  model.MoveVector(1, s21::kX);
  vector1 = {1, 1, 0, 0, 0, -1, 2, 0, -1, 2, 0, 1, 0, 1, 1};
  auto it_1 = model.GetWireVertexArray().begin();
  auto it_2 = model.GetShadeVertexArray().begin();
  auto it_3 = model.GetNormalArray().begin();
  auto it_1_end = model.GetWireVertexArray().end();
  auto it_2_end = model.GetShadeVertexArray().end();
  auto it_3_end = model.GetNormalArray().end();
  for (auto it_check = vector1.begin();
       it_check != vector1.end() && it_1 != it_1_end && it_2 != it_2_end &&
       it_3 != it_3_end;
       ++it_check, ++it_1, ++it_2, ++it_3) {
    EXPECT_NEAR(*it_1, *it_check, 1e-6);
    EXPECT_NEAR(*it_2, *it_check, 1e-6);
  }
}

TEST(Move, MoveY) {
  s21::Model model;
  std::vector<double> vector1 = {0,  1, 0, -1, 0,  -1, 1, 0,
                                 -1, 1, 0, 1,  -1, 1,  1};
  model.SetWire(vector1);
  model.SetShade(vector1);
  model.SetNormal(vector1);
  model.SetFileName("skull.obj");
  model.Transform(1, s21::kMove, s21::kY, true);
  vector1 = {0, 2, 0, -1, 1, -1, 1, 1, -1, 1, 1, 1, -1, 2, 1};
  auto it_1 = model.GetWireVertexArray().begin();
  auto it_2 = model.GetShadeVertexArray().begin();
  auto it_3 = model.GetNormalArray().begin();
  auto it_1_end = model.GetWireVertexArray().end();
  auto it_2_end = model.GetShadeVertexArray().end();
  auto it_3_end = model.GetNormalArray().end();
  for (auto it_check = vector1.begin();
       it_check != vector1.end() && it_1 != it_1_end && it_2 != it_2_end &&
       it_3 != it_3_end;
       ++it_check, ++it_1, ++it_2, ++it_3) {
    EXPECT_NEAR(*it_1, *it_check, 1e-6);
    EXPECT_NEAR(*it_2, *it_check, 1e-6);
  }
}

TEST(Move, MoveZ) {
  s21::Model model;
  std::vector<double> vector1 = {0,  1, 0, -1, 0,  -1, 1, 0,
                                 -1, 1, 0, 1,  -1, 1,  1};
  model.SetWire(vector1);
  model.SetShade(vector1);
  model.SetNormal(vector1);
  model.MoveVector(1, s21::kZ);
  vector1 = {0, 1, 1, -1, 0, 0, 1, 0, 0, 1, 0, 2, -1, 1, 2};
  auto it_1 = model.GetWireVertexArray().begin();
  auto it_2 = model.GetShadeVertexArray().begin();
  auto it_3 = model.GetNormalArray().begin();
  auto it_1_end = model.GetWireVertexArray().end();
  auto it_2_end = model.GetShadeVertexArray().end();
  auto it_3_end = model.GetNormalArray().end();
  auto it_check = vector1.begin();
  for (; it_check != vector1.end() && it_1 != it_1_end && it_2 != it_2_end &&
         it_3 != it_3_end;
       ++it_check, ++it_1, ++it_2, ++it_3) {
    EXPECT_NEAR(*it_1, *it_check, 1e-6);
    EXPECT_NEAR(*it_2, *it_check, 1e-6);
  }
  model.Undo(1);
  vector1 = {0, 1, 0, -1, 0, -1, 1, 0, -1, 1, 0, 1, -1, 1, 1};
  for (it_check = vector1.begin();
       it_check != vector1.end() && it_1 != it_1_end && it_2 != it_2_end &&
       it_3 != it_3_end;
       ++it_check, ++it_1, ++it_2, ++it_3) {
    EXPECT_NEAR(*it_1, *it_check, 1e-6);
    EXPECT_NEAR(*it_2, *it_check, 1e-6);
  }
  vector1 = {0, 1, 1, -1, 0, 0, 1, 0, 0, 1, 0, 2, -1, 1, 2};
  model.Redo(1);
  for (it_check = vector1.begin();
       it_check != vector1.end() && it_1 != it_1_end && it_2 != it_2_end &&
       it_3 != it_3_end;
       ++it_check, ++it_1, ++it_2, ++it_3) {
    EXPECT_NEAR(*it_1, *it_check, 1e-6);
    EXPECT_NEAR(*it_2, *it_check, 1e-6);
  }
  model.ReturnToBase();
  vector1 = {0, 1, 0, -1, 0, -1, 1, 0, -1, 1, 0, 1, -1, 1, 1};
  for (it_check = vector1.begin();
       it_check != vector1.end() && it_1 != it_1_end && it_2 != it_2_end &&
       it_3 != it_3_end;
       ++it_check, ++it_1, ++it_2, ++it_3) {
    EXPECT_NEAR(*it_1, *it_check, 1e-6);
    EXPECT_NEAR(*it_2, *it_check, 1e-6);
  }
}

TEST(Open, open) {
  s21::Model model;
  s21::Controller controller(&model);
  controller.ParseFile("3DViewer/tests/skull.obj");
  EXPECT_EQ(model.GetErrorMessage(), "skull.obj - Error in 18 line");
  EXPECT_TRUE(model.GetWireVertexArray().size() == 0);
  controller.ParseFile("3DViewer/tests/cat.obj");
  EXPECT_TRUE(model.GetWireVertexArray().size() != 15);
  EXPECT_EQ(model.GetFilename(), "cat.obj");
  EXPECT_EQ(model.GetWireIndexArray().size() / 2, 6139);
  EXPECT_EQ(model.GetCountVertexes(), 2247);
  EXPECT_EQ(model.GetScreenHeight(), 480);
  EXPECT_EQ(model.GetScreenWidth(), 640);
  model.GetMaxCoordinate();
  model.GetShadeVertexArray();

  model.GetTextureArray();
  model.GetTextureIndexArray();
  model.GetWireTextureArray();
  model.GetShadeIndexArray();
  model.GetShadeVertexArray();
  //  controller.ParseFile("3DViewer/tests/pyramid.obj");
  //  EXPECT_TRUE(model.GetVertexArray()->size() == 15);
  //  controller.ParseFile("3DViewer/tests/skull11.obj");
  //  EXPECT_EQ(model.GetErrorMessage(), "skull11.obj - No such file or
  //  directory"); controller.ParseFile(""); EXPECT_EQ(model.GetErrorMessage(),
  //  "");
}