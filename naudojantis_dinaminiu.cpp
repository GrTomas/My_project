#include <iostream>
#include <string>
#include <cstdio>
#include <vector>
#include <iomanip>
#include <algorithm>

using std::cout;
using std::cin;
using std::endl;
using std::string;

struct duom {
    string vardas;
    string pavarde;
    int* paz;
    int egz;
    double galutinis;
};

duom ivedimas(int a, int& m);
double galutinis_pagal_vidurki(int* paz, int m);
double galutinis_pagal_mediana(int* paz, int m);
void isvedimas(duom temp[], int studentai, string pasirinkimas);

int main() {

    int studentai;
    cout << "Iveskite studentu kieki (iki 100): ";
    cin >> studentai;
    while (cin.fail() || studentai < 1 || studentai > 100) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Neteisinga reiksme" << endl;
        cout << "Iveskite studentu kieki: ";
        cin >> studentai;
    }

    string pasirinkimas = " ";
    while (pasirinkimas != "vidurkis" && pasirinkimas != "mediana") {
        cout << "Pagal ka noresite, kad butu skaiciuojamas galutinis balas (vidurkis, mediana)? "; cin >> pasirinkimas;
        if (pasirinkimas != "vidurkis" && pasirinkimas != "mediana") {
            cout << "Neteisingai ivestas zodis." << endl;
        }
    }

    duom stud[100];

    for (int z = 0; z < studentai; z++) {
        duom studentas;
        int m;
        studentas = ivedimas(z, m);
        if (pasirinkimas == "vidurkis") {
            studentas.galutinis = galutinis_pagal_vidurki(studentas.paz, m) * 0.4 + studentas.egz * 0.6;
            delete[] studentas.paz;
        }
        else {
            studentas.galutinis = galutinis_pagal_mediana(studentas.paz, m) * 0.4 + studentas.egz * 0.6;
            delete[] studentas.paz;
        }
        stud[z] = studentas;
    }
  isvedimas(stud, studentai, pasirinkimas);
}

duom ivedimas(int a, int& m) {
    duom asmuo;
    cout << "Iveskite " << a + 1 << " studento  varda: "; cin >> asmuo.vardas;
    cout << "Iveskite " << a + 1 << " studento  pavarde: "; cin >> asmuo.pavarde;
    int ivertinimu_sk = 0;
    int ivertinimas;
    string dadejimas = " ";
    string ats = " ";
    while (ats != "taip" && ats != "ne") {
        cout << "Ar norite kad visi ivertinimai butu atsitiktiniai? ";
        cin >> ats;
      if (ats != "taip" && ats != "ne"){
        cout << "Neteisingai ivestas zodis." << endl;
      }
    }
    if (ats == "ne") {
        asmuo.paz = new int[0];
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
                cout << "Iveskite namu darbu ivertinima: ";
                cin >> asmuo.paz[ivertinimu_sk];
                while (cin.fail() || (asmuo.paz[ivertinimu_sk] < 1 || asmuo.paz[ivertinimu_sk] > 10)) {
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    cout << "Neteisinga reiksme" << endl;
                    cout << "Iveskite namu darbu ivertinima: ";
                    cin >> asmuo.paz[ivertinimu_sk];
                }
                ivertinimu_sk++;
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
        asmuo.paz = new int[0];

        while (dadejimas != "ne" && dadejimas != "Ne" && dadejimas != "NE") {

            cout << "Ar norite prideti namu darbu ivertinima (Taip, Ne)?"; cin >> dadejimas;
            if (dadejimas == "taip" || dadejimas == "TAIP" || dadejimas == "Taip") {
                asmuo.paz[ivertinimu_sk] = rand() % 10 + 1;
                cout << "Atsitiktinis namu darbu ivertinimas yra: " << asmuo.paz[ivertinimu_sk] << endl;
                ivertinimu_sk++;
            }
            if (dadejimas != "ne" and dadejimas != "taip") {
                cout << "Neteisingai ivestas zodis" << endl;
            }
        }
    }
    cout << "--------------------------------------------------------------" << endl;
    m = ivertinimu_sk;
    return asmuo;

}

double galutinis_pagal_vidurki(int* paz, int m) {

    double galutine_suma = 0;
    for (int i = 0; i < m; i++) {
        galutine_suma = galutine_suma + paz[i];
    }
    if (m != 0 && m != 1) {
        return (double)galutine_suma / m;
    }
    else {
        return 0;
    }
}

double galutinis_pagal_mediana(int* paz, int m) {

    std::sort(paz, paz + m + 1);
    if (m % 2 == 0) {
        return (double)(paz[(m) / 2] + paz[(m - 1) / 2]) / 2.0;
    }
    if (m == 0) {
        return 0;
    }
    else {
        if (m == 1) {
            return (double)paz[m];
        }
        else {
            return (double)paz[(m+1) / 2];
        }

    }
}
void isvedimas(duom temp[], int studentai, string pasirinkimas) {

  cout << std::left << std::setw(20) << "Vardas" << std::left << std::setw(20) << "Pavarde";
    cout << std::right << std::setw(5) << "Galutinis (" << pasirinkimas << ")" << endl;
    cout << "--------------------------------------------------------------" << endl;
    for (int z = 0; z < studentai; z++) {
      cout << std::left << std::setw(20) << temp[z].vardas << std::left << std::setw(20) << temp[z].pavarde;
      cout << std::right << std::fixed << std::setprecision(2) << std::setw(5) << temp[z].galutinis << endl;
      
    }  
}
