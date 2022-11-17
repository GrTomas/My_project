#include "struct.h"
#include "failai_vector.h"
#include "funkcijos.h"

void failo_kurimas(string pav, int kiekis, int nd_sk) {

    std::ofstream failas;
    failas.open(pav, std::ios::out);

    if (failas.fail()) {
        cout << "Failas nebuvo sukurtas";
    }
    else {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<int> dist(1, 10);

        failas << left << setw(20) << "Vardas" << left << setw(20) << "Pavarde";
        for (int i = 1; i <= nd_sk; i++) {
            std::stringstream pavadinimai;
            pavadinimai << "ND" << i;
            failas << left << '\t' << pavadinimai.str();
        }
        failas << left << '\t' << "EGZ" << endl;

        for (int i = 0; i < kiekis; i++) {
            string str_vard = "Vardas";
            str_vard += std::to_string(i + 1);
            string str_pav = "Pavarde";
            str_pav += std::to_string(i + 1);
            if (i == kiekis - 1) {
                std::stringstream eilute;
                eilute << left << setw(20) << str_vard << left << setw(20) << str_pav;
                for (int i = 0; i < nd_sk; i++) {
                    eilute << left << '\t' << dist(mt);
                }
                eilute << left << '\t' << dist(mt);
                failas << eilute.str();
            }
            else {
                std::stringstream eilute;

                eilute << left << setw(20) << str_vard << left << setw(20) << str_pav;
                for (int i = 0; i < nd_sk; i++) {
                    eilute << left << '\t' << dist(mt);
                }
                eilute << left << '\t' << dist(mt) << endl;
                failas << eilute.str();
            }
        }
    }
    failas.close();
}

void isvedimai_auto_failams(vector<duom> failai, string pavadinimas) {
    std::ofstream rezultatai;
    rezultatai.open(pavadinimas, std::ios::out);
    if (rezultatai.fail()) {
        cout << "Failas nebuvo sukurtas";
    }
    else {
        rezultatai << std::left << std::setw(20) << "Vardas" << std::left << std::setw(20) << "Pavarde";
        rezultatai << std::left << std::setw(20) << "Galutinis (vid.)" << std::left << std::setw(20) << "Galutinis (med.)" << endl;
        rezultatai << "----------------------------------------------------------------------------------" << endl;
        for (int i = 0; i < failai.size(); i++) {
            rezultatai << std::left << std::setw(20) << failai[i].vardas;
            rezultatai << std::left << std::setw(20) << failai[i].pavarde;
            rezultatai << std::left << std::fixed << std::setprecision(2) << std::setw(20) << failai[i].galutinis;
            rezultatai << std::left << std::fixed << std::setprecision(2) << std::setw(20) << failai[i].galutinis_papildomas << endl;
        }
        rezultatai.close();
    }

}

bool gavoSkola(duom st) {
    if (st.galutinis < 5) {
        return true;
    }
    else {
        return false;
    }
}

void pirmos_strategijos_dalijimas(vector <duom> stud, vector <duom> &pirmieji, vector <duom> &antrieji) {

    for (int i = 0; i < stud.size() - 1; i++) {
        if (stud[i].galutinis >= 5) {
            pirmieji.push_back(stud[i]);
        }
        else { antrieji.push_back(stud[i]); }
    }
    stud.clear();
    stud.shrink_to_fit();
}

void antros_strategijos_dalijimas(vector <duom> &stud, vector <duom>& antrieji) {

    vector<duom>::iterator it = stud.begin();
    while (it != stud.end()) {
        if (gavoSkola(*it)) {
            antrieji.push_back(*it);
            it = stud.erase(it); 
        }
        else
            ++it;
    }

    stud.shrink_to_fit();
}

bool ArDaugiau(const duom& i) { return (i.galutinis < 5.0); }

void trecios_strategijos_dalijimas(vector <duom>& stud, vector <duom>& antrieji) {

    std::copy_if(stud.begin(), stud.end(), std::back_inserter(antrieji), ArDaugiau);
    stud.erase(std::remove_if(stud.begin(), stud.end(), ArDaugiau), stud.end());

}

void darbas_su_auto_failu(string pav, int kiek, int variantas) {

    vector <duom> stud;
    stud.reserve(kiek + 1);
    duom studentas;
    ifstream failas;
    failas.open(pav);
    cout << "Failo is " << kiek << " irasu suskirstymo ir rusiavimo laikas su vector naudojant " << variantas << " strategija: ";

    if (failas.is_open()) {
        string eilute;
        std::getline(failas, eilute);
        while (failas) {
            std::getline(failas, eilute);
            studentas = duomenu_issaugojimas(eilute);
            studentas.galutinis = galutinis_pagal_vidurki(studentas.paz) * 0.4 + studentas.egz * 0.6;
            studentas.galutinis_papildomas = galutinis_pagal_mediana(studentas.paz) * 0.4 + studentas.egz * 0.6;
            stud.push_back(studentas);
        }
    }

    auto start2 = std::chrono::high_resolution_clock::now(); auto st2 = start2;
    vector<duom> pirmieji;
    vector<duom> antrieji;
    std::sort(stud.begin(), stud.end(), vid);

    if (variantas == 1) {
        pirmos_strategijos_dalijimas(stud, pirmieji, antrieji);
    }
    if (variantas == 2) {
        antros_strategijos_dalijimas(stud, antrieji);
    }
    if (variantas == 3) {
        trecios_strategijos_dalijimas(stud, antrieji);
    }

    auto end2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff2 = end2 - start2;
    cout << diff2.count() << endl;


    failas.close();

    if (variantas == 1) {
        std::stringstream pavad;
        pavad << "galvociai" << kiek << "vector.txt";
        isvedimai_auto_failams(pirmieji, pavad.str());
        pirmieji.clear();
        pirmieji.shrink_to_fit();
        std::stringstream pavadin;
        pavadin << "nuskriaustukai" << kiek << "vector.txt";
        isvedimai_auto_failams(antrieji, pavadin.str());
        antrieji.clear();
        antrieji.shrink_to_fit();
    }
    else {
        std::stringstream pavad;
        pavad << "galvociai" << kiek << "vector.txt";
        isvedimai_auto_failams(stud, pavad.str());
        stud.clear();
        stud.shrink_to_fit();
        std::stringstream pavadin;
        pavadin << "nuskriaustukai" << kiek << "vector.txt";
        isvedimai_auto_failams(antrieji, pavadin.str());
        antrieji.clear();
        antrieji.shrink_to_fit();
    }
}