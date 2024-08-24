#include "dsa/sport.hpp"
#include "dsa/country.hpp"

namespace dsa {
bool Sport::insert_scored_country(dsa::vararray<country_score> const &input) {
  Q_ASSERT(!_inserted);

  if (_inserted)
    return false;

  Q_ASSERT((sport_type() == SCORE_TOP3 && input.size() == 3) ||
           (sport_type() == SCORE_TOP5 && input.size() == 5));

  countries = input;

  _inserted = true;
  return true;
}

int Sport::get_points(int const rank) const {
  Q_ASSERT(rank >= 1 && rank <= sport_type());

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

#ifdef _DSA_DEBUG
void Sport::show_info(Country const *const CountryList) const {
  qDebug() << "[SPORT DEBUG INFO]";
  qDebug() << "sport:" << sport_name;
  qDebug() << "type:" << sport_type_str();
  qDebug() << "gender:" << sport_gender_str();
  qDebug() << "related country:" << countries.size();

  Q_ASSERT((sport_type() == SCORE_TOP3 && countries.size() == 3) ||
           (sport_type() == SCORE_TOP5 && countries.size() == 5));

  for (int i = 0; i < countries.size(); i++) {
    auto cur = countries[i];
    qDebug() << "country[" << cur.country_index << "]"
             << CountryList[cur.country_index].name() << "score: " << cur.score
             << "rank: " << i + 1;
  }
}
#endif

} // namespace dsa
