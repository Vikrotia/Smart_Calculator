#ifndef DEFOLTWINDOW_H
#define DEFOLTWINDOW_H

#include <form.h>

#include <QDialog>

extern "C" {
#include "backend_calc.h"
}

namespace Ui {
class defoltwindow;
}

class defoltwindow : public QDialog {
  Q_OBJECT

 public:
  explicit defoltwindow(QWidget *parent = nullptr);
  ~defoltwindow();

 signals:
  void firstWindow();  // Сигнал для первого окна на открытие
  void signalBase(QString, QString, QString, QString, QString);

 private slots:
  // void on_Back_clicked();

  void on_button_graph_clicked();
  void digit_numbers();
  void algebra_operations();
  void trigonom_operations();
  void ac_delete();
  void result();

 private:
  Ui::defoltwindow *ui;
  Form *form;
};

#endif  // DEFOLTWINDOW_H
