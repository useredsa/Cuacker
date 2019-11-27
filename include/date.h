#ifndef AEDI_DATE_H_
#define AEDI_DATE_H_

#include <iostream>
#include <tuple>

namespace AEDI {

class Date {
 public:
  friend bool operator<(const Date& lhs, const Date& rhs);
  friend std::istream& operator>>(std::istream& is, Date& obj);
  friend std::ostream& operator<<(std::ostream& os, const Date& obj);

  inline int day() const { return day_; }
  inline int month() const { return month_; }
  inline int year() const { return year_; }
  inline int secs() const { return secs_; }
  inline int mins() const { return mins_; }
  inline int hour() const { return hour_; }

 private:
  int day_, month_, year_;
  int secs_, mins_, hour_;
};

inline bool operator <(const Date& lhs, const Date& rhs) {
  return std::tie(lhs.year_, lhs.month_, lhs.day_, lhs.hour_, lhs.mins_, lhs.secs_)<
         std::tie(rhs.year_, rhs.month_, rhs.day_, rhs.hour_, rhs.mins_, rhs.secs_);
}
inline bool operator> (const Date& lhs, const Date& rhs) { return rhs < lhs; }
inline bool operator<=(const Date& lhs, const Date& rhs) { return !(rhs < lhs); }
inline bool operator>=(const Date& lhs, const Date& rhs) { return !(lhs < rhs); }

}  // namespace AEDI

#endif
