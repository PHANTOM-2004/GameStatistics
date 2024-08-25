#include "mainwindow.hpp"
#include "QStringLiteral"
#include "ui_mainwindow.h"
#include <qtablewidget.h>

dsa::Statistic MainWindow::statistic = dsa::Statistic{};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  this->setFixedSize(this->size());
  // this->setWindowFlag(this->flags);

  /*---------------------------------------------------------------------------*/
  initSportsPage();

  initScoresPage();

  initRankPage();

  initQueryPage();

  // menuBar
  initMenuBar();
  /*---------------------------------------------------------------------------*/
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::initMenuBar() {
  // software info
  initSoftwareInfo();
  // set build info
  initBuildInfo();

  QMenu *about = menuBar()->addMenu(tr("About"));
  about->addAction(softwareInfoAction);
  about->addAction(buildInfoAction);
}

void MainWindow::showSoftwareInfo() {
  qDebug() << "Show Software";
  softwareInfo->show();
}

void MainWindow::showBuildInfo() {
  qDebug() << "Show Build information";
  qDebug() << COMPILER_VERION;
  qDebug() << GENERATOR;
  qDebug() << CMAKE_VERSION;
  /*
  static QString const info =
      tr("C++ Compiler:\n") + tr(COMPILER_VERION) + "\n\n" + tr("Generator: ")
  + tr(GENERATOR) + "\n\n" + tr("CMake Version: ") + tr(CMAKE_VERSION);
  QMessageBox::information(this, tr("Build Information"), info);
  */
  buildInfo->show();
}

void MainWindow::initSoftwareInfo() {
  static QString const softwareInfoText =
#include "profile.html"
      ;

  softwareInfo = new QMessageBox(this);
  softwareInfo->setWindowTitle(tr("Software Information"));
  softwareInfo->setTextFormat(Qt::RichText); // show as html
  softwareInfo->setText(softwareInfoText);

  softwareInfoAction = new QAction(tr("software information"), this);
  softwareInfoAction->setStatusTip(
      tr("About this software")); // when mouse hover on action
  connect(softwareInfoAction, &QAction::triggered, this,
          &MainWindow::showSoftwareInfo);
}

void MainWindow::initBuildInfo() {
  static QString const newline = "<br>";
  static QString const buildInfoTextFmt =
#include "build.html"
      ;

  static QString const compiler_info =
      QStringLiteral(COMPILER_VERION).replace("\n", newline);
  static QString const generator_info =
      QStringLiteral(GENERATOR).replace("\n", newline);
  static QString const cmake_version = QStringLiteral(CMAKE_VERSION);
  static QString const qt_version = QStringLiteral(QT6_VERSION);

  buildInfo = new QMessageBox(this);
  buildInfo->setWindowTitle(tr("Build Information"));
  buildInfo->setTextFormat(Qt::RichText); // show as html
  buildInfo->setText(buildInfoTextFmt.arg(compiler_info, generator_info,
                                          cmake_version, qt_version));

  buildInfoAction = new QAction(tr("build information"), this);
  buildInfoAction->setStatusTip("Building environment");
  connect(buildInfoAction, &QAction::triggered, this,
          &MainWindow::showBuildInfo);
}

void MainWindow::setTableFormat(QTableWidget *table, int const row,
                                int const col) {
  Q_ASSERT(row > 0 && row <= table->rowCount());
  Q_ASSERT(col > 0 && col <= table->columnCount());

  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      auto item = table->item(i, j);
      item->setTextAlignment(Qt::AlignCenter);
      item->setFlags(item->flags() & ~Qt::ItemIsEditable); // type
    }
  }
}
