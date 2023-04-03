#include "credit.h"

#include <QPixmap>

#include "ui_credit.h"

credit::credit(QWidget *parent) : QDialog(parent), ui(new Ui::credit) {
  ui->setupUi(this);

  QPixmap label_11(":/photo/photo/5.png");
  int w5 = ui->label_11->width();
  int h5 = ui->label_11->height();
  ui->label_11->setPixmap(label_11.scaled(w5, h5, Qt::KeepAspectRatio));

  QPixmap label_12(":/photo/photo/6.png");
  int w6 = ui->label_12->width();
  int h6 = ui->label_12->height();
  ui->label_12->setPixmap(label_12.scaled(w6, h6, Qt::KeepAspectRatio));

  QPixmap label_16(":/photo/photo/7.png");
  int w7 = ui->label_16->width();
  int h7 = ui->label_16->height();
  ui->label_16->setPixmap(label_16.scaled(w7, h7, Qt::KeepAspectRatio));
}

credit::~credit() { delete ui; }

void credit::on_pushButton_clicked() {
  std::string str_sum = ui->doubleSpinBox->text().toStdString();
  char *sum = &str_sum[0];
  std::string str_month = ui->spinBox->text().toStdString();
  char *month = &str_month[0];
  std::string str_procent = ui->doubleSpinBox_3->text().toStdString();
  char *procent = &str_procent[0];

  double overpayment = 0;
  double totalSum = 0;
  double sums = atof(sum);
  double months = atof(month);
  double procents = (atof(procent) / 100) / 12;
  QString new_label = "";

  if (ui->radioButton->isChecked()) {
    double d = sums / months;
    double S = 0.0;
    int n = months;
    int numberMonth = n;

    for (int i = 0; i < n; i++) {
      S = differentiatedСredit(&sums, &months, &procents, &d);
      months--;
      QString num1 = QString::number(S, 'f', 2);
      QString qw = QString::number(numberMonth);
      totalSum = totalSum + S;
      new_label = new_label + num1 + " | " + qw + "month" + '\n';
      numberMonth--;
    }

    overpayment = totalSum - sums;
    QString num2 = QString::number(overpayment, 'f', 2);
    QString num3 = QString::number(totalSum, 'f', 2);

    ui->label->setText(new_label);
    ui->label_2->setText(num2);
    ui->label_3->setText(num3);
  }
  if (ui->radioButton_2->isChecked()) {
    sums = annuityСredit(&sums, &months, &procents, &overpayment, &totalSum);

    QString num1 = QString::number(sums, 'f', 2);
    QString num2 = QString::number(overpayment, 'f', 2);
    QString num3 = QString::number(totalSum, 'f', 2);

    ui->label->setText(num1);
    ui->label_2->setText(num2);
    ui->label_3->setText(num3);
  }
}
