#pragma once
#include <fstream>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <random>
#include <sstream>
#include <chrono>
#include <string>
#include <list>

using std::string;
using std::ifstream;
using std::list;
using std::cout;
using std::endl;
using std::setw;
using std::left;

duom duomenu_issaugojimas_list(string eilute);
void isvedimai_auto_failams_list (list<duom> failai, string pavadinimas);
void darbas_su_auto_failu_list (string pav, int kiek);