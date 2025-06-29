#ifndef SIGIO_H
#define SIGIO_H

class SigIO {
    public:
        SigIO();
        void io_process();
        void digital();
        void analog();
        float v_in;  // Make v_in public
    
    private:
        
        int buttonState1 = 0;
        int buttonState2 = 0;
        int potValue = 0;

        unsigned long ADIO_pre_Millis = 0;
        const long ADIO_Interval = 500; // 1 second interval
};

#endif 