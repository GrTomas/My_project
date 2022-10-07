#include "struct.h"
#include "nuskaitymas.h"

duom ivedimas(int a) {
    duom asmuo;
    int ivertinimu_sk;
    cout << "Iveskite " << a + 1 << " studento  varda: "; cin >> asmuo.vardas;
    cout << "Iveskite " << a + 1 << " studento  pavarde: "; cin >> asmuo.pavarde;
    string dadejimas = " ";
    string ats = " ";

    bool pabaiga = false;
    cout << "Ar norite kad visi ivertinimai butu atsitiktiniai (T, N)? ";
    cin >> ats;
    while (!pabaiga) {
        try {
            if (ats != "t" && ats != "T" && ats != "n" && ats != "N")
                throw - 1;
            pabaiga = true;
        }
        catch (...) {
            cout << "Neteisinga raide" << endl;
            cout << "Ar norite kad visi ivertinimai butu atsitiktiniai (T, N)? ";
            cin >> ats;
        }
    }

    if (ats == "n" || ats == "N") {
        cout << "Iveskite " << a + 1 << " studento  egzamino ivertinima: "; cin >> asmuo.egz;
        while (cin.fail() || (asmuo.egz < 1 || asmuo.egz > 10)) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Neteisinga reiksme" << endl;
            cout << "Iveskite " << a + 1 << " studento  egzamino ivertinima: ";
            cin >> asmuo.egz;
        }

        while (dadejimas != "n" && dadejimas != "N") {

            cout << "Ar norite prideti namu darbu ivertinima (T, N)? "; cin >> dadejimas;
            if (dadejimas == "t" || dadejimas == "T") {
                int ivertinimas = 0;
                while (cin.fail() || ivertinimas < 1 || ivertinimas > 10) {
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    cout << "Iveskite namu darbu ivertinima: ";
                    cin >> ivertinimas;
                    if (cin.fail() || ivertinimas < 1 || ivertinimas > 10) {
                        cout << "Neteisinga reiksme" << endl;
                    }
                    else {
                        asmuo.paz.push_back(ivertinimas);
                    }
                }

            }
            if (dadejimas != "n" && dadejimas != "t" && dadejimas != "N" && dadejimas != "T") {
                cout << "Neteisingai ivesta raide" << endl;
            }
        }
    }

    if (ats == "t" || ats == "T") {
        srand(time(NULL));
        asmuo.egz = rand() % 10 + 1;
        cout << "Atsitiktinis egzamino ivertinimas yra: " << asmuo.egz << endl;
        while (dadejimas != "n" && dadejimas != "N") {
            cout << "Ar norite prideti namu darbu ivertinima (T, N)? "; cin >> dadejimas;
            if (dadejimas == "t" || dadejimas == "T") {
                int ivertinimas = rand() % 10 + 1;
                asmuo.paz.push_back(ivertinimas);
                cout << "Atsitiktinis namu darbu ivertinimas yra: " << ivertinimas << endl;
            }
            if (dadejimas != "n" && dadejimas != "t" && dadejimas != "N" && dadejimas != "T") {
                cout << "Neteisingai ivesta raide" << endl;
            }
        }
    }
    cout << "--------------------------------------------------------------" << endl;
    return asmuo;

}



duom duomenu_issaugojimas(string eilute) {
    duom asmuo;
    vector<string> v;
    std::stringstream ss(eilute);
    string temp;
    while (ss >> temp) {
        v.push_back(temp);
    }

    asmuo.vardas = v[0];
    asmuo.pavarde = v[1];
    for (int i = 0; i < v.size() - 3; i++) {


        try {
            asmuo.paz.push_back(stoi(v[i + 2]));
        }
        catch (std::exception& err)
        {
            cout << "Faile rasta neteisingai ivesta namu darbu reiksme, patikslinkite reiksme:   ";
            int sk;
            cin >> sk;
            asmuo.paz.push_back(sk);
        }

    }
    asmuo.egz = stoi(v[v.size() - 1]);
    return asmuo;
}

double galutinis_pagal_vidurki(vector<int> paz) {

    double galutine_suma = std::accumulate(paz.begin(), paz.end(), 0);
    if (paz.size() != 0) {
        return (double)galutine_suma / paz.size();
    }
    else {
        return 0;
    }
}