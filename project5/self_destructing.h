#ifndef SELF_DESTRUCTING_H
#define SELF_DESTRUCTING_H

#include <string>
using std::string;
#include<string>
using std::string;
#include<vector>
using std::vector;
#include<sstream>
using std::ostringstream; using std::istringstream; using std::ostream; using std::istream;
#include<stdexcept>
using std::out_of_range;
using std::invalid_argument;
#include<iostream>
using std::endl; using std::cin;
#include <ios>

class SelfDestructingMessage {
private:
  vector<string> messages_;
  long number_of_allowed_views_ = 0; //intial
  vector<long> remaining_n_of_views;

public:
  //constructors
  SelfDestructingMessage() = default;
  SelfDestructingMessage(vector<string> m, long n);
  SelfDestructingMessage(SelfDestructingMessage&); // copy constructor


  //getters
  vector<string> messages() const {return messages_;}
  long number_of_allowed_views() const {return number_of_allowed_views_;}

  //setters
  void messages(vector<string> v) {messages_ = v;}
  void number_of_allowed_views(long val) {number_of_allowed_views_ = val;}

  //members
  long size();
  vector<string> get_redacted();
  long number_of_views_remaining(long);
  string& operator[](size_t index);
  void add_array_of_lines(string [], long);
  SelfDestructingMessage& operator=(SelfDestructingMessage &s);

  //friend
  friend ostream &operator<<(ostream&, const SelfDestructingMessage&);
  friend istream & operator>>(istream &, SelfDestructingMessage &);
};

#endif
