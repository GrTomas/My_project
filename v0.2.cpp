#include "my_func.h"

struct duom {
  string vardas;
  string pavarde;
  vector<int> paz;
  int egz;
  double galutinis;
  double galutinis_papildomas;
};

duom ivedimas(int a);
duom duomenu_issaugojimas(string eilute);
double galutinis_pagal_vidurki(vector<int> paz);
double galutinis_pagal_mediana(vector<int> paz);
void isvedimas(vector <duom> stud, string pasirinkimas);
void isvedimas_is_failo(vector<duom> stud);

int main() {

  string ar_failas = " ";
  while (ar_failas != "T" && ar_failas != "t" && ar_failas != "N" && ar_failas != "n"){
    cout << "Noredami, kad duomenys butu imami is failo rasykite T, noredami patys ivesti duomenis rasykite N:   ";
    cin >> ar_failas;
    if(ar_failas != "T" && ar_failas != "t" && ar_failas != "N" && ar_failas != "n"){
      cout << "Neteisingai ivesta reiksme." << endl;
    }
  }
  if(ar_failas == "T" || ar_failas == "t"){

    vector <duom> stud;
    duom studentas;
    bool pabaiga = false;
    
    ifstream failas;
    string failo_vardas;

    while(!pabaiga){
      try {
        cout << "Iveskite failo varda: ";
        cin >> failo_vardas;
        failas.open(failo_vardas);
        if (failas.fail())
          throw -1;
        pabaiga = true;
      }
      catch (...) {
        cout << "Failo tokiu vardu nera" << endl;
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }
    }
    
    if (failas.is_open()){
      string eilute;
      string praeita_eilute;
      int i = 0;
      while (failas){
        std::getline(failas, eilute);
        i = i + 1;
        if(i>1 && praeita_eilute != eilute){
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

  else{
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
    
    while (dadejimas != "n" && dadejimas != "N"){
      cout << "Ar norite prideti studenta (T, N)? ";
      cin >> dadejimas;

      if (dadejimas == "T" || dadejimas == "t"){
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
      if(dadejimas != "T" && dadejimas != "t" && dadejimas != "N" && dadejimas != "n"){
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
  while(!pabaiga){
    try {
      if (ats != "t" && ats != "T" && ats != "n" && ats != "N")
          throw -1;
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
          if (cin.fail() || ivertinimas < 1 || ivertinimas > 10){
            cout << "Neteisinga reiksme" << endl;
          }
          else{
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

duom duomenu_issaugojimas(string eilute){
  duom asmuo;
  vector<string> v; 
  std::stringstream ss(eilute); 
  string temp;
  while (ss >> temp) {
    v.push_back(temp);
  }

  asmuo.vardas = v[0];
  asmuo.pavarde = v[1];
  for (int i = 0; i < v.size()-3; i++){


    try{
      asmuo.paz.push_back(stoi(v[i+2]));	
    }
    catch(std::exception &err)
    {
      cout << "Faile rasta neteisingai ivesta namu darbu reiksme, patikslinkite reiksme:   ";
      int sk;
      cin >> sk;
      asmuo.paz.push_back(sk);
    }
    
  }
  asmuo.egz = stoi(v[v.size()-1]);
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
  cout << std::right << std::setw(5) << "Galutinis (";
  if (pasirinkimas == "v" || pasirinkimas == "V"){
    cout << "vid.)" << endl;
  }
  else{
    cout << "med.)" << endl; 
  }
  cout << "--------------------------------------------------------------" << endl;
  for (int z = 0; z < stud.size(); z++) {
    cout << std::left << std::setw(20) << stud[z].vardas << std::left << std::setw(20) << stud[z].pavarde;
    cout << std::right << std::fixed << std::setprecision(2) << std::setw(5) << stud[z].galutinis << endl;
  }
}

bool palyginimas(const duom &a, const duom &b){
    return a.vardas < b.vardas;
}
void isvedimas_is_failo(vector<duom> stud){
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
    for(int i = 0; i < stud.size(); i++){
      rezultatai << std::left << std::setw(20) << stud[i].vardas;
      rezultatai << std::left << std::setw(20) << stud[i].pavarde;
      rezultatai << std::left << std::fixed << std::setprecision(2) << std::setw(20) << stud[i].galutinis;
      rezultatai << std::left << std::fixed << std::setprecision(2) << std::setw(20) << stud[i].galutinis_papildomas << endl;
    }
    rezultatai.close();
	}
}
