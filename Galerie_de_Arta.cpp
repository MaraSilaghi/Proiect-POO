#include<iostream>
#include<set>
#include <algorithm>
#include<memory>
using namespace std;

template<typename T>
class Vector
{
  private:
    int marime;           //nr curent de elemente din vector
    int nr_max_elem;      //nr maxim de elemente care pot fi stocate in vector
    T* obiect;

  public:
    //constructor
    Vector()
    {
        this ->marime = 0;
        this ->nr_max_elem=0;
        this ->obiect = new T[nr_max_elem];
    }
    //destructor
    ~Vector()
    {
        delete[] obiect;
    }

    // implementarea push_back-ului - adauga la final obiectul si dubleaza capacitatea vectorului daca e cazul
    void push_back(const T& valoare)
    {
        if (marime == nr_max_elem)
            {
            nr_max_elem *= 2;
            T* obiect_nou = new T[nr_max_elem];
            for (int i=0; i<marime; i++)
             obiect_nou[i] = obiect[i];
            delete[] obiect;
            obiect = obiect_nou;
            }
     obiect[marime++] = valoare;
    }

    //prin metoda operator[] putem accesa elementele vectorului dupa index
    T& operator[](const int index)
     {
        return obiect[index];
     }

    //functia size - returneaza lungimea vectorului
    int size() const
    {
        return marime;
    }

    // functia copy - copiaza continutul altui vector in vectorul curent
    void copy(const Vector<T>& v)
    {
        if (this != &v)
        {
            delete[] obiect;
            marime = v.marime;
            nr_max_elem = v.nr_max_elem;
            obiect = new T[nr_max_elem];
            for (int i = 0; i < marime; i++)
            {
                obiect[i] = v.obiect[i];
            }
        }
    }

    // functia erase - sterge un element din vector la indexul dat
    void erase(const int index)
    {
        if (index < marime)
        {
            for (int i = index; i < marime - 1; i++)
            {
                obiect[i] = obiect[i + 1];
            }
            marime--;
        }
    }


  class VectorIterator
  {
  private:
    T* curent;  // pointer catre elementul curent

  public:
    // Constructor
    VectorIterator(T* ptr) : curent(ptr) {}

    T& operator*() const
    {
      return *curent; // accesarea elementului
    }

    VectorIterator& operator++()   //incrementare
    {
      ++curent;
      return *this;
    }

    bool operator==(const VectorIterator& elem) const    //suprascriere ==
    {
      return curent == elem.curent;
    }

    bool operator!=(const VectorIterator& elem) const     //suprascriere !=
    {
      return !(curent == elem.curent);
    }
  };

  // iterator care pointeaza catre primul element
  VectorIterator begin()
  {
    return VectorIterator(obiect);
  }

  // iterator care pointeaza catre ultimul element
  VectorIterator end()
  {
    return VectorIterator(obiect + marime);
  }
};


class Artist
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

        string getNume() const
            {
            return nume;
            }

        void setNume(const string& nume)
            {
            this->nume = nume;
            }
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

        //setter, getter
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
        friend ostream & operator << (ostream & out , const Pictura &pict)   //polimorfism
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

         bool operator== (const Pictura& elem) const
        {
            return (this->titlu == elem.titlu && this->material == elem.material && this->an_finisare == elem.an_finisare);
        }

        string get_descriere() const override    //apelam clasa de baza abstracta
        {
           return "Pictura '" + titlu + "', realizata de " + getArtist().getNume();
        }
        ~Pictura(){}
    };


class PrintPictura
    {
    private:
        string titlu;
        Artist artist;

    public:
        //constructori
        PrintPictura()                           ///constructor fara parametri
            {
                this->titlu = "";
            }
        PrintPictura(string titlu, Artist artist)   //constructor cu parametri
            {
                this->titlu = titlu;         //alocare dinamica
                this->artist = artist;

            }
        //setter, getter
        string getTitlu() const                            //getter pentru nume pictura
            {
                return titlu;
            }
        Artist getArtist() const                           //getter pentru artist
            {
             return artist;
            }
    };


class Vizitator
    {
    protected:                           //date de tip protected
        string nume;
        string statut_vizitator;             //elev, student, pensionar
        int varsta;
        Artist artist_preferat;
        set<shared_ptr<PrintPictura>> copii_cumparate_;
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

    void adaugaPrintCumparat(shared_ptr<PrintPictura> pictura)
     {
        copii_cumparate_.insert(pictura);
     }

        void afiseaza_print()
         {
            for (auto it = copii_cumparate_.begin(); it != copii_cumparate_.end(); ++it) {
                cout << "Copie dupa pictura "<<(*it)->getTitlu() << endl;
         }
            cout<<endl;
        }

    };


class Cumparator : public Vizitator
{
    private:
        set<Pictura*> picturi_cumparate_;
    public:
    //constructori - folosesc constructorii clasei de baza
    Cumparator():Vizitator(){}
    Cumparator(string nume, string statut_vizitator, int varsta, Artist artist_preferat) : Vizitator(nume, statut_vizitator, varsta, artist_preferat) {}

    //functie care adauga picturi in vectorul de picturi cumparate al cumparatorului
     void adaugaPicturaCumparata(Pictura* pictura)
     {
        picturi_cumparate_.insert(pictura);
     }

     void afiseaza_picturi_cumparate()
     {
       for (auto it = picturi_cumparate_.begin(); it != picturi_cumparate_.end(); ++it)
       {
            cout << "Pictura "<<(*it)->getTitlu() << endl;
            cout<<endl;
        }

        auto it = find_if(picturi_cumparate_.begin(), picturi_cumparate_.end(), [](Pictura* p) { return p->getMaterial() == "ulei"; });
        if (it != picturi_cumparate_.end())
            cout << "Prima pictura cumparata cu tehnica ulei: " << (*it)->getTitlu() << endl;
        else
        cout << "Nu s-a gasit nicio pictura cumparata cu tehnica ulei." << endl;

        bool sunt_toate_ulei = toate_ulei(picturi_cumparate_);
        if (sunt_toate_ulei)
        cout << "Toate picturile cumparate sunt realizate in tehnica ulei." << endl;
    else
        cout << "Nu toate picturile cumparate sunt realizate in tehnica ulei." << endl;
     }

     bool toate_ulei(set<Pictura*>& picturi) const
     {
        return all_of(picturi.begin(), picturi.end(), [](Pictura* p) { return p->getMaterial() == "ulei"; });
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
        void Reducere (const Vizitator& viz)
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
        Vector<Pictura*> colectie_picturi;
        Galerie(){}
    public:
        static Galerie& getInstanta()
        {
            static Galerie g;
            return g;
        }
         Galerie(const Galerie&) = delete;             // ii spunem compilatorului sa nu faca
         Galerie& operator=(const Galerie&) = delete;   //un constructor de copiere / assignment default


        //adauga picturi la baza de date a galeriei doar daca nu se regaseste in picturile deja adaugate
        void addPictura(Pictura* pictura)
        {
            for (Vector<Pictura*>::VectorIterator pict = colectie_picturi.begin(); pict != colectie_picturi.end(); ++pict)
                if ((*pict) -> getTitlu() == pictura -> getTitlu())
                    throw ExceptiePicturaExistenta();                 //exceptie custom

            if (pictura->getTitlu().empty())
            {
            throw ExceptiePicturaInvalida();
            }
            colectie_picturi.push_back(pictura);

        }


        //functie de afisare a picturilor si atributelor lor
        void listaPicturi()
        {
            for (Vector<Pictura*>::VectorIterator pict = colectie_picturi.begin(); pict != colectie_picturi.end(); ++pict)
            {
                cout<< (*pict) -> getTitlu() << ", " << (*pict) -> getArtist().getNume() << ", " << (*pict) -> getMaterial()<<endl;
            }
        }

        Vector<Pictura*>& getPicturi()
        {
            return colectie_picturi;
        }
};


template<typename T>                         //metoda template
bool contine(Vector<T*>& v, T*& element)
{
    for (typename Vector<T*>::VectorIterator obiect = v.begin(); obiect!=v.end(); ++obiect)
        if ((*obiect) == element)
            return true;
    return false;
}

template<>
bool contine<Pictura>(Vector<Pictura*>& v, Pictura*& pict2)
{
    for (Vector<Pictura*>::VectorIterator pict = v.begin(); pict != v.end(); ++pict)
        if ((*pict)->getTitlu() == pict2->getTitlu())
            return true;
    return false;
}

int main()
{
    Galerie& galerie = Galerie::getInstanta();   //crearea unei noi variabile de tip galerie face referire
                                                 //la aceeasi instanta statica
    Artist artist1("Vincent van Gogh", "neerlandez");
    Artist artist2("Leonardo da Vinci", "italian");
    Artist artist3("Salvador Dali", "spaniol");

    Pictura* pictura1 = new Pictura ("Starry Night", artist1, 1889,  "Ulei pe panza");
    Pictura* pictura2 = new Pictura ("Mona Lisa", artist2, 1503, "Ulei pe lemn");
    Pictura* pictura3 = new Pictura ("The Persistence of Memory", artist3, 1931, "Ulei pe panza");
    Pictura* pictura4 = new Pictura ("Irises", artist1, 1889, "Ulei pe panza");

    shared_ptr<PrintPictura> pictura1_print = make_shared<PrintPictura>("Starry Night", artist1);
    shared_ptr<PrintPictura> pictura2_print = make_shared<PrintPictura>("Mona Lisa", artist2);
    shared_ptr<PrintPictura> pictura3_print = make_shared<PrintPictura>("The Persistence of Memory", artist3);
    shared_ptr<PrintPictura> pictura4_print = make_shared<PrintPictura>("Irises", artist1);
    try{                                       //try-catch care re-arunca un alt tip de excepție din blocul catch
    galerie.addPictura(pictura1);
    galerie.addPictura(pictura2);
    galerie.addPictura(pictura3);
    galerie.addPictura(pictura4);
    } catch (const ExceptiePicturaExistenta& e) {
        cout << "Exceptie: " << e.what() << endl;
        throw;
    } catch (const ExceptiePicturaInvalida& e) {
        cout << "Exceptie: " << e.what() << endl;
        throw;
    }

    cout<<"Lista picturilor din galerie:"<<endl;
    galerie.listaPicturi(); //afiseaza lista cu picturile si atributele lor
    cout<<endl;

    if (contine(galerie.getPicturi(), pictura1))
        cout << "Pictura " << pictura1->getTitlu() << " a fost gasita in galerie." << endl;
    else cout << "Galeria nu contine pictura cautata";

    Vizitator vizitator1 ("Ana", "elev", 14, artist2);
    Vizitator vizitator2 ("Mihai", "student", 23, artist1);
    Vizitator vizitator3 ("Andrei", "vizitator", 46, artist2);
    Cumparator cumparator1 ("Andreea", "pensionar", 82, artist3);
    Cumparator cumparator2 ("Bogdan", "vizitator", 30, artist1);

    cumparator1.adaugaPicturaCumparata(pictura3);
    cumparator1.adaugaPicturaCumparata(pictura4);

    vizitator1.adaugaPrintCumparat(pictura1_print);
    vizitator2.adaugaPrintCumparat(pictura1_print);
    vizitator3.adaugaPrintCumparat(pictura3_print);

    cout<<endl<<"Print-uri cumparate de "<<vizitator1.getNume()<<":"<<endl;
    vizitator1.afiseaza_print();
    cout<<"Print-ul 'Starry Night' a fost cumparat de "<<pictura1_print.use_count()-1<<"ori";
    cout<<"Print-ul 'The Persistence of Memory' a fost cumparat de "<<pictura3_print.use_count()-1<<"ori";
    cout<<endl;
    cout<<"Picturi cumparate de "<<cumparator1.getNume()<<":"<<endl;
    cumparator1.afiseaza_picturi_cumparate();

    delete pictura1;
    delete pictura2;
    delete pictura3;
    delete pictura4;
    return 0;
}
