#pragma once
class ResultProvider {
    protected:
        int result=-1;
        bool ready=false;
    public:
    int getResult() { return this->result;}
    virtual void setResult(int i) { this->result=i;}
    bool isReady() { return this->ready; }
    void complete() {this->ready=true;}

};