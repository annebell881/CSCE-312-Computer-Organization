/*
Sample Solution-1 for Lab-1, Problem-4
Add your own INPUT/OUTPUT code to test it.
*/

unsigned int input;  

unsigned int output;  



//For input interface implementation
inline void read_inputs_from_ip_if(){

		/* write your own input code */
		 //place your input code here
    //to read the current state of the available sensors
	
//set the original sensor bits
	input = 0x3FF; //mask the bits 


}

//For output interface implementation
inline void write_output_to_op_if(){

		/* write your own output code */
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

	//Reset output
	output = 0;
	
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
			output = output | 0x4;

}


//The main program
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