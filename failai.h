#pragma once
#include <fstream>
#include <iostream>
#include <iomanip>
#include <random>
#include <sstream>
#include <chrono>

using std::string;
using std::cout;
using std::endl;
using std::setw;
using std::left;


void failo_kurimas(string pav, int kiekis, int nd_sk);
void isvedimai_auto_failams(vector<duom> stud);
void darbas_su_auto_failu(string pav, int kiek);