//our old code below. this pretty much just switches to mode 2 so we can run the code below:
void quadtwo(){
	if (mode == 1){
		int sum = 0;
		for (int element = 0; element < 320; element++){
			sum = sum + whi[element];
		}
		if (sum > 300){ //all white
			mode = 2;
			return;
		}
	}
}

//quadrant 3 code below!



//scans the left part of the image. returns a value based on how much white is in that column
int scanLeft(){
	int leftPixels[240];
	for (int i=0; i<240; i++){
		leftPixels[i] = 0;
		int pixLeft = get_pixel(i, 40, 3);
		if (pixLeft > threshold){
			leftPixels[i] = 1;
		}
	}
	int sum = 0;
	for (int j=0; j < 240; j++){
		sum = sum + leftPixels[j];
	}
	return sum;
}

//scans the right part of the image. returns a value based on how much white is in that column
int scanRight(){
	int rightPixels[240];
	for (int i=0; i<240; i++){
		rightPixels[i] = 0;
		int pixRight = get_pixel(i, 280, 3);
		if (pixRight > threshold){
			rightPixels[i] = 1;
		}
	}
	int sum = 0;
	for (int j=0; j < 240; j++){
		sum = sum + rightPixels[j];
	}
	return sum;
}





void mainQuadThree(){
	if (scanLeft > 20){ //found some white on left side
		//turn left
	}
	else { //found no white
		if (scanRight > 20){ //found some swhite on right side
			//turn right
		}
		else {
			//turn around (do180)
		}
	}
	
}


