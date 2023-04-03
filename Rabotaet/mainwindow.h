#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <credit.h>
#include <defoltwindow.h>

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:

  void on_button_calculator_clicked();

  //    void on_button_credit_clicked();

  void on_button_credit_clicked();

 private:
  Ui::MainWindow *ui;
  defoltwindow *sWindow;
  credit *sCredit;
};
#endif  // MAINWINDOW_H
