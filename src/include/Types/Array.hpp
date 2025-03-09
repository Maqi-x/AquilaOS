template <typename T, size_t N> class Array {
  private:
    T data[N];

  public:
    Array() {}

    template <typename... Args> Array(Args&&... args) : data{static_cast<T>(args)...} { static_assert(sizeof...(args) == N, "Wrong number of elements"); }

    ~Array() {}

    T& operator[](size_t index) { return data[index]; }

    const T& operator[](size_t index) const {
        static_assert(index < N, "Index out of the range");
        return data[index];
    }

    size_t Len() const { return N; }

    T* begin() { return data; }
    T* end() { return data + N; }
    const T* begin() const { return data; }
    const T* end() const { return data + N; }
};