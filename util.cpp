#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
    set<string> keywords;
    stringstream ss;
    ss << rawWords;

    string temp;
    while (!ss.fail()){
        ss >> temp;

        if (temp.length() >= 2){
          //array that stores where to split the string
          int split[temp.length()];
          int splitTimes = 0;

          //whatever index has punctuation, it should be split
          for (unsigned int i = 0; i < temp.length(); i++){
            if (ispunct(temp[i])){
              split[splitTimes] = i;
              splitTimes ++;
            }
          }

          if (splitTimes == 0){
            temp = convToLower(temp);
            keywords.insert(temp);
          } else {

            //split at the stored indeces, then add
            string add;
            int prev = 0;
            for(int j = 0; j < splitTimes; j++){
              add = temp.substr(prev, split[j]);
              prev = split[j]+1;

              if (add.length() >= 2){
                add = convToLower(add);
                keywords.insert(add);
              }
            }

            //add whatever remains after all splitting
            add = temp.substr(prev);
            if (add.length() >= 2){
              add = convToLower(add);
              keywords.insert(add);
            }
          }
        }
    }

    return keywords;

}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
