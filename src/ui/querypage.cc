#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <limits>

enum {
  COL_COUNTRY_INDEX = 0,
  COL_COUNTRY,
  COL_COUNTRY_SCORE,
  COL_COUNTRY_RANK,
  SIZE_OF_COL
};

void MainWindow::initQueryTable() {

  queryTableHeaders.resize(SIZE_OF_COL);
  queryTableHeaders[COL_COUNTRY_INDEX] = tr("CountryIndex");
  queryTableHeaders[COL_COUNTRY] = tr("Country");
  queryTableHeaders[COL_COUNTRY_SCORE] = tr("Score");
  queryTableHeaders[COL_COUNTRY_RANK] = tr("Rank");
  ui->queryTable->setColumnCount(queryTableHeaders.size());
  ui->queryTable->setHorizontalHeaderLabels(queryTableHeaders);
  ui->queryTable->verticalHeader()->setVisible(false);
  ui->queryTable->resizeColumnToContents(COL_COUNTRY);
}

void MainWindow::initQueryPage() {
  // set the country combobox, there will be
  // an option for all country

  initCountryComboBox(ui->searchCountryComboBox);
  ui->searchCountryComboBox->insertItem(0, tr("All Countries"));
  ui->searchCountryComboBox->setCurrentIndex(0);

  // set the sport combobox, there will not be
  // an option for all sports, just because i am lazy

  auto sports = statistic.sport_data();
  int const cnt = statistic.sport_count();

  Q_ASSERT(cnt > 1);
  for (int i = 0; i < cnt; i++)
    ui->searchCountrySportComboBox->addItem(QString::asprintf("[%2d] ", i + 1) +
                                            sports[i].name());

  // init the table page
  initQueryTable();

  // connnect the search button
  connect(ui->searchButton, &QPushButton::clicked, this,
          &MainWindow::updateQueryTable);

  // connect the info label
  connect(ui->searchCountryComboBox, &QComboBox::currentIndexChanged, this,
          &MainWindow::updateQueryInfo);
  connect(ui->searchCountrySportComboBox, &QComboBox::currentIndexChanged, this,
          &MainWindow::updateQueryInfo);
  updateQueryInfo();
}

void MainWindow::updateQueryTable() {
  qDebug() << "search button clicked";
  qDebug() << "current country" << ui->searchCountryComboBox->currentText();
  qDebug() << "current sport" << ui->searchCountrySportComboBox->currentText();

  static int last_country_index = std::numeric_limits<int>::min();
  static int last_sport_index = std::numeric_limits<int>::min();

  int const target_country_index =
      ui->searchCountryComboBox->currentIndex() - 1;
  int const target_sport_index = ui->searchCountrySportComboBox->currentIndex();

  Q_ASSERT((target_country_index >= 0 &&
            target_country_index < statistic.country_count()) ||
           target_country_index == -1);
  Q_ASSERT(target_sport_index >= 0 &&
           target_sport_index < statistic.sport_count());

  if (!query_updated && (last_country_index == target_country_index &&
                         last_sport_index == target_sport_index)) {
    qDebug() << "No need to update";
    return;
  }

  query_updated = false;
  last_country_index = target_country_index;
  last_sport_index = target_sport_index;

  auto const &current_sport = get_statistic().sport(target_sport_index);
  auto const &scored_countries = current_sport.get_scored_countries();

  ui->queryTable->clear();
  ui->queryTable->setHorizontalHeaderLabels(queryTableHeaders);
  ui->queryTable->setRowCount(current_sport.sport_type());

  int row = 0;
  for (int i = 0; i < scored_countries.size(); i++) {
    int const rank = i + 1;
    int const country_index = scored_countries[i].country_index;
    int const country_score = scored_countries[i].score;
    QString const &country_name = get_statistic().country(country_index).name();

    bool const hit =
        target_country_index < 0 ||
        (target_country_index >= 0 && target_country_index == country_index);

    qDebug() << "target index" << target_country_index;
    qDebug() << "test country:" << country_index
             << "hit: " << (hit ? "Y" : "N");
    qDebug() << "score:" << country_score;
    qDebug() << "rank:" << rank;

    if (!hit)
      continue;

    auto item_index = new QTableWidgetItem(QString::number(country_index + 1));
    ui->queryTable->setItem(row, COL_COUNTRY_INDEX, item_index);

    auto item_country_name = new QTableWidgetItem(country_name);
    ui->queryTable->setItem(row, COL_COUNTRY, item_country_name);

    auto item_country_score =
        new QTableWidgetItem(QString::number(country_score));
    ui->queryTable->setItem(row, COL_COUNTRY_SCORE, item_country_score);

    auto item_country_rank = new QTableWidgetItem(QString::number(rank));
    ui->queryTable->setItem(row, COL_COUNTRY_RANK, item_country_rank);

    row++;
  }

  if (row > 0) {
    setTableFormat(ui->queryTable, row, SIZE_OF_COL);
    ui->queryTable->resizeColumnToContents(COL_COUNTRY);
  }

  if (row == 0) {
    // there is no result
    qDebug() << "no result";
  }
}

void MainWindow::updateQueryInfo() {
  int const sport_index = ui->searchCountrySportComboBox->currentIndex();

  qDebug() << "updateQueryInfo";
  auto const &sport = get_statistic().sport(sport_index);

  QString const text = tr("Query for country: %1 ; Sport: %2, type: [%3]+[%4]")
                           .arg(ui->searchCountryComboBox->currentText())
                           .arg(ui->searchCountrySportComboBox->currentText())
                           .arg(sport.sport_type_str())
                           .arg(sport.sport_gender_str());

  ui->queryInfoLabel->setText(text);
}
