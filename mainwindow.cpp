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

    ui->customerStateComboBox->addItem("AL");
    ui->customerStateComboBox->addItem("AK");
    ui->customerStateComboBox->addItem("AZ");
    ui->customerStateComboBox->addItem("AR");
    ui->customerStateComboBox->addItem("CA");
    ui->customerStateComboBox->addItem("CO");
    ui->customerStateComboBox->addItem("CT");
    ui->customerStateComboBox->addItem("DE");
    ui->customerStateComboBox->addItem("DC");
    ui->customerStateComboBox->addItem("FL");
    ui->customerStateComboBox->addItem("GA");
    ui->customerStateComboBox->addItem("HI");
    ui->customerStateComboBox->addItem("ID");
    ui->customerStateComboBox->addItem("IL");
    ui->customerStateComboBox->addItem("IN");
    ui->customerStateComboBox->addItem("IA");
    ui->customerStateComboBox->addItem("KS");
    ui->customerStateComboBox->addItem("KY");
    ui->customerStateComboBox->addItem("LA");
    ui->customerStateComboBox->addItem("ME");
    ui->customerStateComboBox->addItem("MD");
    ui->customerStateComboBox->addItem("MA");
    ui->customerStateComboBox->addItem("MI");
    ui->customerStateComboBox->addItem("MN");
    ui->customerStateComboBox->addItem("MS");
    ui->customerStateComboBox->addItem("MO");
    ui->customerStateComboBox->addItem("MT");
    ui->customerStateComboBox->addItem("NE");
    ui->customerStateComboBox->addItem("NV");
    ui->customerStateComboBox->addItem("NH");
    ui->customerStateComboBox->addItem("NJ");
    ui->customerStateComboBox->addItem("NM");
    ui->customerStateComboBox->addItem("NY");
    ui->customerStateComboBox->addItem("NC");
    ui->customerStateComboBox->addItem("ND");
    ui->customerStateComboBox->addItem("OH");
    ui->customerStateComboBox->addItem("OK");
    ui->customerStateComboBox->addItem("OR");
    ui->customerStateComboBox->addItem("PA");
    ui->customerStateComboBox->addItem("PR");
    ui->customerStateComboBox->addItem("RI");
    ui->customerStateComboBox->addItem("SC");
    ui->customerStateComboBox->addItem("SD");
    ui->customerStateComboBox->addItem("TN");
    ui->customerStateComboBox->addItem("TX");
    ui->customerStateComboBox->addItem("UT");
    ui->customerStateComboBox->addItem("VT");
    ui->customerStateComboBox->addItem("VA");
    ui->customerStateComboBox->addItem("VI");
    ui->customerStateComboBox->addItem("WA");
    ui->customerStateComboBox->addItem("WV");
    ui->customerStateComboBox->addItem("WI");
    ui->customerStateComboBox->addItem("WY");
    ui->shippingMethodComboBox->addItem("Standard");
    ui->shippingMethodComboBox->addItem("2 Day");
    ui->shippingMethodComboBox->addItem("Next Day");

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
        //qDebug() << "Username: " << userValue;
        //qDebug() << "Password: " << passwdValue;
        //qDebug() << "Hostname: " << hostValue;
        //qDebug() << "Database: " << dbValue;
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

void MainWindow::on_employeeLoginPushButton_clicked()
{
    QString employeeId = ui->employeeIdLineEdit->text();
    employeeIdGlobal = employeeId;

    QString employeePassword = ui->employeePasswordLineEdit->text();

    QString queryConcat = "select * from employee_login where emp_id=" + employeeId;
    qDebug() << queryConcat;
    QString query;
    QSqlQuery qry;

    QSqlRecord record = db.record("employee_login");

    qry.prepare(queryConcat);
    qry.executedQuery();

    if (qry.exec())
    {
        qDebug() << "Query executed";
        qDebug() << "Number of fields: " << record.count();
        while (qry.next())
        {
            for (int i = 0; i < 2; i++)
            {
                QString inputWord = qry.value(i).toString();
                qDebug() << inputWord;

                switch(i)
                {
                    case 0:
                        break;
                    case 1:
                        if (inputWord == employeePassword)
                        {
                            ui->employeeLoggedInLabel->setStyleSheet("font: 700 10pt \"Quicksand\"; color: rgb(0, 255, 0);");
                            ui->employeeLoggedInLabel->setText("Employee ID: " + employeeId + " logged in");
                            ui->welcomeEmployeeLine1Label->setText("");
                            ui->welcomeEmployeeLine2Label->setText("");
                        }
                        else
                        {
                            ui->welcomeEmployeeLine1Label->setText("Invalid Credentials For:");
                            ui->welcomeEmployeeLine2Label->setText(employeeId);
                            ui->welcomeEmployeeLine2Label->setStyleSheet("font: 700 20pt \"Quicksand\"; color: rgb(255, 0, 0);");
                        }
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

void MainWindow::on_lookupOrderPushButton_clicked()
{
    QString orderId = ui->orderIdLookupLineEdit->text();
    QString customerId = ui->customerIdLookupLineEdit->text();

    if (orderId == NULL && customerId != NULL)
    {
        qDebug() << "orderid null";
        QString queryConcat = "select * from orders where customer_id=" + customerId;
        qDebug() << queryConcat;
        QString query;
        QSqlQuery qry;

        QSqlRecord record = db.record("orders");

        qry.prepare(queryConcat);
        qry.executedQuery();

        if (qry.exec())
        {
            qDebug() << "Query executed";
            qDebug() << "Number of fields: " << record.count();
            while (qry.next())
            {
                for (int i = 0; i < 6; i++)
                {
                    QString inputWord = qry.value(i).toString();
                    qDebug() << inputWord;

                    switch(i)
                    {
                        case 0:
                            ui->orderIdLookupLabel->setText(inputWord);
                            break;
                        case 1:
                            ui->customerIdLookupLabel->setText(inputWord);
                            break;
                        case 2:
                            ui->orderDateLookupLabel->setText(inputWord);
                            break;
                        case 3:
                            //Not Needed for display
                            break;
                        case 4:
                            ui->shippingIdLookupLabel->setText(inputWord);
                            break;
                        case 5:
                            ui->fByEmployeeIdLookupLabel->setText(inputWord);
                            break;

                        default:
                            qDebug() << "Invalid index";
                            break;


                    }

                }
            }
        }
    }

    else if (orderId != NULL && customerId == NULL)
    {
        qDebug() << "customerid null";
        QString queryConcat = "select * from orders where order_id=" + orderId;
        qDebug() << queryConcat;
        QString query;
        QSqlQuery qry;

        QSqlRecord record = db.record("orders");

        qry.prepare(queryConcat);
        qry.executedQuery();

        if (qry.exec())
        {
            qDebug() << "Query executed";
            qDebug() << "Number of fields: " << record.count();
            while (qry.next())
            {
                for (int i = 0; i < 6; i++)
                {
                    QString inputWord = qry.value(i).toString();
                    qDebug() << inputWord;

                    switch(i)
                    {
                        case 0:
                            ui->orderIdLookupLabel->setText(inputWord);
                            break;
                        case 1:
                            ui->customerIdLookupLabel->setText(inputWord);
                            break;
                        case 2:
                            ui->orderDateLookupLabel->setText(inputWord);
                            break;
                        case 3:
                            //Not Needed for display
                            break;
                        case 4:
                            ui->shippingIdLookupLabel->setText(inputWord);
                            break;
                        case 5:
                            ui->fByEmployeeIdLookupLabel->setText(inputWord);
                            break;

                        default:
                            qDebug() << "Invalid index";
                            break;


                    }

                }
            }
        }
    }

    else if (orderId != NULL && customerId != NULL)
    {
        qDebug() << "none null, defaulting to orderid";
        QString queryConcat = "select * from orders where order_id=" + orderId;
        qDebug() << queryConcat;
        QString query;
        QSqlQuery qry;

        QSqlRecord record = db.record("orders");

        qry.prepare(queryConcat);
        qry.executedQuery();

        if (qry.exec())
        {
            qDebug() << "Query executed";
            qDebug() << "Number of fields: " << record.count();
            while (qry.next())
            {
                for (int i = 0; i < 6; i++)
                {
                    QString inputWord = qry.value(i).toString();
                    qDebug() << inputWord;

                    switch(i)
                    {
                        case 0:
                            ui->orderIdLookupLabel->setText(inputWord);
                            break;
                        case 1:
                            ui->customerIdLookupLabel->setText(inputWord);
                            break;
                        case 2:
                            ui->orderDateLookupLabel->setText(inputWord);
                            break;
                        case 3:
                            //Not Needed for display
                            break;
                        case 4:
                            ui->shippingIdLookupLabel->setText(inputWord);
                            break;
                        case 5:
                            ui->fByEmployeeIdLookupLabel->setText(inputWord);
                            break;

                        default:
                            qDebug() << "Invalid index";
                            break;


                    }

                }
            }
        }
    }

    else if (orderId == NULL && customerId == NULL)
    {
        //error enter either id
        ui->nullLookupLabel->setText("Error, enter an order id or customer id");
    }

    else
    {
        qDebug() << "Query failed";
    }
}

void MainWindow::on_createOrderPushButton_clicked()
{
    QString customerFName = ui->customerFnameLineEdit->text();
    QString customerLName = ui->customerLnameLineEdit->text();
    QString customerAddress = ui->customerAddress1LineEdit->text();
    QString customerStreet = ui->customerAddress2LineEdit->text();
    QString customerCity = ui->customerCityLineEdit->text();
    QString customerState = ui->customerStateComboBox->currentText();
    QString customerPostalCode = ui->customerZipLineEdit->text();
    QString customerEmail = ui->customerEmailLineEdit->text();
    QString customerPhone = ui->customerPhoneNumberLineEdit->text();
    QString customerCountry = "USA";
    QString customerOrderDate = "2023-11-29";

    QString customerId = ui->customerIdLineEdit->text();
    QString orderId = ui->orderIdLineEdit->text();
    QString queryConcat1 = "INSERT INTO oscarrci_warehouse.customer VALUES(" "'" + customerId + "', '" + customerFName + "', '" + customerLName + "', '" + customerEmail +  "', '" + customerPhone + "')";
    qDebug() << queryConcat1;
    QString query1;
    QSqlQuery qry1;
    qry1.prepare(queryConcat1);
    qry1.executedQuery();

    if (qry1.exec())
    {
        qDebug() << "Query executed";
        ui->orderSubmissionLabel->setStyleSheet("font: 700 16pt \"Quicksand\"; color: rgb(0, 255, 0)");
        ui->orderSubmissionLabel->setText("Executed");
        while (qry1.next())
        {
            QString inputWord = qry1.value(0).toString();
            qDebug() << inputWord;
        }
    }

    else
    {
        qDebug() << "Query failed";
        ui->orderSubmissionLabel->setStyleSheet("font: 700 16pt \"Quicksand\"; color: rgb(255, 0, 0)");
        ui->orderSubmissionLabel->setText("Failed");
    }


    QString queryConcat2 = "INSERT INTO oscarrci_warehouse.shipping_address VALUES(" "'" + customerId + "', '" + customerAddress + "', '" + customerStreet + "', '" + customerCity +
            "', '" + customerState +  "', '" + customerPostalCode + "', '" + customerCountry + "')";
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
        ui->orderSubmissionLabel->setStyleSheet("font: 700 16pt \"Quicksand\"; color: rgb(0, 255, 0)");
        ui->orderSubmissionLabel->setText("Executed");
    }

    else
    {
        qDebug() << "Query failed";
        ui->orderSubmissionLabel->setStyleSheet("font: 700 16pt \"Quicksand\"; color: rgb(255, 0, 0)");
        ui->orderSubmissionLabel->setText("Failed");
    }

    QString queryConcat3 = "INSERT INTO orders(order_id, customer_id, order_date, shipping_add_id, emp_id) VALUES(" "'" + orderId + "', '" + customerId + "', '" + customerOrderDate + "', '" "1"
            "', '" + employeeIdGlobal + "')";
    qDebug() << queryConcat3;
    QString query3;
    QSqlQuery qry3;
    qry3.prepare(queryConcat3);
    qry3.executedQuery();

    if (qry3.exec())
    {
        qDebug() << "Query executed";
        while (qry3.next())
        {
            QString inputWord = qry3.value(0).toString();
            qDebug() << inputWord;
        }
        ui->orderSubmissionLabel->setStyleSheet("font: 700 16pt \"Quicksand\"; color: rgb(0, 255, 0)");
        ui->orderSubmissionLabel->setText("Executed");
    }

    else
    {
        qDebug() << "Query failed";
        ui->orderSubmissionLabel->setStyleSheet("font: 700 16pt \"Quicksand\"; color: rgb(255, 0, 0)");
        ui->orderSubmissionLabel->setText("Failed");
    }
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
