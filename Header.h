#include <functional>
#include <iostream>
template<typename Type>
class Hash;
template <class Type>
class Visitor{
public:
	Visitor() {}
	virtual void visit(Type& e) = 0;
};

template <class Type>
class GetVisitor : public Visitor<Type>{
	GetVisitor() {}
	Type visit(Type& e)
	{
		return e;
	}
};
//simple iterator
template <class Type>
class Iterator
{
	int usedElems;
	int pos;
	Hash <Type>& hashTable;
public:
	Iterator(Hash<Type> &obj) : pos(0), usedElems(0), hashTable(obj) { while (!hashTable.use[pos]) { pos++; } }
	Type next() {
		if (hasNext()){
			while (!hashTable.use[pos]) { pos++; }
			Type curElem = hashTable.arr[pos];
			pos++;
			usedElems++;
			return curElem;
		}
		return hashTable.arr[pos];
	}
	Type& operator* () {
		while (!hashTable.use[pos]) { pos++; }
		return hashTable.table[pos];
	}
	bool hasNext() { return !(usedElems == hashTable.siz); }

};
template <class Type>
class Hash
{

	std::hash <Type> key;
	Type *arr;
	bool *use;
	int numb = 120;
	int siz;
	friend Iterator <Type>;
	friend Visitor <Type>;
	friend GetVisitor <Type>;
public:
//like STL iterator
	/*class Iterator {
	public:
	const Hash <Type>&h;
	int index;
	public:
	Iterator(Hash &d, int i) : h(d), index(i) {}
	Iterator(const Iterator& it) : h(it.h), index(it.index) {}
	Type& operator *(){
	return h.arr[index];
	}
	Iterator operator = (const Iterator & val)
	{
	this->index = val.index;
	h = val.h;
	return *this;
	}
	Iterator& operator ++(){
	index++;
	while (!h.use[index] && index < h.numb)
	index++;
	return *this;
	}
	bool operator ==(Iterator &it){
	return (&h == &it.h && index == it.index);
	}

	bool operator !=(Iterator&it){
	return !(*this == it);
	}
	Type current_value()
	{
	return h.arr[index];
	}
	};*/

	/*Iterator begin()
	{
	if (isEmpty()) { return Iterator (*this, 0); }
	for (int i = 0; i < numb; i++)
	if (use[i]) { return Iterator (*this, i); }
	}
	Iterator end()
	{
	if (isEmpty()) { return Iterator (*this, 0); }
	for (int i = numb - 1; i >= 0; i--)
	if (use[i]) { return Iterator (*this, i); }
	}*/
	Iterator <Type> createIterator()
	{
		return Iterator<Type>(*this);
	}
	Hash()
	{
		siz = 0;
		arr = new Type[numb];
		use = new bool[numb];
		for (int i = 0; i < numb; i++)
			use[i] = false;
	}
	Hash(const Hash<Type>&table)
	{
		siz = table.siz;
		delete[] arr;
		delete[] use;
		arr = new Type[numb];
		use = new bool[numb];
		for (int i = 0; i < numb; i++)
		{
			arr[i] = table.arr[i];
			use[i] = table.use[i];
		}
	}
	~Hash()
	{
		delete[] use;
		delete[] arr;
	}
	bool isFull()
	{
		return (numb == siz);
	}
	bool isEmpty()
	{
		return (siz == 0);
	}
	int size()
	{
		return siz;
	}
	bool find(Type value)
	{
		return (use[key(value) % numb]);
	}
	bool add(Type value)
	{
		if (use[key(value) % numb] == true)
			return false;
		arr[key(value) % numb] = value;
		use[key(value) % numb] = true;
		siz++;
		return true;
	}
	void delet(Type value)
	{
		if (arr[key(value) % numb] == value)
		{
			use[key(value) % numb] = false;
			siz--;
		}
	}
	void clear()
	{
		siz = 0;
		for (int i = 0; i < numb; i++)
			use[i] = false;
	}
	void swap(const Hash<Type>& table)
	{
		Hash <Type> time(table);
		use = new bool[numb];
		arr = new Type[numb];
		table.siz = siz;
		siz = time.siz;
		for (int i = 0; i < numb; i++)
		{
			table.use[i] = use[i];
			table.arr[i] = arr[i];
			use[i] = time.use[i];
			arr[i] = time.arr[i];
		}
	}
	Hash <Type> operator = (const Hash <Type> & val)
	{
		this->siz = val.siz;
		for (int i = 0; i < numb; i++)
		{
			this->arr[i] = val.arr[i];
			this->use[i] = val.use[i];
		}
		return *this;
	}
	friend std::ostream& operator<<(std::ostream& os, const Hash <Type> & dt)
	{
		for (int i = 0; i < numb; i++)
			if (dt.use[i])
				os << dt.arr[i];
		return os;
	}
	friend std::ofstream& operator<<(std::ofstream& ofs, const Hash <Type> & dt)
	{
		for (int i = 0; i < numb; i++)
			if (dt.use[i])
				ofs << dt.arr[i];
		return ofs;
	}
	friend std::istream& operator>>(std::istream& is, const Hash <Type> & dt)
	{
		while (is.peek() != '\n')
		{
			int a;
			is >> a;
			dt.add(a);
		}
		return is;
	}
	friend std::ifstream& operator>>(std::ifstream& ifs, const Hash <Type> & dt)
	{
		while (ifs.peek() != '\0')
		{
			int a;
			ifs >> a;
			dt.add(a);
		}
		return ifs;
	}
	Type operator[] (Type a)
	{
		if (this->add(a))
			return a;
		else
			return NULL;
	}
	Hash<Type>& operator=(Hash<Type>&& other)
	{
		if (this == &other) { return *this; }
		delete[] used;
		delete[] arr;
		used = other.used;
		arr = other.arr;
		siz = other.siz;
	}
	Hash(const Hash<Type>&&table)
	{
		used = new bool[numb];
		arr = new Type[numb];
		used = table.used;
		arr = arr.used;
		siz = table.siz;
	}
	Hash(std::initializer_list<Type> initL)
	{
		siz = initL.end() - initL.begin();
		if (capacity > numb)
		{
			siz = 0;
			arr = new Type[numb];
			use = new bool[numb];
			for (int i = 0; i < numb; i++)
				use[i] = false;
			return;
		}
		arr = new Type[numb];
		used = new bool[numb];
		for (int i = 0; i < numb; i++)
		{
			used[i] = false;
		}
		for (auto i = initL.begin(); i != initL.end(); i++)
			this->add(*i);
	}
	void Accept(Visitor<Type>& vis) {
		vis.visit(*this);
	}
};