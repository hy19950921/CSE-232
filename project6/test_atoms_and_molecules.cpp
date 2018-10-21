#include<iostream>
using std::cout;
using std::endl;
#include <iomanip>
#include <string>
#include "atoms_and_molecules.h"


int main()
{

	// compile this file with g++ -std=c++14 -Wall test_atoms_and_molecules.cpp

	cout << std::fixed << std::setprecision(1) << std::boolalpha;
	// Creating the elements 	
	Hydrogenyx h;
	cout << "This is an atom of " << h.get_id()<< endl;
		//Should print out:
		//This is an atom of Hh
	Carbonyx c;
	cout << "This is an atom of " << c.get_id()<< endl;
		//Should print out:
		//This is an atom of Cc
	Sulphuryx s;
	cout << "This is an atom of " << s.get_id()<< endl;
		//Should print out:
		//This is an atom of Ss

	// Creating an empty molecule 
	Molecule m1;
	cout << "This molecule has the formula " << m1.get_formula() << " and weight " << m1.get_weight() << endl; 
		//Should print out:
		//This molecule has the formula  and weight 0
	
	// Creating a molecule from some kind of atom
	Molecule m2(c);
	cout << "This molecule has the formula " << m2.get_formula() << " and weight " << m2.get_weight() << endl; 
		//Should print out:
		//This molecule has the formula Cc1 and weight 5.6
	
// Note: the default copy constructor should work just fine
	// Creating a molecule from some molecule
	Molecule m3(m2);
	cout << "This molecule has the formula " << m3.get_formula() << " and weight " << m3.get_weight() << endl; 
		//Should print out:
		//This molecule has the formula Cc1 and weight 5.6

// Note: the default assignment operator should work just fine
	// Assigning a molecule to another molecule
	Molecule m4 = m2;
	cout << "This molecule has the formula " << m4.get_formula() << " and weight " << m4.get_weight() << endl; 
		//Should print out:
		//This molecule has the formula Cc1 and weight 5.6

//Note: from this point you need to start thinking about templates
	// adding n atoms of some atom type to a molecule
	Molecule m5;
	m5.add_atoms(s,5);
	cout << "After adding atoms, the molecule has the formula " << m5.get_formula() << " and weight " << m5.get_weight() << endl; 
		//Should print out:
		//After adding atoms, the molecule has the formula Ss5 and weight 54.0

	// assigning an atom to a molecule
	Molecule m6 = s;
	cout << "This molecule has the formula " << m6.get_formula() << " and weight " << m6.get_weight() << endl; 
		//Should print out:
		//This molecule has the formula Ss1 and weight 10.8

	// checking if 2 molecules are equal
	cout << (m6 == m5) << endl;
		//Should print out:
		//false
	m6.add_atoms(s,4);

	cout << (m6 == m5) << endl;
		//Should print out:
		//true
	
	// checking for stability of molecule
	cout << m6.is_stable() <<endl; 
		//Should print out:
		//27
	Molecule m7;
	m7.add_atoms(h,4);
	//m7.add_atoms(c);  
	cout << m7.is_stable() <<endl; 
		//Should print out:	
		//0

	// using operators to do the above more conveniently (again, templates are your friend here
			// Note: it makes no sense to multiply 2 atoms together
	Molecule m8; 
	m8.add_atoms(c);		// by default, add_atoms should add a single specified atom
	m8 = m3 + m6;
	m8 = m8 + c;
	m8 = c + m8;
	m8+=  3 * c;
	m8+=  h * 2;
	m8+=  h + c;
	m8+=  s + c * 2 + h + s * 2;
	cout << "After some reactions, the molecule has the formula " << m8.get_formula() << " and weight " << m8.get_weight() << endl; 
		//Should print out:
		//After some reactions, the molecule has the formula Cc9Hh4Ss8 and weight 146.4

//Note: this function basically is a bunch of string processing. Once you've extracted the necessary atom information, the
//rest should be already implemented 

	// Evaulating equation	
	string eq1 = "Cc3";
	Molecule m9;
	cout << m9.evaluate_chemical_equation(eq1); 
		//Should print out:
		//This is a Simple Molecule
		//The molecule Cc1 has the weight 5.6 and is unstable with 4 loose bonds


	// Evaulating equation	
	string eq2 = "Cc3 + Ss3Cc1Hh2";
	Molecule m10; 
	cout << m10.evaluate_chemical_equation(eq2); 
		//Should print out:
		//This is a Reaction
		//The resulting molecule is Cc4HhSs3 and has the weight 57.2 and is unstable with 14 loose bonds

	// evaulating equation	
	string eq3 = "Cc4Hh2Ss1 + Ss3Cc1Hh2 -> Cc3Hh3 + Ss4Cc2Hh1";
	Molecule m11; 
    cout <<	m11.evaluate_chemical_equation(eq3); 
		//Should print out:
		//This is a Transformation
		//The transformation is valid!!! and results in a stable molecule!!!
		//The resulting molecule is Cc5Hh4Ss4 and has the weight 80.8

return 0;
}
