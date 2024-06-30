# qt-plot Тестовое задание 1 вариант 2

## Опиcание

    В соответсвии с условиями задания, реализовано на Qt6.

### Используемые нструменты

* QtCreator
* Qt Designer
* Qmake

### Библиотеки

QCustomPlot ([https://www.qcustomplot.com/](URL))

### Особенности реализации

#### Основные требования

 1. *Генерация точек должна происходить в отдельном потоке без использования* **QTimer**

Генерация осуществляется классом **Generator**, унаследованным от **QThread**:

```C++
class Generator : public QThread
{
    Q_OBJECT

protected:
        void run();
```
Главный цикл генерации:
```
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

        // Обработка очереди сигналов
        loop.processEvents(QEventLoop::AllEvents);
    }
```

    2. *Список результатов должен быть сделан отдельным виджетом на базе* **QScrollArea**

Список реализован посредством **QLabel**, вложенного в **QScrollArea**:

```XML
         <widget class="QScrollArea" name="scrollArea">
          <property name="maximumSize">
           <size>
            <width>10000</width>
            <height>10000</height>
           </size>
          </property>
          <property name="verticalScrollBarPolicy">
           <enum>Qt::ScrollBarAsNeeded</enum>
          </property>
          <property name="widgetResizable">
           <bool>true</bool>
          </property>
          <property name="alignment">
           <set>Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop</set>
          </property>
          <widget class="QLabel" name="textLog">
           <property name="geometry">
            <rect>
             <x>0</x>
             <y>0</y>
             <width>244</width>
             <height>749</height>
            </rect>
           </property>
           <property name="text">
            <string/>
           </property>
           <property name="scaledContents">
            <bool>true</bool>
           </property>
           <property name="alignment">
            <set>Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop</set>
           </property>
           <property name="wordWrap">
            <bool>true</bool>
           </property>
           <property name="textInteractionFlags">
            <set>Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse</set>
           </property>
          </widget>
         </widget>

```


#### Дополнительно к условиям задачи реализованы следующие функции:

 1. Возможность запуска нескольких потоков генерации данных. Остановка потоков осуществляется сразу для всех запущенных ранее.

 2. Динамическое изменение статуса и наименований кнопок в зависимости от текущего состояния

 3. Отображение статуса в StatusBar


## Построение

Рекомендуемый порядок сборки из командной строки:

```bash
mkdir bin
cd bin
qmake ../src/qt-plot.pro
make
make clean
```

Для удобства построения последовательность продублирована в файле `build.sh`
