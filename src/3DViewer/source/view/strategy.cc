#include "strategy.h"

namespace s21 {

void StrategyImage::make(QString filename) {
  if (!filename.isEmpty()) {
    QPixmap pixmap(ui_->widget->size());
    ui_->widget->render(&pixmap, QPoint(), QRegion(ui_->widget->rect()));
    pixmap.save(filename);
  }
}

void StrategyGifButton::make(QString filename) {
  int count = 0;
  double move_x = ui_->lineEditMoveX->text().toDouble() / (FRAMES - 1);
  double move_y = ui_->lineEditMoveY->text().toDouble() / (FRAMES - 1);
  double move_z = ui_->lineEditMoveZ->text().toDouble() / (FRAMES - 1);
  double rot_x = ui_->lineEditRotateX->text().toDouble() / (FRAMES - 1);
  double rot_y = ui_->lineEditRotateY->text().toDouble() / (FRAMES - 1);
  double rot_z = ui_->lineEditRotateZ->text().toDouble() / (FRAMES - 1);
  double scale =
      pow(10, log10(ui_->lineEditScale->text().toDouble()) / (FRAMES - 1));
  if (move_x || move_y || move_z || rot_x || rot_y || rot_z || scale) {
    Gif gif;
    Gif::GifWriter gifWriter = {};
    int width = ui_->widget->width();
    int height = ui_->widget->height();
    ui_->widget->setFixedSize(GIF_WIDTH, GIF_HEIGHT);
    gif.GifBegin(&gifWriter, filename.toStdString().c_str(), GIF_WIDTH,
                 GIF_HEIGHT, 10, 8, true);
    while (count < FRAMES) {
      if (count) {
        controller_->MakeTransform(move_x, kMove, kX, true);
        controller_->MakeTransform(move_y, kMove, kY, true);
        controller_->MakeTransform(move_z, kMove, kZ, true);
        controller_->MakeTransform(rot_x, kRotate, kX, true);
        controller_->MakeTransform(rot_y, kRotate, kY, true);
        controller_->MakeTransform(rot_z, kRotate, kZ, true);
        controller_->MakeTransform(scale, kScale, kX, true);
        ui_->widget->update();
      }
      QPixmap pixmap(ui_->widget->size());
      ui_->widget->render(&pixmap, QPoint(), QRegion(ui_->widget->rect()));
      QImage image = pixmap.toImage().convertToFormat(QImage::Format_RGBA8888);
      gif.GifWriteFrame(&gifWriter, image.bits(), GIF_WIDTH, GIF_HEIGHT, 10, 8,
                        true);
      ++count;
    }
    gif.GifEnd(&gifWriter);
    ui_->widget->setFixedSize(width, height);
    ui_->statusbar->showMessage("Gif done");
  } else {
    ui_->statusbar->showMessage("No transformations set");
  }
}

void StrategyGifMovie::make(QString filename) {
  Gif gif;
  QTime timer;
  Gif::GifWriter gifWriter = {};
  int width = ui_->widget->width();
  int height = ui_->widget->height();
  ui_->widget->setFixedSize(GIF_WIDTH, GIF_HEIGHT);
  gif.GifBegin(&gifWriter, filename.toStdString().c_str(), GIF_WIDTH,
               GIF_HEIGHT, 100);
  for (short int i = 0; i < 50; ++i) {
    QPixmap pixmap(ui_->widget->size());
    ui_->widget->render(&pixmap, QPoint(), QRegion(ui_->widget->rect()));
    QImage image = pixmap.toImage().convertToFormat(QImage::Format_RGBA8888);
    gif.GifWriteFrame(&gifWriter, image.bits(), GIF_WIDTH, GIF_HEIGHT, 0);
    timer = QTime::currentTime().addMSecs(100);
    while (QTime::currentTime() < timer) {
      QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
  }
  gif.GifEnd(&gifWriter);
  ui_->widget->setFixedSize(width, height);
  ui_->statusbar->showMessage("Gif done");
}

MediaMaker::~MediaMaker() { delete media_; }

void MediaMaker::MakeMedia(QString filename) {
  if (media_) media_->make(filename);
}

void MediaMaker::SetMedia(Strategy *strategy) {
  if (media_) delete media_;
  media_ = strategy;
}

}  // namespace s21
