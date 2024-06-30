#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../qcustomplot/qcustomplot.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

    ///
    /// Управление UI виджетами
    ///
    void setupPlot(QCustomPlot *customPlot);
    void updateStatusBar();
    void updateButtons();

    ///
    /// Создать и запустить поток генератора
    /// При каждом запуске новый поток будет создан
    /// и привязан сигналами к потоку экземпляра
    /// MainWindow
    ///
    void startGeneratorThread();

signals:
    // Посылается экземпляру(ам) генератора для мягкой остановки
    void stopSignal();

private slots:

    ///
    /// Получение данных от генератора
    ///
    void realtimeDataSlot(int);

    ///
    /// Поток генератора завершен
    ///
    void threadFinishedSlot();

    ///
    /// Обраьотка сигналов UI виджетов
    ///
    void startThreadSlot();
    void stopAllSlot();
    void resetSlot();
    void saveSlot();
    void clearSlot();


private:
    Ui::MainWindow *ui;

    ///
    /// Максимальное количество точек на графике по оси X
    /// При превышении этого количества график начнет скролиться
    ///
    /// Включено в класс для реализации в будущем возможности
    /// менять значение в RunTime
    ///
    int maxCount = 25;

    ///
    /// Status
    ///
    bool isStarted = false;
    int threadCount = 0;

    ///
    /// Statistics
    ///
    int count = 0;
    int summary = 0;
    int logCounter = 0;

};

#endif // MAINWINDOW_H
