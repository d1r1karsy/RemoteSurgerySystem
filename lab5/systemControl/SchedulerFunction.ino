#include "dataStructs.h"                                                  //import the variables
#include "SchedulerFunction.h"                                            //import the header of this function

#ifndef SchedulerFunction                                                 //check to see if variables are defined elsewhere
#define SchedulerFunction                                                 //assigns definiton to dataStructs

void schedulerFunctionAdd(MyTCB* TCBPtr, void* list){                     //Function takes in a TCB pointer and a void pointer
    struct LinkedList* newList = (struct LinkedList*) list;                 //the void pointer is dereferenced into a linkedlist pointer
    TCBPtr->next = newList->placeholder->next;                              //the TCB pointer's next TCB is now the placeholder's next
    TCBPtr->prev = newList->placeholder;                                    //the TCB's pointer prev TCB is now the placeholder
    newList->placeholder->next = TCBPtr;                                    //the placeholder's next pointer TCB is now the TCBPtr
    newList->placeholder->next->prev = TCBPtr;                              //the placeholder's next TCB's prev pointer TCB is now the TCBPtr
    newList->size++;                                                        //increment size by 1
}

int schedulerContains(MyTCB* TCBPtr, LinkedList* newList){
    MyTCB* cur = newList->front;

    for (int i = 0; i < newList->size; i++){
        //Serial.print(cur->TCBname);
        if (cur->TCBname == TCBPtr->TCBname){
            //Serial.print(cur->TCBname);
            //Serial.print(" is equal to ");
            //Serial.println(TCBPtr->TCBname);
            return 1;
        }
        cur = cur->next;
    }
    //Serial.println("");
    return 0;
}

void schedulerFunctionDelete(MyTCB* TCBPtr, void* list){                  //the function takes in a TCB pointer and a void pointer
    struct LinkedList* newList = (struct LinkedList*) list;                 //the void pointer is dereferenced into a linkedlist pointer
    MyTCB* cur = newList->front;                                            //a MyTCB pointer is created pointing at the front of the newList
    for (int i = 0; i < newList->size; i++){                                //a for loop that runs for the size of the newList
        if (cur->TCBname == TCBPtr->TCBname){                                                   //if the MyTCB pointer cur is the same as the TCBPtr                                      //the prev TCB's prev pointer points to the cur's prev pointer
            cur->next = cur->next->next;
            newList->size--;
            return;                                                              //the code ends
        }
        cur = cur->next;                                                      //cur is not cur.next
    }
}

void schedulerFunctionRun(void* list){                                    //function takes in a void pointer
    struct LinkedList* newList = (struct LinkedList*) list;                 //the void pointer is dereferenced into a linkedlist pointer
    (*newList->placeholder->timedActionPtr).check();                        //the check method is run on the timedActionPtr of the MyTCB
    MyTCB* cur = newList->placeholder;                                      //the MyTCB pointer cur is now pointing to the placeholder
    //Serial.print(runCompute);
    //Serial.println(" is Compute");
    //int output = schedulerContains(&computeT, newList);
    //Serial.print(output);
    //Serial.println(" is scheduler");
    if (runCompute && schedulerContains(&computeT, newList) == 0) {                                                       //if compute needs to be run
        schedulerFunctionAdd(&computeT, &scheduler);                        //add compute to task queue
        //Serial.println("added compute");
    } else if (schedulerContains(&computeT, newList) == 1) {
        schedulerFunctionDelete(&measureT, &scheduler);                     //delete compute to task queue
        //Serial.println("deleted compute");
    }
    if (runEKGProcess && schedulerContains(&EKGProcessT, newList) == 0){
      schedulerFunctionAdd(&EKGProcessT, &scheduler);
      schedulerContains(&EKGProcessT, newList);
      //Serial.println("EKGProcessT has been added");
      //Serial.println(EKGProcessT.TCBname);
    } else if (schedulerContains(&EKGProcessT, newList) == 1){
      //Serial.println("EKGProcessT has been deleted");
      schedulerFunctionDelete(&EKGMeasureT, &scheduler);
    }
    // if (trafficSwitch) {
    //   schedulerFunctionAdd(&trafficT, &scheduler);
    // } else {
    //   schedulerFunctionDelete(trafficT.prev, &scheduler);
    // }
    newList->placeholder = newList->placeholder->next;                      //placeholder is now equal to placeholder.next
}

#endif
