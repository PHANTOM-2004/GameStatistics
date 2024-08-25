/// \file
/// \brief the definition of the Statistic class
#pragma once

#include "dsa/vararray.hpp"
#ifndef __STATISTIC_CLASS_HPP__
#define __STATISTIC_CLASS_HPP__

#include "dsa/country.hpp"
#include "dsa/sport.hpp"

namespace dsa {
/// \brief the class to process the data
/// insert/search/sort
/// note: it is a singleton, only exist one copy
///
class Statistic {
public:
  /// \brief constructor
  Statistic() = default;

  /// \brief getter for the count of countries
  /// \return the count of countries
  int country_count() const { return _countries_count; }

  /// \brief getter for the count of sport
  /// \return the count of sport
  int sport_count() const { return _sports_count; }

  /// \brief getter for the const pointer of sport array
  /// \return the count of sport array
  Sport const *sport_data() const { return SportList; }

  Sport const &sport(int const index) const {
    Q_ASSERT(index >= 0 && index < sport_count());
    return SportList[index];
  }

  /// \brief getter for the const pointer of country array
  /// \return the count of country array
  Country const *country_data() const { return CountryList; }

  Country const &country(int const index) const {
    Q_ASSERT(index >= 0 && index < country_count());
    return CountryList[index];
  }

  /// \brief getter for the index of the name
  /// \param name the name of the sport to get
  /// \return the index of the sport name
  int get_sport_index(QString const &name) const;

  /// \brief getter for the index of the name
  /// \param name the name of the country to get
  /// \return the index of the country name
  int get_country_index(QString const &name) const;

  /// \brief getter for the name of country array at index
  /// \brief the index of the country
  /// \return the name of the sport
  QString const &get_country_name(int const index) const;

  /// \brief getter for the name of sport array at index
  /// \brief the index of the sport
  /// \return the name of the sport
  QString const &get_sport_name(int const index) const;

  /// \brief insert scores into the countries and sports
  /// we have two copy of the countries and sports for faster search
  /// \param sport_index the index of the sport
  /// \param input contains countries's {id, score,rank}
  /// \return unused return true
  bool insert_scores(int const sport_index, vararray<country_score> &input);

private:
  /// \brief getter for the reference of country at index
  /// \param index the index of the country in the country list
  /// \return the reference of the country at index
  Country &country(int const index);

  /// \brief getter for the reference of sport at index
  /// \param index the index of the sport in the sport list
  /// \return the reference of the sport at index
  Sport &sport(int const index);

  /// \brief const pointer to the country list
  static Country *const CountryList;
  /// \brief const pointer to the sport list
  static Sport *const SportList;
  /// \brief count of the countries;
  static int const _countries_count;
  /// \brief count of the sports;
  static int const _sports_count;
};

}; // namespace dsa
#endif // !__STATISTIC_CLASS_HPP__
