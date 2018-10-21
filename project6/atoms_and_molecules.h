#ifndef ATOMS_AND_MOLECULES_H
#define ATOMS_AND_MOLECULES_H
#include<string>
using std::string;
#include<iostream>
#include<vector>
using std::vector;

class Molecule;
//Base class for three types elements
class Atom{
protected:
  string element;
  long bond;
  double weight;

public:
  //constructor
  Atom() = default;
  //members
  string get_id();
  double get_weight();
  long get_bond();
  friend Molecule operator+ (Molecule , Molecule );
  friend Molecule operator+ (Molecule , Atom );
  friend Molecule operator+ (Atom , Molecule );
  friend Molecule operator+ (Atom , Atom );
  friend Molecule operator* (Atom , long);
  friend Molecule operator* (long, Atom );

};

//Derived class
class Hydrogenyx : public Atom{
public:
  Hydrogenyx();
};
class Carbonyx : public Atom{
public:
  Carbonyx();
};
class Sulphuryx : public Atom{
public:
  Sulphuryx();
};

//Basic class for molecule
class Molecule{
public:
  long Hydrogenyx_num = 0;
  long Carbonyx_num = 0;
  long Sulphuryx_num = 0;

public:
  //constructor
  Molecule() = default;
  Molecule(Atom a){
    add_atoms(a,1);
  };
  Molecule(const Molecule &m){
    Hydrogenyx_num = m.Hydrogenyx_num;
    Carbonyx_num = m.Carbonyx_num;
    Sulphuryx_num = m.Sulphuryx_num;
  };
  //members
  double get_weight();
  string get_formula();
  void add_atoms(Atom, long = 1);
  Molecule& operator= (const Molecule &m);
  Molecule& operator= (const Atom &a);
  bool operator== (const Molecule &m);
  long is_stable();
  Molecule& operator+= (const Molecule &);
  Molecule& operator+= (const Atom &);
  void parseStr2Molecule(const string str, Molecule &m);
  string evaluate_chemical_equation(const string);

  //friends
  friend Molecule operator+ (Molecule , Molecule);
  friend Molecule operator+ (Molecule , Atom );
  friend Molecule operator+ (Atom , Molecule );
  friend Molecule operator+ (Atom , Atom );
  friend Molecule operator* (Atom , long);
  friend Molecule operator* (long, Atom );
};
#endif
