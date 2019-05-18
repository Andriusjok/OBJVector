	#include<stdexcept>

	#include <iostream>
	template <typename T>

	class Vector {
	public:
		typedef T&& rvalue;
		typedef T value_type;
		typedef T& reference;
		typedef const T& const_reference ;
		typedef std::size_t size_type;
		typedef T* pointer;
		typedef T* iterator;
		typedef const T* const_iterator;
	private:
		pointer Data_;
		size_type size_;
		size_type capacity_;

	public:

		//konstruktoriai
		Vector() : size_{0}, capacity_{0}, Data_{nullptr} {}
		Vector(size_type s, value_type val) {
			if (s < 0) throw std::out_of_range {"class Vector cannot contain negative amount of values"};
			size_ = s;
			capacity_ = size_;
			Data_ = new value_type[capacity_];

			std::fill_n(Data_, s, val);
		}
		Vector(const Vector& vec) :
			size_{vec.size_},
			capacity_{vec.size_},
			Data_{new value_type[vec.size_]}
		{
			for (int i = 0; i != size_; ++i)
				Data_[i] = vec.Data_[i];
		}
		Vector(std::initializer_list<value_type> il) :
			size_{il.size()},
			capacity_{il.size()},
			Data_{new value_type[il.size()]}
		{
			std::copy(il.begin(), il.end(), Data_);
		}
		Vector(Vector&& vec) :
			size_{vec.size_},
			capacity_{vec.size_},
			Data_{vec.Data_}
		{
			vec.Data_ = nullptr;
			vec.size_ = 0;
			vec.capacity_ = 0;
		}
		//destruktorius

		~Vector() {	delete[] Data_; }

		//getteriai
		iterator begin()
		{
			return Data_;
		}
		iterator back()
		{
			return Data_[size()-1];
		}
		iterator end()
		{
			return Data_ + size_;
		}
		size_type size() const
		{
			return size_;
		}
		size_type capacity()
		{
			return capacity_;
		}
		size_type size()
		{
			return size_;
		}

	//OPERATORIAI

		reference operator[](size_type a)
		{
			if (a > size_ or a < 0) throw std::out_of_range {"ref operator []"};
			return Data_[a];
		}
		const_reference operator[](size_type i) const
		{
			if (i < 0 or capacity() <= i)
				throw std::out_of_range{"const ref operator []"};
			return Data_[i];
		}
		//move
		Vector<value_type>& operator=(Vector&& v)
		{
			if (&v == this)
				return *this;
			delete[] Data_;
			Data_ = v.Data_;
			capacity_ = size_;
			size_ = v.size_;
			v.Data_ = nullptr;
			v.capacity_ = 0;
			v.size_ = 0;
			return *this;
		}
	//copy assigment
		Vector<value_type>& operator=(const Vector& v) {
			if (&v == this) return *this;
			delete[] Data_;
			Data_ = new value_type[v.size_];
			for (auto i = 0; i != v.size_; ++i)
				Data_[i] = v.Data_[i];
			capacity_ = v.capacity_;
			size_ = v.size_;

			return *this;
		}

		void resize(size_type rsize)
		{
			if (rsize < 0) throw std::out_of_range {"in function Vector::resize"};
			if (rsize < size_)
			{
				pointer temp;
				temp = new value_type[rsize];
				for (auto i = 0; i < rsize; i++)
				{
					temp[i] = Data_[i];
				}
				Data_ = temp;
				temp = nullptr;
				size_ = rsize;

			} else if (rsize == capacity_)
			{
				pointer temp;
				temp = new value_type[rsize];
				for (auto i = 0; i < size_; i++)
				{
					temp[i] = Data_[i];
				}
				size_ = rsize;
				delete [] Data_;
				Data_ = temp;
				temp = nullptr;
			}
			if (rsize > capacity_)
			{
				reserve(capacity_);
				pointer temp;
				temp = new value_type[rsize];
				for (auto i = 0; i < size_; i++)
				{
					temp[i] = Data_[i];
				}
				for (auto i = size_; i < capacity_; i++)
				{
					temp[i] = value_type();
				}
				size_ = rsize;
				delete [] Data_;
				Data_ = temp;
				temp = nullptr;

			}
		}
		iterator erase(iterator pointer)
		{
			size_type del;
			for (size_type i = 0; i < size_; ++i)
			{
				if (&Data_[i] == pointer)
					del = i;


			}
			for (size_type i = del; i < size_; i++)
			{
				Data_[i] = Data_[i + 1];
			}
			Data_[size_].~value_type();
			size_ = size_ - 1;
			return &Data_[del];
		}
		iterator erase(iterator start, iterator end)
		{
			size_type st;
			size_type en;
			for (size_type i = 0; i < size_; ++i)
			{
				if (&Data_[i] == start)
				{
					st = i;

				}
				if (&Data_[i] == end - 1)
				{
					en = i;


				}

			}
			if (en > size_) throw std::out_of_range("out of range erasing");
			for (size_type i = st; i <= en; i++)
			{
				int z = 1;
				if (en + z < size_) {
					Data_[i] = Data_[en + z];
					Data_[en + z].~value_type();
				} else Data_[i].~value_type();
				z++;
			}
			size_ = size_ - (en - st +1);
			return &Data_[size_-1];
		}
		void reserve(size_type rcapacity)
		{
			if (capacity_ < rcapacity)
			{
				capacity_ = rcapacity;
				value_type *temp = new value_type[capacity_];

				for (auto i = 0; i < size_; i++)
				{
					temp[i] = Data_[i];
				}
				delete[] Data_;
				Data_ = temp;
				temp = nullptr;
			}
		}
		void push_back(const_reference value)
		{

			if (capacity_ == 0)
			{
				capacity_++;
				size_++;
				Data_ = new value_type[size_];
				Data_[0] = value;
			}
			else
			{
				if (size_ >= capacity_)
				reserve(capacity_ * 2);
				Data_[size_++] = value;
			}

		}
		void push_back(rvalue value)

		{
			if (capacity_ == 0)
			{
				capacity_++;
				size_++;
				Data_ = new value_type[size_];
				Data_[0] = value;

			}
			else
			{
				if (size_ >= capacity_)
					reserve(capacity_ * 2);

				Data_[size_++] = value;
			}

		}
		void pop_back()
		{
			if (size_ == 0) throw std::out_of_range {"pop_back"};
			Data_[size_ - 1].~value_type();
			size_--;
		}
		void shrink_to_fit()
		{
			if (capacity_ > size_)
			{
				value_type *temp = new value_type[size_];
				for (auto i = 0; i < size_; i++)
				{
					temp[i] = Data_[i];
				}
				delete[] Data_;
				Data_ = temp;
				temp = nullptr;
				capacity_ = size_;
			}
		}
		template <typename... Ts>
		void emplace_back(Ts &&... args)
		{
			push_back(value_type(std::forward<Ts>(args)...));
		}

	};