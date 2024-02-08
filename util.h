#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>

/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
  std::set<T> intersectionSet;
  typename std::set<T>::iterator interIt;

  //for each element of s1, insert if it exists n s2
  for (interIt = s1.begin(); interIt != s1.end(); ++interIt) 
  {
    typename std::set<T>::iterator it2 = s2.find(*interIt);
    if (it2 != s2.end()){ //it exists in set 2
      intersectionSet.insert(*interIt);
    }
  }
  
  return intersectionSet;
}

//Create a set with all elements from both sets
template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
  std::set<T> unionSet;
  typename std::set<T>::iterator unionIt;

  for (unionIt = s1.begin(); unionIt != s1.end(); ++unionIt) 
  {
    unionSet.insert(*unionIt);
  }

  for (unionIt = s2.begin(); unionIt != s2.end(); ++unionIt) 
  {
    unionSet.insert(*unionIt);
  }

  return unionSet;
}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
