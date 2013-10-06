#include <iostream>
#include <cstdlib>

using namespace std;

class Bignum
{
	private:
		string value;
		int sign;

	public:
		Bignum(): value("0"), sign(0)
		{

		}

		Bignum(const Bignum &b): value(b.value), sign(b.sign)
		{

		}

		Bignum& operator=(const Bignum &b)
		{
			this->value = b.value;
			this->sign = b.sign;

			return *this;
		}

		friend istream& operator>>(istream &is, Bignum &b)
		{
			string s, temp;
			is >> s;
			if(s[0] == '-'){
				b.sign = 1;
				s = s.substr(1, s.length() - 1);
			}
			else{
				b.sign = 0;
			}
			for(int i = 0, l = s.length(); i < l - 1; i++)
				if(s[0] == '0')
					s = s.substr(1, s.length() - 1);

			for(int i = 0, l = s.length(); i < l; i++){
				if(s[i] > '9' || s[i] < '0'){
					// set istream badbit
					return is;
				}
				temp = s[i] + temp;
			}
			b.value = temp;

			return is;
		}

		friend ostream& operator<<(ostream &os, Bignum &b)
		{
			if(b.sign)
				os << "-";
			for(int i = b.value.length() - 1; i >= 0; i--)
				os << b.value[i];
			return os;
		}
};

int main(){

	Bignum a;
	cin >> a;
	cout << a << endl;

	return 0;
}