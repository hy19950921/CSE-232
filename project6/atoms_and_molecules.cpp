#include "atoms_and_molecules.h"
#include<string>
using std::string;
using std::to_string;
#include<algorithm>
using std::sort;
using std::reverse;
#include<vector>
using std::vector;
#include<iomanip>
using std::setprecision;
#include<iostream>
using std::endl;
using std::cout;
using std::fixed;
#include <numeric>
using std::accumulate;


//Using inheritance to assign the value for three types of elements
Hydrogenyx::Hydrogenyx() : Atom(){
  element = "Hh";
  bond = 1;
  weight = 2.4;
}

Carbonyx::Carbonyx() : Atom(){
  element = "Cc";
  bond = 4;
  weight = 5.6;
}

Sulphuryx::Sulphuryx() : Atom(){
  element = "Ss";
  bond = 7;
  weight = 10.8;
}

//This function returns a string of the id for one atom
string Atom::get_id(){
  return element;
}

//This function returns a double value for the weight of one atom
double Atom::get_weight(){
  return weight;
}

//This function returns a double value for the total weight of a Molecule
double Molecule::get_weight(){
  Hydrogenyx h;
  Carbonyx c;
  Sulphuryx s;
  double result;
  result = h.get_weight() * Hydrogenyx_num + c.get_weight() * Carbonyx_num + s.get_weight() * Sulphuryx_num;
  return result;
}

//This function add the quality of specific atom
void Molecule::add_atoms(Atom a, long number){
  if(a.get_id() == "Hh"){
    Hydrogenyx_num += number;
  }
  else if(a.get_id() == "Ss"){
    Sulphuryx_num += number;
  }
  else if(a.get_id() == "Cc"){
    Carbonyx_num += number;
  }
}

//This function returns a string of the whole formula
string Molecule::get_formula(){
  Hydrogenyx h;
  Sulphuryx s;
  Carbonyx c;
  string result;
  if(Carbonyx_num > 0){
    result += c.get_id();
    if(Carbonyx_num > 1){
      result += to_string(Carbonyx_num);
    }
  }
  if(Hydrogenyx_num > 0){
    result += h.get_id();
    if(Hydrogenyx_num > 1){
      result += to_string(Hydrogenyx_num);
    }
  }
  if(Sulphuryx_num > 0){
    result += s.get_id();
    if(Sulphuryx_num > 1){
      result += to_string(Sulphuryx_num);
    }
  }
  return result;
}

//overload assignment method takes the other molecule as the argument
Molecule& Molecule::operator= (const Molecule &m){
  Hydrogenyx_num = m.Hydrogenyx_num;
  Carbonyx_num = m.Carbonyx_num;
  Sulphuryx_num = m.Sulphuryx_num;
  return *this;
}
//assignment method takes atom as the argument
Molecule& Molecule::operator= (const Atom &a){
  add_atoms(a);
  return *this;
}

//This function is to check if two molecules are equal by checking the same number of each type of atom
bool Molecule::operator== (const Molecule &m){
  if(Hydrogenyx_num == m.Hydrogenyx_num && Carbonyx_num == m.Carbonyx_num && Sulphuryx_num == m.Sulphuryx_num){
    return true;
  }
  else{
    return false;
  }
}

long Molecule::is_stable(){
  vector<long> bonds;
  Hydrogenyx h;
  Carbonyx c;
  Sulphuryx s;
  for(size_t i = 0; i < Sulphuryx_num; i++){
    bonds.push_back(7);
  }
  for(size_t j = 0; j < Carbonyx_num; j++){
    bonds.push_back(4);
  }
  for(size_t k = 0; k < Hydrogenyx_num; k++){
    bonds.push_back(1);
  }
  bool is_done = false;
  while(!is_done){
    sort(bonds.begin(), bonds.end());
    reverse(bonds.begin(), bonds.end());
    if(bonds.empty() || (bonds[0] == 0)){
      return 0;
    }
    // Do bonds
    long num_bonds = bonds[0];
    for(size_t i = 1; i < (num_bonds + 1); i++){
      if((i >= bonds.size()) || (bonds[i] == 0)){
        is_done = true;
        break;
      }
      --bonds[0];
      --bonds[i];
    }
  }
  return accumulate(bonds.begin(), bonds.end(),0);
}

//This operator add two molecules
Molecule operator+ (Molecule m1, Molecule m2){
  Hydrogenyx h;
  Carbonyx c;
  Sulphuryx s;
  Molecule result(m1);
  result.add_atoms(h, m2.Hydrogenyx_num);
  result.add_atoms(c, m2.Carbonyx_num);
  result.add_atoms(s, m2.Sulphuryx_num);
  return result;
}

//This operator add one molecule and one atom
Molecule operator+ (Molecule m, Atom a){
  Molecule result(m);
  result.add_atoms(a);
  return result;
}

//This operator add one atom and one molecule
Molecule operator+ (Atom a, Molecule m){
  Molecule result(m);
  result.add_atoms(a);
  return result;
}

//This operator add two atoms

Molecule operator+ (Atom a1, Atom a2){
  Molecule result;
  result.add_atoms(a1);
  result.add_atoms(a2);
  return result;
}

//This operator times a number with atom
Molecule operator* (long num, Atom a){
  Molecule result;
  result.add_atoms(a, num);
  return result;
}

//This operator times an atom with a number
Molecule operator* (Atom a, long num){
  Molecule result;
  result.add_atoms(a, num);
  return result;
}

//This operator plus and equal the other atom
Molecule& Molecule::operator+= (const Atom & a){
  add_atoms(a);
  return *this;
}

//This operator plus and equal the other molecule
Molecule& Molecule::operator+= (const Molecule & m){
  Hydrogenyx h;
  Carbonyx c;
  Sulphuryx s;
  add_atoms(h, m.Hydrogenyx_num);
  add_atoms(c, m.Carbonyx_num);
  add_atoms(s, m.Sulphuryx_num);
  return *this;
}

//This function transform string to molecule
void Molecule::parseStr2Molecule(const string str, Molecule &m){
	int index = 0;
	for(;index<str.length();){
		if(str[index]=='C'){         //If current atom is Carbonyx
			int num = 0;
			int k = 2;
			while(index + k < str.length() && str[index+k] >= '0' && str[index+k] <= '9'){
				num += num*10+str[index+k]-'0';           //count the number of the Carbonyx
				k++;
			}
			if(num == 0) num=1;
			Carbonyx c;
			m.add_atoms(c,num);
			index += k;
		}
		else if(str[index]=='S'){        //If current atom is Sulphuryx
			int num = 0;
			int k = 2;
			while(index+k<str.length() && str[index+k]>='0' && str[index+k]<='9'){
				num += num*10+str[index+k]-'0';
				k++;
			}
			if(num == 0) num=1;
			Sulphuryx s;
			m.add_atoms(s,num);
			index += k;
		}
		else if(str[index] == 'H'){            //If current atom is Hydrogenyx
			int num=0;
			int k=2;
			while(index+k<str.length() && str[index+k]>='0' && str[index+k]<='9'){
				num += num*10+str[index+k]-'0';
				k++;
			}
			if(num == 0) num=1;
			Hydrogenyx h;
			m.add_atoms(h,num);
			index += k;
		}
		else{
			index++;
		}
	}
}

//This function returns three different forms
string Molecule::evaluate_chemical_equation(const string str){
  string result = "";
  if(str.find("->")!=string::npos){    //This is a Transformation
  	result += "This is a Transformation\n";
  	Molecule m1,m2;
  	int index = str.find("->");
  	parseStr2Molecule(str.substr(0,index),m1);
  	parseStr2Molecule(str.substr(index+1),m2);
  	if(m1 == m2){
  	  	result += "The transformation is valid!!! ";
  	  	if(m1.is_stable() == 0){
  	  		result += "and results in a stable molecule!!!\n";
        }
		else{
			result += "and results in an unstable molecule with " + to_string(m1.is_stable()) + " loose bonds\n";
    }
		string weightStr = to_string(m1.get_weight());
		result += "The resulting molecule is " + m1.get_formula() + " and has the weight " + weightStr.substr(0,weightStr.size()-5) + "\n";
  }
	else{
	  	result += m1.get_formula() + " cannot be transformed to " + m2.get_formula() + "\n";
    }
  }
  else if(str.find("+") != string::npos){           //This is a Reaction
  	result += "This is a Reaction\nThe resulting molecule is ";
  	Molecule m;
  	parseStr2Molecule(str,m);
  	string weightStr = to_string(m.get_weight());
  	result += m.get_formula() + " and has the weight " + weightStr.substr(0,weightStr.size()-5);
  	if(m.is_stable() == 0){
  		result += " and is stable!!!\n";
    }
	else{
		result += " and is unstable with " + to_string(m.is_stable()) + " loose bonds\n";
  }
}
  else{                 //This is a Simple Molecule
  	result += "This is a Simple Molecule\nThe molecule ";
  	Molecule m;
  	parseStr2Molecule(str,m);
  	string weightStr = to_string(m.get_weight());
  	result += m.get_formula()+ " has the weight " + weightStr.substr(0,weightStr.size()-5);
  	if(m.is_stable() == 0){
  		result += " and is stable!!!\n";
    }
	else{
		result += " and is unstable with " + to_string(m.is_stable()) + " loose bonds\n";
  }
}
  return result;
}
