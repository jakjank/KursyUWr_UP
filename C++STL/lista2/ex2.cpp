#include <fstream>
#include <memory>

struct line_writer
{
    line_writer(std::string filename) :
        m_out(std::make_unique<std::ofstream>(filename, std::ios::out))
    {}

    ~line_writer()
    {
        *m_out << "this line writer was closed";
        m_out->close();
    }
    
    void write(std::string s)
    {
        *m_out << s << "\n";
    }

    std::unique_ptr<std::ofstream> m_out;
};

int main()
{
    std::string filename{"ex2.txt"};

    auto writer = std::make_shared<line_writer>(filename);

    auto w1 = writer;
    auto w2 = writer;
    {
        auto w3 = w2;
        w3->write("hello! its w3");
    }
    w1->write("hello! its w1");
    writer->write("hello! its original writer");
    w2->write("hello! its w2");
    w1->write("hello! its w1 again");

    return 0;
}