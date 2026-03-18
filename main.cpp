#include <iostream>

template <class T>
struct List {
	T val;
	List<T>* next;
};

template <class T>
struct Vec {
	T* data;
	size_t s;
	size_t cap;
};



template <class T>
Vec<List<T>*> balanced_copy(Vec<List<T>*> v, size_t k) {
	if (k == 0) {
		throw;
	}

	size_t total = 0;
	for (size_t i = 0; i < v.s; ++i) {
		List<T>* p = v.data[i];
		while (p != nullptr) {
			++total;
			p = p->next;
		}
	}

	Vec<List<T>*> r{nullptr, 0, 0};
	if (total == 0) {
		return r;
	}

	const size_t parts = (total + k - 1) / k;
	r.data = new List<T>*[parts];
	r.s = parts;
	r.cap = parts;

	for (size_t i = 0; i < r.s; ++i) {
		r.data[i] = nullptr;
	}

	List<T>* head = nullptr;
	List<T>* tail = nullptr;
	size_t cursz = 0;
	size_t idx = 0;

	try {
		for (size_t i = 0; i < v.s; ++i) {
			List<T>* p = v.data[i];
			while (p != nullptr) {
				List<T>* q = new List<T>{p->val, nullptr};

				if (head == nullptr) {
					head = q;
					tail = q;
				} else {
					tail->next = q;
					tail = q;
				}

				++cursz;
				if (cursz == k) {
					r.data[idx] = head;
					++idx;
					head = nullptr;
					tail = nullptr;
					cursz = 0;
				}

				p = p->next;
			}
		}

		if (head != nullptr) {
				r.data[idx] = head;
				++idx;
			}

			r.s = idx;
		return r;
	} catch (...) {
		while (head != nullptr) {
			List<T>* nx = head->next;
			delete head;
			head = nx;
		}

		for (size_t j = 0; j < idx; ++j) {
			List<T>* cur = r.data[j];
			while (cur != nullptr) {
				List<T>* nx = cur->next;
				delete cur;
				cur = nx;
			}
			r.data[j] = nullptr;
		}

		delete[] r.data;
		r.data = nullptr;
		r.s = 0;
		r.cap = 0;
		throw;
	}
}
