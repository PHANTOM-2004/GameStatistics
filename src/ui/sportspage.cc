#include "dsa/sport.hpp"
#include "mainwindow.hpp"
#include "ui_mainwindow.h"

void MainWindow::initSportsPage() {
  initSportTable();
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
