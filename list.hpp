#ifndef SIMP_LIST_H
#define SIMP_LIST_H

#include <malloc.h>
namespace simple {
	template <class T>
	class list {
	public:
		T **data;
		list() {
			data = (T **)malloc(100 * sizeof(T*));
			size = 100;
			length = 0;
		}
		~list() {
			for (int i = 0; i < length; i++) {
				delete (data[i]);
			}
			free(data);
		}
		size_t size;
		int length;
		T & operator[](int index) const{
			return *(data[index]);
		}
		void append(T ele) {
			if (length >= size) {
				data = (T **)realloc(data, (size + 100) * sizeof(T*));
				size += 100;
			}
			T *tmp = new T;
			*tmp = ele;
			data[length++] = tmp;
		}
		T remove() {
			delete data[length - 1];
			T tmp = *(data[length - 1]);
			length--;
			return tmp;
		}
		list(const list<T> &other) {
			data = (T **)malloc(other.size * sizeof(T*));
			size = other.size;
			length = other.length;
			for (int i = 0; i < length; i++) {
				data[i] = new T;
				*(data[i]) = other[i];
			}
		}
		void clear() {
			for (int i = 0; i < length; i++) {
				delete (data[i]);
			}
			length = 0;
		}
		list &operator=(const list &other) {
			data = (T **)malloc(other.size * sizeof(T*));
			size = other.size;
			length = other.length;
			for (int i = 0; i < length; i++) {
				data[i] = new T;
				*(data[i]) = other[i];
			}
			return *this;
		}
		};
}

#endif