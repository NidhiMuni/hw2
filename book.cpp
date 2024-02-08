#include "product.h"
#include "book.h"
#include "util.h"
#include <sstream>
#include <iomanip>

using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty, std::string isbn, std::string author) 
: Product (category, name, price, qty){
  isbn_ = isbn;
  author_ = author;
}

Book::~Book(){

}

std::set<std::string> Book::keywords() const{
  set<string> productName = parseStringToWords(name_);
  set<string> author = parseStringToWords(author_);
  set<string> keywords = setUnion(productName, author);
  std::string lowISBN = convToLower(isbn_);
  keywords.insert(lowISBN);

  return keywords;
}

bool Book::isMatch(std::vector<std::string>& searchTerms) const{
  return true;
}

std::string Book::displayString() const{
  std::stringstream display;
  //display << name_ << "\nAuthor: " << author_ << " ISBN: " << isbn_ << "\n" << price_ << " " << qty_ << " left. " << endl;
  display << name_ << endl;
  display << "Author: " << author_ << " ISBN: " << isbn_ << endl;
  display << price_ << " " << qty_ << " left. " << endl;
  return display.str();
}

void Book::dump(std::ostream& os) const{
  os << "book" << endl;
  os << name_ << endl;
  os << std::setprecision(2) << setiosflags(ios::fixed) << price_ << endl;
  os << qty_ << endl;
  os << isbn_ << endl;
  os << author_ << endl;
}