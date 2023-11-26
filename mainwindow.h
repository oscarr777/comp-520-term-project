#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQuery>
#include <QSqlDatabase>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");


private slots:
    void on_createEntryPushButton_clicked();
    void on_readEntryPushButton_clicked();
    void on_updateEntryPushButton_clicked();
    void on_deleteEntryPushButton_clicked();
    void on_returnFromCreatePushButton_clicked();
    void on_returnFromReadPushButton_clicked();
    void on_returnFromUpdatePushButton_clicked();
    void on_returnFromDeletePushButton_clicked();
    void on_employeeLoginPushButton_clicked();
    void on_lookupOrderPushButton_clicked();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
