#include<iostream>
#include <cstring>
#include<vector>
using namespace std;

class SetterGetterNume                     //interfata
{
public:
    virtual string getNume() const = 0;
    virtual void setNume(const string& nume) = 0;
    virtual ~SetterGetterNume() {}
};


class Artist: public SetterGetterNume
    {
    private:
        string nume;
        string nationalitate;

    public:
        //constructori
        Artist()          //fara parametri
        {
            this->nume = "";
            this->nationalitate= "";
        }
        Artist(string nume, string nationalitate)     //cu parametri
        {
            this->nume = nume;
            this->nationalitate= nationalitate;
        }

        string getNume() const override        //verifica că semnăturile metodei din clasa derivată
                                               //sunt identice cu cele ale metodei virtuale din clasa de bază
            {
            return nume;
            }

        void setNume(const std::string& nume) override
            {
            this->nume = nume;
            }
    ~Artist() {}
    };


class Exponat                 //clasa de baza abstracta
{
    protected:
        string titlu;
        int an_finisare;
    public:
    Exponat(string t, int y) : titlu(t), an_finisare(y) {}
    virtual string get_descriere() const = 0;
    virtual ~Exponat() {}
};


class Material
{
protected:
    string material;
public:
    Material()
    {
        this->material="";
    }
    Material(string material)
    {
        this->material=material;
    }
    string getMaterial() const            //getter pentru nume
            {
                return material;
            }
};


class ExceptiePicturaExistenta : public exception
{
   public:
    const char* what() const throw()
    {
        return "Pictura exista deja in galerie!";
    }
};


class ExceptiePicturaInvalida : public exception
{
public:
    const char* what() const throw()
    {
        return "Pictura introdusa este invalida.";
    }
};

class Pictura: public Exponat, public Material
    {
    private:
        Artist artist;
    public:
        //constructor
        Pictura(string titlu, Artist artist, int an_finisare, string material)
        : Exponat(titlu, an_finisare), Material(material), artist(artist) {}

        //setter, gette
        string getTitlu() const                            //getter pentru nume pictura
            {
                return titlu;
            }
        Artist getArtist() const                           //getter pentru artist
            {
             return artist;
            }
        string getMaterial() const                          //getter pentru tehnica
            {
                return material;
            }

        //afisarea datelor prin supraincarcarea operatorului <<
        friend ostream & operator << (ostream & out , const Pictura &pict)
        {
            out <<"Nume pictura: " << pict.titlu  << endl;
            out <<"Nume artist: " << pict.artist.getNume() << endl;
            out << "Tehnica: " << pict.material << endl;
            out << "An finisare pictura: " << pict.an_finisare << endl;
            return out;
        }


        //supraincarcarea operatorului =
        void operator= (const Pictura& p)
            {
                this->titlu = p.titlu;
                this->artist = p.artist;
                this->material = p.material;
                this->an_finisare = p.an_finisare;
            }

        string get_descriere() const override    //apelam clasa de baza abstracta
        {
           return "Pictura '" + titlu + "', realizata de " + getArtist().getNume();
        }
        ~Pictura(){}
    };


class Sculptura: public Exponat, public Material
{
    private:
    Artist artist;
    public:
      Sculptura(string titlu, Artist artist, int an_finisare, string material)
        : Exponat(titlu, an_finisare), Material(material), artist(artist){}

    string getTitlu() const
    {
        return titlu;
    }

    Artist getArtist() const
    {
        return artist;
    }

    string getMaterial() const
    {
        return material;
    }

    friend ostream & operator << (ostream & out , const Sculptura &sculpt)
    {
        out <<"Nume sculptura: " << sculpt.titlu  << endl;
        out <<"Nume artist: " << sculpt.artist.getNume() << endl;
        out << "Material: " << sculpt.material << endl;
        out << "An finisare sculptura: " << sculpt.an_finisare << endl;
        return out;
    }

     string get_descriere() const override             //suprascriere
    {
        return "Sculptura " + titlu + ", realizata din " + material;
    }
    ~Sculptura(){}
};


class Vizitator
    {
    protected:                           //date de tip protected
        string nume;
        string statut_vizitator;             //elev, student, pensionar
        int varsta;
        Artist artist_preferat;
        vector<Pictura*> picturi_cumparate_;
    public:
        //constructori
        Vizitator()                           ///constructor fara parametri
            {
                this->nume = "";
                this->statut_vizitator = "";
                this->varsta = 0;
            }
        Vizitator(string nume, string statut_vizitator, int varsta, Artist artist_preferat)      //cu parametri
            {
                this->nume = nume;
                this->varsta = varsta;
                this->artist_preferat = artist_preferat;
                try{
                    if(statut_vizitator!="elev" && statut_vizitator!="student" && statut_vizitator!="pensionar" && statut_vizitator!="vizitator")
                        throw "Vizitatorul nu are un statut valid.";
                    else
                        this->statut_vizitator=statut_vizitator;
                }
                catch(const char* eroare){
                    cout<<eroare<<endl;
                }
            }

        //settteri, getter

        void setVarstaVizitator (int varsta)                //setter pentru adresa de mail
            {
                this ->varsta = varsta;
            }
        void setStatutVizitator (string statut_vizitator)    //setter pentru statut vizitator
            {
                this -> statut_vizitator = statut_vizitator;
            }
        string getStatutVizitator() const            //getter pentru statut vizitator
            {
                return statut_vizitator;
            }
        string getNume() const            //getter pentru nume
            {
                return nume;
            }

        protected:       //functie pe care o apelam in clasa derivata
        void afiseaza_picturi(vector<Pictura*> picturi_cumparate_)
         {
            for (int i = 0; i < picturi_cumparate_.size(); i++)
                cout << picturi_cumparate_[i] -> getTitlu()<<endl;
            cout<<endl;
        }

    };


class Cumparator : protected Vizitator
{
    private:
        vector<Pictura*> picturi_cumparate_;
    public:
    //constructori - folosesc constructorii clasei de baza
    Cumparator():Vizitator(){}
    Cumparator(string nume, string statut_vizitator, int varsta, Artist artist_preferat) : Vizitator(nume, statut_vizitator, varsta, artist_preferat) {}

    //functie care adauga picturi in vectorul de picturi cumparate al cumparatorului
     void adaugaPicturaCumparata(Pictura* pictura)
     {
        picturi_cumparate_.push_back(pictura);
     }

     void afiseaza_picturi_cumparate()
     {
        afiseaza_picturi(picturi_cumparate_);      //apelam functia din clasa de baza
     }

     string getNume() const            //getter pentru nume - pentru ca vizitator e protected
     {
        return nume;
     }
};


class Bilet
    {
    private:
        int nr_bilet_emis;
        double pret;
        Vizitator vizitator;

    public:
        //constructori
        Bilet()                           ///constructor fara parametri
            {
                this->nr_bilet_emis = 0;
                this->pret = 0;
            }
         Bilet( int nr_bilet_emis, double pret, Vizitator vizitator)   //constructor cu parametri
            {
                this->nr_bilet_emis = nr_bilet_emis;
                this->vizitator = vizitator;
                try{                                    //try-catch
                if(pret<=0) throw "Pretul biletului nu este corect";
                else this -> pret = pret;
                }
                catch(const char* eroare)
                    {
                        cout<<endl<<eroare<<endl;
                        throw;
                    }
            }

        //getter, setter
        void setPretBilet (double pret)    //setter pentru pret bilet
            {
               this->pret = pret;
            }

        //functie de ,,logica de business" - se aplica reducere pretului in functie de statutul vizitatorului (elev, student, pensionar)
        void Reducere (Vizitator viz)
        {
            if(viz.getStatutVizitator()=="elev")  this -> pret = pret/3;
            else if (viz.getStatutVizitator()=="student" || viz.getStatutVizitator()=="pensionar") this -> pret = pret/2;
            else this -> pret = pret;
        }

        //afisare prin supraincarcarea operatorului <<
         friend ostream & operator << (ostream & out , const Bilet &bilet)
        {
            out <<"Numar bilet emis: " << bilet.nr_bilet_emis  << endl;
            out <<"Statut vizitator: " << bilet.vizitator.getStatutVizitator() << endl;
            out << "Pret: " << bilet.pret<< endl;
            return out;
        }

        //constructor de copiere
        Bilet(const Bilet & ob)
            {
                this -> nr_bilet_emis = ob.nr_bilet_emis;
                this -> pret = ob.pret;
                this -> vizitator = ob.vizitator;
            }

        //supraincarcarea operatorului =
        void operator= (const Bilet& b)
            {
                this -> nr_bilet_emis = b.nr_bilet_emis;
                this -> pret = b.pret;
                this -> vizitator = b.vizitator;
            }
    };


class Galerie
{
    private:
        string nume_galerie;
        vector<Pictura*> colectie_picturi;
        static int numarPicturi;           //variabila statica
        static int id_pictura;

    public:
        //adauga picturi la baza de date a galeriei doar daca nu se regaseste in picturile deja adaugate
        void addPictura(Pictura* pictura)
        {
            for (int i = 0; i < colectie_picturi.size(); i++)
                if (colectie_picturi[i] -> getTitlu() == pictura -> getTitlu())
                    throw ExceptiePicturaExistenta();                 //exceptie custom

            if (pictura->getTitlu().empty())
            {
            throw ExceptiePicturaInvalida();
            }
            colectie_picturi.push_back(pictura);
            ++numarPicturi;
        }

        void stergerePictura(Pictura* p)          //try-catch
        {
        try {
            int ok=0, i;
            for ( i = 0; i < colectie_picturi.size(); i++)
                if (colectie_picturi[i] -> getTitlu() == p -> getTitlu())
                   {ok=1;               //verificam daca pictura este in galerie
                   break;
                   }
            if (ok==0)
            throw "Pictura pe care vrem sa o stergem nu exista in galerie.";
            else
                {colectie_picturi.erase(colectie_picturi.begin() + i);
                 numarPicturi--;
                }
            }
        catch (const char* eroare)
            {
            cout<<endl<<eroare<<endl;
            }
        }


        //functie de afisare a picturilor si atributelor lor
        void listaPicturi()
        {
            for (int i = 0; i < colectie_picturi.size(); i++)
            {
                ++id_pictura;
                implementID();
                cout<< colectie_picturi[i] -> getTitlu() << ", " << colectie_picturi[i] -> getArtist().getNume() << ", " << colectie_picturi[i] -> getMaterial()<<endl;
            }
        }
        static int getNumarPicturi()      //getter pentru nr_picturi - metoda statica
        {
        return numarPicturi;
        }

        static int implementID()          //metoda statica
        {
            cout<<id_pictura<<':';
        }

};

int Galerie::numarPicturi = 0;
int Galerie::id_pictura = 0;

int main()
{
    Galerie galerie;

    Artist artist1("Vincent van Gogh", "neerlandez");
    Artist artist2("Leonardo da Vinci", "italian");
    Artist artist3("Salvador Dali", "spaniol");

    Pictura* pictura1 = new Pictura ("Starry Night", artist1, 1889,  "Ulei pe panza");
    Pictura* pictura2 = new Pictura ("Mona Lisa", artist2, 1503, "Ulei pe lemn");
    Pictura* pictura3 = new Pictura ("The Persistence of Memory", artist3, 1931, "Ulei pe panza");
    Pictura* pictura4 = new Pictura ("Irises", artist1, 1889, "Ulei pe panza");
    Pictura* pictura5 = new Pictura ("", artist1, 1889, "Ulei pe panza");

    try{                                       //try-catch care re-arunca un alt tip de excepție din blocul catch
    galerie.addPictura(pictura1);
    galerie.addPictura(pictura2);
    galerie.addPictura(pictura3);
    galerie.stergerePictura(pictura2);
    //galerie.addPictura(pictura5);
    } catch (const ExceptiePicturaExistenta& e) {
        cout << "Exceptie: " << e.what() << endl;
        throw;
    } catch (const ExceptiePicturaInvalida& e) {
        cout << "Exceptie: " << e.what() << endl;
        throw;
    }

    cout<<"Lista picturilor din galerie:"<<endl;
    galerie.listaPicturi(); //afiseaza lista cu picturile si atributele lor
    cout<<"Numarul de picturi din galerie: "<<Galerie::getNumarPicturi()<<endl;   //folosind static int


    Vizitator vizitator1 ("Ana", "elev", 14, artist2);
    Vizitator vizitator2 ("Mihai", "student", 23, artist1);
    Vizitator vizitator3 ("Andrei", "vizitator", 46, artist2);
    Cumparator vizitator4 ("Andreea", "pensionar", 82, artist3);
    Cumparator vizitator5 ("Bogdan", "vizitator", 30, artist1);

    //nu putem realiza vectorul de picturi decat pentru variabilele de tip cumparator
    vizitator4.adaugaPicturaCumparata(pictura3);
    vizitator4.adaugaPicturaCumparata(pictura4);
    cout<<endl<<"Picturi cumparate de "<<vizitator4.getNume()<<":"<<endl;
    vizitator4.afiseaza_picturi_cumparate();

    //upcasting
    cout<<"Cele mai apreciate picturi:"<<endl;
    vector <Exponat*> expozitie;
    expozitie.push_back(pictura1);         //upcasting intre Pictura și Exponat în momentul
                                           //creării unui vector de obiecte de tip Exponat
    expozitie.push_back(pictura3);
    for (int i=0; i<expozitie.size(); i++)
        cout<<expozitie[i]->get_descriere() << endl;  //upcasting -se invocă metoda get_descriere()
    cout<<endl;                                                //a clasei Exponat pentru un obiect de tip Pictura:


    cout<<"Sculptor cunoscut:"<<endl;
    SetterGetterNume* sn = new Artist("Michelangelo", "italian");  //upcasting -pointer de tip sg*
                                                                 //pentru a referi un obiect de tip Artist
    cout << sn->getNume() << endl;

    cout<<"Cea mai cunoscuta sculptura a sa:"<<endl;
    Exponat* e = new Sculptura("David", Artist("Michelangelo Buonarroti", "italian"), 1504, "marmura");
    cout << e->get_descriere() << endl; //upcasting - se invocă metoda get_descriere() a clasei Exponat
                                        //pentru un obiect de tip Sculptura

    Pictura* creatie_noua= dynamic_cast<Pictura*>(e);    //downcasting
    if(creatie_noua!=NULL)
        cout<<"Adaugam lucrarea la expozitia de picturi";
    else cout<< "Creatia nu este o pictura, deci nu o putem adauga la galeria de picturi";

    delete pictura1;
    delete pictura2;
    delete pictura3;
    delete pictura4;
    delete pictura5;
    delete e;
    delete sn;
    return 0;
}
