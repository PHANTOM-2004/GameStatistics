#include "dsa/statistic.hpp"
#include "dsa/countryscore.hpp"
#include "dsa/sport.hpp"
#include "dsa/vararray.hpp"
#include <qdebug.h>

namespace dsa {

#define SIZEOF_ARRAY(arr) (sizeof(arr) / sizeof(arr[0]))

static CountryScore CountryList[] = {
#include "country.list"
};

static Sport SportList[] = {
#include "sport.list"
};

// =========================================================================
//
bool Sport::insert_scored_country(dsa::vararray<country_score> const &input) {

  Q_ASSERT((sport_type() == SCORE_TOP3 && input.size() == 3) ||
           (sport_type() == SCORE_TOP5 && input.size() == 5));

  countries = input;
  return true;
}

int Sport::get_points(int const rank) const {
  Q_ASSERT(rank >= 0 && rank < sport_type());

  if (sport_type() == SCORE_TOP3) {
    return top3_points[rank];
  } else if (sport_type() == SCORE_TOP5) {
    return top5_points[rank];
  } else {
    Q_ASSERT(0);
  }
  return -1;
}

Sport::Sport(QString const &sport_name, SPORT_TYPE const type,
             SPORT_GENDER const gender)
    : sport_name(sport_name), type(type), gender(gender) {}

// =========================================================================
//
CountryScore::CountryScore(QString const &country_name)
    : country_name(country_name) {}

bool CountryScore::insert_sport(int const sport_index, int const rank,
                                int const score) {
  Q_ASSERT(sport_index >= 0 && sport_index < SIZEOF_ARRAY(SportList));

  // insert by index, same index order by score
  sport_score const target = {sport_index, score, rank};

  if (sports.empty()) {
    sports.push_back(target);
    return true;
  }

  auto const pos =
      std::lower_bound(sports.begin_pointer(), sports.end_pointer(), target);
  int const i = pos - sports.begin_pointer();

  sports.insert(i, target);

  // now we count the points
  auto const gender = SportList[sport_index].sport_gender();
  int const points = SportList[sport_index].get_points(rank);

  if (gender == WOMEN)
    this->women_points_count += points;
  else
    this->men_points_count += points;

  return true;
}

// =========================================================================

Statistic::Statistic()
    : _CountriesList(CountryList), _SportsList(SportList),
      _countries_count(SIZEOF_ARRAY(CountryList)),
      _sports_count(SIZEOF_ARRAY(SportList)) {}

int Statistic::get_sport_index(QString const &name) const {
  for (int i = 0; i < sport_count(); i++) {
    if (_SportsList[i].name() == name) {
      return i;
    }
  }
  qDebug() << "sport name " << name << "not found";
  Q_ASSERT(0);
  return -1;
}

int Statistic::get_country_index(QString const &name) const {
  for (int i = 0; i < country_count(); i++)
    if (_CountriesList[i].name() == name)
      return i;

  qDebug() << "country name " << name << "not found";
  Q_ASSERT(0);
  return -1;
}

bool Statistic::insert_scores(int const sport_index,
                              dsa::vararray<country_score> &input) {

  Q_ASSERT(sport_index >= 0 && sport_index < sport_count());

  // insert into sport first so that we get the rank
  Q_ASSERT(input.size() == 3 || input.size() == 5);
  std::sort(input.begin_pointer(), input.end_pointer());
  _SportsList[sport_index].insert_scored_country(input);

  // the insert into the country

  // now sorted
  for (int i = 0, last = -1, rank = 0; i < input.size(); i++) {
    auto const &cur = input[i];
    if (last != cur.score) {
      last = cur.score;
      rank++;
    }
    Q_ASSERT(cur.country_index >= 0 && cur.country_index < country_count());

    _CountriesList[cur.country_index].insert_sport(sport_index, rank,
                                                   cur.score);
  }

  return true;
}

QString const &Statistic::get_country_name(int const index) const {
  Q_ASSERT(index >= 0 && index < country_count());
  return _CountriesList[index].name();
}

QString const &Statistic::get_sport_name(int const index) const {
  Q_ASSERT(index >= 0 && index < sport_count());
  return _SportsList[index].name();
}

} // namespace dsa
