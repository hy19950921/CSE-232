#include "redact.h"
#include<string>
using std::string;
#include<vector>
using std::vector;
#include<algorithm>
using std::replace;

//This function returns a string only has octothorpes ('#') instead of the original characters.
string redact_all_chars(const string & str){
  string input = str;
  for(size_t i = 0; i < input.size(); i++){
    input[i] = '#';
  }
  return input;
}

// returns a string that is the similar to the argument string, but only has octothorpes ('#') instead of
//the original characters if those characters were letters or digits (a-zA-Z0-9).
string redact_alphabet_digits(const string & str){
  string input = str;
  for(size_t i = 0; i < input.size(); i++){
    if(isdigit(input[i])|| isalpha(input[i])){
      input[i] = '#';
    }
  }
  return input;
}

// It returns a string that is the similar to the argument string, but only has octothorpes ('#') instead of
//the original characters if those characters composed a word in words_to_redact.
string redact_words(const string & str, const vector<string> & words_to_redact){
  string input = str;
  for(auto i : words_to_redact){
    while(input.find(i) != string::npos){
      input.replace(input.find(i),i.size(),redact_all_chars(i));
    }
  }
  return input;
}
