#ifndef _H_ARRAY
#define _H_ARRAY



template<class T>
class Array
{
	int physicalSize, logicalSize;
	char delimiter;
	T* arr;
public:
	Array(int size = 1, char delimiter = ' ');
	Array(const Array& other);
	~Array();

	const Array& operator=(const Array& other);
	const Array& operator+=(const T& newVal);
	int getLogical() const;
	T* getArr();
	const T* getArr() const;

	friend ostream& operator<<(ostream& os, const Array& arr)
	{
		for (int i = 0; i < arr.logicalSize; i++)
			os << arr.arr[i] << arr.delimiter;
		return os;
	}
};

template<class T>
Array<T>::Array(int maxSize, char delimiter)
	: physicalSize(maxSize), logicalSize(0), delimiter(delimiter)
{
	arr = new T[physicalSize];
}

template<class T>
Array<T>::Array(const Array& other) : arr(NULL)
{
	*this = other;
}

template<class T>
Array<T>::~Array()
{
	delete[]arr;
}

template<class T>
const Array<T>& Array<T>::operator=(const Array<T>& other)
{
	if (this != &other)
	{
		delete[]arr;
		physicalSize = other.physicalSize;
		logicalSize = other.logicalSize;
		delimiter = other.delimiter;
		arr = new T[physicalSize];
		for (int i = 0; i < logicalSize; i++)
			arr[i] = other.arr[i];
	}
	return *this;
}

template<class T>
const Array<T>& Array<T>::operator+=(const T& newVal)
{
	if (logicalSize < physicalSize)
	{
		arr[logicalSize++] = newVal;
	}
	else
	{
		//Array temp = this;
		physicalSize *= 2;
		T* temp = new T[physicalSize];
		for (int i = 0; i < logicalSize; i++)
			temp[i] = arr[i];

		delete[]arr;
		arr = temp;

		arr[logicalSize++] = newVal;
	}
	return *this;
}

template<class T>
int Array<T>::getLogical() const
{
	return this->logicalSize;
}

template<class T>
T* Array<T>::getArr()
{
	return this->arr;
}

template<class T>
const T* Array<T>::getArr() const
{
	return this->arr;
}
#endif // _H_ARRAY