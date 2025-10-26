#include "signal_handler.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <sstream>
#include <iomanip>  

namespace tk1 {

    signal_handler::signal_handler(const std::string& filename) : filename_(filename) {
        
        if (filename.empty()) {
            std::cerr << "Error: filename is empty" << std::endl;
        }
    
        log_file_.open(filename_);
        if (!log_file_.is_open()) {
            std::cerr << "Error: Could not open file " << filename_ << std::endl;
        }
    }

    signal_handler::~signal_handler() {
        
        if (log_file_.is_open()) {
            log_file_.close();
        }
    }

    void signal_handler::EnterSignals () {
        
        std::cout << "____Ввод данных____" << std::endl;
        std::cout << "завершения ввода введите не int значение" << std::endl;
        
        //Ввод данных
        int value;
        while (std::cin >> value){
            signals.push_back(value);
            std::cout << "Введите_новое_число" << std::endl;
        }
    }

    void signal_handler::CookingSignals (){
        
        std::vector < int > diff_;
        
        //Вычисление разности между соседними элементами
        for (int i = 1; i < signals.size(); i++){
            diff_.push_back(signals[i] - signals[i-1]);
        }
        
        //Вычисление скользящего среднего
        for (int i = 2; i < diff_.size(); i++){
            double sma;
            sma = (diff_[i] + diff_[i-1] + diff_[i-2]) / 3.0;
            buffer_.push_back(sma);
        }
    }

    void signal_handler::CookingTime(){
        
        // Получаем время
        auto now = std::chrono::system_clock::now();
        auto time_t = std::chrono::system_clock::to_time_t(now);
            
        // Делаем читаемым
        std::tm tm_buf;
        localtime_r(&time_t, &tm_buf);
        std::ostringstream timestamp;
        timestamp << std::put_time(&tm_buf, "%Y-%m-%d %H:%M:%S");
            
        // Пишем время в терминале
        std::cout << "[" << timestamp.str() << "] Обработка сигналов: " << std::endl;
        
        // Пишем время в лог
        if (log_file_.is_open()) {   
            log_file_ << "[" << timestamp.str() << "] Обработка сигналов: " << std::endl;
            
        } else {
            std::cerr << "Error: Log file is not open" << std::endl;
        }   
    }

    void signal_handler::ShowTerminal_SaveLog(){

        // Вывод в терминал
        std::cout << "Исходный массив: " << "[";
            for (int i = 0; i < signals.size(); i++) {
                std::cout << signals[i] << ", "; 
            }
        std::cout << "]" << std::endl;

        std::cout << "Скользящее среднее: " << "[";
            for (int i = 0; i < buffer_.size(); i++) {
                std::cout << buffer_[i] << ", "; 
            }
        std::cout << "]" << std::endl;

        // Сохранение в логе
        if (log_file_.is_open()) {
            log_file_ << "Исходный массив: " << "[";
                for (int i = 0; i < signals.size(); i++) {
                    log_file_ << signals[i] << ", "; 
                }
            log_file_ << "]" << std::endl;
            
            log_file_ << "Скользящее среднее: " << "[";
                for (int i = 0; i < buffer_.size(); i++) {
                    log_file_ << buffer_[i] << ", "; 
                }
            log_file_ << "]" << std::endl;
        } else {
            std::cerr << "Error: Log file is not open" << std::endl;
        }   
    }

} //namespace tk1
