#include "qthread.h"
#include "generator.h"
#include <QEventLoop>


void Generator::run()
{
    done = false;
    QEventLoop loop;

    while(!done)
    {
        int value = (std::rand()/(double)RAND_MAX*100.);
        emit dataReady(value);

        // Длительная обработка задания.
        QThread::msleep(1000);        

        // Обработка очереди сигналов в свободное время
        loop.processEvents(QEventLoop::AllEvents);
    }
    emit finished();
}

void Generator::stop()
{
    done = true;
}
