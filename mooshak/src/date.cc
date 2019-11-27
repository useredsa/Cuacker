#include "date.h"

#include <iomanip>
using namespace std;

namespace AEDI {

istream& operator>>(istream& is, Date& obj) {
  char c;
  return is >> obj.day_ >> c >> obj.month_ >> c >> obj.year_
            >> obj.hour_ >> c >> obj.mins_ >> c >> obj.secs_;
  //if( /* T could not be constructed */ )
  //is.setstate(std::ios::failbit);
};

ostream& operator<<(ostream& os, const Date& obj) {
  return os << obj.day_ << '/' << obj.month_ << '/' << obj.year_ << ' '
            << setw(2) << setfill('0') << obj.hour_ << ':'
            << setw(2) << setfill('0') << obj.mins_ << ':'
            << setw(2) << setfill('0') << obj.secs_;
};

}  // namespace AEDI
