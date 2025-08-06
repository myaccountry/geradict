#include <iostream>
#include <geralist.h>
#pragma once
using namespace std;
using ll = long long;

template <typename ktype, typename vtype>
struct DictObject {
	ktype key;
	vtype value;

	DictObject() {};

	DictObject(ktype k) {
		key = k;
		value = 0;
	};

	DictObject(ktype x, vtype y) {
		key = x;
		value = y;
	};

	DictObject(const DictObject &obj) {
		key = obj.key;
		value = obj.value;
	};

	DictObject &operator=(const DictObject &obj) {
		key = obj.key;
		value = obj.value;
		return *this;
	};

	bool operator==(const DictObject &obj) const {
		if (obj.key == key)
			return true;
		return false;
	};

	bool operator==(ktype elem) const {
		if (key == elem)
			return true;
		return false;
	};

	bool operator!=(ktype elem) const {
		if (key != elem)
			return true;
		return false;
	};

	bool operator>=(const DictObject &obj) const {
		if (obj.key >= key)
			return true;
		return false;
	};

	bool operator<=(const DictObject &obj) const {
		if (obj.key <= key)
			return true;
		return false;
	};

	bool operator>(const DictObject &obj) const {
		if (obj.key > key)
			return true;
		return false;
	};

	bool operator<(const DictObject &obj) const {
		if (obj.key < key)
			return true;
		return false;
	};

	friend ostream &operator<<(ostream &out, const DictObject &obj) {
		out << '{' << obj.key << ": " << obj.value << '}';
		return out;
	};
};

template <typename ktype, typename vtype>
class dict {
	list<DictObject<ktype, vtype>> dictarr;
public:

	struct DictProxy : DictObject<ktype, vtype> {
		dict<ktype, vtype> &parent;
		ktype key;
		vtype value;

		DictProxy(dict &obj, ktype key) : parent(obj) {
			this->key = key;

			long long index = parent.dictarr.index(key);
			if (index != -1)
				this->value = parent.dictarr[index].value;
			else
				this->value = 0;
		};

		void operator=(vtype val) {
			DictObject<ktype, vtype> stdata(key, val);
			if (parent.dictarr.find(stdata))
				parent.dictarr[parent.dictarr.index(stdata)].value = val;
			else
				parent.dictarr.append(stdata);
		};

		DictProxy &operator=(DictProxy &obj) {
			parent = obj.parent;
			key = obj.key;
			value = obj.value;
			return *this;
		};

		friend ostream &operator<<(ostream &out, const DictProxy &obj) {
			out << '{' << obj.key << ": " << obj.value << '}';
			return out;
		};
	};

	dict() {};

	dict(const dict &obj) {
		dictarr = obj.dictarr;
	};
	
	dict(ktype key, vtype value) {
		expand(1);
		dictarr[dictarr.size() - 1] = DictObject<ktype, vtype>(key, value);
	};

	dict(DictObject<ktype, vtype> obj) {
		expand(1);
		dictarr[dictarr.size() - 1] = obj;
	};

	dict(DictObject<ktype, vtype> obj, size_t length) {
		expand(length);
		for (size_t i = 0; i < dictarr.size(); i++) {
			dictarr[i] = obj;
		}
	};

	dict(initializer_list<DictObject<ktype, vtype>> init) {
		if (init.size() == 0)
			return;
		
		expand(init.size());
		for (size_t i = 0; i < dictarr.size(); i++) {
		    dictarr[i] = *(init.begin() + i);
		}
	};

	~dict() {};

	dict &operator=(const dict &obj) {
		dictarr = obj.dictarr;
		return *this;
	};
	
	DictProxy operator[](ktype elem) {
		return DictProxy(*this, elem);
	};

	friend ostream &operator<<(ostream &out, const dict &obj) {
		out << '[';
		for (size_t i = 0; i < obj.dictarr.size(); i++) {
			out << '\n' << "  " << obj.dictarr[i];
		}
		out << '\n' << ']';
		return out;
	};

	void expand(size_t size) {
		dictarr.expand(size);
	};

	void sort(bool mintomax = true) {
		dictarr.sort();
		if (mintomax)
			dictarr.reverse();
	};

	void reverse() {
		dictarr.reverse();
	};
};
