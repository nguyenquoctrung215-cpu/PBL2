template <typename T>
class MyVector{
    private:
        T* data;
        int size;
        int capacity;
    public:
        MyVector(int n = 0, const T& value = T()){
            size = n;
            capacity = (n > 2) ? n : 2;
            data = new T[capacity];
            for (int i = 0; i < n; i++)
                data[i] = value;
        }

        MyVector& operator=(const MyVector& other){
            if(this == &other) return *this;
            delete[] data;
            size = other.size;
            capacity = other.capacity;
            data = new T[capacity];
            for(int i = 0; i < size; i++)
                data[i] = other.data[i];
            return *this;
        }

        void push_back(const T& t){
            if (size >= capacity){
                capacity *= 2;
                T* temp = new T[capacity];
                for (int i = 0; i < size; i++)
                    temp[i] = data[i];
                delete[] data;
                data = temp;
            }
            data[size++] = t;
        }

        ~MyVector(){
            delete [] data;
        }

        T& operator[](int i) const{
            return data[i];
        }

        bool empty() const { return size == 0;}

        int length() const { return size;}

        void erase(int x){
            if (x < 0 || x >= size) return;
            for (int i = x; i  < size - 1; i++)
                data[i] = data[i+1];
            size--;
        }
};

