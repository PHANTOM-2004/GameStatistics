/// \file
#pragma once

#include "dsa/vararray.hpp"
#include <qcontainerfwd.h>
#include <qlineedit.h>
#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "dsa/statistic.hpp"
#include <QComboBox>
#include <QMainWindow>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

/// brief the mainwindow
class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  /// \brief trivial constructor
  MainWindow(QWidget *parent = nullptr);
  /// \brief trivial destructor
  ~MainWindow();

private:
  // ==============================================================
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

  // ==============================================================
  /// \brief init the sport display page
  void initSportsPage();

  /// \brief init the sport table in the sport display page
  void initSportTable();

  // ==============================================================
  /// \brief init the score add page
  void initScoresPage();

  /// \brief init the input group box of the score page
  void initScoreInputBox();

  /// \brief init the select group box of the score page
  void initScoreSelectBox();

  /// \brief init the QComboBox of the country in the input group box
  /// \param combo the QComboBox to init
  void initCountryComboBox(QComboBox *combo);

  /// \brief init the QLineEdit of the country in the input group box
  /// \param line the QEditLine to init
  void initScoreLineEdit(QLineEdit *line);

  /// \brief update the input widget, hide the extra input widgets according
  /// to the sport type
  /// \param index the index of the according sport
  void updateSportsInfo(int const index);

  /// \brief update label information of the sport selected
  /// \param index the index of the according sport
  void updateSportsInfoLabel(int const index);

  /// \brief clear all the QLineEdit of the score input group box
  void clearScoreInput();

  /// \brief reset all the QComboBox of the score input group box
  void resetCountryComboBox();

  /// \brief slots when clear button is pressed
  void onClearButtonClicked();

  /// \brief check the score and country the user input
  /// \param combo one of the QComboBox of the input group box
  /// \param line one of the QLineEdit of the input group box
  /// \param id the QComboBox/QLineEdit number
  /// \return return true when the checking is passed
  bool scoreInputCheck(QComboBox const *combo, QLineEdit const *line,
                       int const id) const;

  /// \brief slots when submit button is pressed
  void onSubmitButtonClicked();

  /// \brief the sort type, decides how we rank the different countries
  enum sort_type {
    SORT_BY_MEN_POINTS = 0,
    SORT_BY_WOMEN_POINTS,
    SORT_BY_TOTAL_POINTS,
    SORT_BY_COUNTRY_INDEX,
  };

  // ==============================================================
  // the rank page
  //
  /// \brief init the rank page
  void initRankPage();

  /// \brief struct for updating the rank table in rank page
  struct country_table_item {
    /// \brief name of the country
    QString country_name;
    /// \brief women points of the country
    int women_points;
    /// \brief men points of the country
    int men_points;
    /// \brief index of the country
    int id;
  };

  /// \brief sort the countries according to the given sort type
  /// \param countries the vararray of the country list to be sorted
  /// \param type the type of the sort
  void sortCountry(dsa::vararray<country_table_item> &countries,
                   sort_type const type);

  /// \brief update the rank table;called when the submit button
  /// is pressed
  void updateRankTable();

  // ==============================================================
  void initQueryPage();

  void initQueryTable();

  void updateQueryTable();

  void updateQueryInfo();

  // ==============================================================
  dsa::Statistic const &get_statistic() const { return statistic; }

private:
  /// \brief auto generated ui
  Ui::MainWindow *ui;

  /// \brief record whether the rank has been updated, used as signal
  /// for rank page, if it is true. the rank table will surely be updated
  bool rank_updated = false;

  QStringList rankTableHeaders;

  QStringList queryTableHeaders;

  /// \brief singleton for dsa::Statistic class
  static dsa::Statistic statistic;

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
