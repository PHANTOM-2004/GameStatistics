#include "dsa/country.hpp"
#include "dsa/sport.hpp"

namespace dsa {

Country::Country(QString const &country_name) : country_name(country_name) {}

bool Country::insert_sport(Sport *const SportList, int const sport_index,
                           int const rank, int const score) {
  // Q_ASSERT(sport_index >= 0 && sport_index < SIZEOF_ARRAY(SportList));
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

void Country::show_info(Sport const *const SportList) const {
  qDebug() << "[COUNTRY DEBUG INFO]";
  qDebug() << "country: " << name();
  qDebug() << "women points: " << women_points_count;
  qDebug() << "men points: " << men_points_count;
  qDebug() << "sports involved below:";

  qDebug() << "{";
  for (int i = 0; i < sports.size(); i++) {
    int const sport_index = sports[i].sport_index;
    int const score = sports[i].score;
    int const rank = sports[i].rank;
    qDebug() << "[" << i << "]" << SportList[sport_index].name()
             << " score:" << score << " rank:" << rank;
  }
  qDebug() << "}";
}

} // namespace dsa
