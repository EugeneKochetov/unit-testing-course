#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dataprovider.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionNew_triggered();
    void on_actionEdit_triggered();

    void on_actionDelete_triggered();

    void on_btnSearch_clicked();

private:
    Ui::MainWindow *ui;

    DataProvider* _dataProvider;
    Finder* _finder;
};

#endif // MAINWINDOW_H
