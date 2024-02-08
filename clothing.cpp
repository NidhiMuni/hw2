#include "product.h"
#include "clothing.h"
#include "util.h"
#include <sstream>
#include <iomanip>

using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand) 
: Product (category, name, price, qty){
  size_ = size;
  brand_ = brand;
}

Clothing::~Clothing(){

}

std::set<std::string> Clothing::keywords() const{
  set<string> productName = parseStringToWords(name_);
  set<string> brandWords = parseStringToWords(brand_);
  set<string> keywords = setUnion(productName, brandWords);

  return keywords;
}

bool Clothing::isMatch(std::vector<std::string>& searchTerms) const{
  return true;
}

std::string Clothing::displayString() const{
  std::stringstream display;
  display << name_ << "\nSize: " << size_ << " Brand: " << brand_ << "\n" << price_ << " " << qty_ << " left. " << endl;
  return display.str();
}

void Clothing::dump(std::ostream& os) const{
  os << "clothing" << endl;
  os << name_ << endl;
  os << std::setprecision(2) << setiosflags(ios::fixed) << price_ << endl;
  os << qty_ << endl;
  os << size_ << endl;
  os << brand_ << endl;
}