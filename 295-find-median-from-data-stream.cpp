//Задача: 295 Find Median from Data Stream
//Условие задачи: написать класс структуры данных, которая будет хранить
//значения и будет способна возвращать медиану (среднее значение в в упорядоченном списке)

#include <queue>
#include <vector>

class MedianFinder {
private:
    //Инициализация элементов

    //Очередь, которая будет хранить часть элементов <= медиане.
    //Имеет стандартную сортировку элементов (max_heap)
    std::priority_queue<int> left;

    //Очередь, которая будет хранить элементы >= медиане.
    //Сортировка элементов min_heap, реализованная через лямбду (также можно использовать std::greater)
    std::priority_queue<int, std::vector<int>, decltype([](const int a, const int b) {return a > b;})> right;
    
    //Для версий младше C++20
    //struct min_heap{
    //    bool operator()(const int a, const int b) const {
    //        return a > b;
    //    }
    //};
    // std::priority_queue<int, std::vector<int>, min_heap> right; 

public:
    //Пустой конструктор
    MedianFinder() {}
    
    //Добавление значений:
    //Изначально будем добавлять слева, после чего наибольший элемент 
    //левой кучи будет отправлен в правую, чтобы сбалансировать размеры куч
    void addNum(int num) {
        left.push(num);

        right.push(left.top());
        left.pop();

        //Если размер правого списка стал больше, чем левый,
        //то минимальный элемент правого отправляется в левый
        if (right.size() > left.size()){
            left.push(right.top());
            right.pop();
        }
    }
    
    //Поиск медианы:
    //Изначально проверяем левый список, потому что если он пуст - то значит не поступало вообще ни одного значения
    double findMedian() {
        if (left.empty()) return 0;

        //если же left имеет в себе хотя бы один элемент:
        //1) Если списки имеют одинаковые размеры - кол-во элементов чётно, а значит медиана = left.top() + right.top()
        //2) Иначе left больше чем right, а значит кол-во элементов нечётно, тогда медиана = left.top()
        return (left.size() == right.size()) ? ((left.top() + right.top()) / 2.0) : left.top();
    }
};
/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */

//Примечание: использование priority_queue позволяет максимально оптимизировать взятие значений для медианы
//за счёт особенности контейнера. Нам не приходится использовать индексацию для запоминания индекса, сортировку
//для хранения элементов в нужном порядке и тд. 
