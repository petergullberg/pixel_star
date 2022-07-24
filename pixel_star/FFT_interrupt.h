#ifndef INTERRUPT_H_
#define INTERRUPT_H_

extern volatile uint16_t isrCnt;
void INT_setup(uint16_t samplingrate);

#endif // INTERRUPT_H_