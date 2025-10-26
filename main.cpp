#include "signal_handler.h"
#include <iostream>
#include <vector>

namespace tk1{
    
    void TestSignal(){
        
        //Создание лога
        signal_handler Test("array_processing.log");

        //Ввод данных
        Test.EnterSignals ();

        //Обработка данных
        Test.CookingSignals();
        
        //Вывод данных
        std::cout << "____Вывод____" << std::endl;
        Test.CookingTime ();
        Test.ShowTerminal_SaveLog();
    }  
} // namespace tk1

int main(){
    
    tk1::TestSignal();
}