#include<iostream>
#include <cstring>
using namespace std;

class String
{
  private:
    char* sir;
   
  public:
    //constructori
    String()                     //fara parametri
     {
        size_t len =0;
        sir = new char[0];
    }

    String(const char* str)      //cu parametri
     {
        size_t len = strlen(str);
        sir = new char[len + 1];
        strcpy(sir, str);
    }

    // destructor pentru eliberarea memoriei
    ~String() {
        delete[] sir;
    }

    // constructor de copiere
    String(const String& ob) {
        size_t len = strlen(ob.sir);
        sir = new char[len + 1];
        strcpy(sir, ob.sir);
    }

    // supraincarcare '='
    String& operator=(const String& ob) {
        if (this != &ob) {
            delete[] sir;
            size_t len = strlen(ob.sir);
            sir = new char[len + 1];
            strcpy(sir, ob.sir);
        }
        return *this;
    }

    //supraincaracare '<<'
     friend std::ostream& operator<<(std::ostream& out, const String& s) {
        out << s.sir;
        return out;
    }

    //supraincarcare '=='
    friend bool operator==(const String& op1, const String& op2) {
        return strcmp(op1.sir, op2.sir) == 0;
    }
};


template<typename Pictura>
class Vector 
{
  private:
    int marime;
    int nr_max_elem;
    Pictura* pict;

  public:
    //constructor
    Vector() 
    {
        this ->marime = 0;
        this ->nr_max_elem=0;
        this ->pict = new Pictura[nr_max_elem];
    }
    //destructor
    ~Vector()
    {
        delete[] pict;
    }

    // implementarea push_back-ului - adauga la final obiectul si dubleaza capacitatea vectorului daca e cazul
    void push_back(const Pictura& valoare) 
    {
        if (marime == nr_max_elem) 
            {
            nr_max_elem *= 2;
            Pictura* pict_nou = new Pictura[nr_max_elem];
            for (int i=0; i<marime; i++)
                pict_nou[i] = pict[i];
            delete[] pict;
            pict = pict_nou;
            }
        pict[marime++] = valoare;
    }

    //prin metodele operator[] putem accesa elementele vectorului dupa index
    const Pictura& operator[](int index) const
     {
        return pict[index];
     }


    Pictura& operator[](int index)
     {
        return pict[index];
     }

    //functia size - returneaza lungimea vectorului
    int size() const 
    {
        return marime;
    }
};


class Perioada_artistica
    {
    private:
        String denumire;
        int an_inceput;
        int an_final;
    public:
        //constructori
        Perioada_artistica()          //fara parametri
        {
            this->denumire = "";
            this->an_inceput= 0;
            this->an_final= 0;
        }
        Perioada_artistica(String denumire, int an_inceput, int an_final)          //cu parametri
        {
            this->denumire = denumire;
            this->an_inceput= an_inceput;
            this->an_final= an_final;
        }
       
        //getter
        String getDenumire() const             //getter pentru nume perioada artistica
            {
                return denumire;
            }
    };


class Artist
    {
    private:
        String nume;
        String nationalitate;

    public:
        //constructori
        Artist()          //fara parametri
        {
            this->nume = "";
            this->nationalitate= "";
        }
        Artist(String nume, String nationalitate)     //cu parametri
        {      
            this->nume = nume;
            this->nationalitate= nationalitate;
        }

        //getter
        String getNume() const               //getter pentru nume artist
            {
                return nume;
            }
    };


class Pictura
    {
    private:
        String* titlu;
        Artist artist;
        Perioada_artistica perioada_artistica;
        String* tehnica;
        int an_finisare;  

    public:
        //constructori
        Pictura()                           ///constructor fara parametri
            {
                this->titlu = new String();
                this->tehnica = new String();
                this->an_finisare = 0;
            }
        Pictura(String titlu, Artist artist, Perioada_artistica perioada_artistica, String tehnica, int an_finisare)   //constructor cu parametri
            {
                this->titlu = new String(titlu);         //alocare dinamica
                this->artist = artist;
                this->perioada_artistica=perioada_artistica;
                this->tehnica = new String(tehnica);    //alocare dinamica
                this->an_finisare = an_finisare;
            }
       
         //eliberarea memoriei
        ~Pictura()
        {
            delete titlu;
            delete tehnica;
        }

        //setter, getter
        String getTitlu() const                            //getter pentru nume pictura
            {
                return *titlu;
            } 
        Artist getArtist() const                           //getter pentru artist
            {        
             return artist;
            }
        Perioada_artistica getPerioada() const             //getter pentru perioada
            {        
             return perioada_artistica;
            }
        String getTehnica() const                          //getter pentru tehnica
            {
                return *tehnica;
            }

        //afisarea datelor prin supraincarcarea operatorului <<
        friend ostream & operator << (ostream & out , const Pictura &pict)    
        {
            out <<"Nume pictura: " << *pict.titlu  << endl;
            out <<"Nume artist: " << pict.artist.getNume() << endl;
            out << "Tehnica: " << *pict.tehnica << endl;
            out << "Perioada artistica: " << pict.perioada_artistica.getDenumire()<<endl;
            out << "An finisare pictura: " << pict.an_finisare << endl;
            return out;
        }

        //constructor de copiere
        Pictura(const Pictura & ob)
            {
                this->titlu = ob.titlu;
                this->artist = ob.artist;
                this->perioada_artistica = ob.perioada_artistica;
                this->tehnica = ob.tehnica;
                this->an_finisare = ob.an_finisare;
            }
       
        //supraincarcarea operatorului =
        Pictura& operator= (const Pictura& p)
            {
                this->titlu = p.titlu;
                this->artist = p.artist;
                this->perioada_artistica = p.perioada_artistica;
                this->tehnica = p.tehnica;
                this->an_finisare = p.an_finisare;
            }
    };


class Vizitator
    {
    private:
        String nume;
        String statut_vizitator;             //elev, student, pensionar
        int varsta;
        Artist artist_preferat;
    public:
        //constructori
        Vizitator()                           ///constructor fara parametri
            {
                this->nume = "";
                this->statut_vizitator = "";
                this->varsta = 0;
            }
        Vizitator(String nume, String statut_vizitator, int varsta, Artist artist_preferat)      //cu parametri
            { 
                this->nume = nume;
                this->statut_vizitator = statut_vizitator;
                this->varsta = varsta;
                this->artist_preferat = artist_preferat;
            }

        //settteri, getter

        void setVarstaVizitator (int varsta)                //setter pentru adresa de mail
            {
                this ->varsta = varsta;
            } 
        void setStatutVizitator (String statut_vizitator)    //setter pentru statut vizitator
            {
                this -> statut_vizitator = statut_vizitator;
            }
        String getStatutVizitator() const            //getter pentru statut vizitator
            {
                return statut_vizitator;
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
                this -> pret = pret;
                this->vizitator = vizitator;
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
        Bilet& operator= (const Bilet& b)
            {
                this -> nr_bilet_emis = b.nr_bilet_emis;
                this -> pret = b.pret;
                this -> vizitator = b.vizitator;
            }
    };


class Galerie 
{          
    private:
         Vector <Pictura*> picturi;  

    public:
        //functie de ,,logica de business" - adauga picturi la baza de date a galeriei doar daca nu se regaseste in picturile deja adaugate
        void addPictura(Pictura* pictura)
        {  
            bool ok = true;
            for (int i = 0; i < picturi.size(); i++)
                if (picturi[i] -> getTitlu() == pictura -> getTitlu())
                    ok = false;
            if (ok==true)
                 picturi.push_back(pictura);
        }

        void listaPicturi() {                   //functie de afisare a picturilor si atributelor lor
            for (int i = 0; i < picturi.size(); i++)
            {
                cout << picturi[i] -> getTitlu() << ", " << picturi[i] -> getArtist().getNume() << ", " << picturi[i] -> getTehnica() << ", " << picturi[i] -> getPerioada().getDenumire()<< endl;
            }
        }


};


int main()
{
    Galerie galerie;

    Perioada_artistica perioada1 ("Postimpresionism", 1880, 1910);
    Perioada_artistica perioada2 ("Renastere", 1300, 1600);
    Perioada_artistica perioada3 ("Suprarealism", 1920, 1985);

    Artist artist1("Vincent van Gogh", "neerlandez");
    Artist artist2("Leonardo da Vinci", "italian");
    Artist artist3("Salvador Dali", "spaniol");

    Pictura* pictura1 = new Pictura ("Starry Night", artist1, perioada1, "Ulei pe panza", 1889);
    Pictura* pictura2 = new Pictura ("Mona Lisa", artist2, perioada2, "Ulei pe lemn", 1503);
    Pictura* pictura3 = new Pictura ("The Persistence of Memory", artist3, perioada3, "Ulei pe panza", 1931);

    galerie.addPictura(pictura1);
    galerie.addPictura(pictura2);
    galerie.addPictura(pictura3);
    galerie.addPictura(pictura1);

    cout<<"Lista picturilor din galerie:"<<endl;
    cout<<endl;
    galerie.listaPicturi(); //afiseaza lista cu picturile si atributele lor
    cout<<endl;

    Vizitator vizitator1 ("Ana", "elev", 14, artist2);
    Vizitator vizitator2 ("Mihai", "student", 23, artist1);
    Vizitator vizitator3 ("Andrei", "vizitator", 46, artist2);
    Vizitator vizitator4 ("Andreea", "pensionar", 82, artist3);
    Vizitator vizitator5 ("Bogdan", "vizitator", 30, artist1);

    vizitator5.setStatutVizitator("sarbatorit");
    vizitator5.setVarstaVizitator(31);         //sarbatoritul primeste bilet gratuit - implementarea celor 3 settere

    Bilet bilet1(1, 60, vizitator1);      //se aplica reduceri in functie de statutul vizitatorului
    Bilet bilet2(2, 60, vizitator2);
    Bilet bilet3(3, 60, vizitator3);
    Bilet bilet4(4, 60, vizitator4);
    Bilet bilet5(5, 60, vizitator5);
    bilet5.setPretBilet(0); 

    bilet1.Reducere(vizitator1);
    bilet2.Reducere(vizitator2);
    bilet3.Reducere(vizitator3);
    bilet4.Reducere(vizitator4);

    cout<<"Bilete dupa reduceri: "<<endl;
    cout<<endl;
    Bilet b1=bilet1;           //apelam constructorul de copiere, supraincarcarea lui =
    cout<<b1<<endl;            //supraincarcare <<
    cout<<bilet2<<endl;
    cout<<bilet3<<endl;
    cout<<bilet4<<endl;
    cout<<bilet5<<endl;
    
    cout<<"Cea mai cautata pictura:"<<endl;
    cout<<endl;
    Pictura p1=*pictura1;   //apelam constructorul de copiere, supraincarcarea lui =
    cout<<p1;

    delete pictura1;
    delete pictura2;
    delete pictura3;
    return 0;
}









