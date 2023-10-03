#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <set>
// Windows only
// #include <Windows.h>

using namespace std;

struct Taisykle {
    string Bus, NaujBus;
    char Sim, NaujSim, Krypt;
};

void NaujasSimbolis(char NaujSim, string &Juosta, int &GalvPoz);
void NaujaBusena(string NaujBus, string &DabrBus);
void NaujaKryptis(char Krypt, int &GalvPoz);
void SpausdintiJuosta(string Juosta, int GalvPoz);
void VienaJuosta(string file);
void DviJuostos(string file);

int main(int argc, char **argv) {
    system("Clear");
    if (argc == 1) {
        cout << "Programa nebuvo paleista. Prasau naudotis komandu eilute ir ivesti failu pavadinimus" << endl;
        return 0;
    } else {
        int TempJuostSk;
        string Pl;

        cout << "Sveiki atvyke I Universalia Tiuringo Masina." << endl;
        for (int i = 1; i < argc; i++) {
            ifstream df(argv[i]);
            
            if (df) {
                df >> TempJuostSk;
                
                cout << "Ar norite paleisti " << argv[i] << " faila ?!" << endl;
                cout << "2 - Nutraukti programa" << endl;
                cout << "1 - Taip" << endl;
                cout << "0 - Ne" << endl;
                cin >> Pl;

                if (Pl == "1") {
                    if (TempJuostSk == 1) {
                        VienaJuosta(argv[i]);
                    } else if (TempJuostSk == 2) {
                        DviJuostos(argv[i]);
                    } else {
                        cout << "Deja, faile " << argv[i] << " yra " << TempJuostSk << " juostu tiuringo masina, si tiuringo masina palaiko tik 1 arba 2" << endl;
                    }
                } else if (Pl == "2") {
                    cout << "Aciu kad naudojotes Universalia Tiuringo Masina" << endl;
                    return 0;
                } else if (Pl != "0") {
                    system("Clear");
                    cout << "Prasau ivesti tik (1 - Taip), (0 - Ne), (2 - Nutraukti programa)" << endl << endl;
                    i--;
                }
            } else {
                cout << "Failas " << argv[i] << " neegzistuoja" << endl;
            }
        }
    }

    cout << "Aciu kad naudojotes Universalia Tiuringo Masina" << endl;

    return 0;
}

void VienaJuosta(string file) {
    ifstream df(file);
    vector<Taisykle> A;
    int GalvPoz, JuostSk;
    string Juost, DabrBus = "0";
    Taisykle temp;
    bool Rado;

    df >> JuostSk >> Juost >> GalvPoz;
    cout << Juost << endl;
    while (!df.eof()) {
        df >> temp.Bus >> temp.Sim >> temp.NaujSim >> temp.Krypt >> temp.NaujBus;
        A.push_back(temp);
    }

    while (true) {
        Rado = false;
        for (int i = 0; i < A.size(); i++) {
            if (A[i].Bus == DabrBus && A[i].Sim == Juost[GalvPoz - 1]) {
                NaujasSimbolis(A[i].NaujSim, Juost, GalvPoz);
                NaujaBusena(A[i].NaujBus, DabrBus);
                NaujaKryptis(A[i].Krypt, GalvPoz);

                system("Clear");
                cout << "Jei norite nutraukti " << file << " veikima, spauskite Esc" << endl;
                SpausdintiJuosta(Juost, GalvPoz);
                Rado = true;
            }
        }
        if (GalvPoz <= 0 || GalvPoz > Juost.length()) {
            system("Clear");
            NaujasSimbolis('_', Juost, GalvPoz);
            cout << "Galtvute isejo uz juostos ribu, programa sustabdyta" << endl;
            SpausdintiJuosta(Juost, GalvPoz);
            break;
        }
        if (!Rado) {
            system("Clear");
            SpausdintiJuosta(Juost, GalvPoz);
            cout << "Masina buvo sustabdyta, nes busena: " << DabrBus << " neturi taisykles." << endl << endl;
            break;
        }
        // Windows.h -> Only works on windows.
        // if (GetAsyncKeyState(VK_ESCAPE)) {
        //     cout << "Masinos veikimas buvo nutrauktas" << endl << endl;
        //     break;
        // }
        // Sleep(25);
    }
}

void DviJuostos(string file) {
    ifstream df(file);
    vector<Taisykle> A, B;
    int PirmGalvPoz, AntrGalvPoz, JuostSk;
    string PirmJuost, AntrJuost, PirmDabrBus = "0", AntrDabrBus = "0", TempBus, TempNaujBus;
    Taisykle PirmTemp, AntrTemp;
    bool RadoP, RadoA, PirmMem = false, AntrMem = false;

    df >> JuostSk >> PirmJuost >> AntrJuost >> PirmGalvPoz >> AntrGalvPoz;
    while (!df.eof()) {
        df >> TempBus >> PirmTemp.Sim >> AntrTemp.Sim >> PirmTemp.NaujSim >> AntrTemp.NaujSim >> PirmTemp.Krypt >>
        AntrTemp.Krypt >> TempNaujBus;

        PirmTemp.Bus.append(TempBus);
        AntrTemp.Bus.append(TempBus);
        PirmTemp.NaujBus.append(TempNaujBus);
        AntrTemp.NaujBus.append(TempNaujBus);

        A.push_back(PirmTemp);
        B.push_back(AntrTemp);

        PirmTemp.Bus.clear();
        AntrTemp.Bus.clear();
        PirmTemp.NaujBus.clear();
        AntrTemp.NaujBus.clear();
    }

    while (true) {
        RadoP = false; RadoA = false;
        system("Clear");
        cout << "Jei norite nutraukti " << file << " veikima, spauskite Esc" << endl;

        for (int i = 0; i < A.size(); i++) {
            if (A[i].Bus == PirmDabrBus && A[i].Sim == PirmJuost[PirmGalvPoz - 1] && !RadoP) {
                NaujasSimbolis(A[i].NaujSim, PirmJuost, PirmGalvPoz);
                NaujaBusena(A[i].NaujBus, PirmDabrBus);
                NaujaKryptis(A[i].Krypt, PirmGalvPoz);
                SpausdintiJuosta(PirmJuost, PirmGalvPoz);
                RadoP = true;
            }
            if (B[i].Bus == AntrDabrBus && B[i].Sim == AntrJuost[AntrGalvPoz - 1] && !RadoA) {
                NaujasSimbolis(B[i].NaujSim, AntrJuost, AntrGalvPoz);
                NaujaBusena(B[i].NaujBus, AntrDabrBus);
                NaujaKryptis(B[i].Krypt, AntrGalvPoz);
                SpausdintiJuosta(AntrJuost, AntrGalvPoz);
                RadoA = true;
            }
        }

        if (PirmGalvPoz <= 0 || PirmGalvPoz >= PirmJuost.length()) {
            NaujasSimbolis('_', PirmJuost, PirmGalvPoz);
            cout << "Pirmos juostos galtvute isejo uz juostos ribu, programa sustabdyta" << endl;
            SpausdintiJuosta(PirmJuost, PirmGalvPoz);
            PirmMem = true;
        }

        if (AntrGalvPoz <= 0 || AntrGalvPoz >= AntrJuost.length()) {
            NaujasSimbolis('_', AntrJuost, AntrGalvPoz);
            cout << "Antros juostos galtvute isejo uz juostos ribu, programa sustabdyta" << endl;
            SpausdintiJuosta(AntrJuost, AntrGalvPoz);
            AntrMem = true;
        }

        if (PirmMem && AntrMem) {
            system("Clear");
            SpausdintiJuosta(PirmJuost, PirmGalvPoz);
            cout << "Pirmos juostos galtvute isejo uz juostos ribu, programa sustabdyta" << endl;
            SpausdintiJuosta(AntrJuost, AntrGalvPoz);
            cout << "Antros juostos galtvute isejo uz juostos ribu, programa sustabdyta" << endl << endl;
            break;
        }

        if (!RadoP && !PirmMem) {
            SpausdintiJuosta(PirmJuost, PirmGalvPoz);
            cout << "Pirmos juostos masina buvo sustabdyta, nes busena: " << PirmDabrBus << " neturi taisykles." << endl;
        }

        if (!RadoA && !AntrMem) {
            SpausdintiJuosta(AntrJuost, AntrGalvPoz);
            cout << "Antros juostos masina buvo sustabdyta, nes busena: " << AntrDabrBus << " neturi taisykles." << endl;
        }

        if (!RadoP && !RadoA) {
            system("Clear");
            SpausdintiJuosta(PirmJuost, PirmGalvPoz);
            cout << "Pirmos juostos masina buvo sustabdyta, nes busena: " << PirmDabrBus << " neturi taisykles." << endl;
            SpausdintiJuosta(AntrJuost, AntrGalvPoz);
            cout << "Antros juostos masina buvo sustabdyta, nes busena: " << AntrDabrBus << " neturi taisykles." << endl << endl;
            break;
        } 
        // Windows.h -> Only works on windows.
        // if (GetAsyncKeyState(VK_ESCAPE)) {
        //     cout << "Masinos veikimas buvo nutrauktas" << endl << endl;
        //     break;
        // }
        // Sleep(25);
    }
}

void NaujasSimbolis(char NaujSim, string &Juosta, int &GalvPoz) {
    if (GalvPoz <= 0) {
        Juosta.insert(Juosta.begin(), NaujSim);
        GalvPoz++;
    } else if (GalvPoz > Juosta.length()) {
        Juosta.push_back(NaujSim);
    } else {
        Juosta[GalvPoz - 1] = NaujSim;
    }
}

void NaujaBusena(string NaujBus, string &DabrBus) {
    DabrBus = NaujBus;
}

void NaujaKryptis(char Krypt, int &GalvPoz) {
    if (Krypt == 'R') {
        GalvPoz++;
    }  else {
        GalvPoz--;
    }
}

void SpausdintiJuosta(string Juosta, int GalvPoz) {
    for (int i = 0; i < GalvPoz - 1; i++) {
        cout << Juosta[i];
    }
    cout << "[" << Juosta[GalvPoz - 1] << "]";
    for (int i = GalvPoz; i < Juosta.length() - 1; i++) {
        cout << Juosta[i];
    }
    cout << endl;
}