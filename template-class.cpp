#include <iostream>

template <typename T>
class tablou
{
	T* table_;
	int rows_, cols_;

public:
	tablou() : table_(nullptr), rows_(0), cols_(0) {}

	tablou(const int rows, const int cols) : table_(nullptr), rows_(0), cols_(0) {
		if (rows <= 0 || cols <= 0)
			throw std::invalid_argument("Dimensiuni invalide");
		table_ = new T[rows * cols];
		rows_ = rows; cols_ = cols;
	}

	tablou(const tablou& other)
	{

		// table_ = static_cast<T*>(malloc(other.rows_ * other.cols_ * sizeof(T)));
		table_ = new T[other.rows_ * other.cols_];
		rows_ = other.rows_; cols_ = other.cols_;
		try
		{
			for (int i = 0; i < rows_ * cols_; i++)
			{
				table_[i] = other.table_[i];
			}
		}
		catch (...)
		{
			delete[] table_;
			throw;
		}
	}

	~tablou() { delete[] table_; }

	T& operator()(const int i, const int j) { return table_[i * cols_ + j]; }

	const T& operator()(const int i, const int j) const { return table_[i * cols_ + j]; }

	T& at(const int i, const int j)
	{
		if (i < 0 || i >= rows_ || j < 0 || j >= cols_)
			throw std::out_of_range("Indice in afara limitelor");
		return table_[i * cols_ + j];
	}

	const T& at(const int i, const int j) const
	{
		if (i < 0 || i >= rows_ || j < 0 || j >= cols_)
			throw std::out_of_range("Indice in afara limitelor");
		return table_[i * cols_ + j];
	}

	int rows() const { return rows_; }

	int cols() const { return cols_; }

	int size() const { return cols_ * rows_; }

	bool empty() const { return cols_ == 0 || rows_ == 0; }

	void fill(const T& value)
	{
		for (auto i = 0; i < rows_; i++)
		{
			for (auto j = 0; j < cols_; j++)
			{
				table_[i * cols_ + j] = value;
			}
		}
	}

	T* begin() { return table_; }

	T* end() { return table_ + rows_ * cols_; }

	const T* begin() const { return table_; }

	const T* end() const { return table_ + rows_ * cols_; }

	bool is_square() const { return rows_ == cols_; }

	tablou& operator*=(const int n)
	{
		for (auto i = 0; i < rows_ * cols_; i++)
		{
			table_[i] *= n;
		}

		return *this;
	}

	tablou& operator=(const tablou& other)
	{
		if (this == &other) return *this;

		//T* new_table = static_cast<T*>(malloc(other.rows_ * other.cols_ * sizeof(T)));
		T* new_table = new T[other.rows_ * other.cols_];
		delete[] table_;
		table_ = new_table;
		rows_ = other.rows_; cols_ = other.cols_;

		for (auto i = 0; i < rows_ * cols_; i++)
		{
			table_[i] = other.table_[i];
		}

		return *this;
	}

	friend std::istream& operator>>(std::istream& in, tablou& t)
	{
		std::cout << "Introduceti numarul de randuri si coloane, separate prin spatiu: ";
		int rows, cols; in >> rows >> cols;
		while (rows <= 0 || cols <= 0)
		{
			std::cout << "Numarul de randuri si coloane nu au fost introduse corect. Incercati din nou: ";
			in >> rows >> cols;
		}

		//t.table_ = static_cast<T*>(malloc(rows * cols * sizeof(T)));
		T* new_table = new T[rows * cols];
		delete[] t.table_;
		t.table_ = new_table;
		t.rows_ = rows; t.cols_ = cols;

		for (auto i = 0; i < t.rows_; i++)
		{
			for (auto j = 0; j < t.cols_; j++)
			{
				std::cout << "[" << i << "][" << j << "]: ";
				in >> t.table_[i * t.cols_ + j];
			}
		}
		return in;
	}

	friend std::ostream& operator<<(std::ostream& out, const tablou& t)
	{
		for (auto i = 0; i < t.rows_; i++)
		{
			for (auto j = 0; j < t.cols_; j++)
			{
				out << "[" << i << "][" << j << "]: ";
				out << t.table_[i * t.cols_ + j] << "\n";
			}
		}
		return out;
	}
};


int main()
{
	tablou<int> t1(3, 3);
	std::cin >> t1;
	std::cout << "\n";

	std::cout << t1 << "\n";

	tablou<int> t2 = t1;
	t1(0, 0) = 999;
	std::cout << "t1 dupa modificare:\n" << t1 << "\n";
	std::cout << "t2 (copie independenta):\n" << t2 << "\n";

	tablou<int> t3(2, 5);
	t3.fill(7);
	std::cout << "t3 umplut cu 7:\n" << t3 << "\n";

	t3 = t1;
	std::cout << "t3 dupa asignare din t1:\n" << t3;

	std::cout << "rows=" << t1.rows() << " cols=" << t1.cols() << " size=" << t1.size() << "\n";
	std::cout << "is_square=" << t1.is_square() << " empty=" << t1.empty() << "\n";

	try {
		std::cout << t1.at(0, 0) << "\n";
		std::cout << t1.at(10, 10) << "\n";
	}
	catch (const std::out_of_range& e) {
		std::cout << "Exceptie: " << e.what() << "\n";
	}

	for (auto& x : t1) x *= 2;
	std::cout << "t1 dupa inmultire cu 2:\n" << t1 << "\n";

	t1 *= 3;
	std::cout << "t1 dupa inmultirea cu 3:\n" << t1 << "\n";

	tablou<int> t4;
	std::cout << "t4 empty=" << t4.empty() << "\n";
}