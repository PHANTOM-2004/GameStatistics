#include "dsa/statistic.hpp"
#include "dsa/country.hpp"
#include "macro.hpp"

namespace dsa {

namespace data {
static Country CountryList[] = {
#include "country.list"
};

static Sport SportList[] = {
#include "sport.list"
};
} // namespace data

Country *const Statistic::CountryList = data::CountryList;
Sport *const Statistic::SportList = data::SportList;

int const Statistic::_countries_count = SIZEOF_ARRAY(data::CountryList);
int const Statistic::_sports_count = SIZEOF_ARRAY(data::SportList);

int Statistic::get_sport_index(QString const &name) const {
  for (int i = 0; i < sport_count(); i++) {
    if (SportList[i].name() == name) {
      return i;
    }
  }
  qDebug() << "sport name " << name << "not found";
  Q_ASSERT(0);
  return -1;
}

int Statistic::get_country_index(QString const &name) const {
  for (int i = 0; i < country_count(); i++)
    if (CountryList[i].name() == name)
      return i;

  qDebug() << "country name " << name << "not found";
  Q_ASSERT(0);
  return -1;
}

Country &Statistic::country(int const index) {
  Q_ASSERT(index >= 0 && index < _countries_count);
  return CountryList[index];
}

Sport &Statistic::sport(int const index) {
  Q_ASSERT(index >= 0 && index < _sports_count);
  return SportList[index];
}

bool Statistic::insert_scores(int const sport_index,
                              dsa::vararray<country_score> &input) {

  Q_ASSERT(sport_index >= 0 && sport_index < sport_count());

  // insert into sport first so that we get the rank
  Q_ASSERT(input.size() == 3 || input.size() == 5);
  std::sort(input.begin_pointer(), input.end_pointer());
  sport(sport_index).insert_scored_country(input);

  // the insert into the country

  // now sorted
  for (int i = 0, last = -1, rank = 0; i < input.size(); i++) {
    auto const &cur = input[i];
    if (last != cur.score) {
      last = cur.score;
      rank++;
    }
    Q_ASSERT(cur.country_index >= 0 && cur.country_index < country_count());

    country(cur.country_index)
        .insert_sport(SportList, sport_index, rank, cur.score);
  }

  // show some debug information
  sport(sport_index).show_info(CountryList);

  return true;
}

QString const &Statistic::get_country_name(int const index) const {
  Q_ASSERT(index >= 0 && index < country_count());
  return CountryList[index].name();
}

QString const &Statistic::get_sport_name(int const index) const {
  Q_ASSERT(index >= 0 && index < sport_count());
  return SportList[index].name();
}

} // namespace dsa
