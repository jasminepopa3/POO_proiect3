#include <iostream>
#include <cstring>
#include <vector>
#include <string>
#include <exception>
#include <memory>
#include <algorithm>

using namespace std;



//implementez propria mea exceptie
class ArtistNotInExhibitionException : public std::exception {
private:
    std::string nume_artist;
public:
    ArtistNotInExhibitionException(const std::string& artistName) : nume_artist(artistName) {}
    const char* what() const noexcept override {
        return ("Artist " + nume_artist + " is not in the exhibition.").c_str();
    }
};


//------------------------------------------------------------------------------------------------------------------------------------

class IOInterface {
public:
    virtual istream& read(istream& in) = 0;
    virtual ostream& write(ostream& out) const = 0;
    // clasa abstracta + metoda constanta
};

//-----------------------------------------------------------------------------------------------------------------------------------------------------

class Perioada: public IOInterface
{
protected:
    char* data_inc;
    char* data_fin;

public:
    Perioada(); //constructor fara param
    Perioada(char* data_inc, char* data_fin); //constructor cu param
    Perioada(const Perioada& P1); //copy constructor
    Perioada& operator = (const Perioada& P1); //supraincarcarea opertaorului egal
    ~Perioada(); //destructor

    //getters
    char* getdata_inc();
    char* getdata_fin();

    //setters
    void setdata_inc(char* data_inc);
    void setdata_fin(char* data_fin);

    //citire si afisare
    friend istream& operator>>(istream& in, Perioada& P1);
    friend ostream& operator<< (ostream& out, const Perioada& P1);

    istream& read(istream& in);
    ostream& write(ostream& out) const;

};

char* Perioada::getdata_inc() {return this->data_inc;}
char* Perioada::getdata_fin() {return this->data_fin;}

void Perioada::setdata_inc(char* data_inc)
{
    if(this->data_inc!=NULL)
        delete[] this->data_inc;
    this->data_inc=new char[strlen(data_inc)+1];
    strcpy(this->data_inc,data_inc);
}

void Perioada::setdata_fin(char* data_fin)
{
    if(this->data_fin!=NULL)
        delete[] this->data_fin;
    this->data_fin=new char[strlen(data_fin)+1];
    strcpy(this->data_fin,data_fin);
}

Perioada::Perioada()
{
    this->data_inc = new char [strlen("01/01/1900")+1];
    strcpy(this->data_inc, "01/01/1900");

    this->data_fin = new char [strlen("12/04/1976")+1];
    strcpy(this->data_fin, "12/04/1976");
}

Perioada::Perioada(char* data_inc, char* data_fin)
{
    this->data_inc = new char [strlen(data_inc)+1];
    strcpy(this->data_inc, data_inc);

    this->data_fin = new char [strlen(data_fin)+1];
    strcpy(this->data_fin, data_fin);

}

Perioada::Perioada(const Perioada& P1)
{
    this->data_inc = new char [strlen(P1.data_inc)+1];
    strcpy(this->data_inc, P1.data_inc);

    this->data_fin = new char [strlen(P1.data_fin)+1];
    strcpy(this->data_fin, P1.data_fin);

}

Perioada& Perioada::operator= (const Perioada& P1)
{
    if( this!= &P1 )
    {
        if( this->data_inc != NULL)
            delete[] this->data_inc;

        if( this->data_fin != NULL)
            delete[] this->data_fin;

        this->data_inc = new char [strlen(P1.data_inc)+1];
        strcpy(this->data_inc, P1.data_inc);

        this->data_fin = new char [strlen(P1.data_fin)+1];
        strcpy(this->data_fin, P1.data_fin);

    }

    return* this;

}

Perioada::~Perioada()
{
    if( this->data_inc != NULL)
        delete[] this->data_inc;

    if( this->data_fin != NULL)
        delete[] this->data_fin;
}

istream& Perioada::read(istream& in)
{
    char a[101], b[101];
    in>>a>>b;

    if(this->data_inc!=NULL)
        delete[] this->data_inc;

    if(this->data_fin!=NULL)
        delete[] this->data_fin;

    this->data_inc = new char[strlen(a)+1];
    this->data_fin = new char[strlen(b)+1];

    strcpy(this->data_inc, a);
    strcpy(this->data_fin, b);

    return in;
}

istream& operator>>(istream& in, Perioada& P1)
{
    return P1.read(in);
}

ostream& Perioada::write(ostream& out)const
{
     out<<this->data_inc<<" "<<this->data_fin;

    return out;
}

ostream& operator<< (ostream& out, const Perioada& P1)
{
   return P1.write(out);
}

//---------------------------------------------------------------------------------------------------------------------------------------


class Curent_artistic: public IOInterface
{
protected:
    char* denumire;
    Perioada perioada_desfasurarii;

public:
    Curent_artistic();
    Curent_artistic(char* denumire, Perioada perioada_desfasurarii);
    Curent_artistic(const Curent_artistic& C1); //copy constructor
    Curent_artistic& operator = (const Curent_artistic& C1); //supraincarcarea operatorului egal
    ~Curent_artistic(); //destructor

    //getters
    char* getdenumire();

    //setters
    void setdenumire(char* denumire);

    //citire si afisare
    friend istream& operator>>(istream& in, Curent_artistic& C1);
    friend ostream& operator<< (ostream& out, const Curent_artistic& C1);

    istream& read(istream& in);
    ostream& write(ostream& out) const;

};

char* Curent_artistic::getdenumire() {return this->denumire;}

void Curent_artistic::setdenumire(char* denumire)
{
    if(this->denumire!=NULL)
        delete[] this->denumire;
    this->denumire=new char[strlen(denumire)+1];
    strcpy(this->denumire,denumire);
}

Curent_artistic::Curent_artistic()
{
    this->denumire = new char[strlen("curent anonim")+1];
    strcpy(this->denumire,"curent anonim");

    this->perioada_desfasurarii;
}

Curent_artistic::Curent_artistic(char* denumire, Perioada perioada_desfasurarii)
{
    this->denumire = new char[strlen(denumire)+1];
    strcpy(this->denumire,denumire);

    this->perioada_desfasurarii=perioada_desfasurarii;
}

Curent_artistic::Curent_artistic(const Curent_artistic& C1)
{
    this->denumire = new char[strlen(C1.denumire)+1];
    strcpy(this->denumire,C1.denumire);

    this->perioada_desfasurarii=C1.perioada_desfasurarii;
}

Curent_artistic& Curent_artistic::operator= (const Curent_artistic& C1)
{
    if(this != &C1)
    {
        if(this->denumire!=NULL)
            delete[] this->denumire;

        this->denumire = new char[strlen(C1.denumire)+1];
        strcpy(this->denumire,C1.denumire);

        this->perioada_desfasurarii=C1.perioada_desfasurarii;

    }

    return* this;
}

Curent_artistic::~Curent_artistic()
{
    if(this->denumire!=NULL)
        delete[] this->denumire;

}


istream& Curent_artistic::read(istream& in)
{
    char a[100];
    in>>a;

    if(this->denumire!=NULL)
        delete[] this->denumire;


    this->denumire = new char[strlen(a)+1];
    strcpy(this->denumire, a);

    in>>this->perioada_desfasurarii;

    return in;
}

istream& operator>>(istream& in, Curent_artistic& C1)
{
    return C1.read(in);
}



ostream& Curent_artistic::write(ostream& out)const
{
    out<<this->denumire<<" "<<this->perioada_desfasurarii;

    return out;
}

ostream& operator<< (ostream& out, const Curent_artistic& C1)
{
    return C1.write(out);
}

//--------------------------------------------------------------------------------------------------------------------------------------------


class Artist: public IOInterface
{
protected:
    char* nume;
    char* prenume;
    const int ID_artist;
    static int contorArtist;
    bool in_viata;
    Curent_artistic curent_aderent;
    Perioada perioada_vietii;

public:
    Artist(); //constructor fara parametrii
    Artist(char* nume, char* prenume, bool in_viata); //constructor cu mai multi parametrii
    Artist(char* nume, char* prenume, bool in_viata, Curent_artistic curent_aderent, Perioada perioada_vietii); //constructor cu toti
    Artist(const Artist& A1); //copy constructor
    Artist& operator = (const Artist& A1); //supraincarcarea operatorului egal
    ~Artist(); //destructor

    //getters
    char* getnume();
    char* getprenume();
    bool getin_viata();
    const int getID_artist();
    static int getcontorArtist();

    //setters
    void setnume(char* nume);
    void setprenume(char* prenume);
    void setin_viata(bool in_viata);

    //citire/afisare
    friend istream& operator>>(istream& in, Artist& A1);
    friend ostream& operator<< (ostream& out, const Artist& A1);

    istream& read(istream& in);
    ostream& write(ostream& out) const;

    //2 metode statice (una care sa foloseasca data membru statica)

    static void afisare_contor_artist() {
        cout << "Numarul total de artisti: " << contorArtist << endl;
    }

    static void set_contor(int val) {
    contorArtist = val;
    }




};

char* Artist::getnume(){return this->nume;}
char* Artist::getprenume(){return this->prenume;}
bool Artist::getin_viata(){return this->in_viata;}
const int Artist::getID_artist(){return this->ID_artist;}
int Artist::getcontorArtist(){return contorArtist;}


void Artist::setnume(char* nume)
{
    if(this->nume!=NULL)
        delete[] this->nume;
    this->nume=new char[strlen(nume)+1];
    strcpy(this->nume,nume);
}

void Artist::setprenume(char* prenume)
{
    if(this->prenume!=NULL)
        delete[] this->prenume;
    this->prenume=new char[strlen(prenume)+1];
    strcpy(this->prenume,prenume);
}

void Artist::setin_viata(bool in_viata)
{
    this->in_viata=in_viata;
}


int Artist::contorArtist=1000;

Artist::Artist():ID_artist(contorArtist++)
{
    this->nume = new char[strlen("fara nume")+1];
    strcpy(this->nume,"fara nume");

    this->prenume = new char[strlen("fara prenume")+1];
    strcpy(this->prenume,"fara prenume");

    this->in_viata=0;

    this->curent_aderent;

    this->perioada_vietii;

}

Artist::Artist(char* nume, char* prenume, bool in_viata):ID_artist(contorArtist++)
{
    this->nume = new char[strlen(nume)+1];
    strcpy(this->nume,nume);

    this->prenume = new char[strlen(prenume)+1];
    strcpy(this->prenume,prenume);

    this->in_viata=in_viata;

    this->curent_aderent;

    this->perioada_vietii;
}

Artist::Artist(char* nume, char* prenume, bool in_viata, Curent_artistic curent_aderent, Perioada perioada_vietii):ID_artist(contorArtist++)
{
    this->nume = new char[strlen(nume)+1];
    strcpy(this->nume,nume);

    this->prenume = new char[strlen(prenume)+1];
    strcpy(this->prenume,prenume);

    this->in_viata=in_viata;

    this->curent_aderent=curent_aderent;

    this->perioada_vietii=perioada_vietii;
}

Artist::Artist(const Artist& A1):ID_artist(A1.ID_artist)
{
    this->nume = new char[strlen(A1.nume)+1];
    strcpy(this->nume,A1.nume);

    this->prenume = new char[strlen(A1.prenume)+1];
    strcpy(this->prenume,A1.prenume);

    this->perioada_vietii=A1.perioada_vietii;

    this->in_viata=A1.in_viata;

    this->curent_aderent=A1.curent_aderent;
}

Artist& Artist::operator= (const Artist& A1)
{
    if(this != &A1)
    {
        if(this->nume!=NULL)
            delete[] this->nume;

        this->nume = new char[strlen(A1.nume)+1];
        strcpy(this->nume,A1.nume);

        if(this->prenume!=NULL)
            delete[] this->prenume;

        this->prenume = new char[strlen(A1.prenume)+1];
        strcpy(this->prenume,A1.prenume);

        this->in_viata=A1.in_viata;

        this->perioada_vietii=A1.perioada_vietii;

        this->curent_aderent=A1.curent_aderent;

    }

    return* this;
}

Artist::~Artist()
{
    if(this->nume!=NULL)
        delete[] this->nume;
    if(this->prenume!=NULL)
        delete[] this->prenume;

}

istream& Artist::read(istream& in)
{
    char a[100],b[100];
    in>>a>>b;

    if(this->nume!=NULL)
        delete[] this->nume;

    this->nume = new char[strlen(a)+1];
    strcpy(this->nume, a);

    if(this->prenume!=NULL)
        delete[] this->prenume;

    this->prenume = new char[strlen(b)+1];
    strcpy(this->prenume, b);

    in>>this->in_viata>>this->curent_aderent>>this->perioada_vietii;

    return in;
}


istream& operator>>(istream& in, Artist& A1)
{
    return A1.read(in);
}

ostream& Artist::write(ostream& out)const
{
    out<<"Artistul se numeste "<<this->nume<<" "<<this->prenume<<" "<<endl<<"El este in viata? "<<this->in_viata<<" "<<endl<<"ID-ul lui este "<<this->ID_artist<<" "<<endl<<"El adera la curentul "<<this->curent_aderent<<" "<<endl<<"A trait in perioada "<<this->perioada_vietii<<endl;

    return out;
}


ostream& operator<< (ostream& out, const Artist& A1)
{
    return A1.write(out);
}


//------------------------------------------------------------------------------------------------------------------------------------------

class Exponat: public IOInterface
{
protected:
    char* denumire;
    int anul_aparitiei;
    const int ID_exponat;
    static int contorExpo;
    Artist artist_exponat;
    Curent_artistic curent;

public:
    Exponat(); //constructor fara parametrii
    Exponat(char* denumire, int anul_aparitiei, const int ID_exponat, Artist artist_exponat, Curent_artistic curent);
    Exponat(const Exponat& E); //copy constructor
    Exponat& operator = (const Exponat& E); //supraincarcarea operatorului egal
    ~Exponat(); //destructor

    //getters
    int getanul_aparitiei()const;
    const int getID_exponat() const;

    //setters
    void setdenumire(char* denumire);
    void setanul_aparitiei(int anul_aparitiei);

    //citire/afisare
    friend istream& operator>>(istream& in, Exponat& E);
    friend ostream& operator<< (ostream& out, const Exponat& E);

    istream& read(istream& in);
    ostream& write(ostream& out) const;

    //metode
    bool exponate_dupa1900();
};

const int Exponat::getID_exponat()const {return this->ID_exponat;}
int Exponat::getanul_aparitiei()const {return anul_aparitiei;}

void Exponat::setdenumire(char* denumire)
{
    if(this->denumire!=NULL)
        delete[] this->denumire;
    this->denumire=new char[strlen(denumire)+1];
    strcpy(this->denumire,denumire);
}

void Exponat::setanul_aparitiei(int anul_aparitiei)
{
    this->anul_aparitiei=anul_aparitiei;
}


int Exponat::contorExpo=2000;

Exponat::Exponat():ID_exponat(contorExpo++)
{
    this->denumire = new char[strlen("fara denumire")+1];
    strcpy(this->denumire,"fara denumire");

    this->anul_aparitiei=0;

    this->artist_exponat;

    this->curent;

}

Exponat::Exponat(char* denumire, int anul_aparitiei, const int ID_exponat, Artist artist_exponat, Curent_artistic curent):ID_exponat(contorExpo++)
{
    this->denumire = new char[strlen(denumire)+1];
    strcpy(this->denumire,denumire);

    this->anul_aparitiei=anul_aparitiei;

    this->artist_exponat=artist_exponat;

    this->curent=curent;
}

Exponat::Exponat(const Exponat& E):ID_exponat(E.ID_exponat)
{
    this->denumire = new char[strlen(E.denumire)+1];
    strcpy(this->denumire,E.denumire);

    this->artist_exponat=E.artist_exponat;

    this->anul_aparitiei=E.anul_aparitiei;

    this->curent=E.curent;
}

Exponat& Exponat::operator= (const Exponat& E)
{
    if(this != &E)
    {
        if(this->denumire!=NULL)
            delete[] this->denumire;

        this->denumire = new char[strlen(E.denumire)+1];
        strcpy(this->denumire,E.denumire);


        this->artist_exponat=E.artist_exponat;

        this->anul_aparitiei=E.anul_aparitiei;

        this->curent=E.curent;

    }

    return* this;
}

istream& Exponat::read(istream& in)
{
    char a[100];
    in>>a;

    if(this->denumire!=NULL)
        delete[] this->denumire;

    this->denumire = new char[strlen(a)+1];
    strcpy(this->denumire, a);

    in>>this->anul_aparitiei>>this->artist_exponat>>this->curent;

    return in;
}


istream& operator>>(istream& in, Exponat& E)
{
    return E.read(in);

}

ostream& Exponat::write(ostream& out) const
{
    out<<this->denumire<<" "<<this->anul_aparitiei<<" "<<this->ID_exponat<<" "<<this->artist_exponat<<" "<<this->curent;

    return out;
}

ostream& operator<< (ostream& out, const Exponat& E)
{
    return E.write(out);
}

Exponat::~Exponat()
{
    if(this->denumire!=NULL)
        delete[] this->denumire;

}


bool Exponat::exponate_dupa1900()
{
    if(this->anul_aparitiei>2023)  //exceptie 2
        throw std::logic_error("Un exponat nu poate fi aparut dupa anul curent.");
    else
       if(this->anul_aparitiei>1900)
         return true;
       else
         return false;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

class interfata_expozitie //asta e o interfata
{
public:
    //aici am 2/4 metode virtuale pe care le voi suprascrie
    virtual void mesaj_expozitie_dupa_nrArtisti() = 0;
    virtual void afiseaza_rezumat() = 0;

    virtual ~interfata_expozitie() {}

};


//-------------------------------------------------------------------------------------------------------------------------------


class Angajat: public IOInterface
{
protected:
    std::unique_ptr<char[]> nume;
    std::unique_ptr<char[]> prenume;
    std::unique_ptr<int[]> shifts;
    float day;
    float salariu;

    const int ID_angajat;
    static int contorId_angajat;

public:
    Angajat();

    Angajat(const Angajat& a); //copy constructor
    Angajat& operator = (Angajat a); //supraincarcarea operatorului egal
    ~Angajat() = default; //destructor is automatically generated by the compiler

    Angajat(const char* nume, const char* prenume, const int* shifts, float day, float salariu); //constructor

    float valoare() const {
        return this->salariu;
    }

    friend ostream& operator<<(ostream&, const Angajat& p);
    friend istream& operator>>(istream&, Angajat& p);

    istream& read(istream& in);
    ostream& write(ostream& out) const;
};

int Angajat::contorId_angajat=3000;

Angajat::Angajat():ID_angajat(contorId_angajat++)
{
    nume = std::make_unique<char[]>(strlen("Nume")+1);
    strcpy(nume.get(),"Nume");

    prenume = std::make_unique<char[]>(strlen("Prenume")+1);
    strcpy(prenume.get(),"Prenume");

    shifts = std::make_unique<int[]>(8);
    for(int i=1;i<=7;i++)
        shifts[i]=0;

    this->day=0;
    this->salariu=0;
}

Angajat::Angajat(const char* nume, const char* prenume, const int* shifts, float day, float salariu):ID_angajat(contorId_angajat++)
{
    this->nume = std::make_unique<char[]>(strlen(nume)+1);
    strcpy(this->nume.get(), nume);

    this->prenume = std::make_unique<char[]>(strlen(prenume)+1);
    strcpy(this->prenume.get(), prenume);

    this->shifts = std::make_unique<int[]>(8);
    for(int i=1; i<=7; i++)
        this->shifts[i] = shifts[i];

    this->day = day;
    this->salariu = salariu;
}

Angajat::Angajat(const Angajat& p):ID_angajat(contorId_angajat++)
{
    nume = std::make_unique<char[]>(strlen(p.nume.get())+1);
    strcpy(nume.get(), p.nume.get());

    prenume = std::make_unique<char[]>(strlen(p.prenume.get())+1);
    strcpy(prenume.get(), p.prenume.get());

    shifts = std::make_unique<int[]>(8);
    for(int i=1; i<=7; i++)
        shifts[i] = p.shifts[i];

    this->day=p.day;
    this->salariu=p.salariu;
}

Angajat& Angajat::operator= (Angajat p)
{
    std::swap(nume, p.nume);
    std::swap(prenume, p.prenume);
    std::swap(shifts, p.shifts);
    day = p.day;
    salariu = p.salariu;

    return *this;
}

istream& Angajat::read(istream& in)
{
    char a[100],b[100];
    in>>a>>b;

    nume = std::make_unique<char[]>(strlen(a)+1);
    strcpy(nume.get(),a);

    prenume = std::make_unique<char[]>(strlen(b)+1);
    strcpy(prenume.get(),b);

    shifts = std::make_unique<int[]>(8);
    for(int i=1; i<=7; i++)
        in>>shifts[i];

    in>>this->day>>this->salariu;

    return in;
}

istream& operator>>(istream& in, Angajat& ex)
{
    return ex.read(in);
}


ostream& Angajat::write(ostream& out)const
{
   out<<nume.get()<<" "<<prenume.get()<<" "<<this->day<<" "<<this->salariu<<" ";
    for(int i=1;i<=7;i++)
        out<<shifts[i]<<" ";

    return out;
}

ostream& operator<<(ostream& out, const Angajat& ex)
{
    return ex.write(out);
}


//-------------------------------------------------------------------------------------------------------------------------------------------------

class Expozitie: public IOInterface  //clasa de baza abstracta ptc am metode pur virtuale
{
protected:
    char* denumire;
    Curent_artistic curent;
    int nrArtisti;
    Artist* artisti_expusi;
    Perioada perioada_desfasurarii_expozitiei;
    vector<shared_ptr<Angajat>> angajati;
        //metode
    void detalii_Artisti();

public:
    Expozitie();
    Expozitie(char* denumire, Curent_artistic curent, int nrArtisti, Artist* artisti_expusi, Perioada perioada_desfasurarii_expozitiei);
    Expozitie(const Expozitie& ex); //copy constructor
    Expozitie& operator = (const Expozitie& ex); //supraincarcarea operatorului egal

    void adauga_angajat(shared_ptr<Angajat> angajat) {
            angajati.push_back(angajat);
        }
    void elimina_angajati() {
        angajati.clear();
    }
    const vector<shared_ptr<Angajat>>& get_angajati() const {
        return angajati;
    }

    ~Expozitie(); //destructor

    //getter
    int getnrArtisti();

    //citire/afisare
    friend istream& operator>>(istream& in, Expozitie& ex);
    friend ostream& operator<< (ostream& out, const Expozitie& ex);

    istream& read(istream& in);
    ostream& write(ostream& out) const;

    //aici am celelalte 2/4 metode virtuale pure pe care o sa le implementam in clasele copil
     virtual void adauga_artist(Artist& a) = 0;
     virtual void elimina_artist(int index) = 0;

     //metoda publica care o sa ma ajute sa apelez metoda protejata din clasa derivata
     virtual void public_detaliiArtisti(){
         detalii_Artisti();
     }



};

int Expozitie::getnrArtisti()
{
    return this->nrArtisti;
}

Expozitie::Expozitie()
{
    this->denumire = new char[strlen("fara denumire")+1];
    strcpy(this->denumire,"fara denumire");

    this->curent;

    this->nrArtisti=0;

    this->artisti_expusi=NULL;

    this->perioada_desfasurarii_expozitiei;

}

Expozitie::Expozitie(char* denumire, Curent_artistic curent, int nrArtisti, Artist* artisti_expusi, Perioada perioada_desfasurarii_expozitiei)
{
    this->denumire = new char[strlen(denumire)+1];
    strcpy(this->denumire,denumire);

    this->curent=curent;

    this->nrArtisti=nrArtisti;

    this->artisti_expusi= new Artist[nrArtisti+1];
    for(int i=0;i<nrArtisti;i++)
        this->artisti_expusi[i]=artisti_expusi[i];

    this->perioada_desfasurarii_expozitiei=perioada_desfasurarii_expozitiei;
}


Expozitie::Expozitie(const Expozitie& ex)
{
    this->denumire = new char[strlen(ex.denumire)+1];
    strcpy(this->denumire,ex.denumire);

    this->curent=ex.curent;

    this->nrArtisti=ex.nrArtisti;

    this->artisti_expusi= new Artist[nrArtisti+1];
    for(int i=0;i<=nrArtisti;i++)
        artisti_expusi[i]=ex.artisti_expusi[i];

    this->perioada_desfasurarii_expozitiei=ex.perioada_desfasurarii_expozitiei;
}

Expozitie& Expozitie::operator= (const Expozitie& ex)
{
    if(this != &ex)
    {
        if(this->denumire!=NULL)
            delete[] this->denumire;

        this->denumire = new char[strlen(ex.denumire)+1];
        strcpy(this->denumire,ex.denumire);

        this->curent=ex.curent;

        this->nrArtisti=ex.nrArtisti;

        if(this->artisti_expusi!=NULL)
            delete[] this->artisti_expusi;

        this->artisti_expusi= new Artist[nrArtisti+1];
        for(int i=0;i<=nrArtisti;i++)
             artisti_expusi[i]=ex.artisti_expusi[i];

        this->perioada_desfasurarii_expozitiei=ex.perioada_desfasurarii_expozitiei;

    }

    return* this;
}

Expozitie::~Expozitie()
{
    if(this->denumire!=NULL)
        delete[] this->denumire;

    if(this->artisti_expusi!=NULL)
        delete[] this->artisti_expusi;

}

istream& Expozitie::read(istream& in)
{
    char a[100];
    in>>a;

    if(this->denumire!=NULL)
        delete[] this->denumire;


    in>>this->curent>>this->nrArtisti;

    this->artisti_expusi = new Artist[this->nrArtisti+1];
    for(int i=0;i<this->nrArtisti;i++)
        in>>this->artisti_expusi[i];

    in>>this->perioada_desfasurarii_expozitiei;

    return in;
}

istream& operator>>(istream& in, Expozitie& ex)
{
    return ex.read(in);
}

ostream& Expozitie::write(ostream& out)const
{
    out<<"Expozitia "<<this->denumire<<" "<<"apartine curentului "<<this->curent<<" "<<" si are expusi "<<this->nrArtisti<<" artisti."<<endl<<"Expozitia se va desfasura in perioada: "<<this->perioada_desfasurarii_expozitiei<<". Aceasta este lista artistilor expusi: "<<endl<<endl;
    for(int i=0;i<this->nrArtisti;i++)
        out<<this->artisti_expusi[i]<<endl;
    out<<endl;


    return out;
}

ostream& operator<< (ostream& out, const Expozitie& ex)
{
    return ex.write(out);
}

void Expozitie::detalii_Artisti()
{
    for(int i=0;i<this->nrArtisti;i++)
        cout<<this->artisti_expusi[i].getnume()<<" "<<this->artisti_expusi[i].getprenume()<<endl;
}



//mostenire public 1 ---------------------------------------------------------------------------------------------------------------------

class Expozitie_virtuala: public Expozitie, public interfata_expozitie
{
protected:
    int nr_sectiuni;
    vector<string> sectiuni;
public:
    Expozitie_virtuala(char* denumire, Curent_artistic curent, int nrArtisti, Artist* artisti_expusi, Perioada perioada_desfasurarii_expozitiei, int nr_sectiuni, vector<string> sectiuni);
    ~Expozitie_virtuala(){};

    //metoda specifica pt try-catch
    //const Artist& cauta_artist(const std::string& nume) const {
      //  for (const auto& artist : artisti_expusi) {
        //    if (artist.nume() == nume) {
          //      return artist;
           // }
        //}
        //throw ArtistNotFoundException(nume);
    //}


    std::string getNume() const {
    return this->denumire;
    }




    //metoda specifica + exceptie 1
    void medie_artisti_sectiune()
    {
        if(nrArtisti==0)
            throw std::invalid_argument("Nu poti face impartire la 0.");
        else
            cout<<nr_sectiuni/nrArtisti;
    }

    //suprascrierea celor 4 metode virtuale

    void mesaj_expozitie_dupa_nrArtisti() override
    {
        if(nrArtisti<0)  //exceptie 3
            throw std::logic_error("Nu poate exista o expozitie cu nr negativ de artisti.");
        else
          if (nrArtisti > 10)
            cout << "Aceasta expozitie are un numar mare de artisti!" << endl;
          else
            cout << "Aceasta expozitie are un numar mic de artisti." << endl;

    }

    void adauga_artist(Artist& a) override
    {
        Artist* artisti_nou = new Artist[nrArtisti + 1]; // alocare memorie pentru un nou vector cu un element în plus
        for (int i = 0; i < nrArtisti; i++) {
            artisti_nou[i] = artisti_expusi[i]; // copierea vechilor artiști în noul vector
        }
        artisti_nou[nrArtisti] = a; // adăugarea noului artist la finalul vectorului
        nrArtisti++; // incrementarea numărului de artiști
        delete[] artisti_expusi; // eliberarea memoriei vechiului vector
        artisti_expusi = artisti_nou; // asignarea noului vector
    }


    void elimina_artist(int index) override
{
    if (index < 0 || index >= nrArtisti) {
        cout << "Index invalid!" << endl;
        return;
    }
    Artist* artisti_nou = new Artist[nrArtisti - 1]; // alocare memorie pentru un nou vector cu un element în minus
    for (int i = 0; i < index; i++) {
        artisti_nou[i] = artisti_expusi[i]; // copierea artiștilor anteriori indexului în noul vector
    }
    for (int i = index + 1; i < nrArtisti; i++) {
        artisti_nou[i - 1] = artisti_expusi[i]; // copierea artiștilor de după index în noul vector
    }
    nrArtisti--; // decrementarea numărului de artiști
    delete[] artisti_expusi; // eliberarea memoriei vechiului vector
    artisti_expusi = artisti_nou; // asignarea noului vector
}


    void afiseaza_rezumat() override
{
    cout<<"Pe scurt, expozitia "<<denumire<<" va avea loc in perioada "<<perioada_desfasurarii_expozitiei<<" si va expune "<<nrArtisti<<" artisti din curentul "<<curent<<endl;
}


  //suprascrierea metodei pt a apela metoda protected
  void public_detaliiArtisti()
  {
      detalii_Artisti();
  }

};


//constructorul care folosește o listă de inițializare pentru a apela constructorul clasei de bază

 Expozitie_virtuala::Expozitie_virtuala(char* denumire, Curent_artistic curent, int nrArtisti, Artist* artisti_expusi, Perioada perioada_desfasurarii_expozitiei, int nr_sectiuni, vector<string> sectiuni):Expozitie(denumire, curent, nrArtisti, artisti_expusi, perioada_desfasurarii_expozitiei)
{
    this->nr_sectiuni=nr_sectiuni;
    for(int i=0;i<nr_sectiuni;i++)
        this->sectiuni.push_back(sectiuni[i]);
}



//mostenire public2 ---------------------------------------------------------------------------------------------------------------------

class Expozitie_ghidata: public virtual Expozitie, public interfata_expozitie
{
protected:
    string nume_ghid;
    float pret;
public:
    Expozitie_ghidata(char* denumire, Curent_artistic curent, int nrArtisti, Artist* artisti_expusi, Perioada perioada_desfasurarii_expozitiei, string nume_ghid, float pret);
    ~Expozitie_ghidata(){};

    void adauga_angajat(shared_ptr<Angajat> angajat) {
            angajati.push_back(angajat);
        }
    void elimina_angajati() {
        angajati.clear();
    }
    const vector<shared_ptr<Angajat>>& get_angajati() const {
        return angajati;
    }

    //suprascrierea celor 4 metode virtuale

    void mesaj_expozitie_dupa_nrArtisti() override
    {
        if (nrArtisti > 10) {
            cout << "Aceasta expozitie are un numar mare de artisti!" << endl;
        } else {
            cout << "Aceasta expozitie are un numar mic de artisti." << endl;
        }
    }

    void adauga_artist(Artist& a) override
    {
        Artist* artisti_nou = new Artist[nrArtisti + 1]; // alocare memorie pentru un nou vector cu un element în plus
        for (int i = 0; i < nrArtisti; i++) {
            artisti_nou[i] = artisti_expusi[i]; // copierea vechilor artiști în noul vector
        }
        artisti_nou[nrArtisti] = a; // adăugarea noului artist la finalul vectorului
        nrArtisti++; // incrementarea numărului de artiști
        delete[] artisti_expusi; // eliberarea memoriei vechiului vector
        artisti_expusi = artisti_nou; // asignarea noului vector
    }


    void elimina_artist(int index) override
{
    if (index < 0 || index >= nrArtisti) {
        cout << "Index invalid!" << endl;
        return;
    }
    Artist* artisti_nou = new Artist[nrArtisti - 1]; // alocare memorie pentru un nou vector cu un element în minus
    for (int i = 0; i < index; i++) {
        artisti_nou[i] = artisti_expusi[i]; // copierea artiștilor anteriori indexului în noul vector
    }
    for (int i = index + 1; i < nrArtisti; i++) {
        artisti_nou[i - 1] = artisti_expusi[i]; // copierea artiștilor de după index în noul vector
    }
    nrArtisti--; // decrementarea numărului de artiști
    delete[] artisti_expusi; // eliberarea memoriei vechiului vector
    artisti_expusi = artisti_nou; // asignarea noului vector
}


    void afiseaza_rezumat() override
{
    cout<<"Pe scurt, expozitia "<<denumire<<" va avea loc in perioada "<<perioada_desfasurarii_expozitiei<<" si va expune "<<nrArtisti<<" artisti din curentul "<<curent<<endl;
}
};

 Expozitie_ghidata::Expozitie_ghidata(char* denumire, Curent_artistic curent, int nrArtisti, Artist* artisti_expusi, Perioada perioada_desfasurarii_expozitiei, string nume_ghid, float pret):Expozitie(denumire, curent, nrArtisti, artisti_expusi, perioada_desfasurarii_expozitiei)
{
    this->nume_ghid=nume_ghid;
    this->pret=pret;
}

//mostenire protected, mostenire multipla, mostenire diamant ---------------------------------------------------------------------------

class Expozitie_virtuala_ghidata: protected virtual Expozitie_virtuala, protected virtual Expozitie_ghidata
{
protected:
    int durata;
    int nr_limbi_posibile;
    vector<string> limbi_posibile;
public:
    Expozitie_virtuala_ghidata(char* denumire, Curent_artistic curent, int nrArtisti, Artist* artisti_expusi, Perioada perioada_desfasurarii_expozitiei, int nr_sectiuni, vector<string> sectiuni, string nume_ghid, float pret, int durata, int nr_limbi_posibile, vector<string>limbi_posibile);
    ~Expozitie_virtuala_ghidata(){};

    //metoda specifica
    void mesaj_dupa_limbi_vorbite()
    {
        if(nr_limbi_posibile<=0)  //exceptie 4
            throw std::logic_error("Nu poate exista o expozitie ghidata in care sa nu se vorbeasca.");
        else
          if (nr_limbi_posibile > 3)
            cout << "Aceasta expozitie poate fi ascultata in multe limbi straine!" << endl;
          else
            cout << "Aceasta expozitie nu poate fi ascultata in prea multe limbi straine." << endl;
    }

};



Expozitie_virtuala_ghidata::Expozitie_virtuala_ghidata(char* denumire, Curent_artistic curent, int nrArtisti, Artist* artisti_expusi, Perioada perioada_desfasurarii_expozitiei, int nr_sectiuni, vector<string> sectiuni, string nume_ghid, float pret, int durata, int nr_limbi_posibile, vector<string>limbi_posibile):Expozitie(denumire, curent, nrArtisti, artisti_expusi, perioada_desfasurarii_expozitiei), Expozitie_virtuala(denumire, curent, nrArtisti, artisti_expusi, perioada_desfasurarii_expozitiei, nr_sectiuni, sectiuni), Expozitie_ghidata(denumire, curent, nrArtisti, artisti_expusi, perioada_desfasurarii_expozitiei,nume_ghid, pret)
{
    this->durata=durata;
    this->nr_limbi_posibile=nr_limbi_posibile;
    for(int i=0;i<nr_limbi_posibile;i++)
        this->limbi_posibile.push_back(limbi_posibile[i]);
}







//un try catch in care se reproceseaza eroare si se arunca o alta eroare -exceptie 4
void apelare_exceptie4()
{

   Perioada p2("10/11/2000","10/05/2009");
   Curent_artistic c("simbolism",p2);
   vector<string> sectiuni1={"sectiunea1","sectiunea2"};
   Artist artisti_expusi[3]={Artist("Van","Gogh",0,c,p2),Artist("Van","Gogh",0,c,p2)};

   try {
       vector<string> limbi2;
    Expozitie_virtuala_ghidata expozitie("expoooo",c,2,artisti_expusi,p2,2,sectiuni1,"ana",12,1,0,limbi2);
    expozitie.mesaj_dupa_limbi_vorbite();
} catch (const std::invalid_argument& e) {
    std::cerr << "Exceptie prinsa: " << e.what() << '\n';
} catch (const std::logic_error& e) {
    std::cerr << "Exceptie prinsa: " << e.what() << '\n';
    throw std::runtime_error("Nu s-a putut afisa mesajul despre limbi vorbite.");
} catch (...) {
    std::cerr << "Exceptie neprevazuta prinsa\n";
}


}


//aici fac un try-catch pt logic_error -exceptie 2
void apelare_exceptie2()
{

    Perioada p2("10/11/2000","10/05/2009");
    Curent_artistic c("simbolism",p2);
    Artist a("Van","Gogh",0,c,p2);
    Exponat exponat1("un exponat",2060,1012,a,c);
    cout<<exponat1<<endl<<endl<<endl;

    try {
          bool rezultat = exponat1.exponate_dupa1900(); // apelăm funcția și încercăm să obținem rezultatul
          std::cout << "Exponatul a fost creat dupa 1900: " << (rezultat ? "da" : "nu") << std::endl;
  }
    catch (const std::logic_error& e) { // prindem excepția de tip logic_error și afișăm mesajul de eroare
        std::cerr << "Eroare: " << e.what() << std::endl;
  }
}



//functie sablon ---------------------------------------------
//funcția poate fi utilizată cu orice clasă care are o metodă valoare() care returnează un număr.

template <typename T>
T minim(const std::vector<T>& elemente) {
    if (elemente.empty()) {
        throw std::invalid_argument("Vectorul nu poate fi gol.");
    }

    T minim = elemente[0];
    for (const T& elem : elemente) {
        if (elem.valoare() < minim.valoare()) {
            minim = elem;
        }
    }

    return minim;
}
template <>
Exponat minim(const std::vector<Exponat>& v) {
    Exponat minExponat = v[0];

    for (const Exponat& exponat : v) {
        if (exponat.getanul_aparitiei() < minExponat.getanul_aparitiei()) {
            minExponat = exponat;
        }
    }

    return minExponat;
}



//clasa sablon
template <typename T>
class Interschimbare {
public:
    static void schimba(T& a, T& b) {
        T temp = a;
        a = b;
        b = temp;
    }
};



int main()
{
    //1.functia sablon cu care vad in lista de angajati ala cu salariu min
    int shifts[8] = {0, 1, 2, 3, 4, 5, 6, 7};  // presupunem aceste ture pentru fiecare angajat
    Angajat angajat1("Popescu", "Ion", shifts, 8.0, 2000.0);
    Angajat angajat2("Ionescu", "Maria", shifts, 8.0, 2500.0);
    Angajat angajat3("Georgescu", "Vasile", shifts, 8.0, 2200.0);

    std::vector<Angajat> angajati;
    angajati.push_back(angajat1);
    angajati.push_back(angajat2);
    angajati.push_back(angajat3);

    Angajat angajat_minim = minim(angajati);

    std::cout << angajat_minim;


    //2.functia sablon specializata - exponatul cel mai vechi
    Perioada p("11/11/1899","10/12/1905");
    Perioada p2("10/11/2000","10/05/2009");
    cout<<"Perioada este "<<p<<" si "<<p2<<endl<<endl;
    Curent_artistic c("simbolism",p);
    cout<<"Curentul artistic este "<<c<<endl<<endl;

    Artist artist("Van","Gogh",0,c,p);
    Curent_artistic curent("simbolism",p);
    Exponat exponat1("Exponat1", 1900, 1, artist, curent);
    Exponat exponat2("Exponat2", 1920, 2, artist, curent);
    Exponat exponat3("Exponat3", 1910, 3, artist, curent);

    std::vector<Exponat> vectorExponate;
    vectorExponate.push_back(exponat1);
    vectorExponate.push_back(exponat2);
    vectorExponate.push_back(exponat3);

    Exponat exponat_minim = minim(vectorExponate);

    std::cout << exponat_minim;


    //3.clasa sablon
    //interschimbare int
    int x = 5, y = 10;
    Interschimbare<int>::schimba(x, y);
    cout << "x = " << x << ", y = " << y << endl;  // Va afisa: x = 10, y = 5

    cout<<endl<<endl;

    //de ex, vr sa sortez vectorul de exponate dupa vechime (sortare prin selectie)
    //ma folosesc de clasa sablon interschimbare si de functia sablon minim
    int n = vectorExponate.size();
    for (int i = 0; i < n - 1; i++) {
        int pozitieMin = i;
        for (int j = i + 1; j < n; j++) {
             if (vectorExponate[j].getanul_aparitiei() < vectorExponate[pozitieMin].getanul_aparitiei()) {
                      pozitieMin = j;
                 }
        }
        Interschimbare<Exponat>::schimba(vectorExponate[i], vectorExponate[pozitieMin]);
    }

    for (Exponat& exponat : vectorExponate) {
        cout << exponat << endl;
    }





    //2. shared_ptr

    Expozitie_ghidata expo1("Expo1", c, 5 /*nrArtisti*/, nullptr /*artisti_expusi*/, Perioada("01-05-2023", "31-05-2023"),"Andrei",17.5);
    Expozitie_ghidata expo2("Expo2", c, 3 /*nrArtisti*/, nullptr /*artisti_expusi*/, Perioada("01-06-2023", "30-06-2023"),"Mihai", 14.0);


    int shiftss[7] = {1, 0, 1, 0, 1, 0, 1};  // Exemplu de schimburi
    auto angajat = make_shared<Angajat>("Gigel", "Popescu", shiftss, 5 /*day*/, 3000 /*salariu*/);

    expo1.adauga_angajat(angajat);
    expo2.adauga_angajat(angajat);

    expo1.elimina_angajati();

    if (!expo2.get_angajati().empty()) {
    cout << *expo2.get_angajati()[0] << endl;
}




    //3. sort/find

    std::sort(vectorExponate.begin(), vectorExponate.end(), [](const Exponat& e1, const Exponat& e2) {
        return e1.getanul_aparitiei() < e2.getanul_aparitiei();
    });


    int idCautat = 123;
    auto it = std::find_if(vectorExponate.begin(), vectorExponate.end(), [idCautat](const Exponat& e) {
        return e.getID_exponat() == idCautat;
    });

    if (it != vectorExponate.end()) {
        cout<<"Exponatul a fost găsit";
        Exponat exponatGasit = *it;
    } else {
        cout<<"Exponatul nu a fost găsit";
    }












   Artist artisti_expusi[3]={Artist("Van","Gogh",0,c,p),Artist("Van","Gogh",0,c,p)};


   //am initializat constructorul clasei care mosteneste
   vector<string> sectiuni1={"sectiunea1","sectiunea2"};
   Expozitie_virtuala e_virt("iernii",c,2,artisti_expusi,p2,2,sectiuni1);
   cout<<e_virt;


   vector<string> limbi_posibile={"romana","engleza","franceza","italiana"};
   Expozitie_virtuala_ghidata e_virt_ghid("prin muzeu, online cu Marius",c,2,artisti_expusi,p2,2,sectiuni1,"marius toader",8.55,1,4,limbi_posibile);



   //avem deja creat un obiect de tipul expozitie_virtuala
   //acum cream un pointer la interfata si ii atribuim adresa obiectului
   interfata_expozitie* ptr = &e_virt;
   //apelam metode din interfata cu ajutorul pointerului
   ptr->afiseaza_rezumat();
   ptr->mesaj_expozitie_dupa_nrArtisti();
   //dezalocam obiectul folosind apelul la destructorul virtual din interfata
   delete ptr;
   cout<<endl;


       //apelez metoda protejata
    e_virt.public_detaliiArtisti();


    //cele 2 blocuri try-catch
    apelare_exceptie4();
    apelare_exceptie2();



   //polimorfism la executie 1 si 2
   //Polimorfismul la execuție (dynamic dispatch) este un concept din programarea orientată pe obiecte care se referă la
   //capacitatea unei clase derivate de a suprascrie și
   //de a furniza propria implementare pentru metodele virtuale definite în clasa de bază.

   Expozitie* exp = &e_virt; // crearea unui pointer de tip Expozitie initializat cu un obiect de tip Expozitie_virtuala
   Artist a2("Van","Gogh",0,c,p); // crearea unui obiect de tip Artist
   exp->adauga_artist(a2); // apelul metodei adauga_artist prin intermediul pointerului de tip Expozitie
   exp->elimina_artist(1);
   delete exp; // stergerea pointerului de tip Expozitie


   //polimorfism la executie 3 si 4

   Expozitie_ghidata e_ghid("expo cu Andrei",c,2,artisti_expusi,p2,"Andrei",15.5);
   Expozitie* ptr2=&e_ghid;
   Artist a3("Claude","Monet",0,c,p);
   ptr2->adauga_artist(a3);
   ptr2->elimina_artist(1);
   delete ptr;


   //upcasting 1 si 2 -se poate converti o instanță a unei clase derivate la clasa de bază din ierarhia de moștenire.
   Expozitie_virtuala ev("inca o expo",c,2,artisti_expusi,p2,2,sectiuni1);
   Expozitie* ePtr = &ev;
   ePtr->adauga_artist(a2); // apelare metoda din clasa de baza
   ePtr->elimina_artist(1);

   //upcasting 3 si 4
   Expozitie_ghidata eg("alta ghidata",c,2,artisti_expusi,p2,"alexandra",14.5);
   Expozitie* ePtr2 = &eg;
   ePtr2->adauga_artist(a2); // apelare metoda din clasa de baza
   ePtr2->elimina_artist(1);




   //downcasting - o instanță a clasei Expozitie_virtuala și un pointer la clasa de bază Expozitie, vr sa accesez metoda specifica de la Expozitie_virtuala
   Expozitie* expozitie_ptr=&e_virt;
   Expozitie_virtuala* expozitie_virtuala_ptr = dynamic_cast<Expozitie_virtuala*>(expozitie_ptr);
   if (expozitie_virtuala_ptr != nullptr)
    {
      expozitie_virtuala_ptr->medie_artisti_sectiune();
    }




    return 0;
}
