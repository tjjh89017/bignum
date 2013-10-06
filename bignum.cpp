#include <iostream>
#include <cstdlib>

using namespace std;

class Bignum
{
	private:
		string value;
		int sign;

		static string _plus(string a, string b)
		{
			// for two positive integer
			string rtn = (a.length() >= b.length() ? a : b) + "0";
			b = (a.length() >= b.length() ? b : a);

			for(int i = 0, l = b.length(); i < l; i++){
				rtn[i + 1] += (rtn[i] + b[i] - 2 * '0') / 10;
				rtn[i] = '0' + (rtn[i] + b[i] - 2 * '0') % 10;
			}
			if(rtn[rtn.length() - 1] == '0')
				rtn = rtn.substr(0, rtn.length() - 1);

			return rtn;
		}

		static string _minus(string a, string b)
		{
			// make true a >= b
			string rtn;
			if(a.length() == b.length()){
				rtn = (a[a.length() - 1] > b[b.length() - 1] ? a : b) + "0";
				b = (a[a.length() - 1] > b[b.length() - 1] ? b : a);
			}
			else{
				rtn = (a.length() >= b.length() ? a : b) + "0";
				b = (a.length() >= b.length() ? b : a);
			}
			for(int i = 0, l = b.length(); i < l; i++){
				rtn[i + 1] -= (rtn[i] < b[i]);
				rtn[i] = '0' + 10 * (rtn[i] < b[i]) + rtn[i] - b[i];
			}
			while(rtn.length() > 1 && rtn[rtn.length() - 1] == '0')
				rtn = rtn.substr(0, rtn.length() - 1);
			for(int i = 0, l = rtn.length(); i < l; i++)
				if(rtn[i] < '0'){
					rtn[i + 1] -= 1;
					rtn[i] += 10;
				}

			return rtn;
		}

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

		Bignum& operator+(const Bignum &b)
		{
			// TODO why?
			Bignum *rtn = new Bignum();
			if(this->sign == b.sign){
				rtn->sign = this->sign;
				rtn->value = _plus(this->value, b.value);
			}
			else{
				rtn->sign = 0;
				rtn->value = _minus(this->value, b.value);
			}


			return *rtn;
		}

		int operator>(const Bignum &b) const
		{
			if(this->sign != b.sign)
				return !(this->sign > b.sign);
			if(this->value.length() == b.value.length())
				return this->value[this->value.length() - 1] > b.value[b.value.length() - 1];

			return this->value.length() > b.value.length();
		}

		friend istream& operator>>(istream &is, Bignum &b)
		{
			string s, temp = "";
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
				else
					break;

			for(int i = 0, l = s.length(); i < l; i++){
				if(s[i] > '9' || s[i] < '0'){
					// set i0010stream badbit
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

	Bignum a, b;
	cin >> a >> b;
	//cout << a << endl;
	//cout << b << endl;
	cout << (a + b) << endl;

	return 0;
}