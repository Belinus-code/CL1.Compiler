#include <string>
#include <iostream>
using namespace std;

void formatAddressReg();
void setAddressReg(int aktuelleAdresse);
int getAdress(int relativeAdresse);

bool valueRequired = false;
bool adressRequired = false;
bool bruecke=false;
int addressReg[256];
int aktuelleAdr = 1;
bool errorFound = false;
bool isBinaryIn = false;
string seingabe;
string seingabeZeile;
string sword;
string szahl;
string scode;
string sbefehle[11][3] = //[x][0]: Befehl [x][1]: LC Code [x][2]: 1 = Wert, 2 = Adresse
{
  {"load","1","1"},
  {"move","2","0"},
  {"add","3","0"},
  {"mova","4","0"},
  {"jump","5","2"},
  {"compare","6","0"},
  {"jne","7","2"},
  {"movled","8","1"},
  {"sub","9","0"},
  {"loada","10","2"},
  {"val","11","1"}
};
string sErrorMeldung[2] =
{
    "Ganzzahliger Wert erwartet!","Ganzzahlige Adresse erwartet!"
};

int main()
{
    formatAddressReg();
    int ibefehlanzahl = (sizeof sbefehle / sizeof sbefehle[0][0])/3;
    cout << "Hier bitte Code einfuegen: ";
    bool isEnde = false;
    while (isEnde == false)
    {
        getline(cin, seingabeZeile);
        if (seingabeZeile == "end")isEnde = true;
        else
        {
            seingabe += seingabeZeile;
            seingabe += " ";
        }
    }
    cout << endl;
    scode += "0 ";
    for(int i = 0; i < seingabe.size(); i++)
    {
        string szeichen;
        szeichen += seingabe[i];
        if (szeichen != " " && valueRequired == true)
        {
            szahl += szeichen;
            if (szahl == "b")
            {
                isBinaryIn = true;
                szahl = "";
            }
            if (seingabe[i + 1] == ' ')
            {
                try
                {
                    int itest = stoi(szahl);
                }
                catch (...)
                {
                    cout << "Ein fehler in Zeile " << aktuelleAdr - 1 << " ist aufgetreten!" << endl;
                    cout << "Fehlermeldung: " << sErrorMeldung[0] << endl << endl;
                    errorFound = true;
                }
                valueRequired = false;
                if (isBinaryIn == true)scode += "0b";
                scode += szahl;
                scode += " ";
                szahl = "";
                setAddressReg(aktuelleAdr);
                isBinaryIn = false;
            }
            bruecke = true;
        }
        if (szeichen != " " && adressRequired == true)
        {
            szahl += szeichen;
            if (seingabe[i + 1] == ' ')
            {
                int iadresse;
                try
                {
                    iadresse = stoi(szahl);
                    scode += to_string(getAdress(iadresse));
                }
                catch(...)
                {
                    cout << "Ein fehler in Zeile " << aktuelleAdr -1 << " ist aufgetreten!" << endl;
                    cout << "Fehlermeldung: " << sErrorMeldung[1] << endl << endl;
                    errorFound = true;
                }

                
                scode += " ";
                adressRequired = false;
                bruecke = true;
                szahl = "";
                setAddressReg(aktuelleAdr);
            }
        }
        if (szeichen != " " && valueRequired == false && bruecke == false)
        {
            sword += szeichen;

            for (int x = 0; x < ibefehlanzahl; x++)
            {
                if (sword == sbefehle[x][0])
                {
                    scode += sbefehle[x][1];
                    scode += " ";
                    sword = "";
                    if (sbefehle[x][2] == "1")valueRequired = true;
                    if (sbefehle[x][2] == "2")adressRequired = true;
                    aktuelleAdr++;
                }
            }
        }
        bruecke = false;
    }
    if(errorFound == false)cout << scode << endl << endl;
    cout << "MaxVal: ";
    int maxVal;
    cin >> maxVal;
    for (int i = 1; i < maxVal; i++)
    {
        cout << "Absolute Adresse: " << i << " Relative Adresse: " << getAdress(i) << endl;
    }
    cout << "Beliebige Taste zum beenden druecken: ";
    string sende;
    cin >> sende;
}
void formatAddressReg()
{
    addressReg[0] = 0;
    for (int i = 1; i < 256; i++)
    {
        addressReg[i] = addressReg[i - 1] + 1;
    }
}
void setAddressReg(int aktuelleAdresse)
{
    addressReg[aktuelleAdresse] = addressReg[aktuelleAdresse]+1;
    for (int i = aktuelleAdresse+1; i < 256; i++)
    {
        addressReg[i] = addressReg[i - 1] + 1;
    }
}
int getAdress(int relativeAdresse)
{
    cout << "Relative Adresse: " << relativeAdresse << endl;
    return addressReg[relativeAdresse];
}
