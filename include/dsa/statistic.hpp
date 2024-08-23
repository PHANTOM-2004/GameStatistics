/// \file 
/// \brief the definition of the Statistic class
#pragma once

#include "dsa/vararray.hpp"
#ifndef __STATISTIC_CLASS_HPP__
#define __STATISTIC_CLASS_HPP__

#include "dsa/countryscore.hpp"
#include "dsa/sport.hpp"

namespace dsa {
/// \brief the class to process the data 
/// insert/search/sort
/// note: it is a singleton, only exist one copy
///
class Statistic {
public:
  /// \brief constructor
  Statistic();

  /// \brief getter for the count of countries
  /// \return the count of countries
  inline int country_count() const { return _countries_count; }

  /// \brief getter for the count of sport
  /// \return the count of sport
  inline int sport_count() const { return _sports_count; }

  /// \brief getter for the const pointer of sport array
  /// \return the count of sport array
  inline Sport const *sport_data() const { return _SportsList; }

  /// \brief getter for the const pointer of country array
  /// \return the count of country array
  inline CountryScore const *country_data() const { return _CountriesList; }

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
  /// \brief const pointer to the country list
  CountryScore *const _CountriesList;
  /// \brief const pointer to the sport list
  Sport *const _SportsList;
  /// \brief count of the countries;
  int const _countries_count;
  /// \brief count of the sports;
  int const _sports_count;
};

}; // namespace dsa
#endif // !__STATISTIC_CLASS_HPP__
