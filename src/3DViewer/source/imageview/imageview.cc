#include "imageview.h"

ImageView::ImageView(QWidget *parent) : QOpenGLWidget{parent} { Init(); }

ImageView::~ImageView() {}

size_t ImageView::GetCountVertexes() { return count_vertexes_; }
void ImageView::SetCountVertexes(size_t size) { count_vertexes_ = size; }
size_t ImageView::GetCountWireVertexes() { return count_wire_vertexes_; }
void ImageView::SetCountWireVertexes(size_t size) {
  count_wire_vertexes_ = size;
}
void ImageView::SetCountShadeVertexes(size_t size) {
  count_shade_vertexes_ = size;
}

QColor ImageView::GetBackgroundColor() { return background_color_; }
void ImageView::SetBackgroundColor(QColor color) { background_color_ = color; }

QColor ImageView::GetEdgeColor() { return edge_color_; }
void ImageView::SetEdgeColor(QColor color) { edge_color_ = color; }

QColor ImageView::GetVertexColor() { return vertex_color_; }
void ImageView::SetVertexColor(QColor color) { vertex_color_ = color; }

int ImageView::GetEdgeThickness() { return edge_thickness_; }
void ImageView::SetEdgeThickness(int thickness) { edge_thickness_ = thickness; }

int ImageView::GetEdgeType() { return edge_type_; }
void ImageView::SetEdgeType(int type) { edge_type_ = type; }

int ImageView::GetVertexSize() { return vertex_size_; }

void ImageView::SetVertexSize(int size) { vertex_size_ = size; }

int ImageView::GetVertexType() { return vertex_type_; }

void ImageView::SetVertexType(int size) { vertex_type_ = size; }

int ImageView::GetProjection() { return projection_; }
void ImageView::SetProjection(int projection) { projection_ = projection; }

void ImageView::SetDistanceZ(double distance) { distance_z_ = distance; }

void ImageView::SetWireVertexArray(double *array) {
  wire_vertex_array_ = array;
}
void ImageView::SetShadeVertexArray(double *array) {
  shade_vertex_array_ = array;
}

void ImageView::SetNormalArray(double *array) { normal_array_ = array; }

void ImageView::SetTextureArray(double *array) { texture_array_ = array; }

void ImageView::SetWireIndexArray(unsigned int *array) {
  wire_index_array_ = array;
}
void ImageView::SetShadeIndexArray(unsigned int *array) {
  shade_index_array_ = array;
}

void ImageView::SetMode(s21::ImageMode mode) { mode_ = mode; }

void ImageView::SetTexture(QImage texture) { texture_ = texture; }

void ImageView::SetString(QString string) { string_ = string; }

void ImageView::SetLightColor(QColor light_color) {
  light_color_ = light_color;
}

QImage ImageView::GetTexture() { return texture_; }

QColor ImageView::GetLightColor() { return light_color_; }

float ImageView::GetLightPositionX() { return position_[0]; }
float ImageView::GetLightPositionY() { return position_[1]; }
float ImageView::GetLightPositionZ() { return position_[2]; }

void ImageView::Init() {
  texture_ = QImage();
  distance_z_ = 0;
  screen_scale_ = 1;
  count_vertexes_ = 0;
  count_wire_vertexes_ = 0;
  count_shade_vertexes_ = 0;
  wire_vertex_array_ = nullptr;
  shade_vertex_array_ = nullptr;
  wire_index_array_ = nullptr;
  shade_index_array_ = nullptr;
  mode_ = s21::kWireframe;
  position_[0] = 0;
  position_[1] = 0;
  position_[2] = 0;
  position_[3] = 0;
}

void ImageView::LoadTexture() {
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, 3, GLsizei(texture_.width()),
               GLsizei(texture_.height()), 0, GL_RGBA, GL_UNSIGNED_BYTE,
               texture_.bits());
}

void ImageView::initializeGL() {
  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT);
  glClearDepth(1.0);
  glEnable(GL_DEPTH_TEST);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
}

void ImageView::resizeGL(int, int) {
  if ((double)WIDTH / HEIGHT > (double)width() / height()) {
    screen_scale_ = width() / static_cast<double>(WIDTH);
  } else {
    screen_scale_ = height() / static_cast<double>(HEIGHT);
  }
}

void ImageView::PaintWireFrame() {
  glVertexPointer(3, GL_DOUBLE, 0, wire_vertex_array_);  //каркасный рисунок
  glDrawElements(GL_LINES, count_wire_vertexes_, GL_UNSIGNED_INT,
                 wire_index_array_);  //каркасный рисунок
  DrawVertex();                       //каркасный рисунок
}

void ImageView::PaintShading() {
  glEnable(GL_LIGHTING);  //теневой и текстурный рисунок
  glEnable(GL_LIGHT0);  //теневой и текстурный рисунок
  glEnable(GL_COLOR_MATERIAL);  //теневой и текстурный рисунок
  glEnable(GL_NORMALIZE);  //теневой и текстурный рисунок
  glEnable(GL_TEXTURE_2D);  //текстурный рисунок
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);  //текстурный рисунок
  glEnableClientState(GL_NORMAL_ARRAY);  //теневой и текстурный рисунок
  glVertexPointer(3, GL_DOUBLE, 0,
                  shade_vertex_array_);  //теневой и текстурный рисунок
  glNormalPointer(GL_DOUBLE, 0, normal_array_);  //теневой и текстурный рисунок
  glTexCoordPointer(2, GL_DOUBLE, 0, texture_array_);  //текстурный рисунок
  glDrawElements(GL_TRIANGLES, count_shade_vertexes_, GL_UNSIGNED_INT,
                 shade_index_array_);  // теневой и текстурный рисунок
  glDisable(GL_TEXTURE_2D);  //текстурный рисунок
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);  //текстурный рисунок
  glDisable(GL_LIGHTING);  //теневой и текстурный рисунок
  glDisable(GL_LIGHT0);  //теневой и текстурный рисунок
  glDisable(GL_COLOR_MATERIAL);  //теневой и текстурный рисунок
  glDisable(GL_NORMALIZE);  //теневой и текстурный рисунок
  glDisableClientState(GL_NORMAL_ARRAY);  //теневой и текстурный рисунок
}

void ImageView::SetPositionX(float position_x) { position_[0] = position_x; }

void ImageView::SetPositionY(float position_y) { position_[1] = position_y; }

void ImageView::SetPositionZ(float position_z) { position_[2] = position_z; }

void ImageView::SetPositionAll(float position[]) {
  position_[0] = position[0];
  position_[1] = position[1];
  position_[2] = position[2];
  position_[3] = 0;
}

void ImageView::paintGL() {
  LoadTexture();
  SettingBackground();
  SettingEdge();
  glColor4d(edge_color_.red() / 255.0, edge_color_.green() / 255.0,
            edge_color_.blue() / 255.0, edge_color_.alpha() / 255.0);

  if (mode_ != s21::kWireframe) {
    float ambient_light[3];
    light_color_.getRgbF(&ambient_light[0], &ambient_light[1],
                         &ambient_light[2]);
    glLightfv(GL_LIGHT0, GL_POSITION, position_);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
  }

  SettingProjection();

  glMatrixMode(GL_MODELVIEW);

  if (mode_ == s21::kFlatShading) {
    glShadeModel(GL_FLAT);
  } else {
    glShadeModel(GL_SMOOTH);
  }
  if (!wire_index_array_) {
    return;
  }

  glEnableClientState(GL_VERTEX_ARRAY);

  if (mode_ == s21::kWireframe) {
    PaintWireFrame();
  } else {
    PaintShading();
  }

  glDisableClientState(GL_VERTEX_ARRAY);
}

void ImageView::SettingBackground() {
  glClearColor(
      background_color_.red() / 255.0, background_color_.green() / 255.0,
      background_color_.blue() / 255.0, background_color_.alpha() / 255.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void ImageView::SettingEdge() {
  glColor4d(edge_color_.red() / 255.0, edge_color_.green() / 255.0,
            edge_color_.blue() / 255.0, edge_color_.alpha() / 255.0);
  glLineWidth(edge_thickness_);
  if (edge_type_ == s21::EdgeType::kDashed) {
    glLineStipple(1, 0x00FF);
    glEnable(GL_LINE_STIPPLE);
  } else {
    glDisable(GL_LINE_STIPPLE);
  }
}

void ImageView::SettingProjection() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (projection_ == s21::ProjectionType::kFrustum) {
    glFrustum(-width() / 2, width() / 2, -height() / 2, height() / 2,
              distance_z_ * screen_scale_ * 2,
              distance_z_ * screen_scale_ * 1000);
    glTranslatef(0, 0, -distance_z_ * screen_scale_ * 4);
  } else {
    glOrtho(-width() / 2 - 150, width() / 2 + 150, -height() / 2 - 150,
            height() / 2 + 150, -distance_z_ * screen_scale_ * 1000,
            distance_z_ * screen_scale_ * 1000);
  }
}

void ImageView::DrawVertex() {
  if (vertex_type_ != s21::VertexType::kNone) {
    if (vertex_type_ == s21::VertexType::kCircle) {
      glEnable(GL_POINT_SMOOTH);
    } else if (vertex_type_ == s21::VertexType::kSquare) {
      glDisable(GL_POINT_SMOOTH);
    }
    glPointSize(vertex_size_);
    glColor4d(vertex_color_.red() / 255.0, vertex_color_.green() / 255.0,
              vertex_color_.blue() / 255.0, vertex_color_.alpha());
    glDrawArrays(GL_POINTS, 0, static_cast<int>(count_vertexes_));
  }
}
/// todo multi
/// todo язык
/// todo проверить тесты
/// todo 3,2,2,2,2,3,2,2,2,2,3,2,3,2,2,1
/// todo check inline
