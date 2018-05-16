#include <iostream>
#include <string.h>

using namespace std;


//////////////////////////////////////////////////////////

class Plata
{
protected:
    char date[10];
    float sum;

public:

    Plata()
    {
        //date = new char[10];
        sum = -1;
    }

    /*~Plata()
    {
        delete[] date;
        date=NULL;
    }*/

    virtual void print()
    {
        cout<< "Suma de "<< sum <<" LEI a fost platita CASH pe data de "<<date<<"."<<endl;
    }


    friend istream& operator >> (istream& in, Plata &obj);
};

    istream& operator >> (istream& in, Plata &obj)
    {
        int OK;
        do{
        OK=1;
        cout<<"DATE(DD/MM/YYYY): ";
        in>>obj.date;
        if(obj.date[2]!='/' || obj.date[5]!='/')OK=0;
        if(obj.date[0]>'3' || (obj.date[0]=='3' && obj.date[1]>'1'))OK=0;
        if(obj.date[3]!='1'&&obj.date[3]!='0')OK=0;
        if(obj.date[3]=='1'&& obj.date[4]>'2')OK=0;
        if(OK==0)cout<<"Data introdusa este invalida."<<endl;
        }while(OK==0);
        cout<<endl;
        cout<<"SUM : ";
        in>>obj.sum;
        cout<<endl;
        return in;
    }


//////////////////////////////////////////////////////

class Card : public Plata
{
protected:
    int card_id;

public:

    Card() : Plata()
    {
        card_id = -1;
    }

    virtual void print()
    {
        cout<< "Suma de "<< sum <<" LEI a fost platita CARD pe data de "<<date<<", cu numarul de card "<<card_id<<"."<<endl;
    }

    friend istream& operator >> (istream& in, Card &obj);

};
    istream& operator >> (istream& in, Card &obj)
    {
        int OK;
        do{
        OK=1;
        cout<<"DATE(DD/MM/YYYY): ";
        in>>obj.date;
        if(obj.date[2]!='/' || obj.date[5]!='/')OK=0;
        if(obj.date[0]>'3' || (obj.date[0]=='3' && obj.date[1]>'1'))OK=0;
        if(obj.date[3]!='1'&&obj.date[3]!='0')OK=0;
        if(obj.date[3]=='1'&& obj.date[4]>'2')OK=0;
        if(OK==0)cout<<"Data introdusa este invalida."<<endl;
        }while(OK==0);
        cout<<endl;
        cout<<"SUM: ";
        in>>obj.sum;
        cout<<endl;

        cout<<"CARD_ID: ";
        in>>obj.card_id;
        cout<<endl;

        return in;
    }

////////////////////////////////////////////////////////

class Cheque : public Plata
{
protected:
    char provider[50];

public:

    Cheque() : Plata()
    {
        //provider=new char[50];
    }

    /*~Cheque()
    {
        delete[] provider;
        provider=NULL;
    }*/

    virtual void print()
    {
        cout<< "Suma de "<< sum <<" LEI a fost platita CEC pe data de "<<date<<", sursa fiind "<<provider<<"."<<endl;
    }


    friend istream& operator >> (istream& in, Cheque &obj);
};

    istream& operator >> (istream& in, Cheque &obj)
    {
        int OK;
        do{
        OK=1;
        cout<<"DATE(DD/MM/YYYY): ";
        in>>obj.date;
        if(obj.date[2]!='/' || obj.date[5]!='/')OK=0;
        if(obj.date[0]>'3' || (obj.date[0]=='3' && obj.date[1]>'1'))OK=0;
        if(obj.date[3]!='1'&&obj.date[3]!='0')OK=0;
        if(obj.date[3]=='1'&& obj.date[4]>'2')OK=0;
        if(OK==0)cout<<"Data introdusa este invalida."<<endl;
        }while(OK==0);
        cout<<endl;
        cout<<"SUM: ";
        in>>obj.sum;
        cout<<endl;

        cout<<"PROVIDER: ";
        in>>obj.provider;

        return in;
    }
///////////////////////////////////////////////////////////////

template <class T>
class Gestiune
{
protected:

    int nr_total;
    Plata **v;

public:

    Gestiune()
    {
        nr_total=-1;
        v=NULL;
    }

    Gestiune(int nr)
    {
        nr_total=-1;
        v = new Plata*[nr];
    }

    ~Gestiune()
    {
        delete[] v;
        v=NULL;
    }

    /*Gestiune& add(T &obj)
    {
        Plata* p = dynamic_cast<Plata*>(&obj);

        this->nr_total++;
        this->v[nr_total]=p;

        return *this;
    }*/

    void print()
    {
        for(int i=0; i<=nr_total; i++)
        {
            v[i]->print();
            //cout<<"ok"<<endl;
        }
    }

    Gestiune& operator += ( T &obj)
    {
        Plata* p = dynamic_cast<Plata*>(&obj);

        if(p!=NULL){
        this->nr_total++;
        this->v[nr_total]=p;
        return *this;

        }
        else
        {
            throw 15;
            return *this;
        }

    }


};

////////////////////////////////////////////////

/*void Stocare<char*>(char* clienti[], int &total, char* current)
{
    total++;
    clienti[total]=new char[20];
    cout<<"NUME CLIENT : ";
    char nume[20]; cin>>nume;
    strcpy(clienti[total], nume);
    delete[] nume;
}*/

int main()
{


    Gestiune <Plata> G(50);

    int optiune,ok;
    do
    {
        cout<<" --!--!-- P L A T A  S I M U L A T O R --!--!--";
        cout<<endl<<"-------------------------------"<<endl;
        cout<<"1. Plata noua"<<endl;
        cout<<"2. Afisarea tuturor platilor"<<endl;
        cout<<"0. EXIT"<<endl;
        cout<<"-------------------------------";

        do{
        ok=1;
        cout<<endl<<"Alegeti optiunea : ";
        cin>>optiune;
        if(optiune<0||optiune>2)ok=0;
        if(!ok)cout<<"Optiune aleasa e invalida."<<endl;
        }while(ok==0);
        cout<<endl<<endl;

        switch(optiune)
        {
        case 1:

           {

            cout<<"Selectati modul de plata :"<<endl;
            cout<<endl<<"1. CASH";
            cout<<endl<<"2. CARD";
            cout<<endl<<"3. CEC"<<endl;

            int mod;
            do{
            ok=1;
            cout<<endl<<"Alegeti optiunea : ";
            cin>>mod;
            if(mod<0||mod>3)ok=0;
            if(!ok)cout<<"Optiunea aleasa e invalida."<<endl;
            }while(ok==0);

            switch(mod)
            {
            case 1:
                {
                    Plata p;
                    cin>>p;
                    try
                    {
                        G += p;
                    }
                    catch(int er)
                    {
                        if(er==15)cout<<"Castarea nu a reusit. Repetati comanda..."<<endl;
                    }
                    //G.add(p);
                    break;
                }
            case 2:
                {
                    Card c;
                    cin>>c;
                    try
                    {
                        G += c;
                    }
                    catch(int er)
                    {
                        if(er==15)cout<<"Castarea nu a reusit. Repetati comanda..."<<endl;
                    }
                    //G.add(c);
                    break;
                }
            case 3:
                {
                    Cheque ch;
                    cin>>ch;
                    try
                    {
                        G += ch;
                    }
                    catch(int er)
                    {
                        if(er==15)cout<<"Castarea nu a reusit. Repetati comanda..."<<endl;
                    }
                    //G.add(ch);
                    break;
                }
            }
            break;
           }
        case 2:
            {
                G.print();
                //cout<<"HELLO"<<endl;
                break;
            }
        }
    }while(optiune>0 && optiune<3);

    return 0;
}
