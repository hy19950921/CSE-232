#include<iostream>
using std::cout; using std::endl; using std::cin;
#include<fstream>
using std::ifstream;
#include<string>
using std::string;
using std::to_string;
#include<vector>
using std::vector;
#include<sstream>
using std::istringstream; using std::ostringstream; using std::stringstream;
#include<map>
using std::map;
#include<algorithm>
using std::sort;
#include<iomanip>
using std::setprecision;
using std::fixed;

//Create sturcture to store information about store name, location, item name, quality and price.
struct Item{
  string store;
  string location;
  string item;
  long quality;
  double price;
  Item() = default;
  Item(string s, string l,string i, long q, double p) {store = s; location = l; item = i; quality = q; price = p;}
};

//Create sturcture to store the information from the shopping list, including shop_item and the quality.
struct Shopping{
  string shop_item;
  long shop_quality;
  Shopping() = default;
  Shopping(string si, long sq) {shop_item = si; shop_quality = sq;}
};

//Create a function to read integer from a given string and this function should return long.
long read_num(const string& s){
  stringstream ss;
  ss << s;
  long number;
  ss >> number;
  return number;
}

//This function is from lecture video and it split string into a vector<string>.
void split(const string &s, vector<string> &elems, char sep) {
    istringstream iss(s);
    string item;
    while(getline(iss, item, sep)){
      if(item[0] == '$'){
        item = item.substr(1,item.size()-1);
      }
      elems.push_back(item);
    }
}

int main(){
  string line;
  map<string,long> item_list;
  vector<Item> all_item;
  vector<string> store_list;
  vector<string> store_item;
  long store_number;
  getline(cin,line);
  store_number = read_num(line);
  cout << fixed << setprecision(2);
  cout << "Store Related Infomation (ordered by in-file order):" << endl;
  cout << "There are " << store_number << " store(s)." << endl;
  for(long i=0; i < store_number; i++){
    string store_name;
    string store_location;
    vector<string> item_info;
    vector<string> store_item;
    getline(cin,line);    //read store name.
    store_name = line;
    getline(cin,line);     //read store location.
    store_location = line;
    store_list.push_back(store_name);
    while(getline(cin,line)){
      if(line.empty() == false){         //when the line is not empty line then split item information to a vector<string>.
        split(line,item_info,',');
        Item CNM(store_name,store_location,item_info[0],stol(item_info[1]),stod(item_info[2]));       //add value to structure.
        item_list[CNM.item] += CNM.quality;
        store_item.push_back(CNM.item);
        item_info.clear();
        all_item.push_back(CNM);
      }
      else{
        cout << store_list[i] << " has " << store_item.size() << " distinct items." << endl;;
        store_item.clear();
        break;
      }
    }
  }
  cout << endl;
  cout << "Item Related Infomation (ordered alphabetically):" << endl;
  cout << "There are " << item_list.size() << " distinct item(s) avaliable for purchase." << endl;
  for(auto j : item_list){
    cout << "There are " << j.second<< " " << j.first <<"(s)." << endl;
  }
  cout << endl;
  cout << "Shopping:" << endl;

//The method comes from lecture vedio.
  sort(all_item.begin(),
        all_item.end(),
        [](const Item& i1, const Item& i2){
 	   return i1.price < i2.price;
        }
     );

  getline(cin,line);       //read shopping list.
  long shopping;
  long shopping_size;
  double total_price = 0;
  shopping = read_num(line);        //read shopping item from shopping list.
  for(long k=0; k < shopping; k++){
    string shopping_item;
    long shopping_quality;
    long buy_quality;
    while(getline(cin,line)){
      vector<string> shop_location;
      vector<long> buy_number;
      vector<string> buy_store;
      double single_price = 0;
      shopping_quality = read_num(line);
      buy_quality = shopping_quality;
      shopping_size = to_string(shopping_quality).size();
      shopping_item = line.substr(shopping_size+1,line.size()-shopping_size-1);
      Shopping CAO(shopping_item,shopping_quality);            //add value to sturcture.
      for(auto l : all_item){
        if(CAO.shop_item == l.item){
          if(buy_quality > l.quality){                          //if the store' quality is less than the quality from the shopping list.
            single_price += l.quality * l.price;
            buy_quality -= l.quality;
            buy_number.push_back(l.quality);                   //add quality bought, store location and store name into three different vector.
            shop_location.push_back(l.location);
            buy_store.push_back(l.store);
          }
          else{
            single_price += buy_quality * l.price;
            buy_number.push_back(buy_quality);
            shop_location.push_back(l.location);
            buy_store.push_back(l.store);
            buy_quality = 0;
          }
        }
    }
    cout << "Trying to order " << shopping_quality << " " << shopping_item << "(s)." << endl;
    long store_sell = 0;
    for(auto m : all_item){
      if(shopping_item == m.item){
        store_sell += 1;                //calculate how many stores sell this item you found.
      }
    }
    cout << store_sell << " store(s) sell " << shopping_item << "." << endl;
    cout << "Total price: $" << single_price << endl;
    total_price += single_price;
    for(unsigned long h=0; h < buy_number.size(); h++){
      if(buy_number[h] >0){
        cout << "Order " << buy_number[h] << " from " << buy_store[h] << " in " << shop_location[h] << endl;
      }
    }
    cout << endl;
  }
}
cout << "Be sure to bring $" << total_price << " when you leave for the stores." << endl;
}



/*
#ifndef SHOP_H
#define SHOP_H

#include<string>
using std::string;
#include<vector>
using std::vector;


struct Item{
  string store;
  string location;
  string item;
  long quality = 0 ;
  double price = 0.0;
  Item()=default;
  Item(string s, string l, string i, long q, double p) : store(s), location(l), item(i), quality(q), price(p) {};
  explicit Item(string line);
};


void split(const string &, vector<string> &, char);

#endif
*/
