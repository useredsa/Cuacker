#include<iostream>
#include<tuple>
#include<iomanip>
using namespace std;

class Fecha {
  int day, month, year;
  int sec, min, hour;



public:
  friend istream& operator>>(istream& is, Fecha& obj) {
    char c;
    is >> obj.day >> c >> obj.month >> c >> obj.year;
    is >> obj.hour >> c >> obj.min >> c >> obj.sec;
    //if( /* T could not be constructed */ )
    //is.setstate(std::ios::failbit);
    return is;
  };

  friend ostream& operator<<(ostream& os, Fecha& obj) {
    os << obj.day << '/' << obj.month << '/' << obj.year;
    os << ' ' << setw(2) << setfill('0') << obj.hour;
    os << ':' << setw(2) << setfill('0') << obj.min;
    os << ':' << setw(2) << setfill('0') << obj.sec;
    return os;
  };

  bool operator<(const Fecha& rhs) {
    return tie(year, month, day, hour, min, sec) <
      tie (rhs.year, rhs.month, rhs.day, rhs.hour, rhs.min, rhs.sec);
  }
};


int main () {
  int n;
  Fecha past, actual;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> actual;
    if (i > 0) {
      cout << actual;
      if (actual < past) cout << " ES ANTERIOR A ";
      else if (past < actual) cout << " ES POSTERIOR A ";
      else cout << " ES IGUAL A ";
      cout << past << endl;
    }
    past = actual;
  }
}
