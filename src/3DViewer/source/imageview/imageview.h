#ifndef SRC_3DVIEWER_SOURCE_IMAGEVIEW_IMAGEVIEW_H
#define SRC_3DVIEWER_SOURCE_IMAGEVIEW_IMAGEVIEW_H
#define GL_SILENCE_DEPRECATION

#include <QOpenGLWidget>

#include "../include/viewer.h"

class ImageView : public QOpenGLWidget {
  Q_OBJECT

 public:
  explicit ImageView(QWidget *parent = nullptr);
  ~ImageView();

  size_t GetCountVertexes();
  void SetCountVertexes(size_t size);
  size_t GetCountWireVertexes();
  void SetCountWireVertexes(size_t size);
  void SetCountShadeVertexes(size_t size);
  void SetWireVertexArray(double *array);
  void SetShadeVertexArray(double *array);
  void SetWireIndexArray(unsigned int *array);
  void SetShadeIndexArray(unsigned int *array);
  void SetNormalArray(double *array);
  void SetTextureArray(double *array);
  int GetProjection();
  void SetProjection(int projection);

  QImage GetTexture();

  void SetMode(s21::ImageMode mode);
  void SetTexture(QImage texture);
  void SetString(QString string);

  void LoadTexture();

  void SetDistanceZ(double distance);
  QColor GetBackgroundColor();
  void SetBackgroundColor(QColor color);
  QColor GetEdgeColor();
  void SetEdgeColor(QColor color);
  QColor GetVertexColor();
  void SetVertexColor(QColor color);
  int GetEdgeThickness();
  void SetEdgeThickness(int thickness);
  int GetEdgeType();
  void SetEdgeType(int type);
  int GetVertexSize();
  void SetVertexSize(int size);
  void SetVertexType(int type);
  int GetVertexType();

  void SetLightColor(QColor light_color);
  void SetPositionAll(float position[3]);
  void SetPositionX(float position_x);
  void SetPositionY(float position_y);
  void SetPositionZ(float position_z);

  QColor GetLightColor();
  float GetLightPositionX();
  float GetLightPositionY();
  float GetLightPositionZ();

 protected:
  void initializeGL() override;
  void resizeGL(int nWidth, int nHeight) override;
  void paintGL() override;

 private:
  size_t count_vertexes_;
  size_t count_wire_vertexes_;
  size_t count_shade_vertexes_;
  double *wire_vertex_array_;
  double *shade_vertex_array_;
  double *normal_array_;
  double *texture_array_;
  unsigned int *wire_index_array_;
  unsigned int *shade_index_array_;
  double distance_z_;
  double screen_scale_;
  int projection_;
  QColor background_color_;
  QColor edge_color_;
  QColor vertex_color_;
  QColor light_color_;
  int edge_thickness_;
  int vertex_size_;
  int vertex_type_;
  int edge_type_;
  float position_[4];
  s21::ImageMode mode_;
  QImage texture_;
  QString string_;

  void Init();
  void SettingBackground();
  void SettingEdge();
  void SettingProjection();
  void DrawVertex();
  void PaintShading();
  void PaintWireFrame();
};

#endif  // SRC_3DVIEWER_SOURCE_IMAGEVIEW_IMAGEVIEW_H
