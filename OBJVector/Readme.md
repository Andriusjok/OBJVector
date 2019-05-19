## Vector klases implementacija

# Funkcijos
```

void resize(size_type rsize)
		{
			if (rsize < 0) throw std::out_of_range {"in function vector::resize"};
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
```
Resize funkcija perkopijuoja esancius vectoriaus narius i nauja kitokio dydzio vectoriu ir poto priskiria ji seno pointeriui bei istrina sena
```
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
```
erase funkcija, kuri ištrina narį į kurį paduodamas pointeris, o tada perstumia (jei tokiu yra) visus tolimesnius narius viena vieta atgal
```
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
```
Reserve funkcija isskiria vietos atmintyje dinamiskai sukurdamas reikiamo dydzio objekta. Tuomet perkopijuojamos senos reiksmes ir istrinamos. Po to naujas masyvas priskiriamas senam pointeriui
```
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
```
push_back funkcija (dirbanti su lvalue) "ideda" paduota reiksme i vektoriaus gala ir padidina jo dydi vienu.
```
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
```
shrink_to_fit funkcija sumazina capacity iki size jei capacity didesnis uz size. Tai atliekama sukuriant nauja new objekta ir perkopijuojant reiksmes

push_back()

| Konteineris | Talpa     | Vidutinis laikas |
| ----------- | --------- | ---------------- |
| std::vector | 1000000   | 0.0936002        |
| Vector      | 1000000   | 0.0468001        |
| std::vector | 10000000  | 0.717601         |
| Vector      | 10000000  | 0.390001         |
| std::vector | 100000000 | 5.92801          |
| Vector      | 100000000 | 2.1684           |

capacity count

| Konteineris | Talpa     | capacity() == size() |
| ----------- | --------- | -------------------- |
| std::vector | 100000000 | 28 kartai            |
| Vector      | 100000000 | 28 kartai            |
# vector testas
[Nuoroda į releasą](https://github.com/Andriusjok/Objektinis3uzd/releases/tag/ver2.0)
