#include <vector>
#include <fstream>

namespace tk1 {

    class signal_handler {
    public:
        
    //Конструктор
        explicit signal_handler(const std::string& filename);
        
        //Деcтруктор
        ~signal_handler();

        void EnterSignals ();

        void CookingSignals();

        void CookingTime();

        void ShowTerminal_SaveLog();

    private:
        std::vector < double > buffer_;
        std::vector < int > signals;
        std::ofstream log_file_;       
        std::string filename_;
    };

} // tk1

