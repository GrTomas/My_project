
# v1.0

Programos versija (v1.0) papildo versiją (v0.4).

v1.0 ši programos versija leidžia palyginti 3 skirtingas duomenų grupavimo strategijas, skirstant juos į "galvočius" ir "nuskriaustukus", kai programa yra testuojama. Pirmosios dvi strategijos yra daromos su vector ir list konteineriais, o trečioji strategija yra realizuota tik vector konteineriui. Strategijų aprašymai ir trumpi kodų fragmentai nurodantys strategijas vector konteineriui:

Prieš pradedant naudoti grupavimo strategijas, duomenys yra surūšiuojami didėjimo tvarka pagal vidurkį ir jeigu jis vienodas, tada pagal medianą.
* Pirmoji strategija: duomenys skirstomi į "galvočius" ir "nuskriaustukus" dedant juos į skirtingus konteinerius prieš tai patikrinant ar jų galutinis įvertinimas pagal vidurkį yra didesnis ar mažesnis už 5.

```cpp
  for (int i = 0; i < stud.size() - 1; i++) {
        if (stud[i].galutinis >= 5) {
            pirmieji.push_back(stud[i]);
        }
        else { antrieji.push_back(stud[i]); }
    }
```

* Antroji strategija: pirmiausiai yra patikrinama ar įvertinimas yra mažesnis už 5, tada jis dedamas į kitą konteinerį ir iš bendrojo duomenų konteinerio yra ištrinami. Tokių būdu duomenys nėra dubliuojami ir yra tik padalinti per 2 konteinerius.

```cpp
while (it != stud.end()) {
        if (gavoSkola(*it)) {
            antrieji.push_back(*it);
            it = stud.erase(it); 
        }
        else
            ++it;
    }
```

* Trečioji strategija: pirmiausiai duomenys yra nukopijuojami ir įdedami į atskirą konteinerį pagal sąlygą, kad vidurkis yra mažesnis už 5. Tada naudojant remove_if ir erase sąlygas, nukopijuoti duomenys yra ištrinami iš bendrojo konteinerio.

```cpp
std::copy_if(stud.begin(), stud.end(), std::back_inserter(antrieji), ArDaugiau);
stud.erase(std::remove_if(stud.begin(), stud.end(), ArDaugiau), stud.end());
```


Šioje lentelėje yra pateikiamos laiko informacijos, kiek užtrunka surūšiuoti duomenis ir jiems pritaikyti vieną iš strategijų naudojant vector konteinerį.

Duomenų kiekis | Pirmoji strategija | Antroji strategija | Trečioji strategija  |
---------------|--------------------|--------------------|----------------------|
1000           |      0.0128781     |     0.108993       |      0.0090386       |       
10000          |      0.146756      |     10.3373        |      0.108304        |   
100000         |      1.56781       |     1340.93        |      1.23758         |  
1000000        |      16.4427       |        -           |      11.4213         |  
10000000       |      194.89        |        -           |      135.975         |   

Iš pirmųjų antrosios strategijų rezultatų galima matyti, kad padidinus duomenų kiekį dešimt kartų, laikas pailgėja apie 100 kartu, tai reiškia, kad rūšiavimas ir dalijimas su milijonu duomenų užtruktų ne mažiau nei 30 valandų, todėl tikslūs laikai lentelėje nėra pateikti.



Šioje lentelėje yra pateikiamos laiko informacijos, kiek užtrunka surūšiuoti duomenis ir jiems pritaikyti vieną iš strategijų naudojant list konteinerį.


Duomenų kiekis | Pirmoji strategija | Antroji strategija |
---------------|--------------------|--------------------|
1000           |     0.0061421      |      0.0028408     |               
10000          |     0.0615006      |      0.0363877     |         
100000         |     0.674611       |      0.323743      |          
1000000        |     7.28904        |      3.63578       |            
10000000       |     169.19         |      42.3387       |       


* Iš pirmosios lentelės galime lyginti strategijų laikus vector konteineryje. Paleidus programą, pirmoji strategija pareikalavo daug didesnio kiekio operatyviosios atminties, bet ji buvo daug greitesnė už antrąją strategiją. Antroji strategija nors ir užima mažiau atminties, ji trunka labai ilgai, nes trinant kiekvieną elementą, visus likusius vektoriaus elementus reikia nukopijuoti ir perkelti į šoną, kas ilgai užtrunka. Trečioji strategija apjungia pirmąją ir antrąją, todėl, nes ji yra greita kaip pirmoji strategija ir taip pat užima mažiau operatyviosios atminties kaip antroji strategija. Pagal rezultatus galime matyti, kad ši strategija vector konteineriui yra pati greičiausia.

* Iš antros lentelės galime palyginti pirmąją ir antrąją strategiją. Pirmoji strategija užėmė daugiau atminties ir buvo lėtesnė už antrąją strategiją, todėl ši strategija yra prastesnė list duomenų konteineriui. Antroji strategija yra daug optimalesnė, ji yra daug greitesnė, o taip pat ir užimanti mažiau operatyviosios atminties.

* Paskutinis dalykas kurį galime palyginti tai pačius duomenų konteinerius. Greičiausias būdas, buvo naudoti list duomenų konteinerį su antrąja strategija. Taip pat ir vector trečioji strategija yra visai gera dirbant su duomenimis, bet list duomenų konteineris išlieka greičiausias.

--------------

# v0.4

Programos versija (v0.4) papildo versiją (v0.3).

v0.4 programos versija leidžia taip pat daryti testus kaip ir v0.3 tik dabar yra lyginami laikai naudojant vector ir list tipo kintamuosius. Pradedant programą vartotojas yra paklausiamas ar nori naudoji jau anksčiau sugeneruotus failus, ar failus nori generuoti iš naujo. Kai pasirenkama tada į ekraną pradedami išvesti rezultatai. Pirmiausiai yra išvedama nuskaitymo ir grupavimo laikai vector kintamojo duomenims iki 10 milijonų, tada viskas kartojama su list tipo kintamaisiais. Tai atlikus galima pastebėti, kad studentus sudedant į list tipo kintamąjį, darbas yra atliekamas greičiau - greičius galite pamatyti lentelėje žemiau.

Duomenų kiekis | Nuskaitymas (list) | Nuskaitymas (vector) | Grupavimas (list)  | Grupavimas(vector) |
---------------|--------------------|----------------------|--------------------|--------------------|
1000           |      0.030032      |      0.0382035       |     0.0020437      |      0.0044541     |
10000          |      0.297484      |      0.386496        |     0.0210818      |      0.0653794     |
100000         |      3.07795       |      3.61594         |     0.22024        |      0.505613      |
1000000        |      30.6871       |      36.1878         |     2.21454        |      4.97182       |
10000000       |      319.281       |      366.036         |     38.4771        |      82.5206       |


Lentelėje esančioje žemiau galite pamatyti kiek programa užtruko bendrai (nuskaitant ir grupuojant duomenis) naudojantis vector ir list konteineriais. Paskutinis duomenų stulpelis parodo vector ir list bendro laiko skirtumą ir keliomis sekundėmis programa naudojant list konteinerį buvo greitesnė už programą naudojant vector konteinerį.

Duomenų kiekis | Bendras laikas (vector) | Bendras laikas (list) | Skirtumas tarp vector ir list |
---------------|------------------------|------------------------|------------------------------ |
1000           |        0.0438325       |       0.0331462        |           0.0103705           |
10000          |        0.453493        |       0.320417         |           0.133076            |
100000         |        4.12351         |       3.30058          |           0.82293             |
1000000        |        41.1604         |       32.9034          |           8.275               |
10000000       |        448.572         |       358.004          |           90.568              |

#### Testavimo sistemos parametrai:
* CPU: 11th Gen Intel(R) Core(TM) i7-11800H @ 2.30GHz   2.30 GHz
* RAM: 16,0 GB
* SSD: 500Gb
----------------
# v0.3

Programos versija (v0.3) papildo versiją (v0.2).

v0.3 programos versija leidžia pasirinkus, kad duomenys yra imami iš failo, pasirinkti, kad failai būtų sugeneruoti atsitiktinai ir į ekraną būtų išvedamas kiek laiko užtruks kiekvieno failo sukūrimas, jo nuskaitymas, padalinimas į 2 dalis ir išvedimas į naujus failus. Prieš sukuriant duomenis vartotojas yra paklausiamas koks namų darbų kiekis turėtų būti sukurtuose failuose. Tada failas yra sukuriamas su nurodytu namų darbų skaičiumi ir nuskaitomas naudojantis v0.2 programos versijai sukurta nuskaitymo funkcija. Galiausiai duomenys yra suskirstomi į pirmuosius ir antruosius. Pirmieji yra duomenys, kur žmogaus galutinis įvertinimas (pagal vidurkį) yra didesnis už 5, o antrieji – mažesnis. Tada panaikinamas bendrų duomenų failų vektorius. Galiausiai pirmieji ir antrieji yra išvedami į atskirus failus pavadinimais „galvociai.txt“ ir „nuskriaustukai.txt“. Kiekvienas programos veikimo etapo laikas yra matuojamas ir išvedamas vartotojui į ekraną. Pasinaudojus šia programa ir pasirinkus namų darbų skaičių 5, galime matyti tokius sukurtus duomenis, rezultatus ir laiką. Atsitiktinai žemiau pavaizduota po 5 eilutes iš sukurtų duomenų, galvočiai, nuskriaustukai ir atlikimo laikas (su 1000 duomenų):

Vardas  | Pavarde  | ND1 | ND2 | ND3 | ND4 | ND5 | EGZ  |
--------|----------|-----|-----|-----|-----|-----|------|
Vardas1 | Pavarde1 |  5  |  5  |  8  |  3  |  10 |  7   |
Vardas2 | Pavarde2 |  6  |	9  | 5   | 5   |   8 |  9   |
Vardas3 | Pavarde3 | 9	 | 3 | 6 | 2 | 10 | 1    |
Vardas4 | Pavarde4 | 1 | 7 | 1 | 5 | 7 | 5 |
Vardas5 | Pavarde5 | 4 | 2 | 3 | 3 | 1 | 2 |

Vardas | Pavarde | Galutinis (vid.) | Galutinis (med.)  |
-------|---------|------------------|-------------------|
Vardas1      |       Pavarde1      |        6.68    |            6.20                
Vardas2       |      Pavarde2       |       8.04      |          7.80                
Vardas7         |    Pavarde7   |           9.36      |          9.20                
Vardas9      |       Pavarde9      |        6.44           |     6.20                
Vardas12      |      Pavarde12        |     5.32           |     5.80       

Vardas      |        Pavarde      |       Galutinis (vid.)   | Galutinis (med.) |
------------|---------------------|--------------------------|------------------|
Vardas3      |       Pavarde3     |       3.00       |         3.00                
Vardas4        |     Pavarde4      |      4.68          |      5.00                
Vardas5        |     Pavarde5       |     2.24            |    2.40                
Vardas6       |      Pavarde6        |    4.72        |        4.40                
Vardas8        |     Pavarde8       |     4.68      |          3.80             


1000 irasu failo sukurimas: 0.0345103   
Failo is 1000 irasu nuskaitymo laikas : 0.0373514   
1000 irasu suskirstymo i grupes laikas: 0.0044843   
1000 sugrupuotu studentu isvedimas i du naujus failus: 0.0161059    

--------------------------------

Taip pat žemiau galite pamatyti ir su didesniais duomenų kiekiais atliktus programos rezultatus:

10000 irasu failo sukurimas: 0.283629
Failo is 10000 irasu nuskaitymo laikas : 0.375472
10000 irasu suskirstymo i grupes laikas: 0.0493201
10000 sugrupuotu studentu isvedimas i du naujus failus: 0.149311

100000 irasu failo sukurimas: 2.80279
Failo is 100000 irasu nuskaitymo laikas : 3.89738
100000 irasu suskirstymo i grupes laikas: 0.501119
100000 sugrupuotu studentu isvedimas i du naujus failus: 1.56041

1000000 irasu failo sukurimas: 28.2785
Failo is 1000000 irasu nuskaitymo laikas : 38.8554
1000000 irasu suskirstymo i grupes laikas: 5.16286
1000000 sugrupuotu studentu isvedimas i du naujus failus: 15.3076

10000000 irasu failo sukurimas: 277.656
Failo is 10000000 irasu nuskaitymo laikas : 394.788
10000000 irasu suskirstymo i grupes laikas: 84.252
10000000 sugrupuotu studentu isvedimas i du naujus failus: 155.659
---------------

# v0.2

v0.2 programos versija papildo v0.1 programą tuo, kad visi vartotojo duomenys gali būti paimami iš failo ir rezultatai išvedami į kitą failą. Pirmiausiai vartotojo yra paklausiama ar jis nori duomenis įvesti ranka, ar imti juos iš failo ir pasirinkęs iš failo, vartotojas turi įvesti failo vardą. Failas tada yra nuskaitomas ir atskirame rezultato faile yra išvedami visų studentų vardai, pavardės, galutiniai rezultatai skaičiuoti pagal vidurkį ir galutiniai rezultatai skaičiuoti pagal mediana. Taip pat nuo šios programos versijos, funkcijos yra išskaidytos per kelis cpp failus ir sukurti header failai, o taip pat yra gaudomos vartotojo įvedime atliekamos klaidos naudojantis išimčių valdymu.

----------------------------

# v0.1

0.1 Programa leidžia vartotojui duomenis įvesti ranka. Pirmiausiai vartotojas pasirenka ar galutinis rezultatas skaičiuojamas pagal vidurkį ar medianą. Vartotojui tada reikia įvesti studentus ir jų namų darbų, bei egzamino rezultatus. Visą tai padaręs vartotojas ekrane pamato visų įvestų studentų vardus ir pavardes ir galutinius rezultatus suskaičiuotus pagal namų darbų vidurkį ar medianą. Šie rezultatai skaičiuojami ir išvedami ekrane. Ši versija yra realizuota dviem būdais - dinaminiu masyvu ir vector tipo konteineriu. Kiekvienai realizacijai paskelbtas atskiras projektas.
