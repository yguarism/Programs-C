int switchOn(unsigned int lightNumber, unsigned char &lights){
	if(lightNumber > 7){ // MAX Number of chars in lights is 8 (one byte)
		return -1; 
	}

	lights = lights | (1 << light number);
	return 0;
}

int switchOff (unsigned int lightNumber, unsigned char &lights){
	if(lightNumber > 7){
		return -1;
	}
	lights = lights & ~(1 << lightNumber);
	return 0;
}

int flipLight (unsigned int lightNumber, unsigned char &lights){
	
	lights ^= (1<< lightNumber);
	return 0;
}