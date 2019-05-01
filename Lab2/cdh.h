#ifndef CDH_H
#define CDH_H

class cdh {
    public:
        string getDay();
        string getHoust();
        void toString() const;
    private:
        string courseName;
        string courseDay;
        string courseHour;
};

#endif