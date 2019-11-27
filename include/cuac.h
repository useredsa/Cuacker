#ifndef AEDI_CUAC_H_
#define AEDI_CUAC_H_

#include <iostream>
#include <string>
#include <tuple>

#include "date.h"

namespace AEDI {

class Cuac {
 public:
  Cuac() { }
  Cuac(const std::string& user, const Date& date) : user_(user), date_(date) { }
  virtual ~Cuac() { };

  friend std::istream& operator>>(std::istream& is, Cuac& obj);
  friend std::ostream& operator<<(std::ostream& os, const Cuac& obj);

  inline const std::string& user() const { return user_; }
  inline const Date& date() const { return date_; }
  virtual const std::string& text() const =0;

 private:
  friend class DateCuac;
  std::string user_;
  Date date_;
  virtual std::istream& read_text(std::istream& is) =0;
};

inline bool operator< (const Cuac& lhs, const Cuac& rhs) {
  return tie(rhs.date(), lhs.text(), lhs.user()) < tie (lhs.date(), rhs.text(), rhs.user());
}
inline bool operator> (const Cuac& lhs, const Cuac& rhs) { return rhs < lhs; }
inline bool operator<=(const Cuac& lhs, const Cuac& rhs) { return !(rhs < lhs); }
inline bool operator>=(const Cuac& lhs, const Cuac& rhs) { return !(lhs < rhs); }

class MCuac : public Cuac {
 public:
  ~MCuac() { }
  inline const std::string& text() const { return message_; }
 private:
  std::string message_;
  std::istream& read_text(std::istream& is);
};

class PCuac : public Cuac {
 public:
  ~PCuac() { }
  static const std::string kArr[];
  inline const std::string& text() const { return kArr[message_index_]; }
 private:
  int message_index_;
  std::istream& read_text(std::istream& is);
};

class DateCuac : public Cuac {
 public:
  DateCuac(const Date& date) : Cuac("", date) { }
  inline const std::string& text() const { return kEmptyString; }
 private:
  static const std::string kEmptyString;
  std::istream& read_text(std::istream& is) { return is; }
};

} // namespace AEDI

#endif
