
#pragma once
#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QMessageBox>
#include "dsa/statistic.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private:
  /// \brief initialize the memu bar, call once in constructor
  void initMenuBar();
  /// \brief initialize the build information in menu
  void initBuildInfo();
  /// \brief initialize the software information in menu
  void initSoftwareInfo();
  /// \brief show the software information when clicked
  void showSoftwareInfo();
  /// \brief show the build information when clicked
  void showBuildInfo();

  void initSportsPage();

  void initSportTable();

  void on_sports_submit_button_clicked();

private:
  Ui::MainWindow *ui;

  dsa::Statistic statistic;

  /// \brief action when clicked the software information in menu
  QAction *softwareInfoAction;
  /// \brief action when clicked the build information in menu
  QAction *buildInfoAction;
  /// \brief messagebox to show for build information
  QMessageBox *buildInfo;
  /// \brief messagebox to show for software information
  QMessageBox *softwareInfo;
};
#endif // MAINWINDOW_HPP
