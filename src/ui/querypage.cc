#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <qcombobox.h>

void MainWindow::initQueryTable() {
  enum { COL_COUNTRY = 0, COL_COUNTRY_SCORE, COL_COUNTRY_RANK, SIZE_OF_COL };

  queryTableHeaders.resize(SIZE_OF_COL);
  queryTableHeaders[COL_COUNTRY] = tr("Country");
  queryTableHeaders[COL_COUNTRY_SCORE] = tr("Score");
  queryTableHeaders[COL_COUNTRY_RANK] = tr("Rank");
  ui->queryTable->setColumnCount(queryTableHeaders.size());
  ui->queryTable->setHorizontalHeaderLabels(queryTableHeaders);
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

  int const target_country_index =
      ui->searchCountryComboBox->currentIndex() - 1;
  int const target_sport_index = ui->searchCountrySportComboBox->currentIndex();
  Q_ASSERT((target_country_index >= 0 &&
            target_country_index < statistic.country_count()) ||
           target_country_index == -1);
  Q_ASSERT(target_sport_index >= 0 &&
           target_sport_index < statistic.sport_count());

  auto const &scored_countries =
      get_statistic().sport(target_sport_index).get_scored_countries();

  ui->queryTable->clear();
  ui->queryTable->setHorizontalHeaderLabels(queryTableHeaders);

  for (int i = 0; i < scored_countries.size(); i++) {
    int const rank = i + 1;
    int const country_index = scored_countries[i].country_index;
    int const country_score = scored_countries[i].score;
    if (!(target_country_index >= 0 && target_country_index == country_index))
      continue;
    qDebug() << "query country:" << country_index;
    qDebug() << "query score:" << country_score;
    qDebug() << "query rank:" << rank;
  }
  // auto countries = stat
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
