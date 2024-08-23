#pragma once

#include "dsa/vararray.hpp"
#ifndef __STATISTIC_CLASS_HPP__
#define __STATISTIC_CLASS_HPP__

#include "dsa/countryscore.hpp"
#include "dsa/sport.hpp"

namespace dsa {

class Statistic {
public:
  Statistic();

  inline int country_count() const { return _countries_count; }

  inline int sport_count() const { return _sports_count; }

  inline Sport const *sport_data() const { return _SportsList; }

  inline CountryScore const *country_data() const { return _CountriesList; }

  int get_sport_index(QString const &name) const;

  int get_country_index(QString const &name) const;

  bool insert_scores(int const sport_index, vararray<country_score> &input);

private:
  CountryScore *const _CountriesList;
  Sport *const _SportsList;
  int const _countries_count;
  int const _sports_count;
};

}; // namespace dsa
#endif // !__STATISTIC_CLASS_HPP__
