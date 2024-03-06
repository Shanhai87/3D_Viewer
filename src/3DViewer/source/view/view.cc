#include "view.h"

#include <QPainter>
#include <iostream>

namespace s21 {

View::View(Controller *controller, QWidget *parent)
    : QMainWindow(parent), controller_(controller), ui_(new Ui::MainWindow) {
  ui_->setupUi(this);
  mode_ = kModel;
  file_type_ = kEmpty;
  LoadSettings();
  SetElementsInterface();
  SetTextImage();
  AddValidators();
  InitFiledialog();

  connect(ui_->actionGifButton, SIGNAL(triggered()), this,
          SLOT(ActionGifButtonFunc()));
  connect(ui_->actionGifMovie, SIGNAL(triggered()), this,
          SLOT(ActionGifMovieFunc()));
  connect(ui_->actionEnglish, SIGNAL(triggered()), this,
          SLOT(ActionEnglishFunc()));
  connect(ui_->actionRussian, SIGNAL(triggered()), this,
          SLOT(ActionRussianFunc()));
  connect(ui_->actionOpenOBJ, SIGNAL(triggered()), this,
          SLOT(ActionOpenObjFunc()));
  connect(ui_->actionOpenGIF, SIGNAL(triggered()), this,
          SLOT(ActionOpenGifFunc()));
  connect(ui_->actionImage, SIGNAL(triggered()), this, SLOT(ActionImageFunc()));
  connect(ui_->actionSolid, SIGNAL(triggered()), this, SLOT(ActionSolidFunc()));
  connect(ui_->actionDashed, SIGNAL(triggered()), this,
          SLOT(ActionDashedFunc()));
  connect(ui_->actionCentral, SIGNAL(triggered()), this,
          SLOT(ActionCentralFunc()));
  connect(ui_->actionParallel, SIGNAL(triggered()), this,
          SLOT(ActionParallelFunc()));
  connect(ui_->actionNone, SIGNAL(triggered()), this, SLOT(ActionNoneFunc()));
  connect(ui_->actionCircle, SIGNAL(triggered()), this,
          SLOT(ActionCircleFunc()));
  connect(ui_->actionSquare, SIGNAL(triggered()), this,
          SLOT(ActionSquareFunc()));
  connect(ui_->actionQuit, SIGNAL(triggered()), this, SLOT(ActionQuitFunc()));

  connect(ui_->buttonScale, SIGNAL(released()), this, SLOT(ButtonScaleFunc()));
  connect(ui_->buttonMoveX, SIGNAL(released()), this, SLOT(ButtonMoveXFunc()));
  connect(ui_->buttonMoveY, SIGNAL(released()), this, SLOT(ButtonMoveYFunc()));
  connect(ui_->buttonMoveZ, SIGNAL(released()), this, SLOT(ButtonMoveZFunc()));
  connect(ui_->buttonMoveAll, SIGNAL(released()), this,
          SLOT(ButtonMoveAllFunc()));
  connect(ui_->buttonRotateX, SIGNAL(released()), this,
          SLOT(ButtonRotateXFunc()));
  connect(ui_->buttonRotateY, SIGNAL(released()), this,
          SLOT(ButtonRotateYFunc()));
  connect(ui_->buttonRotateZ, SIGNAL(released()), this,
          SLOT(ButtonRotateZFunc()));
  connect(ui_->buttonRotateAll, SIGNAL(released()), this,
          SLOT(ButtonRotateAllFunc()));
  connect(ui_->buttonResize, SIGNAL(released()), this,
          SLOT(ButtonResizeFunc()));
  connect(ui_->radioButtonCentralProj, SIGNAL(released()), this,
          SLOT(RadioButtonCentralProjFunc()));
  connect(ui_->radioButtonParallelProj, SIGNAL(released()), this,
          SLOT(RadioButtonParallelProjFunc()));

  connect(ui_->sliderVertexSize, &QSlider::valueChanged, this,
          &View::SliderVertexSizeFunc);
  connect(ui_->sliderEdgeThickness, &QSlider::valueChanged, this,
          &View::SliderEdgeThicknessFunc);

  connect(ui_->buttonBkgColor, SIGNAL(clicked()), this,
          SLOT(ButtonBkgColorFunc()));
  connect(ui_->buttonEdgeColor, SIGNAL(clicked()), this,
          SLOT(ButtonEdgeColorFunc()));
  connect(ui_->buttonVertexColor, SIGNAL(clicked()), this,
          SLOT(ButtonVertexColorFunc()));
  connect(ui_->radioButtonEdgeSolid, SIGNAL(clicked()), this,
          SLOT(RadioButtonEdgeSolidFunc()));
  connect(ui_->radioButtonEdgeDashed, SIGNAL(clicked()), this,
          SLOT(RadioButtonEdgeDashedFunc()));
  connect(ui_->radioButtonVertexNone, SIGNAL(clicked()), this,
          SLOT(RadioButtonVertexNoneFunc()));
  connect(ui_->radioButtonVertexCircle, SIGNAL(clicked()), this,
          SLOT(RadioButtonVertexCircleFunc()));
  connect(ui_->radioButtonVertexSquare, SIGNAL(clicked()), this,
          SLOT(RadioButtonVertexSquareFunc()));
  connect(ui_->actionWireframe, SIGNAL(triggered()), this,
          SLOT(ActionWireframeFunc()));
  connect(ui_->actionFlatShading, SIGNAL(triggered()), this,
          SLOT(ActionFlatShadingFunc()));
  connect(ui_->actionSmoothShading, SIGNAL(triggered()), this,
          SLOT(ActionSmoothShadingFunc()));

  connect(ui_->actionLoadTexture, SIGNAL(triggered()), this,
          SLOT(LoadTexture()));

  connect(ui_->actionDeleteTexture, SIGNAL(triggered()), this,
          SLOT(ClearTexture()));

  connect(ui_->actionOpenIMAGE, SIGNAL(triggered()), this, SLOT(OpenFileIMG()));

  connect(ui_->actionSaveUvMap, SIGNAL(triggered()), this,
          SLOT(SaveUvMapFunc()));

  connect(ui_->buttonLightColor, SIGNAL(clicked()), this,
          SLOT(ButtonLightColorFunc()));

  connect(ui_->buttonLightX, SIGNAL(released()), this,
          SLOT(ButtonLightXFunc()));
  connect(ui_->buttonLightY, SIGNAL(released()), this,
          SLOT(ButtonLightYFunc()));
  connect(ui_->buttonLightZ, SIGNAL(released()), this,
          SLOT(ButtonLightZFunc()));
  connect(ui_->buttonLightAll, SIGNAL(released()), this,
          SLOT(ButtonLightAllFunc()));
}

View::~View() { delete ui_; }

void View::closeEvent(QCloseEvent *event) {
  QMessageBox::StandardButton res_button = QMessageBox::question(
      this, tr("3DViewer"), tr("Are you sure?\n"),
      QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel,
      QMessageBox::Yes);
  if (res_button != QMessageBox::Yes) {
    event->ignore();
  } else {
    UploadSettings();
    event->accept();
  }
}

void View::ButtonLightXFunc() {
  double value = ui_->lineEditLightX->text().toDouble();
  ui_->widget->SetPositionX(value);
  ui_->widget->update();
}

void View::ButtonLightYFunc() {
  double value = ui_->lineEditLightY->text().toDouble();
  ui_->widget->SetPositionY(value);
  ui_->widget->update();
}

void View::ButtonLightZFunc() {
  double value = ui_->lineEditLightZ->text().toDouble();
  ui_->widget->SetPositionZ(value);
  ui_->widget->update();
}

void View::ButtonLightAllFunc() {
  double value_x = ui_->lineEditLightX->text().toDouble();
  double value_y = ui_->lineEditLightY->text().toDouble();
  double value_z = ui_->lineEditLightZ->text().toDouble();
  ui_->widget->SetPositionX(value_x);
  ui_->widget->SetPositionY(value_y);
  ui_->widget->SetPositionZ(value_z);
  ui_->widget->update();
}

void View::ButtonLightColorFunc() {
  QColor light_color = QColorDialog::getColor(
      ui_->widget->GetEdgeColor(), this, tr("Choose light color"),
      QColorDialog::DontUseNativeDialog | QColorDialog::ShowAlphaChannel);
  if (light_color.isValid()) {
    ui_->widget->SetLightColor(light_color);
    ui_->buttonLightColor->setStyleSheet("background-color: " +
                                         light_color.name());
    ui_->widget->update();
  }
}

void View::SaveUvMapFunc() {
  QImage tex = ui_->widget->GetTexture();
  QPainter painter(&tex);
  if (ui_->widget->GetEdgeType() == kDashed) {
    painter.setPen(QPen(ui_->widget->GetEdgeColor(), 1, Qt::DotLine));
  } else {
    painter.setPen(QPen(ui_->widget->GetEdgeColor(), 1, Qt::SolidLine));
  }
  std::vector<double> vec = controller_->GetWireTextureArray();
  std::vector<unsigned int> ind = controller_->GetTextureIndexArray();
  size_t size = ind.size();
  for (size_t i = 0; i < size; i += 2) {
    painter.drawLine(tex.width() * vec.at(2 * ind.at(i)),
                     tex.height() * vec.at(2 * ind.at(i) + 1),
                     tex.width() * vec.at(2 * ind.at(i + 1)),
                     tex.height() * vec.at(2 * ind.at(i + 1) + 1));
  }
  QStringList save_filename;
  filedialog_->setDefaultSuffix("bmp");
  filedialog_->setNameFilter("BMP (*.bmp)");
  if (filedialog_->exec()) {
    save_filename = filedialog_->selectedFiles();
  }
  if (!save_filename.isEmpty()) {
    tex.save(save_filename[0]);
  }
}

void View::LoadTexture() {
  QString temp_file =
      QFileDialog::getOpenFileName(this, tr("Open file"), "", tr("*.bmp"));
  QImage texture;
  if (temp_file != "") {
    texture.load(temp_file);
    if (texture.width() != texture.height()) {
      ui_->statusbar->showMessage("The texture can only be square");
    } else if (texture.width() > 1024) {
      ui_->statusbar->showMessage(
          "The resolution of a texture file cannot be more than 1024x1024 "
          "pixels");
    } else {
      texture.convertTo(QImage::Format_RGBA8888);
      ui_->widget->SetTexture(texture);
      ui_->widget->update();
      ui_->actionDeleteTexture->setEnabled(true);
      ui_->actionSaveUvMap->setEnabled(true);
    }
  }
}

void View::ClearTexture() {
  QImage texture;
  ui_->widget->SetTexture(texture);
  ui_->widget->update();
  ui_->actionDeleteTexture->setEnabled(false);
  ui_->actionSaveUvMap->setEnabled(false);
}

void View::OpenFileObj() {
  QString temp_file =
      QFileDialog::getOpenFileName(this, tr("Open file"), "", tr("*.obj"));
  controller_->SetWidth(ui_->widget->width());
  controller_->SetHeight(ui_->widget->height());
  controller_->ParseFile(temp_file.toStdString());
  std::string error_message = controller_->GetErrorMessage();
  if (error_message.empty() && temp_file != "") {
    if (mode_ == kAnimation || mode_ == kPicture) {
      movie_.stop();
      ui_->labelMovie->hide();
      mode_ = kModel;
    }
    ClearTexture();
    ui_->widget->SetMode(kWireframe);
    ui_->widget->SetCountVertexes(controller_->GetCountVertexes());
    ui_->widget->SetCountWireVertexes(controller_->GetWireIndexArray().size());
    ui_->widget->SetCountShadeVertexes(
        controller_->GetShadeIndexArray().size());
    ui_->widget->SetWireVertexArray(controller_->GetWireVertexArray().data());
    ui_->widget->SetShadeVertexArray(controller_->GetShadeVertexArray().data());
    ui_->widget->SetNormalArray(controller_->GetNormalArray().data());
    ui_->widget->SetTextureArray(controller_->GetTextureArray().data());
    ui_->widget->SetWireIndexArray(controller_->GetWireIndexArray().data());
    ui_->widget->SetShadeIndexArray(controller_->GetShadeIndexArray().data());
    ui_->widget->SetDistanceZ(controller_->GetMaxCoordinate());
    ui_->widget->show();
    ui_->widget->update();
    SetTextImage();
    ui_->actionWireframe->setEnabled(true);
    ui_->actionSaveUvMap->setEnabled(false);
    if (!controller_->GetNormalArray().empty()) {
      ui_->actionSmoothShading->setEnabled(true);
      ui_->actionFlatShading->setEnabled(true);
      if (!controller_->GetTextureArray().empty()) {
        ui_->actionLoadTexture->setEnabled(true);
        ui_->actionDeleteTexture->setEnabled(false);
      } else {
        ui_->actionLoadTexture->setEnabled(false);
        ui_->actionDeleteTexture->setEnabled(false);
      }
    } else {
      ui_->actionSmoothShading->setEnabled(false);
      ui_->actionFlatShading->setEnabled(false);
      ui_->actionLoadTexture->setEnabled(false);
      ui_->actionDeleteTexture->setEnabled(false);
    }
  } else {
    ui_->statusbar->showMessage(QString::fromStdString(error_message));
    controller_->SetErrorMessage("");
  }
}

void View::OpenFileIMG() {
  QString open_img = QFileDialog::getOpenFileName(this, tr("Open file"), "",
                                                  tr("*.bmp *.jpg"));
  if (!open_img.isNull()) {
    QPixmap image(open_img);
    image = image.scaled(ui_->widget->size());
    mode_ = kPicture;
    ui_->widget->hide();
    ui_->labelMovie->show();
    ui_->labelMovie->setPixmap(image);
    std::string str = open_img.toStdString();
    size_t pos = str.find_last_of('/');
    filename_ = QString::fromStdString(str.substr(pos + 1));
    SetTextImage();
  }
}

void View::OpenFileGif() {
  QString open_gif =
      QFileDialog::getOpenFileName(this, tr("Open file"), "", tr("*.gif"));
  if (!open_gif.isNull()) {
    movie_.stop();
    mode_ = kAnimation;
    ui_->widget->hide();
    ui_->labelMovie->show();
    movie_.setFileName(open_gif);
    movie_.setScaledSize(
        QSize(controller_->GetScreenWidth(), controller_->GetScreenHeight()));
    ui_->labelMovie->setMovie(&movie_);
    movie_.start();
    std::string str = open_gif.toStdString();
    size_t pos = str.find_last_of('/');
    filename_ = QString::fromStdString(str.substr(pos + 1));
    SetTextImage();
  }
}

void View::SetTextImage() {
  std::string file = controller_->GetFilename();
  if (mode_ == kModel) {
    if (file.empty()) {
      filename_ = tr("Image");
    } else {
      filename_ = QString::fromStdString(file);
    }
  }
  filename_ +=
      QString(" %1x%2").arg(ui_->widget->width()).arg(ui_->widget->height());
  if (mode_ == kModel) {
    if (!file.empty()) {
      filename_ +=
          QString(", %1").arg(ui_->widget->GetCountVertexes()) +
          tr(" vertexes") +
          QString(", %1").arg(ui_->widget->GetCountWireVertexes() / 2) +
          tr(" edges");
    }
  }
  ui_->labelImage->setText(filename_);
}

void View::LoadSettings() {
  QSettings setting("settings.ini", QSettings::IniFormat);
  setting.beginGroup("Settings");

  ui_->widget->SetPositionX(
      setting.value("Light Light Position X", 500).toFloat());
  ui_->widget->SetPositionY(
      setting.value("Light Light Position Y", 0).toFloat());
  ui_->widget->SetPositionZ(
      setting.value("Light Light Position Z", 500).toFloat());
  ui_->widget->SetLightColor(
      setting.value("Light Color", QColor(0, 0, 0, 255)).value<QColor>());

  ui_->widget->SetProjection(
      setting.value("Projection", ProjectionType::kFrustum).toInt());
  ui_->widget->SetBackgroundColor(
      setting.value("Background color", QColor(255, 255, 255, 255))
          .value<QColor>());
  ui_->widget->SetEdgeColor(
      setting.value("Edge color", QColor(120, 140, 255, 255)).value<QColor>());
  ui_->widget->SetVertexColor(
      setting.value("Vertex color", QColor(0, 255, 255, 255)).value<QColor>());
  ui_->widget->SetEdgeThickness(
      (setting.value("Edge thickness", MIN_EDGE_THICKNESS)).toInt());
  ui_->widget->SetVertexSize(
      (setting.value("Vertex size", MIN_VERTEX_SIZE)).toInt());
  ui_->widget->SetVertexType(
      (setting.value("Vertex type", VertexType::kNone)).toInt());
  ui_->widget->SetEdgeType(
      (setting.value("Edge type", EdgeType::kSolid)).toInt());
  SetLanguage(setting.value("Language", kEnglish).toInt());
  setting.endGroup();
}

void View::UploadSettings() {
  QSettings setting("settings.ini", QSettings::IniFormat);
  setting.beginGroup("Settings");
  setting.setValue("Projection", ui_->widget->GetProjection());
  setting.setValue("Background color", ui_->widget->GetBackgroundColor());
  setting.setValue("Edge color", ui_->widget->GetEdgeColor());
  setting.setValue("Vertex color", ui_->widget->GetVertexColor());
  setting.setValue("Edge thickness", ui_->widget->GetEdgeThickness());
  setting.setValue("Vertex size", ui_->widget->GetVertexSize());
  setting.setValue("Vertex type", ui_->widget->GetVertexType());
  setting.setValue("Edge type", ui_->widget->GetEdgeType());
  setting.setValue("Language", language_);
  setting.setValue("Light Light Position X", ui_->widget->GetLightPositionX());
  setting.setValue("Light Light Position Y", ui_->widget->GetLightPositionY());
  setting.setValue("Light Light Position Z", ui_->widget->GetLightPositionZ());
  setting.setValue("Light Color", ui_->widget->GetLightColor());
  setting.endGroup();
}

void View::ActionEnglishFunc() { SetLanguage(kEnglish); }
void View::ActionRussianFunc() { SetLanguage(kRussian); }
void View::ActionOpenObjFunc() { OpenFileObj(); }
void View::ActionOpenGifFunc() { OpenFileGif(); }
void View::ActionImageFunc() {
  if (mode_ == kModel) {
    filedialog_->setDefaultSuffix("jpeg");
    filedialog_->setNameFilter("JPEG (*.jpg *.jpeg);; BMP (*.bmp)");
    SaveMedia(kImage);
  }
}

void View::ActionGifButtonFunc() {
  if (mode_ == kModel) {
    filedialog_->setDefaultSuffix("gif");
    filedialog_->setNameFilter("GIF (*.gif)");
    SaveMedia(kGifButton);
  }
}

void View::ActionGifMovieFunc() {
  if (mode_ == kModel) {
    filedialog_->setDefaultSuffix("gif");
    filedialog_->setNameFilter("GIF (*.gif)");
    SaveMedia(kGifMovie);
  }
}

void View::ActionQuitFunc() { close(); }

void View::ButtonBkgColorFunc() {
  QColor bkg_color = QColorDialog::getColor(
      ui_->widget->GetBackgroundColor(), this, tr("Choose background color"),
      QColorDialog::DontUseNativeDialog | QColorDialog::ShowAlphaChannel);
  if (bkg_color.isValid()) {
    ui_->widget->SetBackgroundColor(bkg_color);
    ui_->buttonBkgColor->setStyleSheet("background-color: " + bkg_color.name());
    ui_->widget->update();
  }
}

void View::ButtonEdgeColorFunc() {
  QColor edge_color = QColorDialog::getColor(
      ui_->widget->GetEdgeColor(), this, tr("Choose edge color"),
      QColorDialog::DontUseNativeDialog | QColorDialog::ShowAlphaChannel);
  if (edge_color.isValid()) {
    ui_->widget->SetEdgeColor(edge_color);
    ui_->buttonEdgeColor->setStyleSheet("background-color: " +
                                        edge_color.name());
    ui_->widget->update();
  }
}

void View::ButtonVertexColorFunc() {
  QColor vertex_color = QColorDialog::getColor(
      ui_->widget->GetVertexColor(), this, tr("Choose vertex color"),
      QColorDialog::DontUseNativeDialog | QColorDialog::ShowAlphaChannel);
  if (vertex_color.isValid()) {
    ui_->widget->SetVertexColor(vertex_color);
    ui_->buttonVertexColor->setStyleSheet("background-color: " +
                                          vertex_color.name());
    ui_->widget->update();
  }
}

void View::SliderEdgeThicknessFunc() {
  QSlider *slider = qobject_cast<QSlider *>(sender());
  if (slider) {
    int position = slider->value();
    ui_->widget->SetEdgeThickness(position);
    ui_->widget->update();
  }
}

void View::SliderVertexSizeFunc() {
  QSlider *slider = qobject_cast<QSlider *>(sender());
  if (slider) {
    int position = slider->value();
    ui_->widget->SetVertexSize(position);
    ui_->widget->update();
  }
}

void View::RadioButtonEdgeSolidFunc() {
  ui_->widget->SetEdgeType(EdgeType::kSolid);
  ui_->widget->update();
}

void View::RadioButtonEdgeDashedFunc() {
  ui_->widget->SetEdgeType(EdgeType::kDashed);
  ui_->widget->update();
}

void View::ActionSolidFunc() {
  ui_->widget->SetEdgeType(EdgeType::kSolid);
  ui_->radioButtonEdgeSolid->toggle();
  ui_->widget->update();
}

void View::ActionDashedFunc() {
  ui_->widget->SetEdgeType(EdgeType::kDashed);
  ui_->radioButtonEdgeDashed->toggle();
  ui_->widget->update();
}

void View::RadioButtonCentralProjFunc() {
  ui_->widget->SetProjection(ProjectionType::kFrustum);
  ui_->widget->update();
}

void View::RadioButtonParallelProjFunc() {
  ui_->widget->SetProjection(ProjectionType::kOrtho);
  ui_->widget->update();
}

void View::ActionCentralFunc() {
  if (ui_->widget->GetProjection() != ProjectionType::kFrustum) {
    ui_->widget->SetProjection(ProjectionType::kFrustum);
    ui_->radioButtonCentralProj->toggle();
    ui_->widget->update();
  }
}

void View::ActionParallelFunc() {
  if (ui_->widget->GetProjection() != ProjectionType::kOrtho) {
    ui_->widget->SetProjection(ProjectionType::kOrtho);
    ui_->radioButtonParallelProj->toggle();
    ui_->widget->update();
  }
}

void View::ActionNoneFunc() {
  ui_->widget->SetVertexType(VertexType::kNone);
  ui_->radioButtonVertexNone->toggle();
  ui_->widget->update();
}

void View::ActionCircleFunc() {
  ui_->widget->SetVertexType(VertexType::kCircle);
  ui_->radioButtonVertexCircle->toggle();
  ui_->widget->update();
}

void View::ActionWireframeFunc() {
  ui_->widget->SetMode(kWireframe);
  ui_->widget->update();
}
void View::ActionFlatShadingFunc() {
  ui_->widget->SetMode(kFlatShading);
  ui_->widget->update();
}
void View::ActionSmoothShadingFunc() {
  ui_->widget->SetMode(kSmoothShading);
  ui_->widget->update();
}

void View::ActionSquareFunc() {
  ui_->widget->SetVertexType(VertexType::kSquare);
  ui_->radioButtonVertexSquare->toggle();
  ui_->widget->update();
}

void View::RadioButtonVertexNoneFunc() {
  ui_->widget->SetVertexType(VertexType::kNone);
  ui_->widget->update();
}

void View::RadioButtonVertexCircleFunc() {
  ui_->widget->SetVertexType(VertexType::kCircle);
  ui_->widget->update();
}

void View::RadioButtonVertexSquareFunc() {
  ui_->widget->SetVertexType(VertexType::kSquare);
  ui_->widget->update();
}

void View::SetElementsInterface() {
  ui_->labelMovie->hide();
  ui_->widget->resize(controller_->GetScreenWidth(),
                      controller_->GetScreenHeight());
  ui_->sliderEdgeThickness->setRange(MIN_EDGE_THICKNESS, MAX_EDGE_THICKNESS);
  ui_->sliderEdgeThickness->setValue(ui_->widget->GetEdgeThickness());
  ui_->sliderVertexSize->setRange(MIN_VERTEX_SIZE, MAX_VERTEX_SIZE);
  ui_->sliderVertexSize->setValue(ui_->widget->GetVertexSize());
  if (ui_->widget->GetProjection() == ProjectionType::kFrustum) {
    ui_->radioButtonCentralProj->toggle();
  } else {
    ui_->radioButtonParallelProj->toggle();
  }
  if (ui_->widget->GetEdgeType() == EdgeType::kSolid) {
    ui_->radioButtonEdgeSolid->toggle();
  } else {
    ui_->radioButtonEdgeDashed->toggle();
  }
  if (ui_->widget->GetVertexType() == VertexType::kNone) {
    ui_->radioButtonVertexNone->toggle();
  } else if (ui_->widget->GetVertexType() == VertexType::kCircle) {
    ui_->radioButtonVertexCircle->toggle();
  } else {
    ui_->radioButtonVertexSquare->toggle();
  }

  ui_->buttonLightColor->setStyleSheet("background-color: " +
                                       ui_->widget->GetLightColor().name());

  ui_->buttonBkgColor->setStyleSheet("background-color: " +
                                     ui_->widget->GetBackgroundColor().name());
  ui_->buttonEdgeColor->setStyleSheet("background-color: " +
                                      ui_->widget->GetEdgeColor().name());
  ui_->buttonVertexColor->setStyleSheet("background-color: " +
                                        ui_->widget->GetVertexColor().name());
  ui_->widget->setFixedSize(controller_->GetScreenWidth(),
                            controller_->GetScreenHeight());
}

void View::ButtonScaleFunc() {
  double value = ui_->lineEditScale->text().toDouble();
  if (value) {
    controller_->MakeTransform(value, kScale);
    ui_->widget->update();
  }
}

void View::ButtonMoveXFunc() {
  double value = ui_->lineEditMoveX->text().toDouble();
  if (value) {
    controller_->MakeTransform(value, kMove, kX);
    ui_->widget->update();
  }
}

void View::ButtonMoveYFunc() {
  double value = ui_->lineEditMoveY->text().toDouble();
  if (value) {
    controller_->MakeTransform(value, kMove, kY);
    ui_->widget->update();
  }
}

void View::ButtonMoveZFunc() {
  double value = ui_->lineEditMoveZ->text().toDouble();
  if (value) {
    controller_->MakeTransform(value, kMove, kZ);
    ui_->widget->update();
  }
}

void View::ButtonMoveAllFunc() {
  double value_x = ui_->lineEditMoveX->text().toDouble();
  double value_y = ui_->lineEditMoveY->text().toDouble();
  double value_z = ui_->lineEditMoveZ->text().toDouble();
  if (value_x || value_y || value_z) {
    controller_->MakeTransform(value_x, kMove, kX);
    controller_->MakeTransform(value_y, kMove, kY);
    controller_->MakeTransform(value_z, kMove, kZ);
    ui_->widget->update();
  }
}

void View::ButtonRotateXFunc() {
  double value = ui_->lineEditRotateX->text().toDouble();
  if (value) {
    controller_->MakeTransform(value, kRotate, kX);
    ui_->widget->update();
  }
}

void View::ButtonRotateYFunc() {
  double value = ui_->lineEditRotateY->text().toDouble();
  if (value) {
    controller_->MakeTransform(value, kRotate, kY);
    ui_->widget->update();
  }
}

void View::ButtonRotateZFunc() {
  double value = ui_->lineEditRotateZ->text().toDouble();
  if (value) {
    controller_->MakeTransform(value, kRotate, kZ);
    ui_->widget->update();
  }
}

void View::ButtonRotateAllFunc() {
  double value_x = ui_->lineEditRotateX->text().toDouble();
  double value_y = ui_->lineEditRotateY->text().toDouble();
  double value_z = ui_->lineEditRotateZ->text().toDouble();
  if (value_x || value_y || value_z) {
    controller_->MakeTransform(value_x, kRotate, kX);
    controller_->MakeTransform(value_y, kRotate, kY);
    controller_->MakeTransform(value_z, kRotate, kZ);
    ui_->widget->update();
  }
}

void View::mousePressEvent(QMouseEvent *event) {
  mouse_position_ = event->globalPosition();
}

void View::mouseMoveEvent(QMouseEvent *event) {
  double difference_x;
  double difference_y;

  difference_x = event->globalPosition().x() - mouse_position_.x();
  difference_y = event->globalPosition().y() - mouse_position_.y();
  if (event->buttons() & Qt::LeftButton) {
    if (event->modifiers() & Qt::ShiftModifier) {
      if (difference_y) {
        controller_->MakeTransform(difference_y, kMove, kZ);
      }
    } else {
      if (difference_x) {
        controller_->MakeTransform(difference_x, kMove, kX);
      }
      if (difference_y) {
        controller_->MakeTransform(-1.5 * difference_y, kMove, kY);
      }
    }
  }
  if (event->buttons() & Qt::RightButton) {
    double rotation_x = 0;
    double rotation_y = 0;
    if (difference_y) {
      rotation_x = 150 * difference_y / ui_->widget->width();
    }
    if (difference_x) {
      rotation_y = 150 * difference_x / ui_->widget->width();
    }
    if (rotation_x) {
      controller_->MakeTransform(rotation_x, kRotate, kX);
    }
    if (rotation_y) {
      controller_->MakeTransform(rotation_y, kRotate, kY);
    }
  }
  if (event->buttons() & Qt::MiddleButton) {
    double rotation_z = 0;
    if (difference_y) {
      rotation_z = -150 * difference_y / ui_->widget->width();
    }
    if (rotation_z) {
      controller_->MakeTransform(rotation_z, kRotate, kZ);
    }
  }
  mouse_position_ = event->globalPosition();
  ui_->widget->update();
}

void View::wheelEvent(QWheelEvent *event) {
  if (event->angleDelta().y() > 0) {
    controller_->MakeTransform(1.1, kScale);
  } else if (event->angleDelta().y() < 0) {
    controller_->MakeTransform(0.9, kScale);
  }
  ui_->widget->update();
}

void View::keyPressEvent(QKeyEvent *key) {
  int k = key->key();
  if (k == Qt::Key_R || k == Qt::Key_F5) {
    controller_->ReturnToBase();
  }
  if (k == Qt::Key_Escape) {
    if (mode_ == kModel) {
      close();
    } else if (mode_ == kAnimation) {
      movie_.stop();
      ui_->labelMovie->hide();
      mode_ = kModel;
      ui_->widget->show();
      ui_->widget->update();
      SetTextImage();
    } else if (mode_ == kPicture) {
      ui_->labelMovie->hide();
      mode_ = kModel;
      ui_->widget->show();
      ui_->widget->update();
      SetTextImage();
    }
  } else if (k == Qt::Key_Left) {
    if (key->modifiers() & Qt::ShiftModifier) {
      controller_->ShiftUndo();
    } else {
      controller_->Undo();
    }
  } else if (k == Qt::Key_Right) {
    if (key->modifiers() & Qt::ShiftModifier) {
      controller_->ShiftRedo();
    } else {
      controller_->Redo();
    }
  }
  ui_->widget->update();
}

void View::SaveMedia(FileType format) {
  QStringList save_filename;
  if (filedialog_->exec()) {
    save_filename = filedialog_->selectedFiles();
  }
  if (!save_filename.isEmpty()) {
    if (format == kImage && file_type_ != kImage) {
      media_maker_.SetMedia(new StrategyImage(ui_));
      file_type_ = kImage;
    } else if (format == kGifButton && file_type_ != kGifButton) {
      media_maker_.SetMedia(new StrategyGifButton(ui_, controller_));
      file_type_ = kGifButton;
    } else if (format == kGifMovie && file_type_ != kGifButton) {
      media_maker_.SetMedia(new StrategyGifMovie(ui_));
      file_type_ = kGifButton;
    }
    media_maker_.MakeMedia(save_filename[0]);
  }
}

void View::AddValidators() {
  double_validator_.setRegularExpression(
      QRegularExpression("^[-+]?\\d{0,5}(\\.\\d{0,3})?$"));
  int_validator_.setRegularExpression(QRegularExpression("^[+]?\\d{0,4}$"));
  file_validator_.setRegularExpression(
      QRegularExpression("[^/|. ,:?*<>\\\\]+"));
  ui_->lineEditLightX->setValidator(&double_validator_);
  ui_->lineEditLightY->setValidator(&double_validator_);
  ui_->lineEditLightZ->setValidator(&double_validator_);
  ui_->lineEditMoveX->setValidator(&double_validator_);
  ui_->lineEditMoveY->setValidator(&double_validator_);
  ui_->lineEditMoveZ->setValidator(&double_validator_);
  ui_->lineEditRotateX->setValidator(&double_validator_);
  ui_->lineEditRotateY->setValidator(&double_validator_);
  ui_->lineEditRotateZ->setValidator(&double_validator_);
  ui_->lineEditScale->setValidator(&double_validator_);
  ui_->lineEditResizeX->setValidator(&int_validator_);
  ui_->lineEditResizeY->setValidator(&int_validator_);
}

void View::SetLanguage(int language) {
  if (language_ != language) {
    if (language == kRussian) {
      if (!translator_.load(":/i18n/3DViewer_ru_RU")) {
        return;
      } else {
        qApp->installTranslator(&translator_);
      }
    } else {
      qApp->removeTranslator(&translator_);
    }
    ui_->retranslateUi(this);
    language_ = language;
    SetTextImage();
  }
}

void View::ButtonResizeFunc() {
  int width = ui_->lineEditResizeX->text().toInt();
  int height = ui_->lineEditResizeY->text().toInt();
  controller_->SetWidth(width);
  controller_->SetHeight(height);
  ui_->widget->setFixedSize(controller_->GetScreenWidth(),
                            controller_->GetScreenHeight());
  movie_.setScaledSize(
      QSize(controller_->GetScreenWidth(), controller_->GetScreenHeight()));
  centralWidget()->setSizePolicy(QSizePolicy::Expanding,
                                 QSizePolicy::Preferred);
  SetTextImage();
}

void View::InitFiledialog() {
  filedialog_ = new QFileDialog(this);
  filedialog_->setOption(QFileDialog::DontUseNativeDialog, true);
  auto children = filedialog_->findChildren<QLineEdit *>();
  if (children.size() == 1) {
    children.front()->setValidator(&file_validator_);
    filedialog_->setAcceptMode(QFileDialog::AcceptSave);
    filedialog_->setFileMode(QFileDialog::AnyFile);
    filedialog_->setViewMode(QFileDialog::List);
  }
  filedialog_->setWindowTitle(tr("Save As"));
  filedialog_->setLabelText(filedialog_->LookIn, tr("Look In"));
  filedialog_->setLabelText(filedialog_->FileName, tr("File &name:"));
  filedialog_->setLabelText(filedialog_->FileType, tr("Files of type:"));
  filedialog_->setLabelText(filedialog_->Accept, tr("Save"));
  filedialog_->setLabelText(filedialog_->Reject, tr("Cancel"));
}
}  // namespace s21
