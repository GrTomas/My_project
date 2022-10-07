#include "struct.h"
#include "func.h"


double galutinis_pagal_mediana(vector<int> paz) {

    std::sort(paz.begin(), paz.end());
    if (paz.size() % 2 == 0 && paz.size() != 0) {
        return (double)(paz[paz.size() / 2] + paz[(paz.size() - 1) / 2]) / 2.0;
    }
    if (paz.size() <= 0) {
        return 0;
    }
    else {
        if (paz.size() == 1) {
            return (double)paz[0];
        }
        else {
            return (double)paz[paz.size() / 2];
        }
    }
}

void isvedimas(vector <duom> stud, string pasirinkimas) {

    cout << std::left << std::setw(20) << "Vardas" << std::left << std::setw(20) << "Pavarde";
    cout << std::right << std::setw(5) << "Galutinis (";
    if (pasirinkimas == "v" || pasirinkimas == "V") {
        cout << "vid.)" << endl;
    }
    else {
        cout << "med.)" << endl;
    }
    cout << "--------------------------------------------------------------" << endl;
    for (int z = 0; z < stud.size(); z++) {
        cout << std::left << std::setw(20) << stud[z].vardas << std::left << std::setw(20) << stud[z].pavarde;
        cout << std::right << std::fixed << std::setprecision(2) << std::setw(5) << stud[z].galutinis << endl;
    }
}

bool palyginimas(const duom& a, const duom& b) {
    return a.vardas < b.vardas;
}
void isvedimas_is_failo(vector<duom> stud) {
    std::sort(stud.begin(), stud.end(), palyginimas);

    std::ofstream rezultatai;
    rezultatai.open("rezultatai.txt", std::ios::out);
    if (rezultatai.fail()) {
        cout << "Failas nebuvo sukurtas";
    }
    else {
        rezultatai << std::left << std::setw(20) << "Vardas" << std::left << std::setw(20) << "Pavarde";
        rezultatai << std::left << std::setw(20) << "Galutinis (vid.)" << std::left << std::setw(20) << "Galutinis (med.)" << endl;
        rezultatai << "----------------------------------------------------------------------------------" << endl;
        for (int i = 0; i < stud.size(); i++) {
            rezultatai << std::left << std::setw(20) << stud[i].vardas;
            rezultatai << std::left << std::setw(20) << stud[i].pavarde;
            rezultatai << std::left << std::fixed << std::setprecision(2) << std::setw(20) << stud[i].galutinis;
            rezultatai << std::left << std::fixed << std::setprecision(2) << std::setw(20) << stud[i].galutinis_papildomas << endl;
        }
        rezultatai.close();
    }

}