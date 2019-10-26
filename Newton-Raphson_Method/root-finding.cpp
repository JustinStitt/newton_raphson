/* Justin Stitt 10/26/2019
* In numerical analysis, Newton's method, 
* also known as the Newton–Raphson method, 
* named after Isaac Newton and Joseph Raphson, 
* is a root-finding algorithm which produces 
* successively better approximations to the roots of a real-valued function. - wiki
*/

//TO:DO's... make a parser to read a poly_func from user input
//implement product, quotient, chain rule
#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

const int DECIMAL_PRECISION = 15;//how many decimal points used for formatting ONLY. doesnt effect actual math procedures (iomanip)

using namespace std;

double newtons_method(double, int);

struct monomial {//a monomial is a (coeff,power) couple. i.e; (3x^2)... coeff = 3, power = 2
	double coeff;
	double power;
};

class poly_function//a poly function is an array of (coeff,power) pairs. ex: [5x^3 (coeff = 5, power = 3)]
{
private:
public:
	vector<monomial> terms;//a vector of type struct monomial. this forms a polynomial function ex) f(x) = 3x^2 + 4x^1 + 1x^0 
	poly_function()//default constructor
	{
		//not much needs to be done as far as constructors go...
		//we are appending all our necessary data POST construction.
	}
	void add_term(struct monomial to_add)//appends a new monomial to the BACK of our poly_function
	{
		terms.push_back(to_add);
	}
	double at(double x)//computes f(x) for some x
	{
		double running_total = 0.0;
		//we need to loop through every term in our polynomial function and add them up
		for (int i = 0; i < terms.size(); i++)
		{
			running_total += (terms[i].coeff * pow(x, terms[i].power));
		}
		return running_total;
	}
	void display( bool is_der = false, int index = -1)//prints entire poly_func or just a single term if index arg is changed. (index >= 0)
	{
		if (index == -1)//by default, print entire polynomial function
		{
			if (!is_der)
				cout << "f(x) = ";
			else//if our func has the derivative tag, then add the ' to f(x) -> f'(x)
				cout << "f'(x) = ";
			for (int i = 0; i < terms.size(); i++)
			{
				if (i == 0 && terms[i].coeff >= 0)//if we are on the first index, dont print the positive sign
				{
					cout << terms[i].coeff << "x^" << terms[i].power;
				}
				else
				{
					if (terms[i].coeff < 0)
						cout << " " << terms[i].coeff << "x^" << terms[i].power;
					else
						cout << " + " << terms[i].coeff << "x^" << terms[i].power;
				}

			}
		}
		else
		{
			cout << terms[index].coeff << "x^" << terms[index].power << endl;
		}
		cout << endl;
	}
	vector<monomial> derivative()//using simple power, chain, quotient, product rules we want ot find the derivative of our poly_func
	{
		vector<monomial> new_terms;//a vector or struct monomial will store our derived terms
		monomial to_add;
		//now loop through each term in 'terms' and derive it at run-time
		for (int i = 0; i < terms.size(); i++)
		{
			if (terms[i].power != 0)//remember we can only use the power rule if our power is not 0 (othewise its just a constant and we should remove the term)
			{
				to_add.coeff = (terms[i].coeff * terms[i].power);//the coeff of derived term is equal to coeff * power
				to_add.power = (terms[i].power - 1);//according to power rule we take 1 off the original power
				new_terms.push_back(to_add);//push our new term to the back of new_terms.
			}
			else {}//if our power is 0 our derived term is 0, so we do nothing.
			
		}
		return new_terms;
	}
};

poly_function some_func, some_der;

int main()
{
	monomial some_term,some_term2,some_term3;//a monomial is a (coeff,power) pairing... i.e; (3x^2) is coeff = 3, power = 2

	//We could make a parser to get user input, but for now... manually input each term before runtime.
	//TERM 0
	some_term.coeff = 1.00;
	some_term.power = 3;
	//TERM 1
	some_term2.coeff = -2.00;
	some_term2.power = 1;
	//TERM 2
	some_term3.coeff = -5.00;
	some_term3.power = 0;
	//ADDING TERMS TO OUR POLYNOMIAL FUNCTION
	some_func.add_term(some_term);//0
	some_func.add_term(some_term2);//1
	some_func.add_term(some_term3);//2

	some_der.terms = some_func.derivative();//calculating the derivative and setting our derivative function to hold its new terms

	some_func.display();//print out poly func
	some_der.display(true);//print out poly func der


	cout << "100 iterations of newtons_method of f(x) returns: " << fixed <<setprecision(DECIMAL_PRECISION) <<  newtons_method(2.0,100) << endl;

	system("PAUSE>nul");//windows only. stops the cmd console from insta-closing
	return 0;
}


double newtons_method(double x, int iterations)//recursive function to iteratively estimate roots of any given function using its derivative and a starting term
{
	double val = x - (some_func.at(x) / some_der.at(x));
	if (iterations > 0)//if we still have some iterations to go
	{
		val = newtons_method(val, --iterations);//the new value of val is equal to the subsequent newtons approximation of val.
	}
	return val;//after our iterations are done. output the final value of val

}