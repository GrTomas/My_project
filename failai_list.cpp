#include "struct.h"
#include "failai_list.h"
#include "func.h"

duom duomenu_issaugojimas_list(string eilute) {
    duom asmuo;
    list<string> v;
    std::stringstream ss(eilute);
    string temp;
    while (ss >> temp) {
        v.push_back(temp);
    }
    asmuo.vardas = v.front();
    v.pop_front();
    asmuo.pavarde = v.front();
    v.pop_front();
    asmuo.egz = stoi(v.back());
    v.pop_back();
    for (list<string>::iterator it = v.begin(); it != v.end(); ++it) {
        asmuo.paz.push_back(stoi(*it));
    }
    v.clear();
    return asmuo;
}

void isvedimai_auto_failams_list(list<duom> failai, string pavadinimas) {
    std::ofstream rezultatai;
    rezultatai.open(pavadinimas, std::ios::out);
    if (rezultatai.fail()) {
        cout << "Failas nebuvo sukurtas";
    }
    else {
        rezultatai << std::left << std::setw(20) << "Vardas" << std::left << std::setw(20) << "Pavarde";
        rezultatai << std::left << std::setw(20) << "Galutinis (vid.)" << std::left << std::setw(20) << "Galutinis (med.)" << endl;
        rezultatai << "----------------------------------------------------------------------------------" << endl;
        for (list<duom>::iterator it = failai.begin(); it != failai.end(); ++it) {
            rezultatai << std::left << std::setw(20) << (*it).vardas;
            rezultatai << std::left << std::setw(20) << (*it).pavarde;
            rezultatai << std::left << std::fixed << std::setprecision(2) << std::setw(20) << (*it).galutinis;
            rezultatai << std::left << std::fixed << std::setprecision(2) << std::setw(20) << (*it).galutinis_papildomas << endl;
        }
        rezultatai.close();
    }

}

void darbas_su_auto_failu_list(string pav, int kiek) {

    list<duom> stud;
    duom studentas;
    ifstream failas;
    failas.open(pav);
    auto start = std::chrono::high_resolution_clock::now(); auto st = start;
    auto start1 = std::chrono::high_resolution_clock::now(); auto st1 = start1;

    if (failas.is_open()) {
        string eilute;
        std::getline(failas, eilute);
        while (failas) {
            std::getline(failas, eilute);
            studentas = duomenu_issaugojimas_list(eilute);
            studentas.galutinis = galutinis_pagal_vidurki(studentas.paz) * 0.4 + studentas.egz * 0.6;
            studentas.galutinis_papildomas = galutinis_pagal_mediana(studentas.paz) * 0.4 + studentas.egz * 0.6;
            stud.push_back(studentas);
        }
    }
    auto end1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff1 = end1 - start1;
    cout << "Failo is " << kiek << " irasu nuskaitymo laikas naudojant list: " << diff1.count() << endl;

    auto start2 = std::chrono::high_resolution_clock::now(); auto st2 = start2;
    list<duom> pirmieji;
    list<duom> antrieji;
    for (list<duom>::iterator it = stud.begin(); it != stud.end(); ++it) {
        if ((*it).galutinis >= 5) {
            pirmieji.push_back((*it));
        }
        else {
            antrieji.push_back(*it);
        }
    }
    stud.clear();
    auto end2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff2 = end2 - start2;
    cout << kiek << " irasu suskirstymo i grupes laikas naudojant list: " << diff2.count() << endl;

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    cout << kiek << " irasu darbo bendras laikas naudojant list: " << diff.count() << endl;

    failas.close();

    std::stringstream pavad;
    pavad << "galvociai" << kiek << "list.txt";
    isvedimai_auto_failams_list(pirmieji, pavad.str());
    pirmieji.clear();
    std::stringstream pavadin;
    pavadin << "nuskriaustukai" << kiek << "list.txt";
    isvedimai_auto_failams_list(antrieji, pavadin.str());
    antrieji.clear();
    cout << endl;


}