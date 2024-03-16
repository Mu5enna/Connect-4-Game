#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main(void) {

    int sira, oyuncu, sutun, count, srow, isutun, irow, idisc;
    int a, b, c, d, e, f, g, h, j, k, l, m;
    int kayitsorgu, siracont;

    cout << "----CONNECT--X----" << endl << endl;
    cout << "Start a New Game => '-4'" << endl << endl;
    cout << "Load Saved Game => '-8'" << endl << endl;
    cout << "Exit the Game => '-1'" << endl;
    cin >> kayitsorgu;
    system("cls");

    if (kayitsorgu == -1) {
        exit(EXIT_SUCCESS);
    }

    if (kayitsorgu == -4) {
        for (int ab = 1; ab < 2; ab++) {
            cout << "Enter the Column Size. (Can't Be Less Than 4!) ";
            cin >> isutun;
            cout << "Enter the Row Size. (Can't Be Less Than 4!) ";
            cin >> irow;
            cout << "Enter The Length of Discs That Need to Be Alongside to Win The Game ";
            cin >> idisc;

            if (isutun * irow < 16 || idisc > irow || idisc > isutun || idisc < 4) {
                ab--;
                system("cls");
                cout << "Invalid Size or Your Adjoining Disc Number is Higher Than Rows/Columns! Please Enter Again." << endl << endl;
            }
            else {
                continue;
            }
        }
        siracont = 0;
    }

    //--Dosyadan--Okuma--   
    else if (kayitsorgu == -8) {
        ifstream gdata;
        gdata.open("gamedata.txt");
        gdata >> sira >> isutun >> irow >> idisc;
        gdata.close();
        siracont = (sira + 1);
    }

    int** c4 = new int* [irow];
    for (int i = 0; i < irow; i++) {
        c4[i] = new int[isutun];
    }

    if (kayitsorgu == -8) {
        ifstream garray;
        garray.open("gamearray.txt");
        string value;
        for (int i = 0; i < irow; i++) {
            for (int k = 0; k < isutun; k++) {
                garray >> value;
                c4[i][k] = stoi(value); 
            }
        }
        garray.close();
    }

    else if (kayitsorgu == -4) {
        for (int i = 0; i < irow; i++) {
            for (int z = 0; z < isutun; z++) {
                c4[i][z] = 0;
            }
        }
    }

    int limit = isutun * irow;

    for (sira = siracont; sira <= limit; sira++) {

        //--Berabere--Olma--Durumu--
        if (sira == limit) {
            cout << "Draw!";
            exit(EXIT_SUCCESS);
        }

        //--Aktif--Oyuncuyu--Belirleme--
        if (sira % 2 == 0) {
            oyuncu = 1;
        }
        else {
            oyuncu = 2;
        }

        if (sira == siracont) {
            system("cls");
            cout << "Enter '-1' if You Want to Close the Aplication!" << endl << endl << endl;
            cout << "-------------CONNECT-" << idisc << "------------- " << endl << endl;
            for (l = 0; l < irow; l++) {
                for (m = 0; m < isutun; m++) {
                    cout << "| " << *(*(c4 + l) + m) << " |";
                }
                cout << endl << endl;
            }
        }
        cout << oyuncu << ". Player's Turn. Please Choose a Column to Place Your Disc." << endl;
        cin >> sutun;
        if (sutun == -1) {
            exit(EXIT_SUCCESS);
        }
        sutun--;
        //--Hamle--Geçerli--Ýse--
        if (*(*(c4 + 0) + sutun) == 0 && sutun < isutun && sutun >= 0) {
            for (srow = irow-1; srow >= 0; srow--) {
                if (*(*(c4 + srow) + sutun) == 0) {
                    *(*(c4 + srow) + sutun) = oyuncu;

                    //--Güncel--Tabloyu--Yazdýrma--
                    system("cls");
                    cout << "Enter '-1' if You Want to Close the Aplication!" << endl << endl << endl;
                    cout << "-------------CONNECT-" << idisc << "------------- " << endl << endl;
                    for (l = 0; l < irow; l++) {
                        for (m = 0; m < isutun; m++) {
                            cout << "| " << *(*(c4 + l) + m) << " |";
                        }
                        cout << endl << endl;
                    }

                    //--Yatay--Kontrol--
                    count = 0;
                    for (a = 0; a < isutun; a++) {
                        if (*(*(c4 + srow) + a) == oyuncu) {
                            count++;
                        }
                        else {
                            count = 0;
                        }
                        if (count >= idisc) {
                            cout << oyuncu << ". Player Won!";
                            exit(EXIT_SUCCESS);
                        }
                    }

                    //--Dikey--Kontrol--
                    count = 0;
                    for (b = srow; b < irow; b++) {
                        if (*(*(c4 + b) + sutun) == oyuncu) {
                            count++;
                        }
                        else {
                            break;
                        }
                        if (count >= idisc) {
                            cout << oyuncu << ". Player Won!";
                            exit(EXIT_SUCCESS);
                        }
                    }

                    //--Çapraz--Kontroller--

                    //--Saða--Yatýk--Kontrol--
                    count = 0;
                    for (c = srow, d = sutun; d < isutun && c >= 0; d++, c--) {
                        if (*(*(c4 + c) + d) == oyuncu) {
                            count++;
                        }
                        else {
                            break;
                        }
                    }
                    for (e = srow + 1, f = sutun - 1; f >= 0 && e < irow; f--, e++) {
                        if (*(*(c4 + e) + f) == oyuncu) {
                            count++;
                        }
                        else {
                            break;
                        }
                    }
                    if (count >= idisc) {
                        cout << oyuncu << ". Player Won!";
                        exit(EXIT_SUCCESS);
                    }

                    //--Sola--Yatýk--Kontrol--
                    count = 0;
                    for (g = srow, h = sutun; g >= 0 && h >= 0; g--, h--) {
                        if (*(*(c4 + g) + h) == oyuncu) {
                            count++;
                        }
                        else {
                            break;
                        }
                    }
                    for (j = srow + 1, k = sutun + 1; j < irow && k < isutun; k++, j++) {
                        if (*(*(c4 + j) + k) == oyuncu) {
                            count++;
                        }
                        else {
                            break;
                        }
                    }
                    if (count >= idisc) {
                        cout << oyuncu << ". Player Won!";
                        exit(EXIT_SUCCESS);
                    }
                    break;
                }
                else {
                    continue;
                }
            }
        }

        //--Hamle--Geçersiz--Ýse--
        else {
            cout << "Invalid Move. Please Choose a Valid Column!" << endl;
            sira--;
            continue;
        }

        //--Dosyaya--Yazma--
        ofstream gdata("gamedata.txt");
        gdata << sira << " " << isutun << " " << irow << " " << idisc;
        gdata.close();

        ofstream garray("gamearray.txt");
        for (int i = 0; i < irow; i++) {
            for (int k = 0; k < isutun; k++) {
                garray << to_string(*(*(c4 + i) + k)) << " ";
            }
        }
        garray.close();

    }

    for (int i = 0; i < irow; i++) {
        delete[] c4[i];
    }
    delete[] c4;

    return 0;
}