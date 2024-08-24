#include "dsa/sport.hpp"
#include "mainwindow.hpp"
#include "ui_mainwindow.h"

void MainWindow::initSportsPage() { initSportTable(); }

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
    item_name->setFlags(item_name->flags() & ~Qt::ItemIsEditable); // type

    // type
    auto item_type = new QTableWidgetItem(cur.sport_type_str());
    item_type->setTextAlignment(Qt::AlignCenter);
    item_type->setFlags(item_type->flags() & ~Qt::ItemIsEditable); // type

    // gender
    auto item_gender = new QTableWidgetItem(cur.sport_gender_str());
    item_gender->setTextAlignment(Qt::AlignCenter);
    item_gender->setFlags(item_gender->flags() & ~Qt::ItemIsEditable); // type

    // insert
    ui->SportsListTable->setItem(i, 0, item_name);
    ui->SportsListTable->setItem(i, 1, item_type);
    ui->SportsListTable->setItem(i, 2, item_gender);
  }

  ui->SportsListTable->resizeColumnToContents(0);
}
