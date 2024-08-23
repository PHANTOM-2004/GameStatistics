#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <qcombobox.h>
#include <qstringliteral.h>

void MainWindow::initScoresPage() {
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
  // ui->sportsGenderLabel->setText("men/women");
  // ui->sportsTypeLabel->setText("score top 3/5");

  connect(ui->sportsCombo, &QComboBox::currentIndexChanged, this,
          &MainWindow::updateSportsInfo);

  updateSportsInfoLabel(0);
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
}
