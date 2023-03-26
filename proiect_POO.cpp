#include<iostream>
#include<vector>
using namespace std;

class Perioada_artistica
    {
        string denumire;
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
        Perioada_artistica(string denumire, int an_inceput, int an_final)          //cu parametri
    {
        this->denumire = denumire;
        this->an_inceput= an_inceput;
        this->an_final= an_final;
    }
       
        //getter
        string getDenumire() const             //getter pentru nume perioada artistica
            {
                return denumire;
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
        Artist(string nume, string nationalitate) {        //cu parametri
        this->nume = nume;
        this->nationalitate= nationalitate;
    }


        //getteri
        string getNume() const               //getter pentru nume artist
            {
                return nume;
            }

        string getNationalitate() const           //getter pentru nationalitate
            {
                return nationalitate;
            }
        
        //constructor de copiere
         Artist(const Artist & ob)
            {
                this->nume = ob.nume;
                this->nationalitate= ob.nationalitate;
            }
    };


class Pictura
    {
    private:
        string titlu;
        Artist artist;
        Perioada_artistica perioada_artistica;
        string tehnica;
        int an_finisare;  
        int nr_picturi=0;
    public:
       
        //constructori
        Pictura()                           ///constructor fara parametri
            {
                this->titlu = "";
                this->tehnica = "";
                this->an_finisare = 0;
            }
        Pictura(string titlu, Artist artist,  Perioada_artistica perioada_artistica, string tehnica, int an_finisare)   //constructor cu parametri
            {
                this->titlu = titlu;
                this->artist = artist;
                this->perioada_artistica=perioada_artistica;
                this->tehnica = tehnica;
                this->an_finisare = an_finisare;
            }
       
        //setter, getter
        string getTitlu() const                            //getter pentru nume pictura
            {
                return titlu;
            }
        void setAnPictura (int an_finisare)                //setter pentru anul finisarii picturii
            {
                this ->an_finisare = an_finisare;
            }  
        Artist getArtist() const                           //getter pentru artist
            {        
             return artist;
            }
        Perioada_artistica getPerioada() const             //getter pentru perioada
            {        
             return perioada_artistica;
            }
        string getTehnica() const
            {
                return tehnica;
            }

        //afisarea datelor prin supraincarcarea operatorului <<
        friend ostream & operator << (ostream & out , const Pictura &pict)     
        {
            out <<"Nume pictura: " << pict.titlu  << endl;
            out <<"Nume artist: " << pict.artist.getNume() << endl;
            out << "Tehnica: " << pict.tehnica << endl;
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
        string nume;
        string statut_vizitator;             //elev, student, pensionar
        string adresa_mail;
        Artist artist_preferat;
    public:
        //constructori
        Vizitator()                           ///constructor fara parametri
            {
                this->nume = "";
                this->statut_vizitator = "";
                this->adresa_mail = "";
            }
        Vizitator(string nume, string statut_vizitator, string adresa_mail, Artist artist_preferat)
            {
                this->nume = nume;
                this->statut_vizitator = statut_vizitator;
                this->adresa_mail = adresa_mail;
                this->artist_preferat = artist_preferat;
            }
        void setStatutVizitator (string statut_vizitator)    //setter pentru pret bilet
            {
                this -> statut_vizitator = statut_vizitator;
            }
        string getStatutVizitator() const            //getter pentru statut vizitator
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
        double getPretBilet() const            //getter pentru pret bilet
            {
                return pret;
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
            out <<"Numar bilet emis:" << bilet.nr_bilet_emis  << endl;
            out <<"Statut vizitator:" << bilet.vizitator.getStatutVizitator() << endl;
            out << "Pret:" << bilet.pret<< endl;
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


class Galerie {
    private:
         vector <Pictura> picturi;

    public:

        //functie de ,,logica de business" - adauga picturi la baza de date a galeriei doar daca nu se regaseste in picturile deja adaugate
        void addPictura(Pictura pictura) 
        {   
            bool ok = true;
            for (int i = 0; i < picturi.size(); i++) 
                if (picturi[i].getTitlu() == pictura.getTitlu())
                    ok = false;
            if (ok==true)
                 picturi.push_back(pictura);
        }

        void listaPicturi() {                   //functie de afisare a picturilor si atributelor lor
            for (int i = 0; i < picturi.size(); i++) 
            {
                cout << picturi[i].getTitlu() << ", " << picturi[i].getArtist().getNume() << ", " << picturi[i].getTehnica() << ", " << picturi[i].getPerioada().getDenumire()<< endl;
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


    Pictura pictura1("Starry Night", artist1, perioada1, "Ulei pe panza", 1889);
    Pictura pictura2("Mona Lisa", artist2, perioada2, "Ulei pe lemn", 1503);
    Pictura pictura3("The Persistence of Memory", artist3, perioada3, "Ulei pe panza", 1931);

    galerie.addPictura(pictura1);
    galerie.addPictura(pictura2);
    galerie.addPictura(pictura3);
    galerie.addPictura(pictura1);

    //galerie.listaPicturi(); afiseaza lista cu picturile si atributele lor

    Vizitator vizitator1 ("Ana", "elev", "ana.m@gmail.com", artist2);
    Vizitator vizitator2 ("Mihai", "student", "mihai30@gmail.com", artist1);
    Vizitator vizitator3 ("Andrei", "vizitator", "andrei.g@gmail.com", artist2);
    Vizitator vizitator4 ("Andreea", "pensionar", "andreea234@gmail.com", artist3);

    Bilet bilet1(1, 60, vizitator1);
    bilet1.Reducere(vizitator1);       //se aplica reduceri in functie de statutul vizitatorului
    Bilet bilet2(2, 60, vizitator2);
    bilet2.Reducere(vizitator2);
    Bilet bilet3(3, 60, vizitator3);
    bilet3.Reducere(vizitator3);
    Bilet bilet4(4, 60, vizitator4);
    bilet4.Reducere(vizitator4);
   
     //apelam constructorul de copiere pentru pictura
    Pictura p1(pictura1);      //sau Pictura p1 = pictura1;
    cout<<p1<<endl;                  //supraincarcare <<

    //apelam constructorul de copiere pentru bilet
    Bilet b1(bilet1);          //sau Bilet b1= bilet1;
    cout<<b1;                  //supraincarcare <<

    return 0;
}



