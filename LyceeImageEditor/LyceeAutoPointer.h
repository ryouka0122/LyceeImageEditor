#ifndef __LYCEE_AUTO_POINTER__HEADER__
#define __LYCEE_AUTO_POINTER__HEADER__


namespace lycee {

	template<class _Ty>
	class LyceeAutoPointer {
		//======================================================
		// typedef
	public:
		typedef _Ty pointer_type;
		typedef LyceeAutoPointer<_Ty> this_type;

		//======================================================
		// constructor / destructor
	public:
		~LyceeAutoPointer() {
			delete _ptr;
		}

		explicit LyceeAutoPointer(_Ty *_Ptr = 0)
			: _ptr(_Ptr)
		{
		}

		template<class _Other>
		LyceeAutoPointer(LyceeAutoPointer<_Other> &_rhs)
			: _ptr(_rhs.release())
		{
		}


		//======================================================
		// function
	public:
		_Ty* get() const {
			return _ptr;
		}

		_Ty* release() const {
			_Ty _tmp = _ptr;
			_ptr = 0;
			return _tmp;
		}

		void reset(_Ty *ptr = 0) {
			if (_ptr != ptr) {
				delete _ptr;
			}
			_ptr = ptr;
		}

		//======================================================
		// operator
		this_type& operator =(this_type &_rhs) {
			_Ty *_tmp = _rhs._ptr;
			_rhs._ptr = 0;
			reset(_tmp);
			return *this;
		}

		_Ty& operator *() const {
			return (*get());
		}

		_Ty* operator ->() const {
			return (get());
		}


	private:
		_Ty *_ptr;
	};

}	// lycee
#endif	// __LYCEE_AUTO_POINTER__HEADER__