#pragma once
#include <iostream>
#include <string>
#include <cstdio>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <fstream>
#include <chrono>
#include <sstream>
#include <random>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::ifstream;

duom ivedimas(int a);
bool palyginimas(const duom& a, const duom& b);
duom duomenu_issaugojimas(string eilute);
double galutinis_pagal_vidurki(vector<int> paz);
double galutinis_pagal_mediana(vector<int> paz);
void isvedimas(vector <duom> stud, string pasirinkimas);
void isvedimas_is_failo(vector<duom> stud);
