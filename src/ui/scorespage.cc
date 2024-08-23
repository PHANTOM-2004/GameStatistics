#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <QMessageBox>

void MainWindow::initCountryCombo(QComboBox *combo) {
  Q_ASSERT(combo == ui->countryComboBox1 || combo == ui->countryComboBox2 ||
           combo == ui->countryComboBox3 || combo == ui->countryComboBox4 ||
           combo == ui->countryComboBox5);

  auto countries = statistic.country_data();
  int const cnt = statistic.country_count();

  Q_ASSERT(cnt > 1);

  for (int i = 0; i < cnt; i++)
    combo->addItem(QString::asprintf("[%2d] ", i + 1) + countries[i].name());

  combo->setCurrentIndex(-1);
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
  connect(ui->submitButton, &QPushButton::clicked, this,
          &MainWindow::onSubmitButtonClicked);

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

  // set index to -1
  // resetCountryCombo();
  // clearScoreInput();

  // hide the extra two input widget
  if (statistic.sport_data()[index].sport_type() == dsa::SCORE_TOP3) {
    ui->scoreLabel4->hide();
    ui->scoreLabel5->hide();

    ui->countryComboBox4->hide();
    ui->countryComboBox4->setCurrentIndex(-1);
    ui->countryComboBox5->hide();
    ui->countryComboBox5->setCurrentIndex(-1);

    ui->countryScoreLineEdit4->hide();
    ui->countryScoreLineEdit4->clear();
    ui->countryScoreLineEdit5->hide();
    ui->countryScoreLineEdit5->clear();
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

bool MainWindow::scoreInputCheck(QComboBox const *combo, QLineEdit const *line,
                                 int const id) const {
  qDebug() << "[check line edit]" << id;
  QString const &number = line->text();
  qDebug() << "score" << number;
  qDebug() << "country" << combo->currentText();

  if (combo->currentIndex() < 0) {
    // no country selected
    QMessageBox::warning(ui->scoreInputBox, "No country selected",
                         QStringLiteral("You have selected none of the country "
                                        "for score.\n\n Fail at comboBox [%1].")
                             .arg(id));
    return false;
  }

  bool ok = false || (number.length() <= 3 && number.length() >= 1);
  int score = 0;

  if (ok) {
    score = number.toInt(&ok);
    ok = ok && (score >= 0 && score <= 100);
  }

  if (!ok) {

    // raise message box
    QString const msg =
        QStringLiteral(
            "get INVALID score [%1] at line edit [%2]\n\n required:\n"
            "integer score: score >= 0 and score <= 100")
            .arg(line->text())
            .arg(id);

    QMessageBox::warning(ui->scoreInputBox, "Invalid Score", msg);
    return false;
  }

  return true;
}

void MainWindow::onSubmitButtonClicked() {
  qDebug() << "submit the input";

  if (ui->sportsCombo->currentIndex() < 0) {
    QMessageBox::warning(ui->sportsSelectBox, "No sports selected",
                         "You have selected none of the sports.");
    return;
  }

  if (!scoreInputCheck(ui->countryComboBox1, ui->countryScoreLineEdit1, 1))
    return;

  if (!scoreInputCheck(ui->countryComboBox2, ui->countryScoreLineEdit2, 2))
    return;

  if (!scoreInputCheck(ui->countryComboBox3, ui->countryScoreLineEdit3, 3))
    return;

  if (!scoreInputCheck(ui->countryComboBox4, ui->countryScoreLineEdit4, 4))
    return;

  if (!scoreInputCheck(ui->countryComboBox5, ui->countryScoreLineEdit5, 5))
    return;

  dsa::vararray<dsa::country_score> input;
}
