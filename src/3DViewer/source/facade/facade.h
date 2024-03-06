#ifndef SRC_3DVIEWER_SOURCE_FACADE_FACADE_H
#define SRC_3DVIEWER_SOURCE_FACADE_FACADE_H

#include <QApplication>

#include "../controller/controller.h"
#include "../model/model.h"
#include "../view/view.h"

namespace s21 {
class Facade {
 public:
  int get_status() { return status_; }
  Facade(int argc, char *argv[]);

 private:
  int status_;
};
}  // namespace s21

#endif  // SRC_3DVIEWER_SOURCE_FACADE_FACADE_H