#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "generator.h"
#include <QDebug>
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
#  include <QDesktopWidget>
#endif
#include <QScreen>
#include <QMessageBox>
#include <QMetaEnum>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ///
    /// Инициализация UI
    ///
    ui->setupUi(this);
    setGeometry(100, 150, 842, 490);

    setupPlot(ui->customPlot);
    statusBar()->clearMessage();
    ui->customPlot->replot();
    updateButtons();


    ///
    /// Подключаем кнопки к слотам обработки
    ///
    connect(ui->startThreadButton, &QPushButton::pressed, this, &MainWindow::startThreadSlot);
    connect(ui->stopButton, &QPushButton::pressed, this, &MainWindow::stopAllSlot);
    connect(ui->resetButton, &QPushButton::pressed, this, &MainWindow::resetSlot);
    connect(ui->clearButton, &QPushButton::pressed, this, &MainWindow::clearSlot);
    connect(ui->saveButton, &QPushButton::pressed, this, &MainWindow::saveSlot);
}

/////////////////////////////////
///
/// Методы управления виджетами
///
/////////////////////////////////

void MainWindow::setupPlot(QCustomPlot *customPlot)
{
    customPlot->addGraph();
    customPlot->graph(0)->setPen(QPen(QColor(40, 110, 255))); // Blue

    customPlot->axisRect()->setupFullAxesBox();
    customPlot->yAxis->setRange(0, 100);

    customPlot->xAxis->setLabel("Count");
    customPlot->yAxis->setLabel("Value");

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));
}

void MainWindow::updateStatusBar()
{
    ui->statusBar->showMessage(
          QString("Threads: %1, Count: %2, Summary: %3")
          .arg(threadCount)
          .arg(count)
          .arg(summary)
          , 0);
}

void MainWindow::updateButtons()
{
    ui->stopButton->setEnabled(threadCount > 0);

    if(threadCount>0)
        ui->stopButton->setText(QString("Stop all (%1)").arg(threadCount));
    else
        ui->stopButton->setText("Nothing to stop");
}

///
/// \brief MainWindow::startGeneratorThread Запуск генератора
///
void MainWindow::startGeneratorThread()
{
    Generator* generator = new Generator();

    // Когда генератор подготовит данные, передать их в MainWindow для обработки
    connect(generator, SIGNAL(dataReady(int)), this, SLOT(realtimeDataSlot(int)));

    // Когда нужно будет остановить генератор, подадим ему сигнал
    connect(this, SIGNAL(stopSignal()), generator, SLOT(stop()));

    // После остановки потока сообщить процессу MainWindow для учета количества
    connect(generator, SIGNAL(finished()), this, SLOT(threadFinishedSlot()));

    // После остановки генератора сигнал на освобождение ресурсов
    connect(generator, SIGNAL(finished()), generator, SLOT(deleteLater()));

    generator->start();

    threadCount++;
 }


///
/// Обработка сигнала завершения потока
///
void MainWindow::threadFinishedSlot()
{    
    threadCount --;
    updateStatusBar();
    updateButtons();
}

/////////////////////////
///
/// Обработчики кнопок
///
/////////////////////////

void MainWindow::startThreadSlot()
{
//    isStarted = !isStarted;

    startGeneratorThread();
    updateStatusBar();
    updateButtons();
}

void MainWindow::stopAllSlot()
{
    emit stopSignal();
}

// Clear collected data and statistic
// Do not affect generator state and log
void MainWindow::resetSlot()
{
    count = 0;
    summary = 0;
    ui->customPlot->graph(0)->data()->clear();
    ui->customPlot->replot();
    updateStatusBar();
}

// Save current statistic to log
void MainWindow::saveSlot()
{
    ui->textLog->setText(ui->textLog->text() + QString("%1\t%2\t%3\n")
                         .arg(++logCounter)
                         .arg(count)
                         .arg(summary)
                         );
    ui->textLog->adjustSize();
    ui->scrollArea->verticalScrollBar()->setSliderPosition(ui->textLog->height());
}

// Clear log
// Do not affect generator state and collected data
void MainWindow::clearSlot()
{
    logCounter = 0;
    ui->textLog->setText("");
    ui->textLog->adjustSize();
    ui->scrollArea->verticalScrollBar()->setSliderPosition(ui->textLog->height());
}


void MainWindow::realtimeDataSlot(int data)
{

  count++;
  summary += data;

  ui->customPlot->graph(0)->addData(count, data);

  // Прокрутка пр необходимости
  ui->customPlot->xAxis->setRange(count>maxCount?count-maxCount:1, count>maxCount?maxCount:count-1 , Qt::AlignLeft);

  ui->customPlot->replot();
  
  updateStatusBar();
}


MainWindow::~MainWindow()
{
  delete ui;
}
