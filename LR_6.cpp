#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

// Потоковая функция для сортировки части массива
void sort_array_part(const string& thread_name, vector<double>& arr, int start, int end) {
  for (int i = start; i < end - 1; ++i) {
    for (int j = i + 1; j < end; ++j) {
      if (arr[i] > arr[j]) {
        swap(arr[i], arr[j]);
      }
    }
  }

  // Вывод отсортированной части массива
  for (int i = start; i < end; ++i) {
    cout << thread_name << ": " << arr[i] << endl;
    this_thread::sleep_for(chrono::milliseconds(10));  // Задержка 10 мс
  }
}

int main() {
  // Инициализация ГПСЧ
  random_device rd;
  mt19937 gen(rd());
  uniform_real_distribution<> dis(1.0, 100.0);

  // Создание и заполнение массива
  vector<double> arr(10);
  for (auto& el : arr) {
    el = dis(gen);
  }

  // Вывод исходного массива
  cout << "Исходный массив: ";
  for (const auto& el : arr) {
    cout << el << " ";
  }
  cout << endl;

  // Запуск потоков для сортировки половин массива
  thread thread1(sort_array_part, "Поток 1", ref(arr), 0, arr.size() / 2);
  thread thread2(sort_array_part, "Поток 2", ref(arr), arr.size() / 2, arr.size());

  // Ожидание завершения потоков 1 и 2
  thread1.join();
  thread2.join();

  // Запуск потока для сортировки всего массива
  thread thread3(sort_array_part, "Поток 3", ref(arr), 0, arr.size());

  // Ожидание завершения потока 3
  thread3.join();

  cout << "Все потоки завершили работу." << endl;

  return 0;
}

