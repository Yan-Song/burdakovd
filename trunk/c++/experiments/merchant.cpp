#include <iostream>
#include <vector>

using namespace std;

class Good
{
public:
    float cost;
    string name;
    Good(string _name, float c): name(_name), cost(c) {};
    virtual ~Good() {};
    virtual void about()=0;
};

class Food: public Good
{
public:
    int restores;
    Food(string _name, float c, int r): Good(_name, c), restores(r) {};
    virtual void about(); // Этот метод смогут переопределить дочерние методы
    virtual ~Food() {}
};

void Food::about()
{
    cout<<"срок годности "<<restores<<" дней";
}

class Transport: public Good
{
public:
    float speed, benzin;
    Transport(string _name, float c, float sp, float ben): Good(_name, c), speed(sp), benzin(ben) {};
    virtual void about();
    virtual ~Transport() {}
};

void Transport::about()
{
    cout<<"достигает скорости в "<<speed<<"км/ч, вместимость топливного бака "<<benzin<<"л.";
}

class Kettle: public Good
{
public:
    float capacity, power;
    Kettle(string _name, float c, float _capacity, float _power):
            Good(_name, c), capacity(_capacity), power(_power) {};
    virtual void about();
    virtual ~Kettle() {}
};

void Kettle::about()
{
    cout<<"вместимость "<<capacity<<"л, мощность "<<power<<"Вт";
}

class Merchant
{
public:
    vector<Good*> goods;
    vector<Good*> basket;
    virtual ~Merchant();
    void add(Good *g);
    void browse();
    void complete();
};

Merchant::~Merchant()
{
    for(int i=0; i<goods.size(); i++)
        delete goods[i];
}

void Merchant::add(Good *g)
{
    goods.push_back(g);
}

void Merchant::browse() // показывает список товаров
{
    if(goods.empty())
        cout<<"В магазине закончился товар"<<endl;
    else
    {
        cout<<endl<<"Введите номер товара, чтобы купить его, 0 - чтоб выйти"<<endl;
        cout<<"Список товаров:"<<endl;
        for(int i=0; i<goods.size(); i++)
        {
            cout<<" "<<(i+1)<<") "<<goods[i]->name<<", стоимость "<<goods[i]->cost<<"$, ";
            goods[i]->about();
            cout<<endl;
        }
        cout<<"Сделайте свой выбор: ";
        while(true)
        {
            int decision=-9;
            cin>>decision;
            if(decision==0) return;
            if((decision<1)||(decision>goods.size()))
                continue;
            decision--; // пользователь считает от единицы а мы от 0
            basket.push_back(goods[decision]);
            cout<<"Куплено "<<goods[decision]->name<<" за "<<goods[decision]->cost<<"$"<<endl;
            cout<<"Ещё что-то? [0 для выхода] ";
        }
    }
}

void Merchant::complete()
{
    cout<<endl;
    if(not basket.empty())
    {
        float sum=0;
        cout<<"Список ваших покупок:"<<endl;
        for(int i=0; i<basket.size(); i++)
        {
            sum += basket[i]->cost;
            cout<<" "<<(i+1)<<") "<<basket[i]->name<<" за "<<basket[i]->cost<<"$, ";
            basket[i]->about();
            cout<<endl;
        }
        cout<<"Общая сумма: "<<sum<<"$"<<endl;
    }
    else
        cout<<"В итоге вы ничего не купили"<<endl;
}

int main()
{
    Merchant* m=new Merchant();
    
    // составляем список товаров для магазина
    m->add(new Food("Яблоко", 0.1, 120));
    m->add(new Food("Апельсин", 0.2, 240));
    m->add(new Food("Сыр", 1.6, 30));
    m->add(new Transport("Механоцикл", 1700, 370, 2));
    m->add(new Transport("Волга", 210, 33, 8));
    m->add(new Kettle("Электрочайник", 14, 1.7, 5));
    m->add(new Kettle("Самовар", 84, 3, 4));
    
    m->browse(); // ждём пока пользователь выбирает товары
    m->complete(); // выдаём результат
    delete m;
    return 0;
}
