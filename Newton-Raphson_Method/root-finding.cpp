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
#include <string>
#include <cmath>
#include <vector>

const int DECIMAL_PRECISION = 15;//how many decimal points used for formatting ONLY. doesnt effect actual math procedures (iomanip)

using namespace std;

double newtons_method(double, int);
void create_tokens(vector<string>&tokens,string);
string remove_whitespace(string);



struct monomial {//a monomial is a (coeff,power) couple. i.e; (3x^2)... coeff = 3, power = 2
	double coeff;
	double power;
};
vector<monomial> parser(vector<string>);

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
	vector<string> tokens;
	string poly;
	cout << "Enter a polynomial function: " << endl;
	getline(cin, poly);
	poly += "#";
	poly = remove_whitespace(poly);
	create_tokens(tokens, poly);
	
	some_func.terms = parser(tokens);
	some_der.terms = some_func.derivative();





	cout << "100 iterations of newtons_method of f(x) returns: " << fixed <<setprecision(DECIMAL_PRECISION) <<  newtons_method(2.0,100) << endl;


	system("PAUSE>nul");//windows only. stops the cmd console from insta-closing
	return 0;
}

string remove_whitespace(string to_clean)
{
	for (int x = 0; x < to_clean.size(); x++)
	{
		if (to_clean[x] == ' ')
		{
			to_clean.erase(x, 1);
			to_clean = remove_whitespace(to_clean);
		}
	}
	return to_clean;
}

void create_tokens(vector<string> & tokens, string to_split)
{
	string delimiter = "+-#";//#signifies the end of the polynomial
	int size = to_split.size();
	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < delimiter.size(); y++)
		{
			if (to_split[x] == delimiter[y])
			{//if we've found a token identifier then we need to split the string and re-pass it (Recursion)
				if (x != 0)
				{
					tokens.push_back(to_split.substr(0, x));//add the token to a vector of strings
					to_split.erase(0, x);//take the token off the front of the string
					size -= x;
					x = 0;//restart x index
				}
			}

		}
	}

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

vector<monomial> parser(vector<string> tokens)
{//goal: convert each token to a monomial struct (coeff,power) form
	vector<monomial> terms;
	monomial term;
	double coeff, power;
	for (int x = 0; x < tokens.size(); x++)
	{//navigate through each token (3x^2) or (-2x^0)
		for (int y = 0; y < tokens[x].size(); y++)
		{
			if (tokens[x][y] == 'x')
			{
				term.coeff = stod(tokens[x].substr(0, y));
				term.power = stod(tokens[x].substr(y + 2, tokens[x].size()));
				terms.push_back(term);//adding a monomial struct to our vector (terms)
			}
		}
	}
	return terms;
}