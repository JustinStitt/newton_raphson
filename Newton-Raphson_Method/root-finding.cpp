/* Justin Stitt 10/26/2019
* In numerical analysis, Newton's method, 
* also known as the Newton–Raphson method, 
* named after Isaac Newton and Joseph Raphson, 
* is a root-finding algorithm which produces 
* successively better approximations to the roots of a real-valued function.
*/

//TO:DO's... make a parser to read a poly_func from user input
//implement product, quotient, chain rule
#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

const int DECIMAL_PRECISION = 7;

using namespace std;

double newtons_method(double, int);

struct monomial {
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
	}
	void add_term(struct monomial to_add)
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
	void display(int index = -1)
	{
		if (index == -1)//by default, print entire polynomial function
		{
			cout << "f(x) = ";
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
	
	monomial some_term,some_term2,some_term3;
	some_term.coeff = 1.00;
	some_term.power = 3;
	some_term2.coeff = -2.00;
	some_term2.power = 1;
	some_term3.coeff = -5.00;
	some_term3.power = 0;
	some_func.add_term(some_term);
	some_func.add_term(some_term2);
	some_func.add_term(some_term3);

	some_der.terms = some_func.derivative();
	some_func.display();
	some_der.display();
	cout << "f(5) = " << some_func.at(5) << endl;

	cout << "100 iterations of newtons_method of f(x) returns: " << fixed <<setprecision(DECIMAL_PRECISION) <<  newtons_method(2,100) << endl;

	system("PAUSE>nul");
	return 0;
}


double newtons_method(double x, int iterations = 10)//default iterations set to 10
{
	double val = x - (some_func.at(x) / some_der.at(x));
	if(iterations > 0)//if we still have some iterations remaining then recursively call newtons_method with our newly calculated 'val'
	{
		newtons_method(val, --iterations);
	}
	return val;
}