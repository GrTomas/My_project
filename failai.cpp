#include "struct.h"
#include "failai.h"
#include "func.h"

void failo_kurimas(string pav, int kiekis, int nd_sk) {

	std::ofstream failas;
	failas.open(pav, std::ios::out);
	auto start = std::chrono::high_resolution_clock::now(); auto st = start;
	
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
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - start;
	cout << kiekis << " irasu failo sukurimas: " << diff.count() << endl;
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

void darbas_su_auto_failu(string pav, int kiek) {

    vector <duom> stud;
    stud.reserve(kiek + 1);
    duom studentas;
    ifstream failas;
    failas.open(pav);
    auto start1 = std::chrono::high_resolution_clock::now(); auto st1 = start1;

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
    auto end1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff1 = end1 - start1;
    cout << "Failo is " << kiek << " irasu nuskaitymo laikas : " << diff1.count() << endl;

    auto start2 = std::chrono::high_resolution_clock::now(); auto st2 = start2;
    vector<duom> pirmieji;
    vector<duom> antrieji;
    for (int i = 0; i < stud.size()-1; i++) {
        if (stud[i].galutinis >= 5) {
            pirmieji.push_back(stud[i]);
        }
        else {
            antrieji.push_back(stud[i]);
        }
    }
    stud.clear();
    stud.shrink_to_fit();
    auto end2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff2 = end2 - start2;
    cout << kiek << " irasu suskirstymo i grupes laikas: " << diff2.count() << endl;
    failas.close();


    auto start3 = std::chrono::high_resolution_clock::now(); auto st3 = start3;
    isvedimai_auto_failams(pirmieji, "galvociai.txt");
    pirmieji.clear();
    pirmieji.shrink_to_fit();
    isvedimai_auto_failams(antrieji, "nuskriaustukai.txt");
    antrieji.clear();
    antrieji.shrink_to_fit();
    auto end3 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff3 = end3 - start3;
    cout << kiek << " sugrupuotu studentu isvedimas i du naujus failus: " << diff3.count() << endl;
    cout << endl;


}