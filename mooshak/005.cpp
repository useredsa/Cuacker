#include<iostream>
#include<iomanip>
#include<limits>
using namespace std;

class Fecha {
  int day, month, year;
  int sec, min, hour;



public:
  bool operator<(const Fecha& rhs) {
    return tie(year, month, day, hour, min, sec) <
    tie (rhs.year, rhs.month, rhs.day, rhs.hour, rhs.min, rhs.sec);
  }

  friend istream& operator>>(istream& is, Fecha& obj) {
    char c;
    is >> obj.day >> c >> obj.month >> c >> obj.year >>
          obj.hour >> c >> obj.min >> c >> obj.sec;
    //if( /* T could not be constructed */ )
    //is.setstate(std::ios::failbit);
    return is;
  };

  friend ostream& operator<<(ostream& os, const Fecha& obj) {
    os << obj.day << '/' << obj.month << '/' << obj.year;
    os << ' ' << setw(2) << setfill('0') << obj.hour;
    os << ':' << setw(2) << setfill('0') << obj.min;
    os << ':' << setw(2) << setfill('0') << obj.sec;
    return os;
  };

};

class cuac {
  string user;
  Fecha date;

  virtual const string& text() {return nullptr;};
  virtual istream& read_text(istream& is) {return is;};

public:
  bool operator<(cuac& rhs) {
    return tie(date, text(), user) <
    tie (rhs.date, rhs.text(), rhs.user);
  }

  friend istream& operator>>(istream& is, cuac& obj) {
    is >> obj.user >> obj.date;
    is.ignore(numeric_limits<streamsize>::max(), '\n');
    obj.read_text(is);
    return is;
  };

  friend ostream& operator<<(ostream& os, cuac& obj) {
    os << obj.user << " " << obj.date << endl << "   " << obj.text();
    return os;
  };

};

class Mcuac : public cuac {
  string message;

  const string& text() {
    return message;
  }

  istream& read_text(istream& is) {
    getline(is, message);
    return is;
  }
};

class Pcuac : public cuac {
  int message_index;

  static string arr[];

  const string& text() {
    return arr[message_index];
  }

  istream& read_text(istream& is) {
    is >> message_index;
    message_index--;
    return is;
  }
};

string Pcuac::arr[]  = {
  "Afirmativo.",
  "Negativo.",
  "Estoy de viaje en el extranjero.",
  "Muchas gracias a todos mis seguidores por vuestro apoyo.",
  "Enhorabuena, campeones!",
  "Ver las novedades en mi pagina web.",
  "Estad atentos a la gran exclusiva del siglo.",
  "La inteligencia me persigue pero yo soy mas rapido.",
  "Si no puedes convencerlos, confundelos.",
  "La politica es el arte de crear problemas.",
  "Donde estan las llaves, matarile, rile, rile...",
  "Si no te gustan mis principios, puedo cambiarlos por otros.",
  "Un dia lei que fumar era malo y deje de fumar.",
  "Yo si se lo que es trabajar duro, de verdad, porque lo he visto por ahi.",
  "Hay que trabajar ocho horas y dormir ocho horas, pero no las mismas.",
  "Mi vida no es tan glamurosa como mi pagina web aparenta.",
  "Todo tiempo pasado fue anterior.",
  "El azucar no engorda... engorda el que se la toma.",
  "Solo los genios somos modestos.",
  "Nadie sabe escribir tambien como yo.",
  "Si le molesta el mas alla, pongase mas aca.",
  "Me gustaria ser valiente. Mi dentista asegura que no lo soy.",
  "Si el dinero pudiera hablar, me diria adios.",
  "Hoy me ha pasado una cosa tan increible que es mentira.",
  "Si no tienes nada que hacer, por favor no lo hagas en clase.",
  "Que nadie se vanaglorie de su justa y digna raza, que pudo ser un melon y salio una calabaza.",
  "Me despido hasta la proxima. Buen viaje!",
  "Cualquiera se puede equivocar, inclusivo yo.",
  "Estoy en Egipto. Nunca habia visto las piramides tan solas.",
  "El que quiera saber mas, que se vaya a Salamanca."
};


int main () {
  int i=0;
  string s, parameter;
  cuac *last_read = nullptr;
  Mcuac myMcuac;
  Pcuac myPcuac;
  Fecha aux;
  while (cin >> s) {
      if (s == "mcuac") {
          cin >> myMcuac;
          last_read = &myMcuac;

          cout << ++i << " cuac" << endl;
      } else if (s == "pcuac") {
          cin >> myPcuac;
          last_read = &myPcuac;

          cout << ++i << " cuac" << endl;
      } else if (s == "last") {
          cin >> parameter;

          cout << s << " " << parameter << endl;
          cout << "1. " << *last_read << endl << "Total: 1 cuac" << endl;
      } else if (s == "follow") {
          cin >> parameter;

          cout << s << " " << parameter << endl;
          cout << "1. " << *last_read << endl << "Total: 1 cuac" << endl;
      } else if (s == "date") {
          cin >> aux;
          cout << s << " " << aux;
          cin >> aux;
          cout << " " << aux << endl;
          cout << "1. " << *last_read << endl << "Total: 1 cuac" << endl;
      } else if (s == "tag") {
          cin >> parameter;

          cout << s << " " << parameter << endl;
          cout << "1. " << *last_read << endl << "Total: 1 cuac" << endl;
      } else if (s == "exit") {
          cout << s << " " << parameter << endl;
          cout << "1. " << *last_read << endl << "Total: 1 cuac" << endl;
        }
  }
}
