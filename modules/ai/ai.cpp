#include "ai.h"


int start(msgertype * msg) {
    return 0;
};

// Включение логирования - вывод всех данных на консоль
//#define LOG

Synaps::Synaps( int layer_,         // Слой нейрона, содержащего синапс
                int i_,             // Индекс нейрона-отправителя
                int j_,             // Индекс нейрона-получателя
                Random *rnd         // Генератор случайных чисел для 
               ):layer(layer_),index_i(i_), index_j(j_){
    
#ifdef LOW_MEM
    w = rnd->Normal_distribution();
    sigma = 0.0;
#else
    w.push_back(rnd->Normal_distribution());
    sigma.push_back(0);
#endif
}; // Synaps::Synaps

ldouble Synaps::impuls(ldouble in){
//    signals.push_back(in);
#ifdef LOG
    print_short();
    std::cout<<"Synaps::impuls in: "<<in<<" out : "<<w.back() * in<<"\n";
#endif
#ifdef LOW_MEM
    return w * in;
#else
    return w.back() * in;//signals.back();
#endif
}; // Synaps::impuls

ldouble Synaps::calculate_sigma(ldouble sigma_){
#ifdef LOW_MEM
    sigma = sigma_;
    return w * sigma;
#else
    sigma.push_back(sigma_);
    return w.back() * sigma.back();
#endif
}; // Synaps::calculate_sigma

void Synaps::change_w(ldouble nu,ldouble f_derivative,ldouble signal){
#ifdef LOW_MEM
    ldouble w_new = w + nu * sigma * f_derivative * signal;// * signals.back();
#else
    ldouble w_new = w.back() + nu * sigma.back() * f_derivative * signal;// * signals.back();
#endif
#ifdef LOG
    std::cout<<"Synaps::change_w "<<layer<<"["<<index_i<<","<<index_j<<"]"<<" nu = "<<nu<<" f\'= "<<
            f_derivative<<" signal = "<<signal<<" w_old ="<<w.back()<<" w_new = "<<w_new<<"\n";
#endif
#ifdef LOW_MEM
    w = w_new;
#else
    w.push_back(w_new);
#endif
}; // Synaps::change_w


void Synaps::print(){
    std::cout<<"Synaps::print Synaps on "<<layer<<" layer from "<<index_i+1<<" to "<<index_j+1<<" neuron \n w list ";
#ifndef LOW_MEM
    for(int i=0;i<w.size();++i) std::cout<<w[i]<<" ";
    std::cout<<"\n Synapses sigmas ";
    for(int i=0;i<sigma.size();++i)
        std::cout<<sigma.back()<<"  ";
    std::cout<<"\n";
#endif
};

void Synaps::print_short(){
#ifndef LOW_MEM
    std::cout<<"Synaps::print_short w"<<layer<<"["<<index_i+1<<","<<index_j+1<<"]= "<<w.back()<<" s= "<<sigma.back()<<"\n";
#endif
};



Neuron::Neuron(int dem_,        // Размерность выходных значений
                int layer_,     // Уровень слоя
                int i_,         // Индекс нейрона в слое
                Random *rnd): dem(dem_),layer(layer_),index_i(i_){
#ifdef LOW_MEM    
    input = 0;
#else
    input.push_back(0);
#endif    
    for(int j=0;j<dem;++j){
        synapses.push_back(Synaps(layer,index_i,j,rnd));
    }
}; // Neuron::Neuron
    
ldouble Neuron::f(ldouble in){// Логистиеская функция
    return  1/(1+exp(-in)); // от 0 до 1
}; // Neuron::f
    
ldouble Neuron::f_derivative(ldouble in){ // Значение производная от логистической функции
    return f(in)* (1 - f(in));
}; // Neuron::f_derivative


std::vector<ldouble> Neuron::impulse(ldouble in){ // Запускает процесс рассчета.
    
    std::vector<ldouble> out(synapses.size());
#ifdef LOW_MEM    
    input = in;
#else
    input.push_back(in); //
#endif
    for(int i=0;i<synapses.size();++i)
        out[i] = synapses[i].impuls(f(in));
    return out;
}; // Neuron::impulse
    
void Neuron::correct(std::vector<ldouble> next){     // Процедура корректировки весов
    std::vector<ldouble> out(synapses.size());
    for(int i=0;i<synapses.size();++i)
#ifdef LOW_MEM    
        synapses[i].change_w(nu,f_derivative(next[i]),f(input));
#else
        synapses[i].change_w(nu,f_derivative(next[i]),f(input.back()));
#endif
//    sigmas = out;
}; // Neuron::correct

ldouble Neuron::calculate_sigmas(std::vector<ldouble> sigmas){  // Процедура
    // На вход подаются сигмы следующего слоя.
    ldouble out=0.0;
//    print();
    if(sigmas.size() != dem) {
        std::cout<<"\nError! in Neuron calculate sigmas \n"; 
        if(dem == 0) return sigmas[index_i];
        print();
        return 0.0;
    }
    for(int i=0;i<dem;++i)
        out += synapses[i].calculate_sigma(sigmas[i]);
//    std::cout<<" Neuron out :"<<out<<"\n";
    print();
    return out;
}; // Neuron::calculate_sigmas

void Neuron::print(){
#ifdef LOG
    std::cout<<"Neuron::print: Neur["<<index_i<<"] in layer "<<layer<<" dem = "<<dem<<"\n";
    for(int i=0;i<synapses.size();++i)
        synapses[i].print_short();
#endif
}; // Neuron::print

//NeuralLayer

NeuralLayer::NeuralLayer(int dem_,     int nextdem_,   int layer_,Random *rnd, bool is_last_):
                         dem(dem_),nextdem(nextdem_),layer(layer_),is_last(is_last_){
#ifdef LOG
    std::cout<<"Layer "<<layer<<" dem ="<<dem<<" nextdem ="<<nextdem<<" is_last = "<<is_last<<" \n";
#endif
    if(is_last) nextdem = 0;
    for(int i=0;i<dem;++i){
        Layer.push_back(Neuron(nextdem,layer,i,rnd)); // Мы передаем размерность следующего слоя
    };
} // NeuralLayer::NeuralLayer



std::vector<ldouble> NeuralLayer::impulses(std::vector<ldouble> inp){
    if(!is_last){
        std::vector<ldouble> out(nextdem);
    
    for(int i=0;i<dem;++i){
//        Layer[i].input.push_back(inp[i]);
        std::vector<ldouble> tmp = Layer[i].impulse(inp[i]);
        for(int j=0;j<nextdem;++j)
            out[j] += tmp[j];
    }
    return out;
    }
    else{
        std::vector<ldouble> out(dem);
        for(int i=0;i<dem;++i){
            out[i] = Layer[i].f(inp[i]);
#ifdef LOW_MEM
            Layer[i].input = inp[i]; //
#else
            Layer[i].input.push_back(inp[i]); //
#endif
        }
        return out;
    }
}; // NeuralLayer::impulses


std::vector<ldouble> NeuralLayer::calculate_sigmas(std::vector<ldouble> sigmas_){
    std::vector<ldouble> out(dem);
    sigmas = sigmas_;
#ifdef LOG
//    std::cout<<"Sigma "<<sigmas.size()<<"  dem ="<<dem<<" nextdem ="<<nextdem<<"  last = "<<is_last<<"\n";
    print();
#endif
    if(!is_last){
        for(int i=0;i<dem;++i)
            out[i] += Layer[i].calculate_sigmas(sigmas);
    }else return sigmas_;
#ifdef LOG
    std::cout<<" -> sigmaout  "<<out.size()<<" \n";
#endif
    return out;
}; // NeuralLayer::calculate_sigmas


void NeuralLayer::correct(std::vector<ldouble> next){
    for(int i=0;i<dem;++i)
        Layer[i].correct(next);
}; // NeuralLayer::correct

std::vector<ldouble> NeuralLayer::inputs(){
    std::vector<ldouble> out(dem);
    for(int i=0;i<dem;++i)
#ifdef LOW_MEM
        out[i] = Layer[i].input;
#else
        out[i] = Layer[i].input.back();
#endif
    return out;
}; // NeuralLayer::correct

void NeuralLayer::print(){
#ifdef LOG
    std::cout<<"NeuralLayer::print Layer of neurons with dem = "<<dem<<" nextdem ="<<nextdem<<" layer = "<<layer<<" is_last ="<<is_last<<"\n";
    std::cout<<" NeuralLayer::print sigmas:";
    for(int i=0;i<sigmas.size();++i)
        std::cout<<sigmas[i]<<" ";
    std::cout<<"\n";
    std::cout<<" NeuralLayer::print data:\n";
    for(int i=0;i<Layer.size();++i)
        Layer[i].print();
#endif
};

void NeuralLayer::save(std::fstream logFile){
//    f<<""
//    logFile.open();//logFileName,std::ios_base::out | std::ios_base::ate);
    logFile<<"NL d "<<dem<<" n "<<nextdem<<" l "<<layer<<" last "<<is_last<<"\n";
//    logFile.close();
    
//    std::cout<<" NeuralLayer::print sigmas:";
//    for(int i=0;i<sigmas.size();++i)
//        std::cout<<sigmas[i]<<" ";
//    std::cout<<"\n";
//    std::cout<<" NeuralLayer::print data:\n";
//    for(int i=0;i<Layer.size();++i)
//        Layer[i].print();
} 

// NeuralNetwork

NeuralNetwork::NeuralNetwork(std::vector<int> NumNeurons, //  = {3,3,3} Размерность слоев
                             NetworkType Nt     // = BackPropagation Тип нейронной сети
                  ){
#ifdef LOG
    std::cout<<NumNeurons.size()<<"size \n";
#endif
    rnd = new Random;

    for(int i=1;i<NumNeurons.size();++i)
        Layers.push_back(NeuralLayer(NumNeurons[i-1],NumNeurons[i],i,rnd,false));
        
    Layers.push_back(NeuralLayer(NumNeurons.back(),0,NumNeurons.size(),rnd,true)); // Последний слой - заполняется отдельно
    
#ifdef LOG
    print();
#endif
}; // NeuralNetwork::NeuralNetwork
    
std::vector<ldouble> NeuralNetwork::train(std::vector<ldouble> in,std::vector<ldouble> out){ // обучение нейросети
    // Рассчет
#ifdef LOG
    std::cout<<"NeuralNetwork::train: Input train set ";
    for(int i=0;i<in.size();++i)
        std::cout<<in[i]<<" ";
    std::cout<<"\n";
    std::cout<<"NeuralNetwork::train: Output train set ";
    for(int i=0;i<out.size();++i)
        std::cout<<out[i]<<" ";
    std::cout<<"\n";
#endif

    std::vector<ldouble> result = in;
    for(int i=0;i<Layers.size();++i)
        result = Layers[i].impulses(result);
    std::vector<ldouble> delta(out.size());
    for(int i=0;i<out.size();++i)
        delta[i] = out[i] - result[i];
#ifdef LOG
    std::cout<<"NeuralNetwork::train: result vector ";
    for(int i=0;i<result.size();++i)
        std::cout<<result[i]<<"\t";
    std::cout<<"\n";
#endif
    
    // Образование
    std::vector<ldouble> sigma = delta;
    for(int i=Layers.size()-1;i>=0;i--){
        sigma= Layers[i].calculate_sigmas(sigma);
//        std::cout<<"train :  "<<sigma.size()<<" i = "<<i<<"\n";
    }
#ifdef LOG
    std::cout<<"NeuralNetwork::train: Sigma calculated ! \n";
#endif

    for(int i=0;i<Layers.size()-1;++i)
        Layers[i].correct(Layers[i+1].inputs());

#ifdef LOG
    std::cout<<"NeuralNetwork::train: Finish Traning \n";
#endif
    return result;
}; // NeuralNetwork::train

std::vector<ldouble> NeuralNetwork::test(std::vector<ldouble> in){ // тестирование нейросети
        
    // Рассчет
    std::vector<ldouble> result = in;
    for(int i=0;i<Layers.size();++i)
        result = Layers[i].impulses(result);
    
#ifdef LOG
    std::cout<<"Finish Testing \n";
#endif
    return result;
}; // NeuralNetwork::test


void NeuralNetwork::print(){
#ifdef LOG
    std::cout<<"Exist NeuralNetwork with "<<Layers.size()<<" layers \n"; 
    for(int i=0;i<Layers.size();++i)
    {
        Layers[i].print();
    }
#endif
}; // NeuralNetwork::print




    std::vector<ldouble> suma0 = { 0., 0., 0., 0., 0.,
                                   0., 0., 0., 0., 0.};
    std::vector<ldouble> res_0 = { 0., 0., 0., 0., 0., 0., 0., 0., 0.};

    std::vector<ldouble> suma1 = { 1.0, 0., 0., 0., 0.,
                                   0., 0., 0., 0., 0.};
    std::vector<ldouble> sumb1 = { 0., 0., 0., 0., 0.,
                                   1.0, 0., 0., 0., 0.};
    std::vector<ldouble> res_1 = { 1.0, 0., 0., 0., 0., 0., 0., 0., 0.};

    std::vector<ldouble> suma2 = { 0., 1.0, 0., 0., 0.,
                                   0., 0., 0., 0., 0.};
    std::vector<ldouble> sumb2 = { 0., 0., 0., 0., 0.,
                                   0., 1.0, 0., 0., 0.};
    std::vector<ldouble> sumc2 = { 1.0, 0., 0., 0., 0.,
                                   1.0, 0., 0., 0., 0.};
    std::vector<ldouble> res_2 = { 0., 1.0, 0., 0., 0., 0., 0., 0., 0.};

    std::vector<ldouble> suma3 = { 0., 0., 1.0, 0., 0.,
                                   0., 0., 0., 0., 0.};
    std::vector<ldouble> sumb3 = { 0., 1.0, 0., 0., 0.,
                                   1.0, 0., 0., 0., 0.};
    std::vector<ldouble> sumc3 = { 1.0, 0., 0., 0., 0.,
                                   0., 1.0, 0., 0., 0.};
    std::vector<ldouble> sumd3 = { 0., 0., 0., 0., 0.,
                                   0., 0., 1.0, 0., 0.};
    std::vector<ldouble> res_3 = { 0., 0., 1.0, 0., 0., 0., 0., 0., 0.};

    std::vector<ldouble> suma4 = { 0., 0., 0., 1.0, 0.,
                                   0., 0., 0., 0., 0.};
    std::vector<ldouble> sumb4 = { 0., 0., 1.0, 0., 0.,
                                   1.0, 0., 0., 0., 0.};
    std::vector<ldouble> sumc4 = { 0., 0., 1.0, 0., 0.,
                                   1.0, 0., 0., 0., 0.};
    std::vector<ldouble> sumd4 = { 0., 1.0, 0., 0., 0.,
                                   0., 1.0, 0., 0., 0.};
    std::vector<ldouble> sume4 = { 0., 0., 0., 0., 0.,
                                   0., 0., 0., 1.0, 0.};
    std::vector<ldouble> res_4 = { 0., 0., 0., 1.0, 0., 0., 0., 0., 0.};


    std::vector<ldouble> suma5 = { 0., 0., 0., 0., 1.0,
                                   0., 0., 0., 0., 0.};
    std::vector<ldouble> sumb5 = { 0., 0., 0., 0., 0.,
                                   0., 0., 0., 0., 1.0};
    std::vector<ldouble> sumc5 = { 0., 0., 0., 1.0, 0.,
                                   1.0, 0., 0., 0., 0.};
    std::vector<ldouble> sumd5 = { 1.0, 0., 0., 0., 0.,
                                   0., 0., 0., 1.0, 0.};
    std::vector<ldouble> sume5 = { 0., 0., 1.0, 0., 0.,
                                   0., 1.0, 0., 0., 0.};
    std::vector<ldouble> sumf5 = { 0., 1.0, 0., 0., 0.,
                                   0., 0., 1.0, 0., 0.};
    std::vector<ldouble> res_5 = { 0., 0., 0., 0., 1.0, 0., 0., 0., 0.};

    std::vector<ldouble> suma6 = { 0., 0., 0., 0., 1.0,
                                   1.0, 0., 0., 0., 0.};
    std::vector<ldouble> sumb6 = { 1.0, 0., 0., 0., 0.,
                                   0., 0., 0., 0., 1.0};
    std::vector<ldouble> sumc6 = { 0., 0., 0., 1.0, 0.,
                                   0., 1.0, 0., 0., 0.};
    std::vector<ldouble> sumd6 = { 0., 1.0, 0., 0., 0.,
                                   0., 0., 0., 1.0, 0.};
    std::vector<ldouble> sume6 = { 0., 0., 1.0, 0., 0.,
                                   0., 0., 1.0, 0., 0.};
    std::vector<ldouble> res_6 = { 0., 0., 0., 0., 0., 1.0, 0., 0., 0.};
    
    std::vector<ldouble> suma7 = { 0., 0., 0., 0., 1.0,
                                   0., 1.0, 0., 0., 0.};
    std::vector<ldouble> sumb7 = { 0., 1.0, 0., 0., 0.,
                                   0., 0., 0., 0., 1.0};
    std::vector<ldouble> sumc7 = { 0., 0., 0., 1.0, 0.,
                                   0., 0., 1.0, 0., 0.};
    std::vector<ldouble> sumd7 = { 0., 0., 1.0, 0., 0.,
                                   0., 0., 0., 1.0, 0.};
    std::vector<ldouble> res_7 = { 0., 0., 0., 0., 0., 0., 1.0, 0., 0.};
    
    std::vector<ldouble> suma8 = { 0., 0., 0., 0., 1.0,
                                   0., 0., 1.0, 0., 0.};
    std::vector<ldouble> sumb8 = { 0., 0., 1.0, 0., 0.,
                                   0., 0., 0., 0., 1.0};
    std::vector<ldouble> sumc8 = { 0., 0., 0., 1.0, 0.,
                                   0., 0., 0., 1.0, 0.};
    std::vector<ldouble> res_8 = { 0., 0., 0., 0., 0., 0., 0., 1.0, 0.};
    
    std::vector<ldouble> suma9 = { 0., 0., 0., 0., 1.0,
                                   0., 0., 0., 1.0, 0.};
    std::vector<ldouble> sumb9 = { 0., 0., 0., 1.0, 0.,
                                   0., 0., 0., 0., 1.0};
    


int main(){
    // Создание обучающей выборки - от сида, размера базиса, размера обучающей и тестовой выборки
//    TrainingSet ts;
    // Создание нейронной сети - от сида, вектора количества нейронов в слоях и типа обучения
    
    
    NeuralNetwork NN(std::vector<int>({10,100,9}));
    NN.print();
    
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution = std::uniform_real_distribution<double>(-1,8);
    int cur = 0;
    for(int i=0;i<18000;++i){
        cur = distribution(generator);
        switch(cur){
            case 0:{
        NN.train(suma1,res_1);
        NN.train(sumb1,res_1);
        break;}
            case 1:{
        NN.train(suma2,res_2);
        NN.train(sumb2,res_2);
        NN.train(sumc2,res_2);
            break;}
            case 2:{
        NN.train(suma3,res_3);
        NN.train(sumb3,res_3);
        NN.train(sumc3,res_3);
        NN.train(sumd3,res_3);
            break;}
            case 3:{
        NN.train(suma4,res_4);
        NN.train(sumb4,res_4);
        NN.train(sumc4,res_4);
        NN.train(sumd4,res_4);
        NN.train(sume4,res_4);
            break;}
            case 4:{
        NN.train(suma5,res_5);
        NN.train(sumb5,res_5);
        NN.train(sumc5,res_5);
        NN.train(sumd5,res_5);
        NN.train(sume5,res_5);
        NN.train(sumf5,res_5);
            break;}
            case 5:{
        NN.train(suma6,res_6);
        NN.train(sumb6,res_6);
        NN.train(sumc6,res_6);
        NN.train(sumd6,res_6);
        NN.train(sume6,res_6);
            break;}
            case 6:{
        NN.train(suma7,res_7);
        NN.train(sumb7,res_7);
        NN.train(sumc7,res_7);
        NN.train(sumd7,res_7);
            break;}
            case 7:{
        NN.train(suma8,res_8);
        NN.train(sumb8,res_8);
        NN.train(sumc8,res_8);
            break;}
            default:{};
        };
    }
    
    
    
    std::vector<ldouble> result;
    int maxindex = 0;
    result = NN.test(suma9);
    std::cout<<" Result summ (without train) 9 = ";
    for(int i=0;i<result.size();++i) {if(result[i] > result[maxindex]) maxindex = i; std::cout<<result[i]<<" ";}
    std::cout<<"\t"<<maxindex+1<<" \n";
    result = NN.test(sumb9);
    std::cout<<" Result summ (without train) 9 = ";
    for(int i=0;i<result.size();++i) {if(result[i] > result[maxindex]) maxindex = i; std::cout<<result[i]<<" ";}
    std::cout<<"\t"<<maxindex+1<<" \n";
    result = NN.test(sumb1);
    std::cout<<" Result summ 1 = ";
    for(int i=0;i<result.size();++i) {if(result[i] > result[maxindex]) maxindex = i; std::cout<<result[i]<<" ";}
    std::cout<<"\t"<<maxindex+1<<" \n";
    result = NN.test(sumc2);
    std::cout<<" Result summ 2 = ";
    for(int i=0;i<result.size();++i) {if(result[i] > result[maxindex]) maxindex = i; std::cout<<result[i]<<" ";}
    std::cout<<"\t"<<maxindex+1<<" \n";
    result = NN.test(sumd3);
    std::cout<<" Result summ 3 = ";
    for(int i=0;i<result.size();++i) {if(result[i] > result[maxindex]) maxindex = i; std::cout<<result[i]<<" ";}
    std::cout<<"\t"<<maxindex+1<<" \n";
    result = NN.test(sume4);
    std::cout<<" Result summ 4 = ";
    for(int i=0;i<result.size();++i) {if(result[i] > result[maxindex]) maxindex = i; std::cout<<result[i]<<" ";}
    std::cout<<"\t"<<maxindex+1<<" \n";
    result = NN.test(sumf5);
    std::cout<<" Result summ 5 = ";
    for(int i=0;i<result.size();++i) {if(result[i] > result[maxindex]) maxindex = i; std::cout<<result[i]<<" ";}
    std::cout<<"\t"<<maxindex+1<<" \n";
    result = NN.test(sume6);
    std::cout<<" Result summ 6 = ";
    for(int i=0;i<result.size();++i) {if(result[i] > result[maxindex]) maxindex = i; std::cout<<result[i]<<" ";}
    std::cout<<"\t"<<maxindex+1<<" \n";
    result = NN.test(sumd7);
    std::cout<<" Result summ 7 = ";
    for(int i=0;i<result.size();++i) {if(result[i] > result[maxindex]) maxindex = i; std::cout<<result[i]<<" ";}
    std::cout<<"\t"<<maxindex+1<<" \n";
    result = NN.test(sumc8);
    std::cout<<" Result summ 8 = ";
    for(int i=0;i<result.size();++i) {if(result[i] > result[maxindex]) maxindex = i; std::cout<<result[i]<<" ";}
    std::cout<<"\t"<<maxindex+1<<" \n";
    
//    std::vector<ldouble> test1= {0.1,0.2};//,0.3};//,0.4,0.5};
//    std::vector<ldouble> test2= {0.5,0.6};//,0.7};//,0.8,0.9};
//    std::vector<ldouble> test3= {0.6};//,0.7,0.8};//,0.9,1.0};
//    std::vector<ldouble> delta;
//    ldouble mnk=0;
//    std::cout<<" ======================   RUN! ==================== \n";
//    for(int i=0;i<100;++i) {
//        delta = NN.train(test1,test1);
//        mnk = 0;
//        for(int i=0;i<delta.size();++i) mnk += delta[i] * delta[i];
//        std::cout<<"  "<<mnk<<" \t ";
//        delta = NN.train(test1,test3);
//        mnk = 0;
//        for(int i=0;i<delta.size();++i) mnk += delta[i] * delta[i];
//        std::cout<<"  "<<mnk<<" \t ";
//        delta = NN.train(test1,test1);
//        mnk = 0;
//        for(int i=0;i<delta.size();++i) mnk += delta[i] * delta[i];
//        std::cout<<"  "<<mnk<<" \t ";
//        delta = NN.train(test2,test2);
//        mnk = 0;
//        for(int i=0;i<delta.size();++i) mnk += delta[i] * delta[i];
//        std::cout<<"  "<<mnk<<" \t ";
//        delta = NN.train(test3,test3);
//        mnk = 0;
//        for(int i=0;i<delta.size();++i) mnk += delta[i] * delta[i];
//        std::cout<<"  "<<mnk<<" \n ";
//    }
    // Прохождение сетью тестовых заданий
//    Result r(&NN);
}
