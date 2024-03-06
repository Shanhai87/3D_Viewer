#ifndef SRC_3DVIEWER_SOURCE_INCLUDE_VIEWER3D_H
#define SRC_3DVIEWER_SOURCE_INCLUDE_VIEWER3D_H

#define MIN_EDGE_THICKNESS 0
#define MAX_EDGE_THICKNESS 10

#define MIN_VERTEX_SIZE 1
#define MAX_VERTEX_SIZE 10

#define WIDTH 640
#define MIN_WIDTH 50
#define MAX_WIDTH 1280
#define HEIGHT 480
#define MIN_HEIGHT 50
#define MAX_HEIGHT 720

#define SPEED 20

#define FRAMES 50
#define GIF_WIDTH 640
#define GIF_HEIGHT 480

namespace s21 {

enum ParseType { kTexture = 0, kNormal, kVertex };
enum SlashType { kNormalSlash = 0, kTextureSlash };
enum Axis { kX = 0, kY, kZ };
enum ProjectionType { kFrustum = 0, kOrtho };
enum VertexType { kNone = 0, kCircle, kSquare };
enum EdgeType { kSolid = 0, kDashed };
enum TransformType { kMove = 0, kRotate, kScale };
enum FileType { kEmpty = 0, kImage, kGifButton, kGifMovie };
enum Language { kEnglish = 0, kRussian };
enum Mode { kModel = 0, kAnimation, kPicture };
enum ParserErrors { kSuccess = 0, kEmptyFile, kParsingError, kCheckError };
enum GifType { kMovie = 0, kButton };
enum ImageMode { kWireframe = 0, kFlatShading, kSmoothShading };
enum TextureDelete { kTextureDelOff = 0, kTextureDelOn };
enum OpenTexture { kOpenTime = 0, kNotOpenTime };
struct Dimentions {
  double x_min = 0;
  double x_max = 0;
  double y_min = 0;
  double y_max = 0;
  double z_min = 0;
  double z_max = 0;
};

}  // namespace s21

#endif  // SRC_3DVIEWER_SOURCE_INCLUDE_VIEWER3D_H
