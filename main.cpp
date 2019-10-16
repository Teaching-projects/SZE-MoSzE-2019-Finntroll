#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <string>
#ifdef _WIN32
    #include "stdafx.h"
    #include <windows.h>   
#endif


using namespace std;

struct filesystem{
    string nev, dir;
    filesystem *kov;
};

filesystem *listaLetrehoz(){
    filesystem *eleje = NULL;
    return eleje;
}

filesystem *hozzaAd(filesystem *eleje, string nev, string dir){
    filesystem *mozgo, *uj;
    uj = new filesystem;
    uj->nev = nev;
    uj->dir = dir;
    uj->kov = NULL;
    if(eleje == NULL){
        return uj;
    }
    for(mozgo = eleje; mozgo->kov != NULL; mozgo = mozgo->kov){
        ;
    }
    mozgo->kov = uj;
    return eleje;
}

void felszabadit(filesystem *lista){
    while(lista != NULL){
        filesystem *kov = lista->kov;
        delete(lista);
        lista = kov;
    }
}

void kiIr(filesystem *lista, string actualdir){
    filesystem *iter;
    int counter = 0;
    for(iter = lista; iter != NULL; iter = iter->kov){
        if(iter->dir == actualdir){
            cout << "\033[1;32m\t" + iter->nev + "\033[0m\n";
            counter++;
        }
    }
    if(counter == 0){
        cout << "Nincsen megjeleníthető mappa/fájl! :( \n";
    }
}

string & keres(filesystem *lista, string parancs, string & actualdir){
    filesystem *iter;
    int counter = 0;
    if (parancs == "cd"){
        cout << "Navigálás a gyökérkönyvtárba...\n";
        actualdir = "/";
        return actualdir;
    }
    string tempparancs  = parancs.erase(0,3);

    if(tempparancs.at(0) != '/'){
        if(actualdir != "/"){
            tempparancs.insert(0, "/");
        }
        tempparancs.insert(0,actualdir);
    }
    else tempparancs;

    //tempparancs.insert(0,"/");
    //cout << tempparancs << "\n";

    for(iter = lista; iter != NULL; iter = iter->kov){
        string tempdir = iter->nev;
        if(iter->dir.size() > 1){
            tempdir.insert(0,"/");
        }
        tempdir.insert(0,iter->dir);
        //cout << tempdir;
        if(tempdir == tempparancs){
            counter++;
        }
    }
    if(counter > 0){
        actualdir = tempparancs;
        //cout << "Sikeres a kereses!\n";
    }
    else if(tempparancs.size() == 1){
        actualdir =tempparancs;
    }
    else cout << "Nincsen ilyen mappa!\n";

    return actualdir;
}

int main(int argc, char** argv) {
    #ifdef _WIN32
        setlocale(LC_ALL, "");
        system("Color F");
        SetConsoleCP(1250);
        SetConsoleOutputCP(1250);
    #endif
    cout << "Ez a program mappakezelésre szolgál.\n";
    cout << "Ezek a parancsok elérhetőek: ls, mkdir, cd <elérési út>, cd ..\n";
    cout << "Kilépés a q karatkerre.\n\n";
    int i = 0, counter = 0;
    filesystem *fs = listaLetrehoz();
    string parancs;
    string actualdir = "/";
    while (parancs != "q"){
        //cout << "[cppfilemanager@localhost " + actualdir + "] # ";
        cout <<"\033[1;31m[root@cppfilemanager " << actualdir << "] # \033[0m";
        getline (cin, parancs);
        if(parancs == "q"){
            cout << "Kilépéshez nyomjon egy ENTER-t...";
        }
        else{
            //cout << "\033[1;32m" + parancs + "\033[0m\n";
            if(parancs == "ls"){
                counter = 0;
                kiIr(fs, actualdir);
            }
            else if(parancs == "cd .."){
                //cout << actualdir.size(); 1 hosszú
                if(actualdir.size() == 1);
                else actualdir.erase(actualdir.find_last_of("/"));
                if(actualdir.size() == 0){
                    actualdir = "/";
                }
            }
            else if(!parancs.find("cd")){
//                actualdir = parancs.erase(0,3);
//                actualdir.insert(0,"/");
                keres(fs, parancs, actualdir);
            }
            //if(parancs == "mkdir"){
            else if(!parancs.find("mkdir")){
                if(parancs.size() > 6){
                fs = hozzaAd(fs,parancs.erase(0,6),actualdir);
                }else cout << "Hibás mappaneved adott meg a mappa létrehozásához!\nPróbálja meg újra!\n";
            }
            else cout << "Ismeretlen parancs! Kérem a fent megadott parancsokat használja!\n";
        }
    }
    felszabadit(fs);
    getchar();
    return 0;
}
