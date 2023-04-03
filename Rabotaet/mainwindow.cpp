#include "mainwindow.h"

#include <QPixmap>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  sWindow = new defoltwindow();
  // подключаем к слоту запуска главного окна по кнопке во втором окне
  connect(sWindow, &defoltwindow::firstWindow, this, &MainWindow::show);

  sCredit = new credit();
  connect(sCredit, &credit::secondWindow, this, &MainWindow::show);

  QPixmap label_2(":/photo/photo/3.png");
  int w2 = ui->label_2->width();
  int h2 = ui->label_2->height();
  ui->label_2->setPixmap(label_2.scaled(w2, h2, Qt::KeepAspectRatio));

  QPixmap label(":/photo/photo/4.png");
  int w3 = ui->label->width();
  int h3 = ui->label->height();
  ui->label->setPixmap(label.scaled(w3, h3, Qt::KeepAspectRatio));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_button_calculator_clicked() {
  sWindow->show();  // Показываем второе окно
  this->close();    // Закрываем основное окно
}

// void MainWindow::on_button_credit_clicked()
//{
//     sCredit->show();  // Показываем второе окно
//     this->close();
// }

void MainWindow::on_button_credit_clicked() {
  sCredit->show();  // Показываем второе окно
  this->close();
}
