#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "QStringLiteral"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  /*---------------------------------------------------------------------------*/
  initSportsPage();
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
