#include "dsa/sport.hpp"
#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <qnamespace.h>
#include <qpushbutton.h>
#include <qtablewidget.h>

void MainWindow::initSportsPage() {
  ui->SportsGenderCombo->addItem("Women");
  ui->SportsGenderCombo->addItem("Men");

  ui->SportsTypeCombo->addItem("Score Top 3");
  ui->SportsTypeCombo->addItem("Score Top 5");

  initSportTable();

  // connect the submit button
  connect(ui->SportsAddButton, &QPushButton::pressed, this,
          &MainWindow::on_sports_submit_button_clicked);
}

void MainWindow::initSportTable() {
  auto sports = statistic.sport_data();
  int const cnt = statistic.sport_count();

  // name; score type; gender
  ui->SportsListTable->setColumnCount(3);
  ui->SportsListTable->setRowCount(cnt);

  QStringList headers;
  headers << "SportsName" << "ScoreType" << "SportsGender";
  ui->SportsListTable->setHorizontalHeaderLabels(headers);

  for (int i = 0; i < cnt; i++) {
    auto const &cur = sports[i];
    // name
    auto item_name = new QTableWidgetItem(cur.name());
    item_name->setTextAlignment(Qt::AlignCenter);
    // type
    auto item_type = new QTableWidgetItem(
        cur.sport_type() == dsa::SCORE_TOP5 ? "score top5" : "score top3");
    item_type->setTextAlignment(Qt::AlignCenter);
    // gender
    auto item_gender =
        new QTableWidgetItem(cur.sport_gender() == dsa::MEN ? "men" : "women");
    item_gender->setTextAlignment(Qt::AlignCenter);
    // insert
    ui->SportsListTable->setItem(i, 0, item_name);
    ui->SportsListTable->setItem(i, 1, item_type);
    ui->SportsListTable->setItem(i, 2, item_gender);
  }

  ui->SportsListTable->resizeColumnToContents(0);
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
