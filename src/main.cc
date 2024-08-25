/// \file main.cc
/// \brief The entry of the program
///
///

/*!  
 \mainpage My Project's Main Page  
 
 \section intro_sec Introduction  
 This is a project for managing scores and rank
 of countries and sports in Olympic Games,base on Qt6.
 
 \section env_sec Environment
 I tested and build it on archlinux(202408) and Debian12(bookworm).
 build(on archlinux) with:<br> 
`clang++ version 18.1.8`<br>
`cmake version 3.30.2`<br>
`ninja version 1.12.1`<br>
`qt6   version 6.7.2`<br>
*/

#include "mainwindow.hpp"

#include <QApplication>

int
main (int argc, char *argv[])
{
  QApplication a (argc, argv);
  MainWindow w;
  w.show ();
  return a.exec ();
}
