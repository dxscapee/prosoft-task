//Задача: 643 Maximum Average Subarray I (Easy)
//time: O(n), space: O(1)

#include <algorithm>
#include <vector>

class Solution {
public:
    double findMaxAverage(const vector<int>& nums, int k) {
        
        //Собираем сумму первых k элементов.
        //Записываем результат именно в max_sum, чтобы в дальнешем корректно сравнивать
        //(по условию элементы могут быть <0 из-за чего нельзя задать max_sum = 0)
        double max_sum = 0;
        for (int i = 0; i < k; ++i){
            max_sum += nums[i];
        }

        //При помощи скользящего окна ищем самую большую сумму k элементов
        double curr_sum = max_sum;
        for (int i = k;i < nums.size(); ++i){
            curr_sum-=nums[i-k];
            curr_sum+=nums[i];
            max_sum = std::max(curr_sum,max_sum);
        }
        //Возвращаем среднее значение (max_sum делённое на k)
        return max_sum / k;
    }
};

//Важный момент: для max_sum и curr_sum используем именно double, а не int или long long, потому что:
//при типе данных int мы рискуем переполнить переменные (пример: max_sum += INT_MAX, max_sum += INT_MAX)
//double, а не long, чтобы проще вернуть вещественную max_average без использования static_cast<double> и тп