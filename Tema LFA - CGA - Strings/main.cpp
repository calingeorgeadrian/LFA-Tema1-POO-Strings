/*Aceasta tema a presupus simularea unui DFA
  DFA-ul simulat de acest program accepta caractere, numere si siruri de caractere
  
  Documentatie
  DFA - https://en.wikipedia.org/wiki/Deterministic_finite_automaton
 */

#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

ifstream fin("date5.in");

struct Nod{
    int state,new_state;
    char letter[101];
    Nod *next;
};

class DFA{
    int states_nr;
    int letters_nr;
    int final_states_nr;
    int trans_nr;
    int current_state;
    char* word;
    int init_state;
    int states[50];
    char alphabet[50][50];
    int final_states[50];
    Nod* transitions[50];
public:
//setter
    void set_states_nr(int x){states_nr=x;}
    void set_letters_nr(int x){letters_nr=x;}
    void set_final_states_nr(int x){final_states_nr=x;}
    void set_trans_nr(int x){trans_nr=x;}
    void set_word(char w[]){word=w;}
    void set_init_state(int x){init_state=x;}
    void set_transitions(){for(int i=0;i<50;i++) transitions[i]=NULL;}
//getter
    int get_states_nr(){return states_nr;}
    int get_letter_nr(){return letters_nr;}
    int get_final_states_nr(){return final_states_nr;}
    int get_trans_nr(){return trans_nr;}
    int get_current_state(){return current_state;}
    char* get_word(){return word;}
    int get_init_state(){return init_state;}
    int get_states(int i){return states[i];}
    //char get_alphabet(int i){return alphabet[i];}
    int get_final_states(int i){return final_states[i];}

//metode
    int convertToInt(char a){
        if(a>='a' && a<='z')
            return a-'a';
        else if(a>='A' && a<='Z')
            return a-'A';
        else return a-'0';
    }

    void readStates(){ ///citim starile si le convertim la int
        char a;
        for(int i=0;i<states_nr;i++)
        {
            fin>>a;
            states[i]=convertToInt(a);
        }
    }

    void readAlphabet(){ ///citim alfabetul
        char a;
        for(int i=0;i<letters_nr;i++)
        {
            fin>>alphabet[i];
        }
    }

    void readFinalStates(){ ///citim starile finale si le convertim la int
        char a;
        for(int i=0;i<final_states_nr;i++)
        {
            fin>>a;
            final_states[i]=convertToInt(a);
        }
    }

    void readTransitions(){ ///citim tranzitiile si le salvam intr--un vector de liste pentru fiecare stare
        char a,b,c[101];
        int x,y;
        for(int i=0;i<trans_nr;i++)
        {
            fin>>a>>b>>c; ///citim elementele tranzitiei (stare1, stare2, litera)
            x=convertToInt(a);
            y=convertToInt(b);
            Nod *p; ///initializam un nod p in care salvam tranzitia curenta
            p=new Nod;
            p->state=x;
            p->new_state=y;
            strcpy(p->letter,c);
            p->next=NULL;
            if(transitions[x]==NULL) ///daca nu exista tranzitii pentru starea x, initializam prima tranzitie
                transitions[x]=p;
            else ///altfel o adaugam in lista de tranzitii pentru starea x
            {
                Nod *q=transitions[x];
                while(q->next!=NULL)
                    q=q->next;
                q->next=p;
            }
        }
    }

    bool checkFinalState(int state){ ///verificam daca ne aflam intr-o stare finala
        for(int i=0;i<final_states_nr;i++)
            if(state==final_states[i])
                return 1;
        return 0;
    }

    bool checkWord(int state, int n, int wordNr){
        if(n==wordNr && checkFinalState(state)) ///daca s-a terminat cuvantul si ne aflam intr-o stare finala, cuvantul este acceptat
            return 1;

        Nod *p=transitions[state];

        while(p!=NULL && strcmp(p->letter,word)) ///traversam lista de tranzitii pentru starea curenta
            p=p->next;

        if(p!=NULL) ///daca a fost gasita o tranzitie, o efectuam, eliminam litera verificata si continuam cu restul cuvantului
        {
            cout<<word<<" "<<state<<endl;
            fin>>word;
            current_state=p->new_state;
            return checkWord(p->new_state,n+1,wordNr);
        }
        return 0;
    }
};

int main(){

    DFA automat;
    int x;
    char a;

    fin>>x;
    automat.set_states_nr(x);
    automat.readStates(); ///citire stari

    fin>>x;
    automat.set_letters_nr(x);
    automat.readAlphabet(); ///citire alfabet

    fin>>a;
    x=automat.convertToInt(a);
    automat.set_init_state(x); ///citire stare initiala

    fin>>x;
    automat.set_final_states_nr(x);
    automat.readFinalStates(); ///citire stari finale

    fin>>x;
    automat.set_trans_nr(x);
    automat.set_transitions();
    automat.readTransitions(); ///citire tranzitii

    char w[101];
    int wordNr;
    fin>>wordNr;
    fin>>w;
    automat.set_word(w); ///citire cuvant

    if(automat.checkWord(automat.get_init_state(),0,wordNr)) ///verificare cuvant
        cout<<"CUVANT ACCEPTAT";
    else cout<<"CUVANT RESPINS";

    return 0;
}
