#ifndef SRC_3DVIEWER_SOURCE_VIEW_STRATEGY_H
#define SRC_3DVIEWER_SOURCE_VIEW_STRATEGY_H

#include <QPainter>
#include <QTime>

#include "../controller/controller.h"
#include "../include/gif.h"
#include "ui_mainwindow.h"

namespace s21 {

class Strategy {
 public:
  virtual ~Strategy() {}
  virtual void make(QString filename) = 0;
};

class StrategyImage : public Strategy {
 public:
  StrategyImage(Ui::MainWindow *ui) : ui_(ui) {}

  void make(QString filename);

 private:
  Ui::MainWindow *ui_;
};

class StrategyGifButton : public Strategy {
 public:
  StrategyGifButton(Ui::MainWindow *ui, Controller *controller)
      : ui_(ui), controller_(controller) {}

  void make(QString filename);

 private:
  Ui::MainWindow *ui_;
  Controller *controller_;
};

class StrategyGifMovie : public Strategy {
 public:
  StrategyGifMovie(Ui::MainWindow *ui) : ui_(ui) {}

  void make(QString filename);

 private:
  Ui::MainWindow *ui_;
};

class MediaMaker {
 public:
  MediaMaker() : media_(nullptr) {}
  ~MediaMaker();

  void MakeMedia(QString filename);

  void SetMedia(Strategy *strategy);

 private:
  Strategy *media_;
};
}  // namespace s21

#endif  // SRC_3DVIEWER_SOURCE_VIEW_STRATEGY_H
