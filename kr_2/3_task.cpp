#include <iostream>
#include <vector>
#include <cmath>
/*
Поле F25 задано при помощи многочлена 𝑥2 + 3
а) выпишите все степени элемента 𝑥 + 3; 
б) найдите порядок элемента 4𝑥 + 1.
*/
static int dimension;

class Area {
	int number = 0;

	static int trans(int num) {
		return (dimension + num % dimension) % dimension;
	}

public:
	Area() = default;

	Area(int num) {
		number = trans(num);
	}

	Area& operator+=(const Area& other) {
		*this = *this + other;
		return *this;
	}

	Area& operator-=(const Area& other) {
		*this = *this - other;
		return *this;
	}

	Area& operator*=(const Area& other) {
		*this = *this * other;
		return *this;
	}

	Area& operator/=(const Area& other) {
		*this = *this / other;
		return *this;
	}

	Area operator+(const Area& other) {
		return number + other.number;
	}

	Area operator-(const Area& other) {
		return number - other.number;
	}

	Area operator*(const Area& other) {
		return number * other.number;
	}

	Area operator/(const Area& other) {
		return number / other.number;
	}

	bool operator==(const Area& other) {
		return number == other.number;
	}

	bool operator!=(const Area& other) {
		return !(number == other.number);
	}

	bool operator>(const Area& other) {
		return number > other.number;
	}

	bool operator>=(const Area& other) {
		return number >= other.number;
	}

	bool operator<(const Area& other) {
		return !(*this >= other);
	}

	bool operator<=(const Area& other) {
		return !(*this > other);
	}


	int num() {
		return number;
	}

	friend std::ostream& operator<< (std::ostream& os, const Area& num) {
		os << num.number;
		return os;
	}
	friend std::istream& operator>> (std::istream& is, Area& num) {
		int temp;
		is >> temp;
		num.number = trans(temp);
		return is;
	}
};

template <typename T>
class Polynomial {
	std::vector<T> data;

	void normalize(std::vector<T>& coef) {
		while (coef.size() > 1 && coef.back() == T(0))
		{
			coef.pop_back();
		}
	}
public:
	Polynomial<T>(const std::vector<T>& a) :data(a) {
		normalize(data);
	}

	Polynomial<T>(const T& num = T(), const int degr = 0) {
		for (int i = 0; i < degr; i++)
		{
			data.push_back(0);
		}
		data.push_back(num);
		normalize(data);
	}

	T operator[] (size_t i) const
	{
		if (i >= data.size()) {
			return T(0);
		}
		else {
			return data[i];
		}
	}

	size_t Degree() const {
		return this->data.size() - 1;
	}

	bool operator==(const Polynomial<T>& other) const {
		if (data.size() != other.data.size()) {
			return false;
		}
		for (size_t i = 0; i != data.size(); ++i) {
			if (data[i] != other[i]) {
				return false;
			}
		}
		return true;
	}

	bool operator!=(const Polynomial<T>& other) const {
		return !(*this == other);
	}

	bool operator==(const T& num) {
		return *this == Polynomial<T>(num);
	}

	bool operator!=(const T& num) {
		return *this != Polynomial<T>(num);
	}

	Polynomial<T>& operator+=(const Polynomial<T>& other) {
		data.resize(std::max(other.data.size(), data.size()), T(0));
		for (size_t i = 0; i != std::min(data.size(), other.data.size()); ++i) {
			data[i] += other.data[i];
		}
		normalize(data);
		return *this;
	}

	Polynomial<T>& operator-=(const Polynomial<T>& other) {
		data.resize(std::max(other.data.size(), data.size()), T(0));
		for (size_t i = 0; i != std::min(data.size(), other.data.size()); ++i) {
			data[i] -= other.data[i];
		}
		normalize(data);
		return *this;
	}

	Polynomial<T>& operator+=(const T& num) {
		*this += Polynomial<T>(num);
		normalize(data);
		return *this;
	}

	Polynomial<T>& operator-=(const T& num) {
		*this -= Polynomial<T>(num);
		normalize(data);
		return *this;
	}

	Polynomial<T>& operator*=(const Polynomial<T>& other) {
		std::vector<T> temp(data.size() + other.data.size(), T(0));
		for (size_t i = 0; i != data.size(); ++i) {
			for (size_t j = 0; j != other.data.size(); ++j) {
				temp[i + j] += data[i] * other.data[j];
			}
		}
		normalize(temp);
		*this = Polynomial(temp);
		return *this;
	}

	Polynomial<T>& operator*=(const T& num) {
		for (size_t i = 0; i != data.size(); ++i) {
			data[i] *= num;
		}
		normalize(data);
		return *this;
	}

	T operator() (const T& point) const {
		T ans = T(0);
		for (auto iter = data.rbegin(); iter != data.rend(); ++iter) {
			ans += *iter;
			if ((iter + 1) != data.rend()) {
				ans *= point;
			}
		}
		return ans;
	}

	friend std::ostream& operator<< (std::ostream& out, const Polynomial<T>& pol) {
		bool flag = false;
		unsigned long long degree = pol.data.size() - 1;
		for (auto iter = pol.data.rbegin(); iter != pol.data.rend(); ++iter, --degree) {
			T coef = *iter;
			if (coef != T(0)) {
				if (coef > T(0) && flag) {
					out << '+';
				}
				flag = true;
				if (degree == 0) {
					out << coef;
				}
				else if (coef == T(1)) {
					out << 'x';
				}
				/*else if (coef == T(-1)) {
					out << "-x";
				}*/
				else {
					out << coef << "*x";
				}
				if (degree > 1) {
					out << '^' << degree;
				}
			}
		}
		if (pol.data.size() == 0) {
			out << 0;
		}
		return out;
	}

	friend Polynomial<T> operator&(const Polynomial<T>& first, const Polynomial<T>& second) {
		Polynomial<T> comp(first.data.at(0));
		Polynomial<T> copy(second.data);
		size_t iter = 1;
		for (size_t degree = 1; degree != first.data.size(); ++degree) {
			for (; iter != degree; ++iter) {
				copy *= second;
			}
			comp += copy * first.data[degree];
		}
		return comp;
	}

	Polynomial<T>& operator/= (const Polynomial<T>& other) {
		Polynomial<T> priv(T(0));
		while (data.size() >= other.data.size()) {
			T coef = data.back() / other.data.back();
			size_t degree = data.size() - other.data.size();
			std::vector<T> div(degree + 1);
			div.back() = coef;
			Polynomial<T> temp(div);
			*this -= other * temp;
			priv += temp;
		}
		data = priv.data;
		return *this;
	}

	Polynomial<T>& operator%= (const Polynomial<T>& other) {
		Polynomial<T> quotient = *this / other;
		*this -= other * quotient;
		return *this;
	}

	friend Polynomial<T> operator,(const Polynomial<T>& first, const Polynomial<T>& second) {
		Polynomial<T> gcd = first;
		Polynomial<T> copy = second;
		while (copy.data.size() != 0) {
			gcd %= copy;
			std::swap(gcd, copy);
		}
		if (gcd.data.size() != 0) {
			Polynomial<T> temp(gcd[gcd.data.size() - 1]);
			gcd /= temp;
		}
		return gcd;
	}

	auto begin() const {
		return data.begin();
	}

	auto end() const {
		return data.end();
	}

	friend Polynomial<T> operator*(Polynomial<T> first, const Polynomial<T>& second) {
		return first.operator*=(second);
	}

	friend Polynomial<T> operator+(Polynomial<T> first, const Polynomial<T>& second) {
		return first += second;
	}

	friend Polynomial<T> operator-(Polynomial<T> first, const Polynomial<T>& second) {
		return first -= second;
	}

	friend Polynomial<T> operator/(const Polynomial<T>& first, const Polynomial<T>& second) {
		auto copy = first;
		copy /= second;
		return copy;
	}

	friend Polynomial<T> operator%(const Polynomial<T>& first, const Polynomial<T>& second) {
		auto copy = first;
		copy %= second;
		return copy;
	}

	friend Polynomial<T> operator+(Polynomial<T> poly, const T& num) {
		return poly += Polynomial<T>(num);
	}

	friend Polynomial<T> operator+(const T& num, Polynomial<T> poly) {
		return poly += Polynomial<T>(num);
	}

	friend Polynomial<T> operator-(Polynomial<T> poly, const T& num) {
		return poly -= Polynomial<T>(num);
	}

	friend Polynomial<T> operator-(const T& num, Polynomial<T> poly) {
		return Polynomial<T>(num) -= poly;
	}

	friend Polynomial<T> operator*(Polynomial<T> poly, const T& num) {
		return  poly *= Polynomial<T>(num);
	}

	friend Polynomial<T> operator*(const T& num, Polynomial<T> poly) {
		return  poly *= Polynomial<T>(num);
	}

	void printCoef(std::ostream& os) {
		for (auto coef : data) {
			os << coef << " ";
		}
	}
};

int main(void) {
	dimension = 5;
	Polynomial<Area> g({ 3, 0, 1});
	Polynomial<Area> dano(std::vector<Area>{ 3, 1 });
	Polynomial<Area> next(1, 0);
	size_t count = 0;

	std::cout << "(" << dano << ")^" << count << " = " << next << std::endl;
	do{
		next = next * dano % g;
		count++;
		std::cout << "(" << dano << ")^" << count << " = " << next << std::endl;
		if(next.Degree() == 0 && next[0] == Area(1)) break;
	}while (true);
	return 0;
}