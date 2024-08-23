#include <iostream>

class Something
{
private:
    int** m_array{};
    int m_height;
    int m_width;

    std::string* m_text{};

    void InitRandomArray(int height, int width)
    {
        if (m_array)
        {
            CleanArray();
        }

        m_height = height;
        m_width = width;
        m_array = new int* [height];
        for (int row = 0; row < height; row++)
        {
            m_array[row] = new int[width];
            for (int col = 0; col < width; col++)
            {
                m_array[row][col] = std::rand();
            }
        }
    }

    void CleanArray()
    {
        for (int row = 0; row < m_height; row++)
        {
            delete m_array[row];
        }
        delete m_array;
        m_array = NULL;
    }

    void DeepCopy(const Something& source)
    {
        m_height = source.m_height;
        m_width = source.m_width;
        m_array = new int* [m_height];
        for (int row = 0; row < m_height; row++)
        {
            m_array[row] = new int[m_width];
            for (int col = 0; col < m_width; col++)
            {
                m_array[row][col] = source.m_array[row][col];
            }
        }

        m_text = new std::string(*source.m_text);
    }

public:
    Something(int height, int width, const std::string& text)
    {
        InitRandomArray(height, width);
        m_text = new std::string{ text };
    }

    Something(const Something& source)
    {
        DeepCopy(source);
    }

    Something() = default;

    Something& operator= (const Something& source)
    {
        if (this == &source)
        {
            return *this;
        }

        if (m_array)
        {
            CleanArray();
            delete m_text;
        }

        DeepCopy(source);

        return *this;
    }

    ~Something()
    {
        CleanArray();
        delete m_text;
    }

    void PrintArray() 
    {
        for (int row = 0; row < m_height; row++)
        {
            for (int col = 0; col < m_width; col++)
            {
                std::cout << m_array[row][col] << ' ';
            }
            std::cout << std::endl;
        }
        std::cout << "text: " << *m_text << std::endl;
    }
};

int main()
{
    Something orig{ 2,2, std::string("sometext")};
    std::cout << "original class:\n";
    orig.PrintArray();

    Something copy{ orig };
    std::cout << std::endl << "class initialized by copy constructor:\n";
    copy.PrintArray();

    Something copy2;
    copy2 = orig;
    std::cout << std::endl << "class copied by assignment operator:\n";
    copy2.PrintArray();

    return 0;
}
