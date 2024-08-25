#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <QMessageBox>

void MainWindow::updateSportsInfoLabel(int const index) {
  Q_ASSERT(index >= 0 && index < statistic.sport_count());
  auto const &target = get_statistic().sport(index);
  ui->sportsGenderLabel->setText(tr("Gender: ") + target.sport_gender_str());
  ui->sportsTypeLabel->setText(tr("Score Type: ") + target.sport_type_str());
}

void MainWindow::updateSportsInfo(int const index) {
  Q_ASSERT(index >= 0 && index < statistic.sport_count());

  qDebug() << "sports selected changed" << index;
  updateSportsInfoLabel(index);
  clearScoreInput();
  resetCountryComboBox();

  // set index to -1
  // resetCountryCombo();
  // clearScoreInput();

  // hide the extra two input widget
  if (get_statistic().sport(index).sport_type() == dsa::SCORE_TOP3) {
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

void MainWindow::resetCountryComboBox() {
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
  resetCountryComboBox();
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
    QMessageBox::warning(ui->scoreInputBox, tr("No country selected"),
                         tr("You have selected none of the country "
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
        tr("get INVALID score [%1] at line edit [%2]\n\n required:\n"
           "integer score: score >= 0 and score <= 100")
            .arg(line->text())
            .arg(id);

    QMessageBox::warning(ui->scoreInputBox, tr("Invalid Score"), msg);
    return false;
  }

  return true;
}

void MainWindow::onSubmitButtonClicked() {
  qDebug() << "submit the input";

  if (ui->sportsCombo->currentIndex() < 0) {
    QMessageBox::warning(ui->sportsSelectBox, tr("No sports selected"),
                         tr("You have selected none of the sports."));
    return;
  }

  if (!scoreInputCheck(ui->countryComboBox1, ui->countryScoreLineEdit1, 1))
    return;

  if (!scoreInputCheck(ui->countryComboBox2, ui->countryScoreLineEdit2, 2))
    return;

  if (!scoreInputCheck(ui->countryComboBox3, ui->countryScoreLineEdit3, 3))
    return;

  bool const top5_type =
      get_statistic().sport(ui->sportsCombo->currentIndex()).sport_type() ==
      dsa::SCORE_TOP5;

  if (top5_type &&
      !scoreInputCheck(ui->countryComboBox4, ui->countryScoreLineEdit4, 4))
    return;

  if (top5_type &&
      !scoreInputCheck(ui->countryComboBox5, ui->countryScoreLineEdit5, 5))
    return;

  dsa::vararray<dsa::country_score> input;

  input.push_back({ui->countryComboBox1->currentIndex(),
                   ui->countryScoreLineEdit1->text().toInt()});

  input.push_back({ui->countryComboBox2->currentIndex(),
                   ui->countryScoreLineEdit2->text().toInt()});

  input.push_back({ui->countryComboBox3->currentIndex(),
                   ui->countryScoreLineEdit3->text().toInt()});

  if (top5_type) {
    input.push_back({ui->countryComboBox4->currentIndex(),
                     ui->countryScoreLineEdit4->text().toInt()});

    input.push_back({ui->countryComboBox5->currentIndex(),
                     ui->countryScoreLineEdit5->text().toInt()});
  }

#ifdef _DSA_DEBUG
  qDebug() << "sports: " << ui->sportsCombo->currentText();
  for (int i = 0; i < input.size(); i++) {
    qDebug() << "country: " << input[i].country_index
             << "score: " << input[i].score;
  }
#endif

  bool ret = statistic.insert_scores(ui->sportsCombo->currentIndex(), input);

  if (!ret) {
    qDebug() << "already inserted";
    QMessageBox::warning(ui->sportsSelectBox, tr("Duplicate Scores"),
                         tr("You have already input scores of the sport:\n %1.")
                             .arg(ui->sportsCombo->currentText()));
    return;
  }

  rank_updated = true;
}
