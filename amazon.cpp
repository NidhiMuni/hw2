#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "product.h"
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"
#include "mydatastore.h"

#include "book.h"
#include "movie.h"

using namespace std;
struct ProdNameSorter {
    bool operator()(Product* p1, Product* p2) {
        return (p1->getName() < p2->getName());
    }
};
void displayProducts(vector<Product*>& hits);

int main(int argc, char* argv[])
{
    if(argc < 2) {
        cerr << "Please specify a database file" << endl;
        return 1;
    }

    //MyDataStore m;
    //Movie* m = new Movie("movie", "prodName_", 12.00, 5, "genre_", "rating_");


    /*string name = "bookie";
    string author = "jk rowling";
    string isbn = "jergbe";
    double price = 4.09;
    int quantity = 6;
    Book b("hi", name, price, quantity, isbn, author);

    Movie* m = new Movie("movie", "prodName_", 12.00, 5, "genre_", "rating_");
    cout << "movie price " << m->getPrice() << endl;*/
    //cout << name + "\nAuthor: " + author + " ISBN: " + isbn + "\n" + price + " " + quantity + " left. " << endl;

    /*
    Test parseStringtoWords()
    
    set<string> test = parseStringToWords("J. I men's shoe I'll");
    set<string>::iterator it;
       for (it = test.begin(); it != test.end(); ++it) 
    {
      cout << *it << " ";
    }*/

    
    /*Test Set Union

    set<string> s1 = parseStringToWords("Cc Aa Bb Dd");
    set<string> s2 = parseStringToWords("Ee Bb Dd Ff");
    set<string> onion = setUnion(s1, s2);
    set<string>::iterator it;
    cout << "begin ";
    for (it = onion.begin(); it != onion.end(); ++it) {
      cout << *it << " ";
    }
    cout << "end " << endl;
    */

    /*Test Set Intersection */

    /*set<string> s1 = parseStringToWords("Cc Aa Bb Dd");
    set<string> s2 = parseStringToWords("Ee Bb Dd Ff");
    set<string> onion = setIntersection(s1, s2);
    set<string>::iterator it;
    cout << "begin ";
    for (it = onion.begin(); it != onion.end(); ++it) {
      cout << *it << " ";
    }
    cout << "end " << endl;*/
    

    

    


    /****************
     * Declare your derived DataStore object here replacing
     *  DataStore type to your derived type
     ****************/
    MyDataStore ds;

    // Instantiate the individual section and product parsers we want
    ProductSectionParser* productSectionParser = new ProductSectionParser;
    productSectionParser->addProductParser(new ProductBookParser);
    productSectionParser->addProductParser(new ProductClothingParser);
    productSectionParser->addProductParser(new ProductMovieParser);
    UserSectionParser* userSectionParser = new UserSectionParser;

    // Instantiate the parser
    DBParser parser;
    parser.addSectionParser("products", productSectionParser);
    parser.addSectionParser("users", userSectionParser);

    // Now parse the database to populate the DataStore
    if( parser.parse(argv[1], ds) ) {
        cerr << "Error parsing!" << endl;
        return 1;
    }

    cout << "=====================================" << endl;
    cout << "Menu: " << endl;
    cout << "  AND term term ...                  " << endl;
    cout << "  OR term term ...                   " << endl;
    cout << "  ADD username search_hit_number     " << endl;
    cout << "  VIEWCART username                  " << endl;
    cout << "  BUYCART username                   " << endl;
    cout << "  QUIT new_db_filename               " << endl;
    cout << "====================================" << endl;

    vector<Product*> hits;
    bool done = false;
    while(!done) {
        cout << "\nEnter command: " << endl;
        string line;
        getline(cin,line);
        stringstream ss(line);
        string cmd;
        if((ss >> cmd)) {
            if( cmd == "AND") {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 0);
                displayProducts(hits);
            }
            else if ( cmd == "OR" ) {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 1);
                displayProducts(hits);
            }
            else if ( cmd == "QUIT") {
                string filename;
                if(ss >> filename) {
                    ofstream ofile(filename.c_str());
                    ds.dump(ofile);
                    ofile.close();
                }
                done = true;
            } else if ( cmd == "ADD" ) {
              string username;
              int searchHitNumber;
              ss >> username;
              ss >> searchHitNumber;
              if (ds.userExists(username) == true){
                ds.addToCart(username, searchHitNumber, hits);
              } else {
                cout << "Invalid request" << endl;
                cerr << "Invalid request" << endl;
              }
            } else if ( cmd == "VIEWCART" ) {
              string username;
              ss >> username;
              if (ds.userExists(username) == true){
                ds.viewCart(username);
              } else {
                cout << "Invalid username" << endl;
                cerr << "Invalid username" << endl;
              }
            } else if ( cmd == "BUYCART" ) {
              string username;
              ss >> username;
              
              if (ds.userExists(username) == true){
                ds.buyCart(username);
              } else {
                cout << "Invalid username" << endl;
                cerr << "Invalid username" << endl;
              }
            } else {
                cout << "Unknown command" << endl;
            }
        }
    }
    return 0;
    
}

void displayProducts(vector<Product*>& hits)
{
    int resultNo = 1;
    if (hits.begin() == hits.end()) {
    	cout << "No results found!" << endl;
    	return;
    }
    std::sort(hits.begin(), hits.end(), ProdNameSorter());
    for(vector<Product*>::iterator it = hits.begin(); it != hits.end(); ++it) {
        cout << "Hit " << setw(3) << resultNo << endl;
        cout << (*it)->displayString() << endl;
        cout << endl;
        resultNo++;
    }
}
