#include "defoltwindow.h"

#include "ui_defoltwindow.h"

defoltwindow::defoltwindow(QWidget *parent)
    : QDialog(parent), ui(new Ui::defoltwindow) {
  ui->setupUi(this);

  form = new Form();
  connect(this, &defoltwindow::signalBase, form,
          &Form::slot);  // для передачи инфы
  connect(form, &Form::signal, this,
          &defoltwindow::show);  // скрываю ненужные окна

  connect(ui->number_0, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->number_1, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->number_2, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->number_3, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->number_4, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->number_5, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->number_6, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->number_7, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->number_8, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->number_9, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->button_plus, SIGNAL(clicked()), this, SLOT(algebra_operations()));
  connect(ui->button_minus, SIGNAL(clicked()), this,
          SLOT(algebra_operations()));
  connect(ui->button_div, SIGNAL(clicked()), this, SLOT(algebra_operations()));
  connect(ui->button_mult, SIGNAL(clicked()), this, SLOT(algebra_operations()));
  connect(ui->button_pow, SIGNAL(clicked()), this, SLOT(algebra_operations()));
  connect(ui->button_mod, SIGNAL(clicked()), this, SLOT(algebra_operations()));
  connect(ui->button_open, SIGNAL(clicked()), this, SLOT(algebra_operations()));
  connect(ui->button_close, SIGNAL(clicked()), this,
          SLOT(algebra_operations()));
  connect(ui->un_minus, SIGNAL(clicked()), this, SLOT(algebra_operations()));
  connect(ui->button_dot, SIGNAL(clicked()), this, SLOT(algebra_operations()));
  connect(ui->button_sin, SIGNAL(clicked()), this, SLOT(trigonom_operations()));
  connect(ui->button_cos, SIGNAL(clicked()), this, SLOT(trigonom_operations()));
  connect(ui->button_tan, SIGNAL(clicked()), this, SLOT(trigonom_operations()));
  connect(ui->button_asin, SIGNAL(clicked()), this,
          SLOT(trigonom_operations()));
  connect(ui->button_acos, SIGNAL(clicked()), this,
          SLOT(trigonom_operations()));
  connect(ui->button_atan, SIGNAL(clicked()), this,
          SLOT(trigonom_operations()));
  connect(ui->button_sqrt, SIGNAL(clicked()), this,
          SLOT(trigonom_operations()));
  connect(ui->button_log, SIGNAL(clicked()), this, SLOT(trigonom_operations()));
  connect(ui->button_ln, SIGNAL(clicked()), this, SLOT(trigonom_operations()));
  connect(ui->button_ac, SIGNAL(clicked()), this, SLOT(ac_delete()));
  connect(ui->button_equals, SIGNAL(clicked()), this, SLOT(result()));
  connect(ui->button_x, SIGNAL(clicked()), this, SLOT(algebra_operations()));
}

defoltwindow::~defoltwindow() { delete ui; }

// void defoltwindow::on_Back_clicked() {
//   this->close();       // Закрываем окно
//   emit firstWindow();  //
// }

void defoltwindow::algebra_operations() {
  QPushButton *button = (QPushButton *)sender();
  QString new_label;
  new_label = ui->result_line->text();
  if (button->text() == "/" && !(ui->result_line->text().endsWith("/"))) {
    new_label += "/";
  } else if (button->text() == "*" &&
             !(ui->result_line->text().endsWith("*"))) {
    new_label += "*";
  } else if (button->text() == "+" &&
             !(ui->result_line->text().endsWith("+"))) {
    new_label += "+";
  } else if (button->text() == "-" &&
             !(ui->result_line->text().endsWith("-"))) {
    new_label += "-";
  } else if (button->text() == "^" &&
             !(ui->result_line->text().endsWith("^"))) {
    new_label += "^";
  } else if (button->text() == "mod" &&
             !(ui->result_line->text().endsWith("%"))) {
    new_label += "%";
  } else if (button->text() == "(") {
    new_label += "(";
  } else if (button->text() == ")") {
    new_label += ")";
  } else if (button->text() == "+/-") {
    new_label += "(-";
  } else if (button->text() == ".") {
    new_label += ".";
  } else if (button->text() == "x") {
    new_label += "x";
  }
  ui->result_line->setText(new_label);
}

void defoltwindow::trigonom_operations() {
  QPushButton *button = (QPushButton *)sender();
  ui->result_line->setText(ui->result_line->text() + button->text() + "(");
}

void defoltwindow::digit_numbers() {
  QPushButton *button = (QPushButton *)sender();
  QString new_label = ui->result_line->text() + button->text();
  ui->result_line->setText(new_label);
}

void defoltwindow::result() {
  std::string str = ui->result_line->text().toStdString();
  char *expression = &str[0];
  std::string str_sum = ui->x_line->text().toStdString();
  char *sum = &str_sum[0];
  double resX = atof(sum);
  double res = 0.0;
  processing(expression, &res, resX);
  QString num1 = QString::number(res, 'f', 6);
  ui->result_line->setText(num1);
}

void defoltwindow::ac_delete() { ui->result_line->setText(""); }

void defoltwindow::on_button_graph_clicked() {
  emit signalBase(ui->result_line->text(), ui->x_min->text(), ui->x_max->text(),
                  ui->y_min->text(), ui->y_max->text());
  form->show();  // Показываем второе окно
  this->close();
}
