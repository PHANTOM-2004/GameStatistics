#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <qcombobox.h>

void MainWindow::initCountryCombo(QComboBox *combo) {
  Q_ASSERT(combo == ui->countryComboBox1 || combo == ui->countryComboBox2 ||
           combo == ui->countryComboBox3 || combo == ui->countryComboBox4 ||
           combo == ui->countryComboBox5);

  auto countries = statistic.country_data();
  int const cnt = statistic.country_count();

  Q_ASSERT(cnt > 1);

  for (int i = 0; i < cnt; i++)
    combo->addItem(QString::asprintf("[%2d] ", i + 1) + countries[i].name());
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
  ui->sportsCombo->setMaxVisibleItems(cnt);
  ui->sportsCombo->setCurrentIndex(-1);
  ui->sportsGenderLabel->setText("men/women");
  ui->sportsTypeLabel->setText("score top 3/5");

  connect(ui->sportsCombo, &QComboBox::currentIndexChanged, this,
          &MainWindow::updateSportsInfo);
}

void MainWindow::initScoreInputBox() {

  // init the input part
  connect(ui->clearButton, &QPushButton::clicked, this,
          &MainWindow::onClearButtonClicked);

  // init country box

  initCountryCombo(ui->countryComboBox1);
  initCountryCombo(ui->countryComboBox2);
  initCountryCombo(ui->countryComboBox3);
  initCountryCombo(ui->countryComboBox4);
  initCountryCombo(ui->countryComboBox5);
}

void MainWindow::updateSportsInfoLabel(int const index) {
  Q_ASSERT(index >= 0 && index < statistic.sport_count());
  auto const &target = statistic.sport_data()[index];
  ui->sportsGenderLabel->setText(QStringLiteral("Gender: ") +
                                 target.sport_gender_str());
  ui->sportsTypeLabel->setText(QStringLiteral("Score Type: ") +
                               target.sport_type_str());
}

void MainWindow::updateSportsInfo(int const index) {
  Q_ASSERT(index >= 0 && index < statistic.sport_count());

  qDebug() << "sports selected changed" << index;
  updateSportsInfoLabel(index);

  // hide the extra two input widget

  resetCountryCombo();
  if (statistic.sport_data()[index].sport_type() == dsa::SCORE_TOP3) {
    ui->scoreLabel4->hide();
    ui->scoreLabel5->hide();

    ui->countryComboBox4->hide();
    ui->countryComboBox5->hide();

    ui->countryScoreLineEdit4->hide();
    ui->countryScoreLineEdit5->hide();
  } else {
    ui->scoreLabel4->show();
    ui->scoreLabel5->show();

    ui->countryComboBox4->show();
    ui->countryComboBox5->show();

    ui->countryScoreLineEdit4->show();
    ui->countryScoreLineEdit5->show();
  }
}

void MainWindow::resetCountryCombo() {
  ui->countryComboBox1->setCurrentIndex(-1);
  ui->countryComboBox2->setCurrentIndex(-1);
  ui->countryComboBox3->setCurrentIndex(-1);
  ui->countryComboBox4->setCurrentIndex(-1);
  ui->countryComboBox5->setCurrentIndex(-1);
}

void MainWindow::clearScoreInput() {
  ui->countryScoreLineEdit1->clear();
  ui->countryScoreLineEdit2->clear();
  ui->countryScoreLineEdit3->clear();
  ui->countryScoreLineEdit4->clear();
  ui->countryScoreLineEdit5->clear();
}

void MainWindow::onClearButtonClicked() {
  qDebug() << "clear the score input";
  resetCountryCombo();
  clearScoreInput();
}
