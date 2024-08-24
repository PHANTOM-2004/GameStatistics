/// \file
/// \brief definition of countryscore type
#pragma once

#ifndef __COUNTRY_CLASS_HPP__
#define __COUNTRY_CLASS_HPP__
#include "dsa/vararray.hpp"
#include "macro.hpp"
#include <QString>
namespace dsa {

class Sport;
/// \brief this class store the country information
/// along with the sports in which the country win scores
/// also, it records the total points of both men sports and women sports
/// and trivial the total points
class Country {

public:
  /// \brief constructor
  /// \param country_name the name of the country
  Country(QString const &country_name);

  /// \brief getter of the total points, readonly
  /// \return the total points the country gets
  int get_total_points() const {
    return women_points_count + men_points_count;
  };

  int get_men_points() const { return men_points_count; }

  int get_women_points() const { return women_points_count; }

  /// \brief insert a kind of sport to the country
  /// \param sport_index the sport id in the sport array
  /// \param rank the rank the country got
  /// \param score the score the country got
  bool insert_sport(Sport *const SportList, int const sport_index,
                    int const rank, int const score);

  /// \brief getter of the country name, readonly
  /// \return  the name of the country
  QString const &name() const { return country_name; }

#ifdef _DSA_DEBUG
  void show_info(Sport const *const SportList) const; // for debug
#endif

private:
  /// \brief the struct records the sports in
  /// which the country wins points
  struct sport_score {
    /// \brief the index of the sport array
    int sport_index;
    /// \brief the score the country gets
    int score;
    /// \brief the rank the country gets
    int rank;

    /// \brief operator< for comparison
    /// the one withe higher score will be stored at
    /// smaller index
    /// \param other the one to compare with
    /// \return trivial
    bool operator<(sport_score const &other) const {
      if (sport_index != other.sport_index)
        return sport_index < other.sport_index;
      // the higher score at smaller index
      return score > other.score;
    }
  };

  /// \brief the name of the country
  QString const country_name;
  /// \brief the total points of the women sports
  int women_points_count = 0;
  /// \brief the total points of the men sports
  int men_points_count = 0;
  /// \brief the sports the country win points in
  vararray<sport_score> sports;
};

} // namespace dsa

#endif
