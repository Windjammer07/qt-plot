#ifndef GENERATOR_H
#define GENERATOR_H

#include <QMainWindow>
#include <QThread>

class Generator : public QThread
{
    Q_OBJECT

protected:
    void run();

private:
    volatile bool done;

public slots:

    // Для получения сигнала на остановку
    void stop();


signals:

    // Отсылка данных в вызвавшую форму
    void dataReady(int);

    // Сигнал вызвавшему об окончании работы потока
    void finished();
};

#endif // GENERATOR_H
