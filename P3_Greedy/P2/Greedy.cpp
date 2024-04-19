#include <iostream>
#include <istream>
#include <ostream>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <list>

using namespace std;

struct info_exam {

    // int id;
    int start_time;      // [0-minutos_del_día[
    int duration;

    info_exam(int hour=0, int minutes=0, int duration=0){
        set_info_exam(hour, minutes, duration);
    }

    info_exam(int minutes, int duration): duration(duration), start_time(minutes) {}

    void set_info_exam(int start_time, int duration) {
        this->start_time = start_time;
        this->duration = duration;
    }

    void set_info_exam(int h, int m, int duration) {
        this->start_time = hour2minFormat(h, m);
        this->duration = duration;
    }
    
    int get_finish_time(void) const {
        return start_time + duration;
    }
    
    void get_finish_time(int &h, int &m) const{
        int aux = start_time + duration;
        min2hourFormat(aux, h, m);
    }

    bool canGoAfter(info_exam e) {
        return get_finish_time() <= e.start_time;
    }

    bool operator<(info_exam e) {
        return this->start_time < e.start_time;
    }
    

    private:

    int hour2minFormat(int hour, int minutes) const{
        return hour*60 + minutes;
    }

    void min2hourFormat(int minutos, int& h, int& m) const{
        h = minutos/60;
        m = minutos%60;
    }

    public:

    // Cambiar formato de entrada
    friend std::istream& operator>>(std::istream& inputStream, info_exam& e){

        int h, m, duration;
        char c;
        inputStream >> h >> c >> m >> duration;

        e.set_info_exam(h, m, duration);

        return inputStream;
    }
    friend ostream& operator<<(ostream& outputStream, const info_exam& e){

        int h, m;
        e.min2hourFormat(e.start_time, h,m);
        outputStream << "[" << h << ":" << setfill('0') << setw(2) << right << m << "," << e.duration << " min]";
        return outputStream;
    }

};



// Sacar el máximo número de clases necesarios
void greedy(vector<info_exam> & all_exams, vector<list<info_exam>>& used_classroom) {

    // Ordena los examenes según tiempo de inicio

    sort(all_exams.begin(), all_exams.end());

    for (int i = 0; i < all_exams.size(); ++i) {

        bool foundAClass = false;

        for (int j = 0; j < used_classroom.size() && !foundAClass; ++j) {
            if(used_classroom[j].back().canGoAfter(all_exams[i])) {
                used_classroom[j].push_back(all_exams[i]);
                foundAClass = true;
            }
        }

        if (!foundAClass) {
            list<info_exam> new_classroom;
            new_classroom.push_back(all_exams[i]);
            used_classroom.push_back(new_classroom);
        }
        
    }
}
int main(int argc, char* argv[]) 
{

    // Lectura de datos: Número de exámenes
    // y los datos relativos a los exámenes


    int n;

    std::cin >> n;

    info_exam aux;
    vector<info_exam> all_exams;

    for (int i=0; i < n; i++) {
        std::cin >> aux;
        all_exams.push_back(aux);
    }
    
    // Ordenar los datos según tiempo de inicio

    vector<list<info_exam>> solution;

    greedy(all_exams, solution);

    for (int i=0; i < solution.size(); ++i) {
        cout << "Classroom " << i << " : " << endl;
        for (typename list<info_exam>::iterator  it = solution[i].begin(); it != solution[i].end(); ++it) {
            cout << *it << " ";
        }

        cout << endl;
    }

    return 0;

}