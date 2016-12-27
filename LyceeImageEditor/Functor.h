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
// 通常の関数やメンバ関数を同じように扱えるようにしたクラスです．
// 戻り値と引数の型を指定することで引数が1つの関数を扱うことができ
// ます．同じように複数の引数を使いたい場合は，Collectionクラスを
// 使うことで対応できるようになります．
// 
//===============================================================
#ifndef __LYCEE__FUNCTOR__HEADER__
#define __LYCEE__FUNCTOR__HEADER__

#include "includes.h"
#include "LyceeAutoPointer.h"

namespace lycee {

	//----------------------------------------------------------
	// 万能ファンクタ
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
			// プレスホルダ
			class any_holder {
			public:
				// デストラクタ
				virtual ~any_holder() { }
				// コピーコンストラクタの代用
				virtual any_holder* clone() = 0;
				// 実行関数
				virtual result_type invoke(argument_type args) = 0;
			};

			// nullプレスホルダ
			class null_any_holder : public any_holder {
			public:
				// デストラクタ
				virtual ~null_any_holder()
				{
				}
				// コピーコンストラクタの代用
				virtual any_holder* clone() {
					return new null_any_holder();
				}
				// 実行関数
				virtual result_type invoke(argument_type args) {
					return result_type();
				}
			};

			// 通常関数のとき
			template<typename _Func>
			class func_any_holder : public any_holder {
			public:
				// デストラクタ
				virtual ~func_any_holder()
				{
				}
				// コンストラクタ（引数を強要）
				explicit func_any_holder(_Func const &func)
					: m_func(func)
				{
				}
				// コピーコンストラクタの代用
				virtual any_holder* clone() {
					return new func_any_holder(m_func);
				}
				// 実行関数
				virtual result_type invoke(argument_type args) {
					return (m_func)(args);
				}
			private:
				_Func	m_func;
			};

			// メンバ関数のとき
			template<typename _Func, typename _ClsPtr>
			class mem_func_any_holder : public any_holder {
			public:
				// デストラクタ
				virtual ~mem_func_any_holder()
				{
				}
				// コンストラクタ（引数を強要）
				explicit mem_func_any_holder(_Func const &func, _ClsPtr const &ptr)
					: m_func(func), m_ptr(ptr)
				{
				}
				// コピーコンストラクタの代用
				virtual any_holder* clone() {
					return new mem_func_any_holder<_Func, _ClsPtr>(m_func, m_ptr);
				}
				// 実行関数
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
	// 戻り値がvoidのときの特化型
	template< typename Args >
	class Functor<void, Args> {
	public:
		typedef void Result;
		typedef Functor<Result, Args>	this_type;
		typedef Result						result_type;
		typedef Args						argument_type;

	private:
		// プレスホルダ
		class any_holder {
		public:
			// デストラクタ
			virtual ~any_holder() { }
			// コピーコンストラクタの代用
			virtual any_holder* clone() = 0;
			// 実行関数
			virtual result_type invoke(argument_type args) = 0;
		};

		// nullプレスホルダ
		class null_any_holder : public any_holder {
		public:
			// デストラクタ
			virtual ~null_any_holder()
			{
			}
			// コピーコンストラクタの代用
			virtual any_holder* clone() {
				return new null_any_holder();
			}
			// 実行関数
			virtual result_type invoke(argument_type args) {
				return;
			}
		};

		// 通常関数のとき
		template<typename _Func>
		class func_any_holder : public any_holder {
		public:
			// デストラクタ
			virtual ~func_any_holder()
			{
			}
			// コンストラクタ（引数を強要）
			explicit func_any_holder(_Func const &func)
				: m_func(func)
			{
			}
			// コピーコンストラクタの代用
			virtual any_holder* clone() {
				return new func_any_holder(m_func);
			}
			// 実行関数
			virtual result_type invoke(argument_type args) {
				(m_func)(args);
				return;
			}
		private:
			_Func	m_func;
		};

		// メンバ関数のとき
		template<typename _Func, typename _ClsPtr>
		class mem_func_any_holder : public any_holder {
		public:
			// デストラクタ
			virtual ~mem_func_any_holder()
			{
			}
			// コンストラクタ（引数を強要）
			explicit mem_func_any_holder(_Func const &func, _ClsPtr const &ptr)
				: m_func(func), m_ptr(ptr)
			{
			}
			// コピーコンストラクタの代用
			virtual any_holder* clone() {
				return new mem_func_any_holder<_Func, _ClsPtr>(m_func, m_ptr);
			}
			// 実行関数
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
	// 引数がvoidのときの特化型
	template<typename Result>
	class Functor<Result, void> {
	public:
		typedef void Args;
		typedef Functor<Result, Args>	this_type;
		typedef Result						result_type;
		typedef Args						argument_type;

	private:
		// プレスホルダ
		class any_holder {
		public:
			// デストラクタ
			virtual ~any_holder() { }
			// コピーコンストラクタの代用
			virtual any_holder* clone() = 0;
			// 実行関数
			virtual result_type invoke() = 0;
		};

		// nullプレスホルダ
		class null_any_holder : public any_holder {
		public:
			// デストラクタ
			virtual ~null_any_holder()
			{
			}
			// コピーコンストラクタの代用
			virtual any_holder* clone() {
				return new null_any_holder();
			}
			// 実行関数
			virtual result_type invoke() {
				return result_type();
			}
		};

		// 通常関数のとき
		template<typename _Func>
		class func_any_holder : public any_holder {
		public:
			// デストラクタ
			virtual ~func_any_holder()
			{
			}
			// コンストラクタ（引数を強要）
			explicit func_any_holder(_Func const &func)
				: m_func(func)
			{
			}
			// コピーコンストラクタの代用
			virtual any_holder* clone() {
				return new func_any_holder(m_func);
			}
			// 実行関数
			virtual result_type invoke() {
				return (m_func)();
			}
		private:
			_Func	m_func;
		};

		// メンバ関数のとき
		template<typename _Func, typename _ClsPtr>
		class mem_func_any_holder : public any_holder {
		public:
			// デストラクタ
			virtual ~mem_func_any_holder()
			{
			}
			// コンストラクタ（引数を強要）
			explicit mem_func_any_holder(_Func const &func, _ClsPtr const &ptr)
				: m_func(func), m_ptr(ptr)
			{
			}
			// コピーコンストラクタの代用
			virtual any_holder* clone() {
				return new mem_func_any_holder<_Func, _ClsPtr>(m_func, m_ptr);
			}
			// 実行関数
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
	// 引数・戻り値がvoidのときの特化型
	template<>
	class Functor<void, void> {
	public:
		typedef void Args;
		typedef void Result;
		typedef Functor<Result, Args>	this_type;
		typedef Result						result_type;
		typedef Args						argument_type;

	private:
		// プレスホルダ
		class any_holder {
		public:
			// デストラクタ
			virtual ~any_holder() { }
			// コピーコンストラクタの代用
			virtual any_holder* clone() = 0;
			// 実行関数
			virtual result_type invoke() = 0;
		};

		// nullプレスホルダ
		class null_any_holder : public any_holder {
		public:
			// デストラクタ
			virtual ~null_any_holder()
			{
			}
			// コピーコンストラクタの代用
			virtual any_holder* clone() {
				return new null_any_holder();
			}
			// 実行関数
			virtual result_type invoke() {
				return;
			}
		};

		// 通常関数のとき
		template<typename _Func>
		class func_any_holder : public any_holder {
		public:
			// デストラクタ
			virtual ~func_any_holder()
			{
			}
			// コンストラクタ（引数を強要）
			explicit func_any_holder(_Func const &func)
				: m_func(func)
			{
			}
			// コピーコンストラクタの代用
			virtual any_holder* clone() {
				return new func_any_holder(m_func);
			}
			// 実行関数
			virtual result_type invoke() {
				(m_func)();
				return;
			}
		private:
			_Func	m_func;
		};

		// メンバ関数のとき
		template<typename _Func, typename _ClsPtr>
		class mem_func_any_holder : public any_holder {
		public:
			// デストラクタ
			virtual ~mem_func_any_holder()
			{
			}
			// コンストラクタ（引数を強要）
			explicit mem_func_any_holder(_Func const &func, _ClsPtr const &ptr)
				: m_func(func), m_ptr(ptr)
			{
			}
			// コピーコンストラクタの代用
			virtual any_holder* clone() {
				return new mem_func_any_holder<_Func, _ClsPtr>(m_func, m_ptr);
			}
			// 実行関数
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
