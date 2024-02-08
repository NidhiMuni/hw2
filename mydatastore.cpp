#include "mydatastore.h"
#include "util.h"
#include <iomanip>

//for testing
#include <iostream>

MyDataStore::MyDataStore() : DataStore(){
  /*products_ = new std::set<Product*>;
  users_ = new std::set<User*>;
  keywordMap_ = new std::map<std::string, std::set<Product*>> ; 
  carts_ = new std::map<std::string, std::vector<Product*>> ;*/
}

MyDataStore::~MyDataStore(){
  std::set<Product*>::iterator it;
  for(it = products_.begin(); it != products_.end(); ++it) {
    delete *it;
  }
  std::map<std::string, User*>::iterator it2;
  for(it2 = users_.begin(); it2 != users_.end(); ++it2) {
    delete it2->second;
  }
}

void MyDataStore::addProduct(Product* p){  
  std::set<Product*>::iterator it = products_.find(p);
  if (it == products_.end()) { // if product does not exist
    std::set<std::string> keywords = p->keywords();
    std::set<std::string>::iterator itKey;
    for(itKey = keywords.begin(); itKey != keywords.end(); ++itKey) {
      keywordMap_[*itKey].insert(p);
    }
    products_.insert(p);
  }
}

void MyDataStore::addUser(User* u){
  std::string username = u->getName();
  users_[username] = u;
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type){
  std::vector<Product*> prods;

  //get all products with those keywords
  std::set<Product*> prodsSet;
  for (size_t i = 0; i < terms.size(); i++){
    std::string term = terms[i];
    std::set<Product*> termProducts = keywordMap_[term];
    std::set<Product*>::iterator iterProds;
    for(iterProds = termProducts.begin(); iterProds != termProducts.end(); ++iterProds){
      prodsSet.insert(*iterProds);
    }
  }

  if (type == 1){
     //convert set to vector
    std::set<Product*>::iterator iterVec;
    for(iterVec = prodsSet.begin(); iterVec != prodsSet.end(); ++iterVec){
      prods.push_back(*iterVec);
    }
    return prods; //OR

  } else if (type == 0){ //AND
    std::set<Product*>::iterator it;
    for(it = prodsSet.begin(); it != prodsSet.end(); ++it){
      Product* p = *it;
      std::set<std::string> keywords = p->keywords();

      std::set<std::string> termSet;
      for (size_t i = 0; i < terms.size(); i++){
        termSet.insert(terms[i]);
      }
      std::set<std::string> intersection = setIntersection(keywords, termSet);

      bool allMatch = true;
      std::set<std::string>::iterator intersectionIt;
      std::set<std::string>::iterator keywordFinder;
      for(intersectionIt = termSet.begin(); intersectionIt != termSet.end(); ++intersectionIt){
        std::string term = *intersectionIt;
        keywordFinder = keywords.find(term);
        if (keywordFinder == keywords.end()){ //not found           
          allMatch = false;
          break;
        }
      }

      if (allMatch == true){
        //std::cout << "pushin " << p->getName() << std::endl;
        prods.push_back(p);
      }
    }
  }
  return prods;
}

void MyDataStore::dump(std::ostream& ofile){
  ofile << "<products>"<< std::endl;
  std::set<Product*>::iterator it;
  for(it = products_.begin(); it != products_.end(); ++it) {
    (*it)->dump(ofile);
  }
  ofile << "</products>" << std::endl;
  ofile << "<users>" << std::endl;
  std::map<std::string, User*>::iterator it2;
  for(it2 = users_.begin(); it2 != users_.end(); ++it2) {
    User* u = it2->second;
    u->dump(ofile);
  }
  ofile << "</users>" << std::endl;
}

void MyDataStore::addToCart(std::string username, int index, std::vector<Product*> hits){
  std::vector<Product*> p = carts_[username];
  p.push_back(hits[index - 1]);
  carts_[username] = p;
}

void MyDataStore::viewCart(std::string username){
  std::vector<Product*> userCart = carts_[username];
  int index = 1;
  for(size_t i = 0; i < userCart.size(); i++) {
    Product* p = userCart[i];
    if (p != nullptr){
      std::cout << "Item " << index << std::endl;
      std::cout << std::setprecision(2) << p->displayString() << std::endl;
      index++;
    }
  }
}

void MyDataStore::buyCart(std::string username){
  double budget = users_[username]->getBalance();
  double initBudget = budget;
  std::vector<Product*> cart = carts_[username];

  for (size_t i = 0; i < cart.size(); i++){
    Product* p = cart[i];
    if (p != nullptr){
      double price = p->getPrice();
      int qty = p->getQty();

      if (budget-price >= 0.0 && qty >= 1){
        budget = budget - price;
        p->subtractQty(1);
        carts_[username][i] = nullptr;
      }
    }
  }

  users_[username]->deductAmount(initBudget - budget); 
}

void MyDataStore::printProducts(){
  std::cout << "Products: "<< std::endl;
  std::set<Product*>::iterator it;
  for(it = products_.begin(); it != products_.end(); ++it) {
    std::cout << (*it)->displayString() << std::endl;
  }
  std::cout << std::endl;
}

void printUsers(){

}

void MyDataStore::printKeywordMap(){
  std::cout << "Keyword Map: "<< std::endl;
  std::map<std::string, std::set<Product*>>::iterator it;
  for(it = keywordMap_.begin(); it != keywordMap_.end(); ++it) {
    std::cout << "Keyword = " << it->first << std::endl;
    std::set<Product*> productsMapped = it->second;
    std::cout << "Products = " << std::endl;
    std::set<Product*>::iterator prodIter;
    for(prodIter = productsMapped.begin(); prodIter != productsMapped.end(); ++prodIter) {
      Product* a = *prodIter;
      std::cout << a->getName() << std::endl;
    }
  }
  std::cout << std::endl;
}

bool MyDataStore::userExists(std::string username){
  std::map<std::string, User*>::iterator it = users_.find(username);
  if (it == users_.end()){
    return false;
  } else {
    return true;
  }
}