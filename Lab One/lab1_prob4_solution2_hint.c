/*
Lab-1, Problem-4, Sample soltion-2
Note: Only requirement 1,2,3,4 is covered 
modify this code to include requirement 5 also

Also add your own INPUT/OUTPUT code to test it.

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

	//Requirement 1, 2, 3, 4 only
	switch (input & 0x3f) //Change to 0xff for all 5 requirements
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
	
	}


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