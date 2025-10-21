#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <set>

enum Sex
{
    male,
    female
};

struct Llama
{
    Llama(std::string name, Sex sex, std::shared_ptr<Llama> father=nullptr, std::shared_ptr<Llama> mother=nullptr)
        : m_name(name)
    {
        if( name != "noname")
        {
            m_father = father ? father : whoWentForMilk();
            m_mother = mother ? mother : whoWentForMilk(); //ma plec male ale chyba nas to nie boli?
        }
        std::cout << "Added Llama " << name << "\n";
    }

    ~Llama()
    {
        std::cout << "Removed Llama " << m_name << "\n";
    }

    std::shared_ptr<Llama> whoWentForMilk() {
        static std::shared_ptr<Llama> noname = std::make_shared<Llama>("noname", Sex::male);
        return noname;
    }

    void listKids() {
        std::cout << "Children of " << m_name << ": ";
        for (auto& wp : m_kids) 
        {
            if (auto sp = wp.lock()) 
            {
                std::cout << sp->m_name << " ";
            } 
            else 
            {
                std::cout << "(expired) ";
            }
        }
        std::cout << "\n";
    }

    friend bool operator<(const Llama& l, const Llama& r)
    {
        return l.m_name < r.m_name; 
    }

    std::string m_name;
    Sex _m_sex;
    std::shared_ptr<Llama> m_father;
    std::shared_ptr<Llama> m_mother;
    std::vector<std::weak_ptr<Llama>> m_kids;
};

struct Herd
{
    void add(std::shared_ptr<Llama> llama)
    {
        m_llamas.insert(llama);
    }

    void remove(std::shared_ptr<Llama> llama)
    {
        m_llamas.erase(llama);
    }

    void buy(const std::string& name, Sex sex) {
        auto llama = std::make_shared<Llama>(name, sex);
        m_llamas.insert(llama);
    }

    void sell(const std::string& name) {
        auto it = std::find_if(m_llamas.begin(), m_llamas.end(),
                               [&](const std::shared_ptr<Llama>& l){ return l->m_name == name; });
        if (it != m_llamas.end()) {
            m_llamas.erase(it);
        }
    }

    void birth(const std::string& name, Sex sex, std::shared_ptr<Llama> mother, std::shared_ptr<Llama> father = nullptr) {
        auto llama = std::make_shared<Llama>(name, sex, father, mother);
        m_llamas.insert(llama);

        if (mother) mother->m_kids.push_back(llama);
        if (father) father->m_kids.push_back(llama);
    }

    auto get(const std::string& name)
    {
        auto it = std::find_if(m_llamas.begin(), m_llamas.end(),
                               [&](const std::shared_ptr<Llama>& l){ return l->m_name == name; });
        return *it;
    }

    std::set<std::shared_ptr<Llama>> m_llamas;
};

int main()
{
    Herd herd;

    herd.buy("Monty", male);
    herd.buy("Plamka", female);

    auto mother =herd.get("Plamka");
    herd.birth("Lulu", female, mother);

    mother->listKids();

    herd.sell("Lulu");

    mother->listKids();

    return 0;
}