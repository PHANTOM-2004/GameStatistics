#pragma once

#ifndef __SPORT_CLASS_HPP__
#define __SPORT_CLASS_HPP__
#include "dsa/vararray.hpp"
#include <QString>
#include <compare>

namespace dsa {

enum SPORT_TYPE { SCORE_TOP3 = 3, SCORE_TOP5 = 5 };
enum SPORT_GENDER { WOMEN, MEN };

struct country_score {
  int country_index;
  int score;

  auto operator<=>(country_score const &other) const {
    // assume the score higher one at smaller index
    if (score > other.score)
      return std::strong_ordering::less;
    else if (score < other.score)
      return std::strong_ordering::greater;
    else
      return std::strong_ordering::equal;
  }
};

class Sport {

public:
  Sport(QString const &sport_name, SPORT_TYPE const type,
        SPORT_GENDER const gender = MEN);

  bool insert_scored_country(dsa::vararray<country_score> const &input);

  int country_scored_count() const { return countries.size(); }

  QString const &name() const { return sport_name; }
  SPORT_TYPE const sport_type() const { return type; }
  SPORT_GENDER const sport_gender() const { return gender; }

  int get_points(int const rank) const;

private:
  QString const sport_name;
  SPORT_TYPE const type;
  SPORT_GENDER const gender;
  dsa::vararray<country_score> countries;

  static constexpr int top5_points[5] = {7, 5, 3, 2, 1};
  static constexpr int top3_points[3] = {5, 3, 2};
};

} // namespace dsa

#endif
