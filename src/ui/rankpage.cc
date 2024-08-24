#include "dsa/country.hpp"
#include "dsa/vararray.hpp"
#include "mainwindow.hpp"
#include "ui_mainwindow.h"

using dsa::Country;

void MainWindow::initRankPage() {
  // ui->sortComboBox;
}

void MainWindow::updateRankTable() {}

void MainWindow::sortCountry(dsa::vararray<country_table_item> &countries,
                             sort_type const type) {
  auto cmp_by_men_points = [](country_table_item const &a,
                              country_table_item const &b) {
    if (a.men_points != b.men_points)
      return a.men_points > b.men_points;
    return a.id < b.id;
  };

  auto cmp_by_women_points = [](country_table_item const &a,
                                country_table_item const &b) {
    if (a.women_points != b.women_points)
      return a.women_points > b.women_points;
    return a.id < b.id;
  };

  auto cmp_by_total_points = [](country_table_item const &a,
                                country_table_item const &b) {
    int const pa = a.men_points + a.women_points;
    int const pb = b.men_points + b.women_points;
    if (pa != pb)
      return pa < pb;
    return a.id < b.id;
  };

  Q_ASSERT(countries.size());

  switch (type) {
  case SORT_BY_MEN_POINTS:
    countries.sort(cmp_by_men_points);
    break;

  case SORT_BY_WOMEN_POINTS:
    countries.sort(cmp_by_women_points);
    break;

  case SORT_BY_TOTAL_POINTS:
    countries.sort(cmp_by_total_points);
    break;

  case SORT_BY_COUNTRY_INDEX:
    // no need to compare
    break;
  default:
    Q_ASSERT(0);
  }
}
