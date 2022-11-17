#include "struct.h"
#include "failai_vector.h"
#include "funkcijos.h"
#include "failai_list.h"

int main() {
    string ar_failas = " ";
    while (ar_failas != "T" && ar_failas != "t" && ar_failas != "N" && ar_failas != "n") {
        cout << "Noredami, kad duomenys butu imami is failo rasykite T, noredami patys ivesti duomenis rasykite N:   ";
        cin >> ar_failas;
        if (ar_failas != "T" && ar_failas != "t" && ar_failas != "N" && ar_failas != "n") {
            cout << "Neteisingai ivesta reiksme." << endl;
        }
    }
    if (ar_failas == "T" || ar_failas == "t") {
        int auto_duom;
        cout << "Noredami patys pasirinkti faila iveskite 1, o noredami atlikti programos testavima iveskite 2:   ";
        cin >> auto_duom;
        while (cin.fail() || (auto_duom != 1 && auto_duom != 2)) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Noredami patys pasirinkti faila iveskite 1 " << endl;
            cout << "Noredami failu su atsitiktinai sugeneruotais duomenimis veikimo laiko informacijos iveskite 2:   ";
            cin >> auto_duom;
            if (cin.fail() || (auto_duom != 1 && auto_duom != 2)) {
                cout << "Neteisingai ivesta reiksme." << endl;
            }
        }

        if (auto_duom == 1) {
            vector <duom> stud;
            duom studentas;
            bool pabaiga = false;

            ifstream failas;
            string failo_vardas;

            while (!pabaiga) {
                try {
                    cout << "Iveskite failo varda: ";
                    cin >> failo_vardas;
                    failas.open(failo_vardas);
                    if (failas.fail())
                        throw - 1;
                    pabaiga = true;
                }
                catch (...) {
                    cout << "Failo tokiu vardu nera" << endl;
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            }

            if (failas.is_open()) {
                string eilute;
                string praeita_eilute;
                int i = 0;
                while (failas) {
                    std::getline(failas, eilute);
                    i = i + 1;
                    if (i > 1 && praeita_eilute != eilute) {
                        studentas = duomenu_issaugojimas(eilute);
                        studentas.galutinis = galutinis_pagal_vidurki(studentas.paz) * 0.4 + studentas.egz * 0.6;
                        studentas.galutinis_papildomas = galutinis_pagal_mediana(studentas.paz) * 0.4 + studentas.egz * 0.6;
                        stud.push_back(studentas);
                    }
                    praeita_eilute = eilute;
                }
            }
            failas.close();
            isvedimas_is_failo(stud);
        }
        else {


            cout << "Ar norite naudotis jau parauostais duomenimis (T ar N)?   ";
            string ats;
            cin >> ats;
            while (ats != "T" && ats != "t" && ats != "N" && ats != "n") {
                cout << "Neteisingai ivesta raide" << endl;
                cout << "Ar norite naudotis jau parauostais duomenimis (T ar N)?   ";
                cin >> ats;
            }
            if (ats == "T" || ats == "t") {

                cout << endl;
                cout << "Pirmosios strategijos rezultatai: " << endl;
                darbas_su_auto_failu("stud1000.txt", 1000, 1); 
                darbas_su_auto_failu("stud10000.txt", 10000, 1); 
                darbas_su_auto_failu("stud100000.txt", 100000, 1); 
                darbas_su_auto_failu("stud1000000.txt", 1000000, 1); 
                darbas_su_auto_failu("stud10000000.txt", 10000000, 1);
                cout << endl;
                darbas_su_auto_failu_list("stud1000.txt", 1000, 1);
                darbas_su_auto_failu_list("stud10000.txt", 10000, 1);
                darbas_su_auto_failu_list("stud100000.txt", 100000, 1);
                darbas_su_auto_failu_list("stud1000000.txt", 1000000, 1);
                darbas_su_auto_failu_list("stud10000000.txt", 10000000, 1);
                cout << "----------------------------------------------------------------------------------------------------------------" << endl;
                cout << "Antrosios strategijos rezultatai: " << endl;
                darbas_su_auto_failu("stud1000.txt", 1000, 2);
                darbas_su_auto_failu("stud10000.txt", 10000, 2);
                darbas_su_auto_failu("stud100000.txt", 100000, 2);
                //darbas_su_auto_failu("stud1000000.txt", 1000000, 2);
                //darbas_su_auto_failu("stud10000000.txt", 10000000, 2);
                cout << endl;
                darbas_su_auto_failu_list("stud1000.txt", 1000, 2);
                darbas_su_auto_failu_list("stud10000.txt", 10000, 2);
                darbas_su_auto_failu_list("stud100000.txt", 100000, 2);
                darbas_su_auto_failu_list("stud1000000.txt", 1000000, 2);
                darbas_su_auto_failu_list("stud10000000.txt", 10000000, 2);
                cout << "----------------------------------------------------------------------------------------------------------------" << endl;
                cout << "Treciosios strategijos rezultatai (tik su vector): " << endl;
                darbas_su_auto_failu("stud1000.txt", 1000, 3);
                darbas_su_auto_failu("stud10000.txt", 10000, 3);
                darbas_su_auto_failu("stud100000.txt", 100000, 3);
                darbas_su_auto_failu("stud1000000.txt", 1000000, 3);
                darbas_su_auto_failu("stud10000000.txt", 10000000, 3);
                
            }

            else {
                bool pabaiga = false;
                int nd_sk;
                cout << "Iveskite skaiciu, kuris nurodys kiek failuose bus namu darbu: ";
                cin >> nd_sk;
                while (!pabaiga) {
                    try {
                        if (cin.fail() || nd_sk < 0)
                            throw - 1;
                        pabaiga = true;
                    }
                    catch (...) {
                        cin.clear();
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        cout << "Neteisingas ivestas skaicius" << endl;
                        cout << "Iveskite skaiciu, kuris nurodys kiek failuose bus namu darbu: ";
                        cin >> nd_sk;
                    }
                }
                cout << endl;

                failo_kurimas("stud1000.txt", 1000, nd_sk);
                failo_kurimas("stud10000.txt", 10000, nd_sk);
                failo_kurimas("stud100000.txt", 100000, nd_sk);
                failo_kurimas("stud1000000.txt", 1000000, nd_sk);
                failo_kurimas("stud10000000.txt", 10000000, nd_sk);

                cout << "Pirmosios strategijos rezultatai: " << endl;
                darbas_su_auto_failu("stud1000.txt", 1000, 1);
                darbas_su_auto_failu("stud10000.txt", 10000, 1);
                darbas_su_auto_failu("stud100000.txt", 100000, 1);
                darbas_su_auto_failu("stud1000000.txt", 1000000, 1);
                darbas_su_auto_failu("stud10000000.txt", 10000000, 1);
                cout << endl;
                darbas_su_auto_failu_list("stud1000.txt", 1000, 1);
                darbas_su_auto_failu_list("stud10000.txt", 10000, 1);
                darbas_su_auto_failu_list("stud100000.txt", 100000, 1);
                darbas_su_auto_failu_list("stud1000000.txt", 1000000, 1);
                darbas_su_auto_failu_list("stud10000000.txt", 10000000, 1);
                cout << "----------------------------------------------------------------------------------------------------------------" << endl;
                cout << "Antrosios strategijos rezultatai: " << endl;
                darbas_su_auto_failu("stud1000.txt", 1000, 2);
                darbas_su_auto_failu("stud10000.txt", 10000, 2);
                darbas_su_auto_failu("stud100000.txt", 100000, 2);
                //darbas_su_auto_failu("stud1000000.txt", 1000000, 2);
                //darbas_su_auto_failu("stud10000000.txt", 10000000, 2);
                cout << endl;
                darbas_su_auto_failu_list("stud1000.txt", 1000, 2);
                darbas_su_auto_failu_list("stud10000.txt", 10000, 2);
                darbas_su_auto_failu_list("stud100000.txt", 100000, 2);
                darbas_su_auto_failu_list("stud1000000.txt", 1000000, 2);
                darbas_su_auto_failu_list("stud10000000.txt", 10000000, 2);
                cout << "----------------------------------------------------------------------------------------------------------------" << endl;
                cout << "Treciosios strategijos rezultatai (tik su vector): " << endl;
                darbas_su_auto_failu("stud1000.txt", 1000, 3);
                darbas_su_auto_failu("stud10000.txt", 10000, 3);
                darbas_su_auto_failu("stud100000.txt", 100000, 3);
                darbas_su_auto_failu("stud1000000.txt", 1000000, 3);
                darbas_su_auto_failu("stud10000000.txt", 10000000, 3);

                cout << endl;
            }
        }
    }

    else {
        int studentai;
        bool pabaiga = false;
        int studento_nr = 0;
        string dadejimas = " ";
        vector <duom> stud;

        string pasirinkimas = " ";
        while (pasirinkimas != "v" && pasirinkimas != "V" && pasirinkimas != "m" && pasirinkimas != "M") {
            cout << "Noredami, kad galutinis ivertinimas butu skaiciuojamas pagal vidurki iveskite V, pagal mediana - M:   ";
            cin >> pasirinkimas;
            if (pasirinkimas != "v" && pasirinkimas != "V" && pasirinkimas != "m" && pasirinkimas != "M") {
                cout << "Neteisingai ivestas zodis." << endl;
            }
        }

        while (dadejimas != "n" && dadejimas != "N") {
            cout << "Ar norite prideti studenta (T, N)? ";
            cin >> dadejimas;

            if (dadejimas == "T" || dadejimas == "t") {
                duom studentas;
                int m;
                studentas = ivedimas(studento_nr);
                if (pasirinkimas == "v" && pasirinkimas == "V") {
                    studentas.galutinis = galutinis_pagal_vidurki(studentas.paz) * 0.4 + studentas.egz * 0.6;
                }
                else {
                    studentas.galutinis = galutinis_pagal_mediana(studentas.paz) * 0.4 + studentas.egz * 0.6;
                }
                stud.push_back(studentas);
                studento_nr++;
            }
            if (dadejimas != "T" && dadejimas != "t" && dadejimas != "N" && dadejimas != "n") {
                cout << "Neteisinai ivesta raide" << endl;
                cout << "Ar norite prideti studenta (T, N)? ";
                cin >> dadejimas;
            }
        }
        cout << "--------------------------------------------------------------" << endl;
        isvedimas(stud, pasirinkimas);
    }
    return 0;
}

