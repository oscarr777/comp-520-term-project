#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QDebug>
#include <QStyle>
#include <iostream>
#include <QSqlRecord>

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
    QString query = (QLatin1String("select budget from Film_Box_Office WHERE movie_id=7"));
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

void MainWindow::on_createRecordPushButton_clicked()
{
    QString movieId = ui->movieIdLineEdit->text();
    QString facenumber = ui->facenumberLineEdit->text();
    QString budget = ui->budgetLineEdit->text();
    QString gross = ui->grossLineEdit->text();
/*
    QString queryConcat1 = "INSERT INTO Film VALUES" "('" + movieId + "')";
    qDebug() << queryConcat1;
    QString query1;
    QSqlQuery qry1;
    qry1.prepare(queryConcat1);
    qry1.executedQuery();

    if (qry1.exec())
    {
        qDebug() << "Query executed";
        ui->queryExecutionStatusLabel->setStyleSheet("font: 700 16pt \"Quicksand\"; color: rgb(0, 255, 0)");
        ui->queryExecutionStatusLabel->setText("Executed");
        while (qry1.next())
        {
            QString inputWord = qry1.value(0).toString();
            qDebug() << inputWord;
        }
    }

    else
    {
        qDebug() << "Query failed";
        ui->queryExecutionStatusLabel->setStyleSheet("font: 700 16pt \"Quicksand\"; color: rgb(255, 0, 0)");
        ui->queryExecutionStatusLabel->setText("Failed");
    }
*/

    QString queryConcat2 = "INSERT INTO Film_Box_Office VALUES"  "('" + movieId + "', " "'" + facenumber + "', " "'" + budget + "', " "'" + gross + "')";
    qDebug() << queryConcat2;
    QString query2;
    QSqlQuery qry2;
    qry2.prepare(queryConcat2);
    qry2.executedQuery();

    if (qry2.exec())
    {
        qDebug() << "Query executed";
        while (qry2.next())
        {
            QString inputWord = qry2.value(0).toString();
            qDebug() << inputWord;
        }
    }

    else
    {
        qDebug() << "Query failed";
    }
}

void MainWindow::on_lokkupReadPushButton_clicked()
{
    QString movieId = ui->lookupLineEdit->text();
    QString queryConcat = "SELECT * FROM Film_Box_Office WHERE movie_id=" + movieId;
    qDebug() << queryConcat;
    QString query;
    QSqlQuery qry;

    QSqlRecord record = db.record("Film_Box_Office");

    qry.prepare(queryConcat);
    qry.executedQuery();

    if (qry.exec())
    {
        qDebug() << "Query executed";
        qDebug() << "Number of fields: " << record.count();
        while (qry.next())
        {
            for (int i = 0; i < 4; i++)
            {
                QString inputWord = qry.value(i).toString();
                qDebug() << inputWord;

                switch(i)
                {
                    case 0:
                        ui->movieIdLookupLabel->setStyleSheet("");
                        ui->movieIdLookupLabel->setText(inputWord);
                        break;
                    case 1:
                        ui->facenumberLookupLabel->setStyleSheet("");
                        ui->facenumberLookupLabel->setText(inputWord);
                        break;
                    case 2:
                        ui->grossLookupLabel->setStyleSheet("");
                        ui->grossLookupLabel->setText(inputWord);
                        break;
                    case 3:
                        ui->budgetLookupLabel->setStyleSheet("");
                        ui->budgetLookupLabel->setText(inputWord);
                        break;
                    default:
                        qDebug() << "Invalid index";
                        break;


                }

            }
        }
    }

    else
    {
        qDebug() << "Query failed";
    }
}

void MainWindow::on_updateRecordPushButton_clicked()
{
    QString movieId = ui->movieIdUpdateLineEdit->text();
    QString facenumber = ui->facenumberUpdateLineEdit->text();
    QString budget = ui->budgetUpdateLineEdit->text();
    QString gross = ui->grossUpdateLineEdit->text();

    QString queryConcat = "UPDATE Film_Box_Office SET " "facenumber_in_poster=" + facenumber + ", budget=" + budget + ", gross=" + gross + " WHERE movie_id=" + movieId;
    qDebug() << queryConcat;
    QString query;
    QSqlQuery qry;
    qry.prepare(queryConcat);
    qry.executedQuery();

    if (qry.exec())
    {
        qDebug() << "Query executed";
        ui->updateRecordStatusLabel->setStyleSheet("font: 700 16pt \"Quicksand\"; color: rgb(0, 255, 0)");
        ui->updateRecordStatusLabel->setText("Executed");
        while (qry.next())
        {
            QString inputWord = qry.value(0).toString();
            qDebug() << inputWord;
        }
    }

    else
    {
        qDebug() << "Query failed";
        ui->updateRecordStatusLabel->setStyleSheet("font: 700 16pt \"Quicksand\"; color: rgb(255, 0, 0)");
        ui->updateRecordStatusLabel->setText("Failed");
    }
}

void MainWindow::on_verifyDeleteRecordPushButton_clicked()
{
    QString movieId = ui->movieIdDeleteLineEdit->text();
    QString queryConcat = "SELECT * FROM Film_Box_Office WHERE movie_id=" + movieId;
    qDebug() << queryConcat;
    QString query;
    QSqlQuery qry;

    QSqlRecord record = db.record("Film_Box_Office");

    qry.prepare(queryConcat);
    qry.executedQuery();

    if (qry.exec())
    {
        qDebug() << "Query executed";
        qDebug() << "Number of fields: " << record.count();
        while (qry.next())
        {
            for (int i = 0; i < 4; i++)
            {
                QString inputWord = qry.value(i).toString();
                qDebug() << inputWord;

                switch(i)
                {
                    case 0:
                        ui->movieIdDeleteLabel->setStyleSheet("");
                        ui->movieIdDeleteLabel->setText(inputWord);
                        break;
                    case 1:
                        ui->facenumberDeleteLabel->setStyleSheet("");
                        ui->facenumberDeleteLabel->setText(inputWord);
                        break;
                    case 2:
                        ui->grossDeleteLabel->setStyleSheet("");
                        ui->grossDeleteLabel->setText(inputWord);
                        break;
                    case 3:
                        ui->budgetDeleteLabel->setStyleSheet("");
                        ui->budgetDeleteLabel->setText(inputWord);
                        break;
                    default:
                        qDebug() << "Invalid index";
                        break;


                }
            }
        }
        ui->deleteRecordStatusLabel->setText("Executed");
        ui->deleteRecordStatusLabel->setStyleSheet("font: 700 16pt \"Quicksand\"; color: rgb(0, 255, 0)");
    }

    else
    {
        ui->deleteRecordStatusLabel->setText("Failed");
        ui->deleteRecordStatusLabel->setStyleSheet("font: 700 16pt \"Quicksand\"; color: rgb(255, 0, 0)");
        qDebug() << "Query failed";
    }
}

void MainWindow::on_deleteRecordPushButton_clicked()
{
    QString movieId = ui->movieIdDeleteLineEdit->text();

    QString queryConcat = "DELETE FROM Film_Box_Office WHERE movie_id=" + movieId;
    qDebug() << queryConcat;
    QString query;
    QSqlQuery qry;
    qry.prepare(queryConcat);
    qry.executedQuery();

    if (qry.exec())
    {
        qDebug() << "Query executed";
        ui->queryExecutionStatusLabel->setStyleSheet("font: 700 16pt \"Quicksand\"; color: rgb(0, 255, 0)");
        ui->queryExecutionStatusLabel->setText("Executed");
        while (qry.next())
        {
            QString inputWord = qry.value(0).toString();
            qDebug() << inputWord;
        }
    }

    else
    {
        qDebug() << "Query failed";
        ui->queryExecutionStatusLabel->setStyleSheet("font: 700 16pt \"Quicksand\"; color: rgb(255, 0, 0)");
        ui->queryExecutionStatusLabel->setText("Failed");
    }
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
