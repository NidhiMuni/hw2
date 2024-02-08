#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include "datastore.h"
#include "product.h"
#include "user.h"
#include <iostream>
#include <set>
#include <vector>
#include <map>

class MyDataStore : public DataStore {
  public: 
  MyDataStore();
  ~MyDataStore(); 
  void addProduct(Product* p);
  void addUser(User* u);
  std::vector<Product*> search(std::vector<std::string>& terms, int type);
  void dump(std::ostream& ofile);
  void addToCart(std::string username, int index, std::vector<Product*> hits);
  void viewCart(std::string username);
  void buyCart(std::string username);
  void printProducts();
  void printUsers();
  void printKeywordMap();
  bool userExists(std::string username);
  
  private:
  std::set<Product*> products_;
  std::map<std::string, User*> users_;
  std::map<std::string, std::set<Product*>> keywordMap_; 
  std::map<std::string, std::vector<Product*>> carts_;
};

#endif