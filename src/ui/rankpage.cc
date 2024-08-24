#include "dsa/country.hpp"
#include "dsa/vararray.hpp"
#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <qtablewidget.h>

static QStringList const rankTableHeaders = {
    "Rank", "Country", "Index", "TotalPoints", "MenPoints", "WomenPoints"};

void MainWindow::initRankPage() {
  static QString sortComboBoxItem[] = {
      "men sports points",
      "women sports points",
      "total points",
      "country index",
  };

  ui->sortComboBox->addItem(sortComboBoxItem[SORT_BY_MEN_POINTS]);
  ui->sortComboBox->addItem(sortComboBoxItem[SORT_BY_WOMEN_POINTS]);
  ui->sortComboBox->addItem(sortComboBoxItem[SORT_BY_TOTAL_POINTS]);
  ui->sortComboBox->addItem(sortComboBoxItem[SORT_BY_COUNTRY_INDEX]);

  ui->sortComboBox->setCurrentIndex(0);

  connect(ui->sortButton, &QPushButton::clicked, this,
          &MainWindow::updateRankTable);

  ui->rankTable->setColumnCount(rankTableHeaders.size());
  ui->rankTable->setHorizontalHeaderLabels(rankTableHeaders);
  ui->rankTable->verticalHeader()->setVisible(false);
  ui->rankTable->resizeColumnsToContents();
}

void MainWindow::updateRankTable() {
  qDebug() << "submit button clicked";
  qDebug() << "sortComboBox: " << ui->sortComboBox->currentText();

  static int last_index = -1;
  int const current_index = ui->sortComboBox->currentIndex();

  if (rank_updated == false && current_index == last_index) {
    qDebug() << "nothing changed";
    return;
  }

  rank_updated = false;
  last_index = current_index;

  Q_ASSERT(current_index >= SORT_BY_MEN_POINTS &&
           current_index <= SORT_BY_COUNTRY_INDEX);

  dsa::vararray<country_table_item> countries;
  countries.reserve(statistic.country_count());
  auto const country_data = statistic.country_data();
  for (int i = 0; i < statistic.country_count(); i++) {
    countries.push_back({country_data[i].name(),
                         country_data[i].get_women_points(),
                         country_data[i].get_men_points(), i + 1});
  }

  // sort the countries
  sortCountry(countries, (sort_type)current_index);

  // set table
  ui->rankTable->clear();
  ui->rankTable->setHorizontalHeaderLabels(rankTableHeaders);
  ui->rankTable->setRowCount(statistic.country_count());

  for (int i = 0; i < countries.size(); i++) {
    auto item_rank = new QTableWidgetItem(QString::number(i + 1));
    ui->rankTable->setItem(i, 0, item_rank);

    auto item_name = new QTableWidgetItem(countries[i].country_name);
    ui->rankTable->setItem(i, 1, item_name);

    auto item_index = new QTableWidgetItem(QString::number(countries[i].id));
    ui->rankTable->setItem(i, 2, item_index);

    auto item_total = new QTableWidgetItem(
        QString::number(countries[i].men_points + countries[i].women_points));
    ui->rankTable->setItem(i, 3, item_total);

    auto item_men =
        new QTableWidgetItem(QString::number(countries[i].men_points));
    ui->rankTable->setItem(i, 4, item_men);

    auto item_women =
        new QTableWidgetItem(QString::number(countries[i].women_points));
    ui->rankTable->setItem(i, 5, item_women);


  }

  // set uneditable and center

  for (int i = 0; i < statistic.country_count(); i++) {
    for (int j = 0; j < rankTableHeaders.size(); j++) {
      auto item = ui->rankTable->item(i, j);
      item->setTextAlignment(Qt::AlignCenter);
      item->setFlags(item->flags() & ~Qt::ItemIsEditable); // type
    }
  }

  ui->rankTable->resizeColumnsToContents();
}

void MainWindow::sortCountry(dsa::vararray<country_table_item> &countries,
                             sort_type const type) {
  auto cmp_by_men_points = [](country_table_item const &a,
                              country_table_item const &b) {
    if (a.men_points != b.men_points)
      return a.men_points > b.men_points;
    return a.id < b.id;
  };

  auto cmp_by_women_points = [](country_table_item const &a,
                                country_table_item const &b) {
    if (a.women_points != b.women_points)
      return a.women_points > b.women_points;
    return a.id < b.id;
  };

  auto cmp_by_total_points = [](country_table_item const &a,
                                country_table_item const &b) {
    int const pa = a.men_points + a.women_points;
    int const pb = b.men_points + b.women_points;
    if (pa != pb)
      return pa > pb;
    return a.id < b.id;
  };

  Q_ASSERT(countries.size());

  switch (type) {
  case SORT_BY_MEN_POINTS:
    countries.sort(cmp_by_men_points);
    break;

  case SORT_BY_WOMEN_POINTS:
    countries.sort(cmp_by_women_points);
    break;

  case SORT_BY_TOTAL_POINTS:
    countries.sort(cmp_by_total_points);
    break;

  case SORT_BY_COUNTRY_INDEX:
    // no need to compare
    break;
  default:
    Q_ASSERT(0);
  }
}
