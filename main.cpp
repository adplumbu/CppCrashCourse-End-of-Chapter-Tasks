#include <iostream>
#include <sys/time.h>

struct TimerClass{

    TimerClass(){
        gettimeofday(&timestamp, nullptr);//timestamp struct is filled by current time
        //std::cout << "Object born at: " << timestamp.tv_usec << std::endl;
    }

    explicit TimerClass(const char* name) : nameOfObject{name}{
        gettimeofday(&timestamp, nullptr);
        //std::cout << nameOfObject << "- object has been born at: " << timestamp.tv_usec
                  //<< " micro sec" << std::endl;
    }

    //first-copy constructor
    TimerClass(const TimerClass& other){
        this->timestamp = other.timestamp;
        std::cout << "Current object has copied data from: " << other.nameOfObject << std::endl;
    }

    //second-copy constructor
    TimerClass(const TimerClass& other, const char* nameCurrentObj) : nameOfObject{nameCurrentObj}{
        this->timestamp = other.timestamp;
        std::cout << nameCurrentObj << " object has copied data from: " << other.nameOfObject << std::endl;
    }

    //copy assigment method
    TimerClass& operator=(const TimerClass& other) {

        if(this == &other) return *this;
        this->timestamp = other.timestamp;
        std::cout << nameOfObject << "- object has copy the data by assigment from: "
                  << other.nameOfObject << std::endl;
        return *this;
    }

    //move constructor
    TimerClass(TimerClass&& other, const char* nameOfCurrentObject) noexcept
        : timestamp(other.timestamp),
        nameOfObject{nameOfCurrentObject}{

        std::cout << "Data of: " << other.nameOfObject
                  << " has been moved to: " << nameOfCurrentObject << std::endl;

        other.timestamp.tv_usec = 0;
        other.timestamp.tv_sec = 0;

        std::cout << other.nameOfObject << " is now a MOVED-FROM Object" << std::endl;

    }

    ~TimerClass(){
        std::cout << "DESTRUCTION TIME!!!" << std::endl;
        if(timestamp.tv_usec == 0 && timestamp.tv_sec == 0){
            std::cout << nameOfObject << " is a MOVED-FROM Object. Nothing to print about." << std::endl;
        }else{
            gettimeofday(&endtime, nullptr);
            std::cout << nameOfObject << "- time of death: " << endtime.tv_usec
                      << " micro sec" << std::endl;
            std::cout << nameOfObject << "- lived exactly: " << endtime.tv_usec - timestamp.tv_usec
                      << " micro sec" << std::endl;
        }


    }

    void getObjectInfo(){

        std::cout << "Object name: " << nameOfObject << std::endl;
        std::cout << "Object birth time: " << timestamp.tv_usec << " ms" << std::endl;
        //std::cout << "Object time of death: " << endtime.tv_usec << " ms" << std::endl;
        //std::cout << "Object time spent living: " << endtime.tv_usec - timestamp.tv_usec << " ms" << std::endl;
    }

private:
    timeval timestamp{};
    timeval endtime{};
    const char* nameOfObject;

};

int main(){

    TimerClass t1("t1");
    TimerClass t1_copy{t1, "t1_copy"};
    TimerClass t2_assigment("t2_assigment");
    t2_assigment = t1;

    TimerClass t3_move(std::move(t1), "t3_move");

    std::cout <<"----------INFO ABOUT OBJECT LIFE TIME----------" << "\n";

    std::cout << "\n";

    t1.getObjectInfo();

    std::cout << "\n\n";

    t1_copy.getObjectInfo();

    std::cout << "\n\n";

    t2_assigment.getObjectInfo();

    std::cout << "\n\n";

    t3_move.getObjectInfo();

    std::cout << "\n\n";

    std::cout << "----------INFO ABOUT OBJECT LIFE TIME----------" << "\n";

    std::cout << "\n\n";


    return 0 ;

}
