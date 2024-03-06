#include "facade.h"

namespace s21 {

Facade::Facade(int argc, char *argv[]) {
  QApplication a(argc, argv);
  Model model;
  Controller controller(&model);
  View view(&controller);
  view.show();
  status_ = a.exec();
}

}  // namespace s21