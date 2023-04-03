#ifndef CREDIT_H
#define CREDIT_H

#include <QDialog>

extern "C" {
#include "backend_calc.h"
}

namespace Ui {
class credit;
}

class credit : public QDialog {
  Q_OBJECT

 public:
  explicit credit(QWidget *parent = nullptr);
  ~credit();

 signals:
  void secondWindow();

 private slots:
  void on_pushButton_clicked();

 private:
  Ui::credit *ui;
};

#endif  // CREDIT_H
