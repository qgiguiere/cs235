#ifndef SNAP_H
#define SNAP_H
class snap {
    public:
        string getName();
        string getAddr();
        string getPhone();
        void toString() const;
    private:
        string studentId;
        string studentName;
        string studentAddress;
        string phoneNumber;
};

#endif