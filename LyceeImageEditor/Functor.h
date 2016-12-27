//===============================================================
// [HEADER]
// Functor.hpp
//
// [DESCRIPTOR]
// Ryouka
//
// [CONTENTS]
// Functor<Result, Args>
//
// [COMMENT]
// �ʏ�̊֐��⃁���o�֐��𓯂��悤�Ɉ�����悤�ɂ����N���X�ł��D
// �߂�l�ƈ����̌^���w�肷�邱�Ƃň�����1�̊֐����������Ƃ��ł�
// �܂��D�����悤�ɕ����̈������g�������ꍇ�́CCollection�N���X��
// �g�����ƂőΉ��ł���悤�ɂȂ�܂��D
// 
//===============================================================
#ifndef __LYCEE__FUNCTOR__HEADER__
#define __LYCEE__FUNCTOR__HEADER__

#include "includes.h"
#include "LyceeAutoPointer.h"

namespace lycee {

	//----------------------------------------------------------
	// ���\�t�@���N�^
	template<
		typename Result,
		typename Args
	>
		class Functor {
		public:
			typedef Functor<Result, Args>	this_type;
			typedef Result					result_type;
			typedef Args					argument_type;

		private:
			// �v���X�z���_
			class any_holder {
			public:
				// �f�X�g���N�^
				virtual ~any_holder() { }
				// �R�s�[�R���X�g���N�^�̑�p
				virtual any_holder* clone() = 0;
				// ���s�֐�
				virtual result_type invoke(argument_type args) = 0;
			};

			// null�v���X�z���_
			class null_any_holder : public any_holder {
			public:
				// �f�X�g���N�^
				virtual ~null_any_holder()
				{
				}
				// �R�s�[�R���X�g���N�^�̑�p
				virtual any_holder* clone() {
					return new null_any_holder();
				}
				// ���s�֐�
				virtual result_type invoke(argument_type args) {
					return result_type();
				}
			};

			// �ʏ�֐��̂Ƃ�
			template<typename _Func>
			class func_any_holder : public any_holder {
			public:
				// �f�X�g���N�^
				virtual ~func_any_holder()
				{
				}
				// �R���X�g���N�^�i���������v�j
				explicit func_any_holder(_Func const &func)
					: m_func(func)
				{
				}
				// �R�s�[�R���X�g���N�^�̑�p
				virtual any_holder* clone() {
					return new func_any_holder(m_func);
				}
				// ���s�֐�
				virtual result_type invoke(argument_type args) {
					return (m_func)(args);
				}
			private:
				_Func	m_func;
			};

			// �����o�֐��̂Ƃ�
			template<typename _Func, typename _ClsPtr>
			class mem_func_any_holder : public any_holder {
			public:
				// �f�X�g���N�^
				virtual ~mem_func_any_holder()
				{
				}
				// �R���X�g���N�^�i���������v�j
				explicit mem_func_any_holder(_Func const &func, _ClsPtr const &ptr)
					: m_func(func), m_ptr(ptr)
				{
				}
				// �R�s�[�R���X�g���N�^�̑�p
				virtual any_holder* clone() {
					return new mem_func_any_holder<_Func, _ClsPtr>(m_func, m_ptr);
				}
				// ���s�֐�
				virtual result_type invoke(argument_type args) {
					return (m_ptr->*m_func)(args);
				}
			private:
				_Func	m_func;
				_ClsPtr	m_ptr;
			};

		public:
			virtual ~Functor() {
				;
			}

			Functor()
				: content(new null_any_holder())
			{
			}

			template<typename _Func>
			Functor(_Func const &func)
				: content(new func_any_holder<_Func>(func))
			{
			}

			template<typename _Func, typename _ClsPtr>
			Functor(_Func const &func, _ClsPtr const &ptr)
				: content(new mem_func_any_holder<_Func, _ClsPtr>(func, ptr))
			{
			}

			Functor(this_type const &_Right)
				: content(_Right.content.get() ? _Right.content->clone() : 0)
			{
			}

			this_type& operator=(this_type const &_Right) {
				if (this != &_Right) {
					content.reset(_Right.content->clone());
				}
				return *this;
			}

			result_type invoke(argument_type args) {
				return content->invoke(args);
			}

		private:
			std::auto_ptr<any_holder> content;
	};

	//----------------------------------------------------------
	// �߂�l��void�̂Ƃ��̓����^
	template< typename Args >
	class Functor<void, Args> {
	public:
		typedef void Result;
		typedef Functor<Result, Args>	this_type;
		typedef Result						result_type;
		typedef Args						argument_type;

	private:
		// �v���X�z���_
		class any_holder {
		public:
			// �f�X�g���N�^
			virtual ~any_holder() { }
			// �R�s�[�R���X�g���N�^�̑�p
			virtual any_holder* clone() = 0;
			// ���s�֐�
			virtual result_type invoke(argument_type args) = 0;
		};

		// null�v���X�z���_
		class null_any_holder : public any_holder {
		public:
			// �f�X�g���N�^
			virtual ~null_any_holder()
			{
			}
			// �R�s�[�R���X�g���N�^�̑�p
			virtual any_holder* clone() {
				return new null_any_holder();
			}
			// ���s�֐�
			virtual result_type invoke(argument_type args) {
				return;
			}
		};

		// �ʏ�֐��̂Ƃ�
		template<typename _Func>
		class func_any_holder : public any_holder {
		public:
			// �f�X�g���N�^
			virtual ~func_any_holder()
			{
			}
			// �R���X�g���N�^�i���������v�j
			explicit func_any_holder(_Func const &func)
				: m_func(func)
			{
			}
			// �R�s�[�R���X�g���N�^�̑�p
			virtual any_holder* clone() {
				return new func_any_holder(m_func);
			}
			// ���s�֐�
			virtual result_type invoke(argument_type args) {
				(m_func)(args);
				return;
			}
		private:
			_Func	m_func;
		};

		// �����o�֐��̂Ƃ�
		template<typename _Func, typename _ClsPtr>
		class mem_func_any_holder : public any_holder {
		public:
			// �f�X�g���N�^
			virtual ~mem_func_any_holder()
			{
			}
			// �R���X�g���N�^�i���������v�j
			explicit mem_func_any_holder(_Func const &func, _ClsPtr const &ptr)
				: m_func(func), m_ptr(ptr)
			{
			}
			// �R�s�[�R���X�g���N�^�̑�p
			virtual any_holder* clone() {
				return new mem_func_any_holder<_Func, _ClsPtr>(m_func, m_ptr);
			}
			// ���s�֐�
			virtual result_type invoke(argument_type args) {
				(m_ptr->*m_func)(args);
				return;
			}
		private:
			_Func	m_func;
			_ClsPtr	m_ptr;
		};

	public:
		virtual ~Functor() {
			;
		}

		Functor()
			: content(new null_any_holder())
		{
		}

		template<typename _Func>
		Functor(_Func const &func)
			: content(new func_any_holder<_Func>(func))
		{
		}

		template<typename _Func, typename _ClsPtr>
		Functor(_Func const &func, _ClsPtr const &ptr)
			: content(new mem_func_any_holder<_Func, _ClsPtr>(func, ptr))
		{
		}

		Functor(this_type const &_Right)
			: content(_Right.content.get() ? _Right.content->clone() : 0)
		{
		}

		this_type& operator=(this_type const &_Right) {
			if (this != &_Right) {
				content.reset(_Right.content->clone());
			}
			return *this;
		}

		result_type invoke(argument_type args) {
			content->invoke(args);
			return;
		}

	private:
		std::auto_ptr<any_holder> content;
	};

	//----------------------------------------------------------
	// ������void�̂Ƃ��̓����^
	template<typename Result>
	class Functor<Result, void> {
	public:
		typedef void Args;
		typedef Functor<Result, Args>	this_type;
		typedef Result						result_type;
		typedef Args						argument_type;

	private:
		// �v���X�z���_
		class any_holder {
		public:
			// �f�X�g���N�^
			virtual ~any_holder() { }
			// �R�s�[�R���X�g���N�^�̑�p
			virtual any_holder* clone() = 0;
			// ���s�֐�
			virtual result_type invoke() = 0;
		};

		// null�v���X�z���_
		class null_any_holder : public any_holder {
		public:
			// �f�X�g���N�^
			virtual ~null_any_holder()
			{
			}
			// �R�s�[�R���X�g���N�^�̑�p
			virtual any_holder* clone() {
				return new null_any_holder();
			}
			// ���s�֐�
			virtual result_type invoke() {
				return result_type();
			}
		};

		// �ʏ�֐��̂Ƃ�
		template<typename _Func>
		class func_any_holder : public any_holder {
		public:
			// �f�X�g���N�^
			virtual ~func_any_holder()
			{
			}
			// �R���X�g���N�^�i���������v�j
			explicit func_any_holder(_Func const &func)
				: m_func(func)
			{
			}
			// �R�s�[�R���X�g���N�^�̑�p
			virtual any_holder* clone() {
				return new func_any_holder(m_func);
			}
			// ���s�֐�
			virtual result_type invoke() {
				return (m_func)();
			}
		private:
			_Func	m_func;
		};

		// �����o�֐��̂Ƃ�
		template<typename _Func, typename _ClsPtr>
		class mem_func_any_holder : public any_holder {
		public:
			// �f�X�g���N�^
			virtual ~mem_func_any_holder()
			{
			}
			// �R���X�g���N�^�i���������v�j
			explicit mem_func_any_holder(_Func const &func, _ClsPtr const &ptr)
				: m_func(func), m_ptr(ptr)
			{
			}
			// �R�s�[�R���X�g���N�^�̑�p
			virtual any_holder* clone() {
				return new mem_func_any_holder<_Func, _ClsPtr>(m_func, m_ptr);
			}
			// ���s�֐�
			virtual result_type invoke() {
				return (m_ptr->*m_func)();
			}
		private:
			_Func	m_func;
			_ClsPtr	m_ptr;
		};

	public:
		virtual ~Functor() {
			;
		}

		Functor()
			: content(new null_any_holder())
		{
		}

		template<typename _Func>
		Functor(_Func const &func)
			: content(new func_any_holder<_Func>(func))
		{
		}

		template<typename _Func, typename _ClsPtr>
		Functor(_Func const &func, _ClsPtr const &ptr)
			: content(new mem_func_any_holder<_Func, _ClsPtr>(func, ptr))
		{
		}

		Functor(this_type const &_Right)
			: content(_Right.content.get() ? _Right.content->clone() : 0)
		{
		}

		this_type& operator=(this_type const &_Right) {
			if (this != &_Right) {
				content.reset(_Right.content->clone());
			}
			return *this;
		}

		result_type invoke() {
			return content->invoke();
		}

	private:
		std::auto_ptr<any_holder> content;
	};

	//----------------------------------------------------------
	// �����E�߂�l��void�̂Ƃ��̓����^
	template<>
	class Functor<void, void> {
	public:
		typedef void Args;
		typedef void Result;
		typedef Functor<Result, Args>	this_type;
		typedef Result						result_type;
		typedef Args						argument_type;

	private:
		// �v���X�z���_
		class any_holder {
		public:
			// �f�X�g���N�^
			virtual ~any_holder() { }
			// �R�s�[�R���X�g���N�^�̑�p
			virtual any_holder* clone() = 0;
			// ���s�֐�
			virtual result_type invoke() = 0;
		};

		// null�v���X�z���_
		class null_any_holder : public any_holder {
		public:
			// �f�X�g���N�^
			virtual ~null_any_holder()
			{
			}
			// �R�s�[�R���X�g���N�^�̑�p
			virtual any_holder* clone() {
				return new null_any_holder();
			}
			// ���s�֐�
			virtual result_type invoke() {
				return;
			}
		};

		// �ʏ�֐��̂Ƃ�
		template<typename _Func>
		class func_any_holder : public any_holder {
		public:
			// �f�X�g���N�^
			virtual ~func_any_holder()
			{
			}
			// �R���X�g���N�^�i���������v�j
			explicit func_any_holder(_Func const &func)
				: m_func(func)
			{
			}
			// �R�s�[�R���X�g���N�^�̑�p
			virtual any_holder* clone() {
				return new func_any_holder(m_func);
			}
			// ���s�֐�
			virtual result_type invoke() {
				(m_func)();
				return;
			}
		private:
			_Func	m_func;
		};

		// �����o�֐��̂Ƃ�
		template<typename _Func, typename _ClsPtr>
		class mem_func_any_holder : public any_holder {
		public:
			// �f�X�g���N�^
			virtual ~mem_func_any_holder()
			{
			}
			// �R���X�g���N�^�i���������v�j
			explicit mem_func_any_holder(_Func const &func, _ClsPtr const &ptr)
				: m_func(func), m_ptr(ptr)
			{
			}
			// �R�s�[�R���X�g���N�^�̑�p
			virtual any_holder* clone() {
				return new mem_func_any_holder<_Func, _ClsPtr>(m_func, m_ptr);
			}
			// ���s�֐�
			virtual result_type invoke() {
				(m_ptr->*m_func)();
				return;
			}
		private:
			_Func	m_func;
			_ClsPtr	m_ptr;
		};

	public:
		virtual ~Functor() {
			;
		}

		Functor()
			: content(new null_any_holder())
		{
		}

		template<typename _Func>
		Functor(_Func const &func)
			: content(new func_any_holder<_Func>(func))
		{
		}

		template<typename _Func, typename _ClsPtr>
		Functor(_Func const &func, _ClsPtr const &ptr)
			: content(new mem_func_any_holder<_Func, _ClsPtr>(func, ptr))
		{
		}

		Functor(this_type const &_Right)
			: content(_Right.content.get() ? _Right.content->clone() : 0)
		{
		}

		this_type& operator =(this_type const &_Right) {
			if (this != &_Right) {
				content.reset(_Right.content->clone());
			}
			return *this;
		}

		result_type invoke() {
			content->invoke();
			return;
		}

	private:
		LyceeAutoPointer<any_holder> content;
	};

}	// alice
#endif	// __LYCEE__FUNCTOR__HEADER__
