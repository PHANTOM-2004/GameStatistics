#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <qpushbutton.h>

void MainWindow::initSportsPage() {
  ui->SportsGenderCombo->addItem("Women");
  ui->SportsGenderCombo->addItem("Men");

  ui->SportsTypeCombo->addItem("Score Top 3");
  ui->SportsTypeCombo->addItem("Score Top 5");

  // connect the submit button
  connect(ui->SportsAddButton, &QPushButton::pressed, this,
          &MainWindow::on_sports_submit_button_clicked);
}

void MainWindow::on_sports_submit_button_clicked() {
  qDebug() << "sports add button clicked";

  QString const sports_name = ui->SportsNameInput->text();
  QString const sports_score_type = ui->SportsTypeCombo->currentText();
  QString const sports_gender = ui->SportsGenderCombo->currentText();

  qDebug() << "name: " << sports_name;
  qDebug() << "score type: " << sports_score_type;
  qDebug() << "gender: " << sports_gender;

  // we need to update the table, which shows all the sports type
}
