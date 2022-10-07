#include "struct.h"
#include "nuskaitymas.h"
#include "func.h"

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

