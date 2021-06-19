//CSCE312: Lab-3 Problem-1 Timing Framework

/* ***   README   **** */
/*This file is a framework: i.e. there is no actual code whose execution time will be
measured. You need to populate the appropriate functions with the code that you wrote 
for the previous problems in order to get useful data. 

Turning in this file without your code will result in zero points being awarded for this problem.

run this file as: gcc FileName.c -o ExecutableName -lrt 

*/


#include <stdio.h>
#include <time.h>
// Macro definitions to ensure portablity between both sun.cs and linux.cs

#if defined(sun)
    #define CLOCKNAME CLOCK_HIGHRES
        
#else
    #define CLOCKNAME CLOCK_PROCESS_CPUTIME_ID
#endif
    

inline void read_inputs_from_ip_if(){

	//place your input code here
	//to read the current state of the available sensors
	 //place your input code here
    //to read the current state of the available sensors
	
//set the original sensor bits
	sensor_inputs = 0x3FF; //mask the bits 

}

inline void write_output_to_op_if(){

	//place your output code here
    //to display/print the state of the 3 actuators (DLA/BELL/BA)
	FILE *my_file_pointer;
	if ( (my_file_pointer = fopen("lab1_prob4_out.txt", "w")) == NULL)
	{
		printf("Error opening the file, so exiting\n");
		exit(1);
	}
	
	printf("bell: %d\ndoor_lock_actuator: %d\nbrake_actuator: %d\n", bell, door_lock_actuator, brake_actuator);
	
	fclose(my_file_pointer);

}


//The code segment which implements the decision logic
inline void control_action(){

//3. Put your control/decision logic code segments inside this function
// This is the actual code whose execution time which is being measure
//This code changes throughout depending on the code... 
	/*switch (input & 0x3f) //Change to 0xff for all 5 requirements
	{
		case 5:
		case 7:
		case 13:
			output = 1;
		break;

		case 32:
		case 34:
		case 36:
		case 38:
		case 40:
		case 42:
		case 44:
		case 46:
		case 49:
		case 51:
			output = 2;
		break;

		case 53:
		case 55:
			output = 3;
		break;

		case 57:
		case 59:
			output = 2;
		break;

		case 61:
			output = 3;
		break;

		case 63:
			output = 2;
	
	}*/
	
	//Reset output
	/*output = 0;
	
	//Requirement 1, 2, 3
	switch (input & 0xf)
	{
		case 5:
		case 7:
		case 13:
			output =  0x1;
	}

	//Requirement 4
	switch (input & 0x31)
	{
		case 32:
		case 49:
			output = output | 0x2;
	}

	//Requirement 5
	if ((input & 0xc0) == 0xc0)
			output = output | 0x4;*/


// call an item to see if it is masked or not to determine the bell
    if (driver_on_seat() && doors_closed())
        bell(1);
	else if (engine_running() && driver_seat_belt_fastened()){
		bell(1);
	}
    else bell(0);
	
	//lock requirements
	if(driver_on_seat() && key_in_car(){
		door_lock_actuator(0);
	}
	else if (door_lock_lever() && driver_on_seat(){
		door_lock_actuator(1);
	}
	else door_lock_actuator(0);
	
	//brakes requirements
	if(brake_pedal() && car_moving()){
		brake_actuator(1);
	}
	else brake_actuator(0);
}



/* ---     You should not have to modify anything below this line ---------*/

/*timespec diff from
http://www.guyrutenberg.com/2007/09/22/profiling-code-using-clock_gettime/
*/
struct timespec diff(struct timespec start, struct timespec end)
 {
    struct timespec temp;
    //the if condition handles time stamp end being smaller than than 
    //time stamp start which could lead to negative time.

     if ((end.tv_nsec-start.tv_nsec)<0) {
          temp.tv_sec = end.tv_sec-start.tv_sec-1;
          temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
      } else {
          temp.tv_sec = end.tv_sec-start.tv_sec;
          temp.tv_nsec = end.tv_nsec-start.tv_nsec;
      }
  return temp;
 }

int main(int argc, char *argv[])
{
	unsigned int cpu_mhz;
	unsigned long long int begin_time, end_time;
	struct timespec timeDiff,timeres;
	struct timespec time1, time2, calibrationTime;
	
    clock_gettime(CLOCKNAME, &time1);
	clock_gettime(CLOCKNAME, &time2);
	calibrationTime = diff(time1,time2); //calibration for overhead of the function calls
    clock_getres(CLOCKNAME, &timeres);  // get the clock resolution data
	
    read_inputs_from_ip_if(); // get the sensor inputs
	
	clock_gettime(CLOCKNAME, &time1); // get current time
	control_action();       // process the sensors
	clock_gettime(CLOCKNAME, &time2);   // get current time

	write_output_to_op_if();    // output the values of the actuators
	
	timeDiff = diff(time1,time2); // compute the time difference

	printf("Timer Resolution = %u nanoseconds \n ",timeres.tv_nsec);
	printf("Calibrartion time = %u seconds and %u nanoseconds \n ", calibrationTime.tv_sec, calibrationTime.tv_nsec);
    printf("The measured code took %u seconds and ", timeDiff.tv_sec - calibrationTime.tv_sec);
	printf(" %u nano seconds to run \n", timeDiff.tv_nsec - calibrationTime.tv_nsec);
	
	return 0;
}