#include "dsa/country.hpp"
#include "dsa/vararray.hpp"
#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <algorithm>

using dsa::Country;

void MainWindow::sortCountry(dsa::vararray<dsa::Country> &countries,
                             sort_type const type) {
  static auto cmp_by_men_points = [](Country const &a, Country const &b) {
    return a.get_men_points() > b.get_men_points();
  };

  static auto cmp_by_women_points = [](Country const &a, Country const &b) {
    return a.get_women_points() > b.get_women_points();
  };

  static auto cmp_by_total_points = [](Country const &a, Country const &b) {
    return a.get_total_points() > b.get_total_points();
  };

  Q_ASSERT(countries.size());

  switch (type) {

  case SORT_BY_MEN_POINTS:
    std::stable_sort(countries.begin_pointer(), countries.end_pointer(),
                     cmp_by_men_points);
    break;

  case SORT_BY_WOMEN_POINTS:
    std::stable_sort(countries.begin_pointer(), countries.end_pointer(),
                     cmp_by_women_points);
    break;

  case SORT_BY_TOTAL_POINTS:
    std::stable_sort(countries.begin_pointer(), countries.end_pointer(),
                     cmp_by_total_points);
    break;

  case SORT_BY_COUNTRY_INDEX:
    // no need to compare
    break;
  default:
    Q_ASSERT(0);
  }
}
