/* 
 * File:   ai.h
 * Author: utop
 *
 * Created on 10 августа 2015 г., 2:58
 */

#ifndef AI_H
#define	AI_H

#define LOW_MEM

//#include "lib.h"

#include <iostream>
#include <vector>
#include <bitset>
#include <algorithm>
#include <cmath>
#include <random>
#include <climits>

#ifndef LOW_MEM
typedef long double ldouble;
#else
typedef float ldouble;
#endif

struct Random{ // Генератор псевдослучайных чисел
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution = std::uniform_real_distribution<double>(0,1);
    
    ldouble Normal_distribution(){ 
        return distribution(generator);
    };//base_uniform();};
    
    
};// struct Random



enum NetworkType{
    BackPropagation, // обратное распростронение ошибки
    Kalman
};// enum NetworkType

struct Synaps{
    //< Ребро, участок между двумя нейронами
    // Хранит информацию для преобразования и историю (для статистики)
    int layer;  //< Слой синапса
    int index_i;      //< Индекс нейрона-источника
    int index_j;      //< Индекс нейрона-приемника
#ifdef  LOW_MEM
    ldouble w;
    ldouble sigma;
#else
    std::vector<ldouble> w;      //< Коэффициент синапса - история
    std::vector<ldouble> sigma;  //< Ошибка в вычислениях - история
#endif

    Synaps( int layer_, int i_, int j_, Random *rnd);
    ldouble impuls(ldouble in);   //< проход одного импульса, возвращает полученное значение
    ldouble calculate_sigma(ldouble sigma);   //< Вычисление скорректированной сигмы
    void change_w(ldouble nu,ldouble f_derivative,ldouble signal); //< Изменение значения w. nu - скорость обучения
    void print();
    void print_short();
    // f_derivative - значение производной логистической функции
};


struct Neuron{
    int dem;                    //< Размерность выходного вектора
    int layer;                  //< Индекс слоя
    int index_i;                  //< индекс нейрона в слое
    
    std::vector<Synaps> synapses;       // synapses; // Веса выходных синапсов
    
    ldouble nu = 1;
    
#ifdef LOW_MEM
    ldouble input;
#else
    std::vector<ldouble> input;           // Входные значение - история
#endif//    std::vector<ldouble> output;  // Последнее выходное значение - не нужное значение
//    std::vector<ldouble> signals; //< Последний прошедший сигнал - сигнал хранится в input
    
    Neuron(int dem_,int layer,int i,Random *rnd);
    
    ldouble f(ldouble); // Логистиеская функция
    ldouble f_derivative(ldouble); // Значение производная от логистической функции
    
    std::vector<ldouble> impulse(ldouble in); // Запускает процесс рассчета.
    void correct(std::vector<ldouble> next); // На вход подается сумма всех входов следующего слоя
    ldouble calculate_sigmas(std::vector<ldouble> sigmas);
    
    void print();
};


class NeuralLayer{
    int dem;                    //< Размерность текущего слоя
    int nextdem;                //< Размерность выходного слоя
    int layer;                  //< Индекс слоя
    bool is_last;               //< признак последнего слоя - нейроны не содержат синапсов.
    std::vector<Neuron> Layer;  //< Список нейронов в слое
    std::vector<ldouble> sigmas;           // Полученные сигмы - для корректировки слоя
    
public:
    NeuralLayer(int dem_,     int nextdem_,   int layer_,Random *rnd,bool is_last = false);
//    std::vector<ldouble> step(std::vector<ldouble>);
    std::vector<ldouble> impulses(std::vector<ldouble>);
    
    std::vector<ldouble> calculate_sigmas(std::vector<ldouble>); // Рассчет сигм для следующего слоя
    
    void correct(std::vector<ldouble> next); // Коррекция происходит на основании уже посчитанных сигм
    
    std::vector<ldouble> inputs();
    
    void print();
    
}; // struct NeuralLay




class NeuralNetwork{// Класс - создатель нейронной сети
    Random *rnd;
    std::vector<NeuralLayer> Layers;
//    TrainingSet *ts; - все-таки отдельно
public:
           //TrainingSet *ts_,  // Тестовый набор
           //long seed = 1,    // Начальное значение псевдослучайной последовательности
    NeuralNetwork(std::vector<int> NumNeurons = {2,3,2,1}, // Размерность слоев
                  NetworkType Nt= BackPropagation     // Тип нейронной сети
                  );
    
    std::vector<ldouble> train(std::vector<ldouble> in,std::vector<ldouble> out); // обучение нейросети
    std::vector<ldouble> test(std::vector<ldouble> in); // тестирование нейросети
    
    void print();
//    void train(long num = 0);   // Тренировка, num - количество тестов(0 - все)
//    std::vector<ldouble> step(Exercise);     // Вызов одного примера
//    std::vector<ldouble> Error (Exercise,std::vector<ldouble>);
//    void CorrectionWeights(std::vector<ldouble>); // Коррекция ошибок - входной вектор - ошибки
//    std::vector<ldouble> testing();   // Тестирование обученной нейросети на тестовой выборке
};// class NeuralNetwork


class Result{
    std::vector<ldouble> res;
public:
    Result(NeuralNetwork *NN);  // Прохождение сетью тестовых заданий
};// class Result





#endif	/* AI_H */

