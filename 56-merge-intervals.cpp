//Задача: 56 Merge Intervals
//time: O(n*log(n)), space: O(n)

#include <queue>
#include <vector>
#include <algorithm>

class Solution {
private:
    //Пишем кастомный компаратор, чтобы временные промежутки (из intervals) шли от раннего к позднему.
    //Для этого сначал проверяем их начальное время (если одинаково вернём элемент с наименьшим конечным временем)
    //после чего (если a[0] != b[0]) возвращем тот, где начальное время меньше 
    struct compareByFirst{
        bool operator()(const std::vector<int>& a, const std::vector<int>& b) const {
            if (a[0] == b[0]) return a[1] > b[1];
            return a[0] > b[0];
        }
    };
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        //Оптимизируем ввод для оптимизации работы алгоритма (в рамках задачи допустимо)
        ios::sync_with_stdio(0);
        cin.tie(0);

        //Сразу проверим содержательность массива, чтобы в случае чего не проходиться по всему алгоритму
        if (intervals.empty()) return {};
        

        //Инициализируем и заполняем priority_queue используя наш компаратор
        std::priority_queue<vector<int>, vector<vector<int>>, compareByFirst> heap(intervals.begin(), intervals.end());
        //Создаем массив, где будем хранить результат
        vector<vector<int>> result;

        //Запускаем цикл, в котором будем рассматривать все элементы нашей кучи priority_queue
        while (!heap.empty()) {
            //Будем отдельно рассматривать каждый подмассив и сравнивать со следующими в куче
            std::vector<int> current = heap.top();
            heap.pop();

            //Пока куча не пуста, а также наш подмассив имеет конечное значение
            //больше, чем начальное значение последующего подмассива
            //мы просто сливаем подмассив с его "соседом"
            while (!heap.empty() && heap.top()[0] <= current[1]) {
                current[1] = std::max(current[1],heap.top()[1]);
                heap.pop();
            }

            //Уже обобщенный подмассив отправляется в массив-результат
            result.push_back(current);
        }

    //Возвращаем ответ
    return result;
    }
};

//Примечание: также для решения можно было использовать std::sort для сортировки intervals, что
//привело бы к оптимизации space: O(1), но для решения был выбран именно priority_queue для
//работы с потоком данных. Этот подход более универсален.