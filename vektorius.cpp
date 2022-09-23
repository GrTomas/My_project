#include <iostream>
#include <string>
#include <cstdio>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <numeric>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

struct duom {
    string vardas;
    string pavarde;
    vector<int> paz;
    int egz;
    double galutinis;
};

duom ivedimas(int a);
double galutinis_pagal_vidurki(vector<int> paz);
double galutinis_pagal_mediana(vector<int> paz);
void isvedimas(vector <duom> stud, string pasirinkimas);

int main() {

    int studentai;
    cout << "Iveskite studentu kieki: ";
    cin >> studentai;
  
    while (cin.fail() || studentai < 1) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Neteisinga reiksme" << endl;
        cout << "Iveskite studentu kieki: ";
        cin >> studentai;
    }

    string pasirinkimas = " ";
    while (pasirinkimas != "vidurkis" && pasirinkimas != "VIDURKIS" && pasirinkimas !="Vidurkis" && pasirinkimas != "mediana" && pasirinkimas != "MEDIANA" && pasirinkimas != "Mediana") {
        cout << "Pagal ka noresite, kad butu skaiciuojamas galutinis balas (vidurkis, mediana)? "; cin >> pasirinkimas;
        if (pasirinkimas != "vidurkis" && pasirinkimas != "VIDURKIS" && pasirinkimas !="Vidurkis" && pasirinkimas != "mediana" && pasirinkimas != "MEDIANA" && pasirinkimas != "Mediana") {
            cout << "Neteisingai ivestas zodis." << endl;
        }
    }

    vector <duom> stud;

    for (int z = 0; z < studentai; z++) {
        duom studentas;
        int m;
        studentas = ivedimas(z);
        if (pasirinkimas == "vidurkis" && pasirinkimas == "VIDURKIS" && pasirinkimas =="Vidurkis") {
            studentas.galutinis = galutinis_pagal_vidurki(studentas.paz) * 0.4 + studentas.egz * 0.6;
        }
        else {
            studentas.galutinis = galutinis_pagal_mediana(studentas.paz) * 0.4 + studentas.egz * 0.6;
        }
        stud.push_back(studentas);
    }
    
    isvedimas(stud, pasirinkimas);
    return 0;
}
    


duom ivedimas(int a) {
    duom asmuo;
    int ivertinimu_sk;
    cout << "Iveskite " << a + 1 << " studento  varda: "; cin >> asmuo.vardas;
    cout << "Iveskite " << a + 1 << " studento  pavarde: "; cin >> asmuo.pavarde;
    string dadejimas = " ";
    string ats = " ";
    while (ats != "taip" && ats != "ne") {
        cout << "Ar norite kad visi ivertinimai butu atsitiktiniai? ";
        cin >> ats;
    }
    if (ats == "ne") {
        cout << "Iveskite " << a + 1 << " studento  egzamino ivertinima: "; cin >> asmuo.egz;
        while (cin.fail() || (asmuo.egz < 1 || asmuo.egz > 10)) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Neteisinga reiksme" << endl;
            cout << "Iveskite " << a + 1 << " studento  egzamino ivertinima: ";
            cin >> asmuo.egz;
        }

        while (dadejimas != "ne" && dadejimas != "Ne" && dadejimas != "NE") {

            cout << "Ar norite prideti namu darbu ivertinima (Taip, Ne)?"; cin >> dadejimas;
            if (dadejimas == "taip" || dadejimas == "TAIP" || dadejimas == "Taip") {
                int ivertinimas = 0;
                while (cin.fail() || ivertinimas < 1 || ivertinimas > 10) {
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    cout << "Iveskite namu darbu ivertinima: ";
                    cin >> ivertinimas;
                    if (cin.fail() || ivertinimas < 1 || ivertinimas > 10){
                        cout << "Neteisinga reiksme" << endl;
                    }
                    else{
                        asmuo.paz.push_back(ivertinimas);
                    }
                }
                
            }
            if (dadejimas != "ne" and dadejimas != "taip") {
                cout << "Neteisingai ivestas zodis" << endl;
            }
        }
    }

    if (ats == "taip") {
        srand(time(0));
        asmuo.egz = rand() % 10 + 1;
        cout << "Atsitiktinis egzamino ivertinimas yra: " << asmuo.egz << endl;
        while (dadejimas != "ne" && dadejimas != "Ne" && dadejimas != "NE") {
            cout << "Ar norite prideti namu darbu ivertinima (Taip, Ne)?"; cin >> dadejimas;
            if (dadejimas == "taip" || dadejimas == "TAIP" || dadejimas == "Taip") {
                int ivertinimas = rand() % 10 + 1;
                asmuo.paz.push_back(ivertinimas);
                cout << "Atsitiktinis namu darbu ivertinimas yra: " << ivertinimas << endl;
            }
            if (dadejimas != "ne" and dadejimas != "taip") {
                cout << "Neteisingai ivestas zodis" << endl;
            }
        }
    }
    cout << "--------------------------------------------------------------" << endl;
    return asmuo;

}

double galutinis_pagal_vidurki(vector<int> paz) {

    double galutine_suma = std::accumulate(paz.begin(),paz.end(),0);
    if (paz.size() != 0) {
        return (double)galutine_suma / paz.size();
    }
    else {
        return 0;
    }
}

double galutinis_pagal_mediana(vector<int> paz) {

    std::sort(paz.begin(), paz.end());
    if (paz.size() % 2 == 0 && paz.size() != 0) {
        return (double)(paz[paz.size()/2] + paz[(paz.size() - 1) / 2]) / 2.0;
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
    cout << std::right << std::setw(5) << "Galutinis (" << pasirinkimas << ")" << endl;
    cout << "--------------------------------------------------------------" << endl;
    for (int z = 0; z < stud.size(); z++) {
        cout << std::left << std::setw(20) << stud[z].vardas << std::left << std::setw(20) << stud[z].pavarde;
        cout << std::right << std::fixed << std::setprecision(2) << std::setw(5) << stud[z].galutinis << endl;
    }
}
