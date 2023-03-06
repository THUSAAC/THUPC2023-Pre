#include <cassert>
#include <cmath>
#include <cstddef>
#include <cstdint>

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <utility>
#include <vector>
#include <string>

struct R {
	using value_type = long double;
	static bool is_equal(value_type x, value_type y) {
		return fabs(x - y) <= 1e-12;
	}
	static value_type inv(value_type x) {
		assert(!is_equal(x, 0));
		return 1 / x;
	}
	static std::string __repr__(value_type x) {
		return std::to_string(x);
	}
	static const value_type zero;
	static const value_type unit;
};
const long double R::zero{0};
const long double R::unit{1};

template<typename Field>
struct PowerSeriesAllocator {
	static size_t addSize(size_t size1, size_t size2) {
		return std::min(size1, size2);
	}

	static size_t mulSize(size_t size1, size_t size2) {
		return std::min(size1, size2);
	}

	static size_t divSize(size_t size1, size_t size2) {
		return std::min(size1, size2);
	}

	static void unify(std::vector<typename Field::value_type>& coefficient) {
	}
};

template<typename Field>
struct PolynomialAllocator {
	static size_t addSize(size_t size1, size_t size2) {
		return std::max(size1, size2);
	}

	static size_t mulSize(size_t size1, size_t size2) {
		return size1 == 0 && size2 == 0 ? 0 : size1 + size2 - 1;
	}

	static size_t divSize(size_t size1, size_t size2) {
		return size1 - size2 + 1;
	}

	static void unify(std::vector<typename Field::value_type>& coefficient) {
		while (!coefficient.empty() && Field::is_equal(coefficient.back(), Field::zero)) {
			coefficient.pop_back();
		}
	}
};

template<typename Dispatch, typename Field, typename Allocator = PowerSeriesAllocator<Field>>
struct AbstractPowerSeries {
	using dispatch_type = Dispatch;
	using field_type = Field;
	using value_type = typename field_type::value_type;
	using allocator_type = Allocator;

	template<typename... Args>
	AbstractPowerSeries(Args... args) : mCoefficient(args...) {}

	const std::vector<value_type>& coefficient() const { return mCoefficient; }
	std::vector<value_type>& coefficient() { return mCoefficient; }
	const value_type& operator[](size_t index) const { return mCoefficient[index]; }
	value_type& operator[](size_t index) { return mCoefficient[index]; }

	size_t size() const { return mCoefficient.size(); }

	void resize(size_t newSize) { mCoefficient.resize(newSize, Field::zero); }

	void swap(dispatch_type& that) { mCoefficient.swap(that.mCoefficient); }

	bool operator==(const dispatch_type& that) const {
		if (mCoefficient.size() != that.mCoefficient.size()) {
			return false;
		}
		for (size_t i = 0; i != mCoefficient.size(); ++i) {
			if (Field::is_equal(mCoefficient[i], that.mCoefficient[i])) {
				return false;
			}
		}
		return true;
	}
	bool operator!=(const dispatch_type& that) const {
		return !(_self() == that);
	}

	dispatch_type& operator+=(const dispatch_type& that) {
		mCoefficient.resize(allocator_type::addSize(size(), that.size()));
		_inc(that, Field::unit, 0);
		allocator_type::unify(mCoefficient);
		return _self();
	}
	dispatch_type operator+(const dispatch_type& that) const {
		dispatch_type ret = _self();
		ret += that;
		return ret;
	}

	dispatch_type& operator-=(const dispatch_type& that) {
		mCoefficient.resize(allocator_type::addSize(size(), that.size()));
		_inc(that, -Field::unit, 0);
		allocator_type::unify(mCoefficient);
		return _self();
	}
	dispatch_type operator-(const dispatch_type& that) const {
		dispatch_type ret = _self();
		ret -= that;
		return ret;
	}

	dispatch_type& operator*=(const value_type& that) {
		for (value_type& coef : mCoefficient) {
			coef *= that;
		}
		allocator_type::unify(mCoefficient);
		return _self();
	}
	dispatch_type operator*(const value_type& that) const {
		dispatch_type ret = _self();
		ret *= that;
		return ret;
	}
	friend dispatch_type operator*(const value_type& left, const dispatch_type& right) {
		return right * left;
	}
	dispatch_type operator-() const {
		return _self() * (-Field::unit);
	}
	dispatch_type& operator/=(const value_type& that) {
		return _self() *= Field::inv(that);
	}
	dispatch_type operator/(const value_type& that) const {
		dispatch_type ret = _self();
		ret /= that;
		return ret;
	}

	dispatch_type operator*(const dispatch_type& that) const {
		dispatch_type ret;
		ret.resize(allocator_type::mulSize(size(), that.size()));
		for (size_t i = 0; i != mCoefficient.size(); ++i) {
			ret._inc(that, mCoefficient[i], i);
		}
		allocator_type::unify(ret.mCoefficient);
		return ret;
	}
	dispatch_type& operator*=(const dispatch_type& that) {
		dispatch_type prod = _self() * that;
		swap(prod);
		return _self();
	}

	std::string __repr__() const {
		std::string ret = "<AbstractPowerSeries | mCoefficient=[";
		for (size_t i = 0; i != mCoefficient.size(); ++i) {
			if (i != 0) {
				ret += ", ";
			}
			ret += Field::__repr__(mCoefficient[i]);
		}
		return ret + "]>";
	}

protected:
	void _inc(const dispatch_type& addend, value_type k, size_t offset) {
		for (size_t i = 0; i + offset != mCoefficient.size() && i != addend.mCoefficient.size(); ++i) {
			mCoefficient[i + offset] += k * addend[i];
		}
	}

	const dispatch_type& _self() const {
		return *static_cast<const dispatch_type*>(this);
	}

	dispatch_type& _self() {
		return *static_cast<dispatch_type*>(this);
	}

protected:
	std::vector<value_type> mCoefficient;
};

template<typename Field>
struct Polynomial : public AbstractPowerSeries<Polynomial<Field>, Field, PolynomialAllocator<Field>> {
	using field_type = Field;
	using value_type = typename field_type::value_type;
	using allocator_type = PolynomialAllocator<field_type>;

	static Polynomial monomial(value_type coef, size_t degree) {
		if (field_type::is_equal(coef, field_type::zero)) {
			return Polynomial();
		}
		Polynomial ret;
		ret.mCoefficient.resize(degree + 1);
		ret.mCoefficient.back() = coef;
		return ret;
	}

	Polynomial() {
	}

	Polynomial(const value_type& v) : AbstractPowerSeries<Polynomial, field_type, allocator_type>(1, v) {
		allocator_type::unify(this->mCoefficient);
	}

	const value_type& operator[](size_t index) const {
		return index < this->size() ? this->mCoefficient[index] : field_type::zero;
	}

	bool operator!() const {
		return this->mCoefficient.empty();
	}
	operator bool() const {
		return !!*this;
	}

	size_t deg() const {
		return this->size() - 1;
	}

	void divmod(const Polynomial& divisor, Polynomial* pQuotient, Polynomial* pRemainder) const {
		assert(divisor);
		Polynomial remainder = *this;
		Polynomial quotient;
		if (this->size() >= divisor.size()) {
			quotient.resize(allocator_type::divSize(remainder.size(), divisor.size()));
			value_type inv = field_type::inv(divisor.mCoefficient.back());
			for (size_t i = quotient.size(); i != 0; ) {
				--i;
				value_type q = remainder.mCoefficient.back() * inv;
				quotient.mCoefficient[i] = q;
				remainder._inc(divisor, -q, i);
				remainder.mCoefficient.pop_back();
			}
			allocator_type::unify(remainder.mCoefficient);
		}
		if (pQuotient != nullptr) {
			pQuotient->swap(quotient);
		}
		if (pRemainder != nullptr) {
			pRemainder->swap(remainder);
		}
	}
	Polynomial& operator/=(const Polynomial& that) {
		divmod(that, this, nullptr);
		return *this;
	}
	Polynomial operator/(const Polynomial& that) const {
		Polynomial ret;
		divmod(that, &ret, nullptr);
		return ret;
	}
	Polynomial& operator%=(const Polynomial& that) {
		divmod(that, nullptr, this);
		return *this;
	}
	Polynomial operator%(const Polynomial& that) const {
		Polynomial ret;
		divmod(that, nullptr, &ret);
		return ret;
	}
};

template<typename Field>
struct PowerSeries : public AbstractPowerSeries<PowerSeries<Field>, Field, PowerSeriesAllocator<Field>> {
	using field_type = Field;
	using value_type = typename Field::value_type;
	using allocator_type = PowerSeriesAllocator<Field>;

	PowerSeries(size_t size) : AbstractPowerSeries<PowerSeries, field_type, allocator_type>(size, field_type::zero) {
	}

	PowerSeries(size_t size, const Polynomial<field_type>& poly) : AbstractPowerSeries<PowerSeries, field_type, allocator_type>(poly.coefficient()) {
		this->mCoefficient.resize(size);
	}

	PowerSeries operator/(const PowerSeries& divisor) const {
		PowerSeries ret = *this;
		ret.resize(allocator_type::divSize(this->size(), divisor.size()));
		value_type inv = field_type::inv(divisor[0]);
		for (size_t i = 0; i != this->size(); ++i) {
			value_type q = ret[i] * inv;
			ret._inc(divisor, -q, i);
			ret[i] = q;
		}
		return ret;
	}

	PowerSeries& operator/=(const PowerSeries& divisor) const {
		PowerSeries ret = *this / divisor;
		swap(ret);
		return *this;
	}
};

template<typename Field>
PowerSeries<Field> linearRecurrence(const Polynomial<Field>& chPoly, uint64_t maxPower) {
	Polynomial<Field> ret = 1;
	Polynomial<Field> x = Polynomial<Field>::monomial(Field::unit, 1);
	while (maxPower != 0) {
		if (maxPower % 2 == 1) {
			ret = ret * x % chPoly;
		}
		x = x * x % chPoly;
		maxPower /= 2;
	}
	ret = ret * Polynomial<Field>::monomial(Field::unit, chPoly.deg()) / chPoly;
	return PowerSeries<Field>(chPoly.deg(), ret);
}

int main() {
	int N, L;
	std::cin >> N >> L;
	std::vector<int> a(N);
	for (int& item : a) {
		std::cin >> item;
	}
	std::sort(a.begin(), a.end());
	int aMax = a.back();
	std::vector<int> cnt(aMax + 1);
	Polynomial<R> chPoly = Polynomial<R>::monomial(1, aMax);
	for (int item : a) {
		chPoly -= Polynomial<R>::monomial(1.0 / N, aMax - item);
		++cnt[item];
	}
	for (int i = aMax; i >= 1; --i) {
		cnt[i - 1] += cnt[i];
	}
	std::vector<long double> pReach = linearRecurrence(chPoly, L).coefficient();
	std::vector<long double> pFirst = pReach;
	for (size_t i = 0; i != aMax; ++i) {
		for (size_t j = 0; j != N && a[j] <= i; ++j) {
			pFirst[i - a[j]] -= pFirst[i] / N;
		}
	}
	std::vector<long double> pWin(aMax);
	for (size_t i = 0; i != aMax; ++i) {
		pWin[i] = pReach[i] * cnt[i + 1] / N;
	}
	for (size_t i = aMax - 1; i != 0; --i) {
		pWin[i - 1] += pWin[i];
	}
	for (size_t i = 0; i != aMax; ++i) {
		long double pChoose = 0;
		for (size_t j = 0; j != N && a[j] <= i; ++j) {
			pChoose += pWin[i - a[j]] / N;
		}
		pWin[i] = std::max(pWin[i], pChoose);
	}
	long double ans = 0;
	for (size_t i = 0; i != aMax; ++i) {
		ans += pWin[i] * pFirst[i];
	}
	std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(18) << ans << std::endl;
}