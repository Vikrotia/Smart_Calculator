#include "form.h"

#include "ui_form.h"

Form::Form(QWidget *parent) : QWidget(parent), ui(new Ui::Form) {
  ui->setupUi(this);
}

Form::~Form() { delete ui; }

void Form::on_pushButton_clicked() {
  this->close();  // Закрываем окно
  emit signal();  // И вызываем сигнал на открытие главного окна
}

void Form::slot(QString z, QString Xmin, QString Xmax, QString Ymin,
                QString Ymax) {
  ui->label->setText(z);
  std::string str0 = z.toStdString();
  char *strRes = &str0[0];
  std::string str = Xmin.toStdString();
  char *startX = &str[0];
  std::string str1 = Xmax.toStdString();
  char *finishX = &str1[0];
  std::string str2 = Ymin.toStdString();
  char *startY = &str2[0];
  std::string str3 = Ymax.toStdString();
  char *finishY = &str3[0];

  double MinX = atof(startX);
  double MaxX = atof(finishX);
  double MinY = atof(startY);
  double MaxY = atof(finishY);
  //  double MinX =-2;
  //  double MaxX = 2;
  //  double MinY = -2;
  //  double MaxY = 2;
  if (Xmin < Xmax && Ymin < Ymax) {
    double h = (MaxX - MinX) / 500;
    int N = (MaxX - MinX) / h + 1;
    QVector<double> x(N), y(N);
    int i = 0;

    for (double X = MinX; X <= MaxX; X += h) {
      double Y = 0;
      double error = processing(strRes, &Y, X);

      if (error && Y <= MaxY && Y >= MinY) {
        x[i] = X;
        y[i] = Y;
        i++;
      }
    }
    ui->graf->clearGraphs();

    ui->graf->addGraph();

    ui->graf->graph(0)->setData(x, y);

    ui->graf->xAxis->setLabel("x");
    ui->graf->yAxis->setLabel("y");

    ui->graf->xAxis->setRange(MinX, MaxX);  //Для оси Ox

    ui->graf->yAxis->setRange(MinY, MaxY);

    ui->graf->replot();
  }
  //  double a = -1; //Начало интервала, где рисуем график по оси Ox
  //  double b =  1; //Конец интервала, где рисуем график по оси Ox
  //  double h = 0.01; //Шаг, с которым будем пробегать по оси Ox
  //  int N = (b - a) / h + 2; //Вычисляем количество точек, которые будем
  //  отрисовывать QVector<double> x(N), y(N); //Массивы координат точек

  //  //Вычисляем наши данные
  //  int i=0;
  //  //Пробегаем по всем точкам
  //  for (double X = a; X <= b; X += h) {
  //    x[i] = X;
  //    y[i] = X * X;//Формула нашей функции
  //    i++;
  //  }
  //  ui->graf->clearGraphs();//Если нужно, но очищаем все графики

  //  //Добавляем один график в widget
  //  ui->graf->addGraph();

  //  //Говорим, что отрисовать нужно график по нашим двум массивам x и y
  //  ui->graf->graph(0)->setData(x, y);

  //  //Подписываем оси Ox и Oy
  //  ui->graf->xAxis->setLabel("x");
  //  ui->graf->yAxis->setLabel("y");

  //  //Установим область, которая будет показываться на графике
  //  ui->graf->xAxis->setRange(a, b);//Для оси Ox

  //  //Для показа границ по оси Oy сложнее, так как надо по правильному
  //  //вычислить минимальное и максимальное значение в векторах
  //  double minY = y[0], maxY = y[0];
  //  for (int i = 1; i < N; i++) {
  //    if (y[i] < minY) minY = y[i];
  //    if (y[i] > maxY) maxY = y[i];
  //  }
  //  ui->graf->yAxis->setRange(minY, maxY);//Для оси Oy

  //  //И перерисуем график на нашем widget
  //  ui->graf->replot();
}
