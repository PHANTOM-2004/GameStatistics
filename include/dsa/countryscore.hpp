#pragma once

#ifndef __COUNTRY_CLASS_HPP__
#define __COUNTRY_CLASS_HPP__
#include "dsa/vararray.hpp"
#include <QString>
namespace dsa {

class CountryScore {

public:
  CountryScore(QString const &country_name);

  int get_total_points() const {
    return women_points_count + men_points_count;
  };

  bool insert_sport(int const sport_index, int const rank, int const score);

  QString const &name() const { return country_name; }

private:
  struct sport_score {
    int sport_index;
    int score;
    int rank;

    bool operator<(sport_score const &other) const {
      if (sport_index != other.sport_index)
        return sport_index < other.sport_index;
      // the higher score at smaller index
      return score > other.score;
    }
  };

  QString const country_name;
  int women_points_count = 0;
  int men_points_count = 0;
  vararray<sport_score> sports;
};

} // namespace dsa

#endif
