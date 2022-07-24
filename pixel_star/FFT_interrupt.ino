int t1 = 0;
int t2 = 0;
int adc_read_counter = 0;

hw_timer_t * timer = NULL; 
volatile uint16_t isrCnt=0;

/*Interrupt routine for Timer overflow event*/
void IRAM_ATTR onTimer() {
   isrCnt++; 
}


void INT_setup(uint16_t samplingrate) {
  timer = timerBegin(0, 80, true);                //Begin timer with 1 MHz frequency (80MHz/80)
  timerAttachInterrupt(timer, &onTimer, true);   //Attach the interrupt to Timer1
  unsigned int timerFactor = 1000000/samplingrate; //Calculate the time interval between two readings, or more accurately, the number of cycles between two readings
  timerAlarmWrite(timer, timerFactor, true);      //Initialize the timer
  timerAlarmEnable(timer); 
}