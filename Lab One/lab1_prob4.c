#include <stdio.h> //This is useful to do i/o to test the code

//bear with me as i try to figuare out data masking ive never done this
//I am bit confused and have spent like 3 days on this.

//two global variables
unsigned int sensor_inputs; // (sensors 8 of theses)
unsigned int actuator_outputs; //(autuators 3 of these bad boys)



/* this just cut cause we need to get the bits and set the bits 
unsigned int driver_on_seat;
unsigned int doors_closed;
unsigned int bell;
unsigned int driver_seat_belt_fastened;
unsigned int engine_running;
unsigned int doors_closed;
unsigned int key_in_car;
unsigned int door_lock_lever;
unsigned int brake_pedal;
unsigned int car_moving;
unsigned int door_lock_actuator;
unsigned int brake_actuator;
*/

// get the bits in order to set the sensors to the right amount of bits 
unsigned int get_ith_bit(unsigned int input, unsigned int i) {
	//sensor value and then we have the store according to the chart
   if((input & (1 << i)) != 0) {
    return 1;
   }  
   return 0; 
}

void read_inputs_from_ip_if(){

    //place your input code here
    //to read the current state of the available sensors
	
//set the original sensor bits
	sensor_inputs = 0x3FF; //mask the bits 

}

//for that to work we need to get the bit 
unsigned int driver_on_seat() {
  return get_ith_bit(sensor_inputs, 0);
}
unsigned int driver_seat_belt_fastened() {
  return get_ith_bit(sensor_inputs, 1);
}
unsigned int engine_running() {
  return get_ith_bit(sensor_inputs, 2);
}
unsigned int doors_closed() {
  return get_ith_bit(sensor_inputs, 3);
}
unsigned int key_in_car() {
  return get_ith_bit(sensor_inputs, 4);
}
unsigned int door_lock_lever(){
  return get_ith_bit(sensor_inputs, 5);
}
unsigned int brake_pedal() {  
  return get_ith_bit(sensor_inputs, 6);
}
unsigned int car_moving() {
  return get_ith_bit(sensor_inputs, 7);
}

//get the bit and by putting it in a function it allows the same address but also gives a clean code by not tying it a bunch
 
//set the bit to 1 or 0 for the high or low //in its given location
//seting allows us to have the authonicators in the correct positions 
void set_ith_bit(unsigned int &input, unsigned int i, unsigned int set) {
  if (set) { 
    input = input | (1 << n);
  }
  else {
    input = input & ~(1 << n);
  }
}

unsigned int bell(unsigned int set) {
  set_ith_bit(actuator_outputs, 0, set);
}
unsigned int door_lock_actuator(unsigned int set) {
  set_ith_bit(actuator_outputs, 1, set);
}
unsigned int brake_actuator(unsigned int set) {
  set_ith_bit(actuator_outputs, 2, set);
}

//also want to get the bits for the final readings

unsigned int bell() {
  return get_ith_bit(actuator_outputs, 0);
}
unsigned int door_lock_actuator() {
  return get_ith_bit(actuator_outputs, 1);
}
unsigned int brake_actuator() {
  return get_ith_bit(actuator_outputs, 2);
}

void write_output_to_op_if(){

    //place your output code here
    //to display/print the state of the 3 actuators (DLA/BELL/BA)
	//stays the same
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
void control_action(){

    /*
       The code given here sounds the bell when driver is on seat
       AND hasn't closed the doors. (Requirement-2)
       Replace this code segment with your own code to do problems 3 and 4.
       */
//bell requirements

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

int main(int argc, char *argv[])
{

    /*The main control loop which keeps the system alive and responsive for ever,
      until the system is powered off */
    for (; ; )
    {
        read_inputs_from_ip_if();
        control_action();
        write_output_to_op_if();

    }

    return 0;
}