#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <QMessageBox>

void MainWindow::initCountryComboBox(QComboBox *combo) {
  Q_ASSERT(combo == ui->countryComboBox1 || combo == ui->countryComboBox2 ||
           combo == ui->countryComboBox3 || combo == ui->countryComboBox4 ||
           combo == ui->countryComboBox5 || combo == ui->searchCountryComboBox);

  auto countries = statistic.country_data();
  int const cnt = statistic.country_count();

  Q_ASSERT(cnt > 1);

  for (int i = 0; i < cnt; i++)
    combo->addItem(QString::asprintf("[%2d] ", i + 1) + countries[i].name());

  combo->setCurrentIndex(-1);
  combo->setStatusTip(tr("select country"));
}

void MainWindow::initScoreLineEdit(QLineEdit *line) {
  line->setStatusTip(tr("input the score of the selected country"));
}

void MainWindow::initScoresPage() {
  initScoreSelectBox();

  initScoreInputBox();
}

void MainWindow::initScoreSelectBox() {
  // set the sports comboBox
  auto sports = statistic.sport_data();
  int const cnt = statistic.sport_count();

  Q_ASSERT(cnt > 1);

  for (int i = 0; i < cnt; i++) {
    ui->sportsCombo->addItem(QString::asprintf("[%2d] ", i + 1) +
                             sports[i].name());
  }

  ui->sportsCombo->setEditable(false);
  ui->sportsCombo->setMaxVisibleItems(10);
  ui->sportsCombo->setCurrentIndex(-1);
  ui->sportsCombo->setStatusTip(tr("select the sport to submit scores"));
  ui->sportsGenderLabel->setText(tr("men/women"));
  ui->sportsTypeLabel->setText(tr("score top 3/5"));

  connect(ui->sportsCombo, &QComboBox::currentIndexChanged, this,
          &MainWindow::updateSportsInfo);
}

void MainWindow::initScoreInputBox() {

  // init the input part
  connect(ui->clearButton, &QPushButton::clicked, this,
          &MainWindow::onClearButtonClicked);
  connect(ui->submitButton, &QPushButton::clicked, this,
          &MainWindow::onSubmitButtonClicked);
  ui->clearButton->setStatusTip(
      tr("clear all the scores and countries selected"));
  ui->submitButton->setStatusTip(tr("submit the scores"));

  // init country box
  initCountryComboBox(ui->countryComboBox1);
  initCountryComboBox(ui->countryComboBox2);
  initCountryComboBox(ui->countryComboBox3);
  initCountryComboBox(ui->countryComboBox4);
  initCountryComboBox(ui->countryComboBox5);
  // init lineEdit
  initScoreLineEdit(ui->countryScoreLineEdit1);
  initScoreLineEdit(ui->countryScoreLineEdit2);
  initScoreLineEdit(ui->countryScoreLineEdit3);
  initScoreLineEdit(ui->countryScoreLineEdit4);
  initScoreLineEdit(ui->countryScoreLineEdit5);
}
