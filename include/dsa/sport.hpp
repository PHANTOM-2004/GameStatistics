/// \file
/// \brief the definition of the sport class
#pragma once

#ifndef __SPORT_CLASS_HPP__
#define __SPORT_CLASS_HPP__
#include "dsa/vararray.hpp"
#include "macro.hpp"
#include <QString>
#include <compare>

namespace dsa {

/// \brief record the sport score type,
/// the top 3 get the points or the top 5 get the points
enum SPORT_TYPE { SCORE_TOP3 = 3, SCORE_TOP5 = 5 };
/// \brief record the sport gender type
/// men sports or women sports
enum SPORT_GENDER { WOMEN, MEN };

/// \brief the struct is designed to record the country that
/// win points in the sport
struct country_score {
  /// \brief the index of the country array
  int country_index;
  /// \brief the score the country gets
  int score;

  /// \brief operator for comparsion(C++20)
  /// \param other trivial
  /// \return trivial(C++20)
  auto operator<=>(country_score const &other) const {
    // assume the score higher one at smaller index
    if (score > other.score)
      return std::strong_ordering::less;
    else if (score < other.score)
      return std::strong_ordering::greater;
    else
      return std::strong_ordering::equal;
  }

  /// \brief operator<, used for descending order in sort
  /// \param other trivial
  /// \return return true when score > other.score
  bool operator<(country_score const &other) const {
    return score > other.score;
  }

  /// \brief operator==, equal in score field
  /// \param other trivial
  /// \return return true when score == other.score
  bool operator==(country_score const &other) const {
    return score == other.score;
  }
};

class Country;

/// \brief the class to store the sport information
class Sport {

public:
  /// \brief constructor
  /// \param sport_name the name of the sport
  /// \param type the score type of the sport
  /// \param gender the gender type of the sport(default men sports)
  Sport(QString const &sport_name, SPORT_TYPE const type,
        SPORT_GENDER const gender = MEN);

  /// \brief insert scored countris into the sport
  /// \param input the list of the countries to insert
  /// \return currently unused, return true
  bool insert_scored_country(dsa::vararray<country_score> const &input);

  /// \brief getter for the count of the country involved
  /// \return the count of the country involved
  int country_scored_count() const { return countries.size(); }

  ///  \brief getter for the name of the sport
  ///  \return the name of the sport
  QString const &name() const { return sport_name; }

  ///  \brief getter for the sport score type of the sport
  ///  \return sport score type of the sport
  SPORT_TYPE const sport_type() const { return type; }

  ///  \brief getter for the sport gender of the sport
  ///  \return the sport gender of the sport
  SPORT_GENDER const sport_gender() const { return gender; }

  ///  \brief QString getter for the sport score type of the sport
  ///  \return sport score type of the sport(QString)
  QString sport_type_str() const {
    return type == SCORE_TOP5 ? QStringLiteral("score top 5")
                              : QStringLiteral("score top 3");
  }

  ///  \brief QString getter for the sport gender of the sport
  ///  \return the sport gender of the sport(QString)
  QString sport_gender_str() const {
    return gender == WOMEN ? QStringLiteral("women") : QStringLiteral("men");
  }

  /// \brief get the points of the rank
  /// \return the points according to the rank of the sport
  int get_points(int const rank) const;

  vararray<country_score> const &get_scored_countries() const {
    return countries;
  }

  /// \brief check if the score of this sport has already been input
  /// \return return true when the score has already been input
  bool inserted() const {
    Q_ASSERT((_inserted && countries.size()) ||
             (!_inserted && countries.empty()));
    return _inserted;
  };

#ifdef _DSA_DEBUG
  /// \brief function for debug , display the information(including all fields)
  /// of this class , readonly
  /// \param CountryList pointer to the country array
  void show_info(Country const *const CountryList) const; // for debug
#endif

private:
  /// \brief the name of the sport
  QString const sport_name;

  /// \brief the score type of the sport
  SPORT_TYPE const type;

  /// \brief the gender type of the sport
  SPORT_GENDER const gender;

  /// \brief the countries that win points in the sport
  dsa::vararray<country_score> countries;

  /// \brief record if the score of this sport has already been input
  bool _inserted = false;

  /// \brief the score rules for top 5 score type
  /// rank i got top5_points[i] points
  static constexpr int top5_points[5] = {7, 5, 3, 2, 1};

  /// \brief the score rules for top 3 score type
  /// rank i got top3_points[i] points
  static constexpr int top3_points[3] = {5, 3, 2};
};

} // namespace dsa

#endif
