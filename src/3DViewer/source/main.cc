#include "facade/facade.h"

int main(int argc, char *argv[]) {
  s21::Facade app_event(argc, argv);
  return app_event.get_status();
}