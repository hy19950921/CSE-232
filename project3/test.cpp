#include<iostream>
using std::cout; using std::endl;
#include <string>
using std::string;
using std::stol;
#include<vector>
using std::vector;
#include<algorithm>
using std::sort;

struct compare_string_value{
    bool operator()(string l, string r){
        return stol(r) > stol(l);
    }
};

int main(){
  vector<string> numbers;
  numbers.push_back("-780");
  numbers.push_back("1000");
  numbers.push_back("-250");
  numbers.push_back("250");
  numbers.push_back("100");
  numbers.push_back("600");
  sort(numbers.begin(), numbers.end(), compare_string_value());
  for(auto i : numbers){
    cout << i << ", ";
  }

}
