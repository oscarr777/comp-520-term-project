#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QDebug>
#include <QStyle>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Passing in credentials through env variables
    char* envVarPass = "COMP520_DB_PASSWORD";
    char* envVarUser = "COMP520_DB_USERNAME";
    char* envVarDbName = "COMP520_DB_NAME";
    char* envVarHostName= "COMP520_HOST_NAME";

    QString passwdValue;
    QString userValue;
    QString dbValue;
    QString hostValue;

    passwdValue = getenv(envVarPass);
    userValue = getenv(envVarUser);
    dbValue = getenv(envVarDbName);
    hostValue = getenv(envVarHostName);

    // if executes if a non null value is returned
    // otherwise else executes
    if (passwdValue != NULL && userValue != NULL && dbValue != NULL && hostValue != NULL)
    {
        qDebug() << "Passing credentials into db login...";
        db.setHostName(hostValue);
        db.setDatabaseName(dbValue);
        db.setUserName(userValue);
        db.setPassword(passwdValue);
    }
    else
    {
        if (passwdValue == NULL)
            qDebug() << "Password env variable not set!";
        if (userValue == NULL)
            qDebug() << "Username env variable not set!";
        if (dbValue == NULL)
            qDebug() << "Database Name env variable not set!";
        if (hostValue == NULL)
            qDebug() << "Hostname env variable not set!";

    }

    if (db.open())
    {
        qDebug() << "db open";
        ui->connectionStatusLabel->setText("Connected");

        ui->connectionStatusLabel->setStyleSheet("font: 700 14pt \"Quicksand\"; color: rgb(76, 255, 73)");
        ui->dbNameLabel->setText(db.databaseName());

    }

    else
    {
        ui->connectionStatusLabel->setText("Not Connected");
        ui->connectionStatusLabel->setStyleSheet("font: 700 14pt \"Quicksand\"; color: rgb(255, 0, 0)");
        qDebug() << "Could not open db";
    }
    //Test query to verify successful connection
    QString query = (QLatin1String("select INV_SUBTOTAL from INVOICE WHERE INV_NUMBER=1002"));
    QSqlQuery qry;
    qry.prepare(query);
    qry.executedQuery();

    if (qry.exec())
    {
        while (qry.next())
        {
            QString inputWord = qry.value(0).toString();
            qDebug() << inputWord;
        }
    }

    else
    {
        qDebug() << "Query failed";
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_connectToDatabasePushButton_clicked()
{
    qDebug() << "connectToDbClicked";

    db.setHostName(ui->dbHostNameLineEdit->text());
    db.setDatabaseName(ui->dbNameLineEdit->text());
    db.setUserName(ui->dbUsernameLineEdit->text());
    db.setPassword(ui->dbUserPasswordLineEdit->text());
    if (db.open())
    {
        qDebug() << "db open";
        ui->connectionStatusLabel->setText("Connected");

        ui->connectionStatusLabel->setStyleSheet("font: 700 14pt \"Quicksand\"; color: rgb(76, 255, 73)");
        ui->dbNameLabel->setText(db.databaseName());

    }

    else
        qDebug() << "Could not open db";

}

void MainWindow::on_createEntryPushButton_clicked()
{
    ui->crudMenu->setCurrentIndex(1);

}
void MainWindow::on_readEntryPushButton_clicked()
{
    ui->crudMenu->setCurrentIndex(2);
}
void MainWindow::on_updateEntryPushButton_clicked()
{
    ui->crudMenu->setCurrentIndex(3);
}
void MainWindow::on_deleteEntryPushButton_clicked()
{
    ui->crudMenu->setCurrentIndex(4);
}

void MainWindow::on_returnFromCreatePushButton_clicked()
{
    ui->crudMenu->setCurrentIndex(0);
}

void MainWindow::on_returnFromReadPushButton_clicked()
{
    ui->crudMenu->setCurrentIndex(0);
}

void MainWindow::on_returnFromUpdatePushButton_clicked()
{
    ui->crudMenu->setCurrentIndex(0);
}

void MainWindow::on_returnFromDeletePushButton_clicked()
{
    ui->crudMenu->setCurrentIndex(0);
}
