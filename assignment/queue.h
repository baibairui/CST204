#include"Vector.cpp"
#include<iostream>


template<typename T>
class queue {
private:
	Vector<T>data;
	

public:
	queue(size_t newcap) {
		data = Vector(newcap);
	}
	~queue() {
		delete data;
	}
	T top() {
		return data[0];
	}
	void pop() {
		data.erase[0];
	}
	void push(const T& newdata) {
		data.push_back(newdata);
	}
	size_t getsize() {
		return data.getsize();
	}

};