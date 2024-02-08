#include "product.h"
#include "movie.h"
#include "util.h"
#include <sstream>
#include <iomanip>

using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty, std::string genre, std::string rating) 
: Product (category, name, price, qty){
  genre_ = genre;
  rating_ = rating;
}

Movie::~Movie(){

}

std::set<std::string> Movie::keywords() const{
  set<string> keywords = parseStringToWords(name_);
  std::string lowGenre = convToLower(genre_);
  keywords.insert(lowGenre);

  return keywords;
}

bool Movie::isMatch(std::vector<std::string>& searchTerms) const{
  return true;
}

std::string Movie::displayString() const{
  std::stringstream display;
  display << name_ << "\nGenre: " << genre_ << " Rating: " << rating_ << "\n" << price_ << " " << qty_ << " left. " << endl;
  return display.str();
}

void Movie::dump(std::ostream& os) const{
  os << "movie" << endl;
  os << name_ << endl;
  os << std::setprecision(2) << setiosflags(ios::fixed) << price_ << endl;
  os << qty_ << endl;
  os << genre_ << endl;
  os << rating_ << endl;
}