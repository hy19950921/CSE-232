#include "self_destructing.h"
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
#include "redact.h"

//This function returns the number of messages.
long SelfDestructingMessage::size(){
  return messages_.size();
}

//This function returns a vector of strings made up of each message in redacted form. Redact all alphabetic and digit characters.
vector<string> SelfDestructingMessage::get_redacted(){
  vector<string> result;
  for(long i = 0; i < messages_.size(); i++){
    result.push_back(redact_alphabet_digits(messages_[i]));
  }
  return result;
}

//This function returns the number of views remaining for that specific message.
long SelfDestructingMessage::number_of_views_remaining(long index){
  return remaining_n_of_views[index];
}

SelfDestructingMessage::SelfDestructingMessage(vector<string> m, long n) {
  messages_ = m;
  number_of_allowed_views_ = n;
  for(int i=0 ; i< messages_.size();i++){
    remaining_n_of_views.push_back(number_of_allowed_views_);
  }
}

//This function should return a const reference to the message string that was indexed.
//When a message is accessed by [], be sure to decrement the number_of_views_remaining for that message.
//If the index is not a legal index for a message (too large), throw a out_of_range exception.
//If the access is to a message with no remaining views, thow a invalid_argument exception.
string& SelfDestructingMessage::operator[](long index){
  if(index < 0 || index >= (messages_.size())){
    throw out_of_range("out_of_range");
  }
  else if(number_of_views_remaining(index) == 0){
    throw invalid_argument("invalid_argument");
  }
  remaining_n_of_views[index] -= 1 ;
  return messages_[index];
}

//The class allows << operator. Each line of the message (in redacted form) is prefixed by the number of views remaining,
//and should be inserted to the ostream.
ostream & operator<<(ostream &out, const SelfDestructingMessage &s){
  for(size_t i = 0; i < s.messages_.size(); i++){
    out << "0" << s.remaining_n_of_views[i] << ": " << redact_alphabet_digits((s.messages_[i])) << endl;
  }
  return out;
}

//The class should also implement the >> operator. It should extract a line from the istream and append it to the
//message list. Number of views remaining starts at number_of_allowed_views.
istream & operator>>(istream &in, SelfDestructingMessage &s){
  string line;
  getline(in,line);
  s.messages_.push_back(line);
  s.remaining_n_of_views.push_back(s.number_of_allowed_views_);
}

//This function  takes two arguments: an array of strings (messages to be added) and a long (the size of the array).
//Each string should be added to the list of messages (number of views remaining starts at number_of_allowed_views).
void SelfDestructingMessage::add_array_of_lines(string arr[], long size){
  for(size_t i = 0; i < size; i++){
    messages_.push_back(arr[i]);
    remaining_n_of_views.push_back(number_of_allowed_views_);
  }
}

//This function should transfer all the views remaining to the copy, and zero out the original.
//(This is to protect from trying to get more views by making copies of the object).
SelfDestructingMessage::SelfDestructingMessage(SelfDestructingMessage &s){
    messages_ = s.messages_;
    number_of_allowed_views_ = s.number_of_allowed_views_;
    remaining_n_of_views = s.remaining_n_of_views;
    for(size_t i = 0; i < s.remaining_n_of_views.size(); i++){
      s.remaining_n_of_views[i] = 0;
    }
}

// overload assignment method
// should return a ref to lhs
// param must be const
SelfDestructingMessage& SelfDestructingMessage::operator=(SelfDestructingMessage &s){
  messages_ = s.messages_;
  number_of_allowed_views_ = s.number_of_allowed_views_;
  remaining_n_of_views = s.remaining_n_of_views;
  for(size_t i = 0; i < s.remaining_n_of_views.size(); i++){
    s.remaining_n_of_views[i] = 0;
  }
  return *this;
}
