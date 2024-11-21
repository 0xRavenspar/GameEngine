#include <iostream>

template <typename T> class Array {
  T *m_arr;
  size_t m_size;

public:
  Array(size_t size) : m_size(size), m_arr(new T[size]) {
    std::cout << "array constructor called" << std::endl;
  }

  ~Array() {
    delete[] m_arr;
    std::cout << "Array Deconstructor" << std::endl;
  }
  int get(size_t index) const { return m_arr[index]; }

  void set(size_t index, T val) { m_arr[index] = val; }

  void print() const {
    for (size_t i = 0; i < m_size; i++) {
      std::cout << i << ' ' << m_arr[i] << std::endl;
    }
  }

  T &operator[](size_t index) { return m_arr[index]; }
};
int main()
{
  Array<int> list(10);
  int x{};
  list.print();

  list.set(0, 999);

  std::cout << std::endl;

  std::cout << x << std::endl;

  list.print();

  Array<float> f_list(5);

  f_list[1] = 2.168;
  f_list.set(3, 3.14);
  f_list.print();
  return 0;
}
