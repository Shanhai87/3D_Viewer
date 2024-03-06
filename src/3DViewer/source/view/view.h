#ifndef SRC_3DVIEWER_SOURCE_VIEW_VIEW_H
#define SRC_3DVIEWER_SOURCE_VIEW_VIEW_H

#include <QColor>
#include <QColorDialog>
#include <QFileDialog>
#include <QKeyEvent>
#include <QMainWindow>
#include <QMessageBox>
#include <QMovie>
#include <QRegularExpressionValidator>
#include <QSettings>
#include <QTranslator>

#include "../controller/controller.h"
#include "../include/viewer.h"
#include "../model/model.h"
#include "strategy.h"
#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace s21 {

class View : public QMainWindow {
  Q_OBJECT

 public:
  View(Controller *controller, QWidget *parent = nullptr);
  ~View();

  void SetController(Controller *controller) { controller_ = controller; }

 protected:
  void closeEvent(QCloseEvent *event) override;
  void keyPressEvent(QKeyEvent *key) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void wheelEvent(QWheelEvent *event) override;

 private slots:
  void ButtonScaleFunc();
  void ButtonMoveXFunc();
  void ButtonMoveYFunc();
  void ButtonMoveZFunc();
  void ButtonMoveAllFunc();
  void ButtonRotateXFunc();
  void ButtonRotateYFunc();
  void ButtonRotateZFunc();
  void ButtonRotateAllFunc();
  void ButtonResizeFunc();
  void ButtonBkgColorFunc();
  void ButtonEdgeColorFunc();
  void ButtonVertexColorFunc();
  void RadioButtonCentralProjFunc();
  void RadioButtonParallelProjFunc();
  void RadioButtonEdgeSolidFunc();
  void RadioButtonEdgeDashedFunc();
  void RadioButtonVertexNoneFunc();
  void RadioButtonVertexCircleFunc();
  void RadioButtonVertexSquareFunc();
  void SliderVertexSizeFunc();
  void SliderEdgeThicknessFunc();

  void ClearTexture();
  void LoadTexture();

  void ButtonLightXFunc();
  void ButtonLightYFunc();
  void ButtonLightZFunc();
  void ButtonLightAllFunc();

  void ButtonLightColorFunc();
  void ActionEnglishFunc();
  void ActionRussianFunc();
  void ActionImageFunc();
  void ActionGifButtonFunc();
  void ActionGifMovieFunc();
  void ActionOpenGifFunc();
  void ActionOpenObjFunc();
  void ActionSolidFunc();
  void ActionDashedFunc();
  void ActionCentralFunc();
  void ActionParallelFunc();
  void ActionNoneFunc();
  void ActionCircleFunc();
  void ActionSquareFunc();
  void ActionQuitFunc();
  void ActionWireframeFunc();
  void ActionFlatShadingFunc();
  void ActionSmoothShadingFunc();
  void OpenFileIMG();
  void SaveUvMapFunc();

 private:
  Controller *controller_;
  Ui::MainWindow *ui_;
  QMovie movie_;
  QTranslator translator_;
  int language_;
  int mode_;
  int file_type_;
  QString filename_;
  QRegularExpressionValidator double_validator_;
  QRegularExpressionValidator int_validator_;
  QRegularExpressionValidator file_validator_;
  QPointF mouse_position_;
  QFileDialog *filedialog_;
  MediaMaker media_maker_;

  void SetTextImage();
  void SetElementsInterface();
  void LoadSettings();
  void UploadSettings();
  void AddValidators();
  void OpenFileObj();
  void OpenFileGif();
  void SetLanguage(int language);
  void InitFiledialog();
  void SaveMedia(FileType format);
};

}  // namespace s21

#endif  // SRC_3DVIEWER_SOURCE_VIEW_VIEW_H
