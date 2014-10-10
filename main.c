#include "main.h"

void task_a(void);
void task_b(void);
void leds(void);

OS_STK taskA_stk[128];  /*!< define "taskA" task stack */
OS_STK taskB_stk[128];  /*!< define "taskB" task stack */
OS_STK led_stk [128];  /*!< define "led" task stack */

OS_FlagID a_flag,b_flag;

OS_EventID mbox0;

int main(void)
{
	PLLInit();

	CoInitOS();
	CoCreateTask (task_a,0,0,&taskA_stk[128-1],128);
	CoCreateTask (task_b,0,1,&taskB_stk[128-1],128);
	CoCreateTask (leds ,0,2,&led_stk[128-1] ,128);

	CoStartOS();



	for(;;);
}


void task_a(void){
	a_flag = CoCreateFlag (Co_TRUE,0);

	for(;;){
		CoWaitForSingleFlag (a_flag,0);
		CoPostMail(mbox0,'A');
		CoTickDelay(20);
	}


}

void task_b(void){
	b_flag = CoCreateFlag (Co_TRUE,0);

	for(;;){
		CoWaitForSingleFlag (b_flag,0);
		CoPostMail(mbox0,'B');
		CoTickDelay(20);
	}
}

void leds(void){
	void* pmail;
	StatusType err;

	mbox0 = CoCreateMbox(EVENT_SORT_TYPE_PRIO); //Sort by preemptive priority

	for(;;){
		pmail = CoPendMail(mbox0,1,&err);
		char data = (char)pmail;

		if (data == 'A'){
			CoSetFlag(b_flag);
		}else {
			CoSetFlag(a_flag);
		}

	}


}
