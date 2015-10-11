/*
 * safe_ptr.h
 *
 *  Created on: Oct 3, 2015
 *      Author: brent
 */

#ifndef SAFE_PTR_HPP_
#define SAFE_PTR_HPP_

#include <memory>
#include <atomic>
#include <cassert>

//useful for detecting stale pointers

class ref_counter {
public:
	std::atomic<void *> underlying;
	std::atomic<int> counter;
	inline ref_counter(void * obj) : underlying(obj), counter(1) {}

	inline void dec() {
		if (--counter == 0) {
			delete this;
		}
	}

	inline void inc() {
		++counter;
	}
};

template<typename T>
class safe_ptr {

	bool is_owner;
	ref_counter * rc;

	safe_ptr(ref_counter * const rc) : is_owner(false), rc(rc) {
		rc->inc();
	}

	template<typename U>
	friend class safe_ptr;
public:

	template<typename... Ts>
	static safe_ptr construct(Ts&&... params) {
		T * const obj = new T(std::forward<Ts>(params)...);
		safe_ptr result;
		result.rc = new ref_counter(obj);
		return result;
	}

	safe_ptr(safe_ptr const & other) : is_owner(false), rc(other.rc) {
		rc->inc();
	}

	safe_ptr(safe_ptr && move) : is_owner(true), rc(0) {
		std::swap(is_owner, move.is_owner);
		std::swap(rc, move.rc);
	}

	safe_ptr() : is_owner(true), rc(new ref_counter(nullptr)) {}

	safe_ptr & operator =(safe_ptr const& rhs) {
		safe_ptr copy = rhs;
		std::swap(this->rc, copy.rc);
		std::swap(this->is_owner, copy.is_owner);
		return *this;
	}

	~safe_ptr() {
		if (rc) {
			if (is_owner) {			
				T* obj = (T*)rc->underlying.exchange(nullptr);
				delete obj;
			}
			rc->dec();
		}
	}

	T& operator *() const {
		return *(T*)rc->underlying;
	}

	T* operator ->() const {
		assert(rc->underlying);
		return (T*)(void*)rc->underlying;
	}

	operator safe_ptr<T const>() const {
		return safe_ptr<T const>(rc);
	}

	operator bool() const {
		assert(rc->underlying || is_owner);
		return rc->underlying;
	}
};


#endif /* SAFE_PTR_HPP_ */
