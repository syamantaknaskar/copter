#include <simplecpp>

void mainmenu();
void play();
void result(int s); // Takes score as argument
void instructions();
void credits();

int main()
{
	mainmenu();
}

void mainmenu()
{
	// This is a menu where you are supposed to choose any of the  given two options.
	initCanvas("Main Menu", 800,600);
	
	Rectangle R6(400,50,600,50);
	R6.setColor(COLOR("blue"));
	Text (400,50,"!!!      THE COPTER GAME     !!!").imprint();
	
	Rectangle R1(400,200,200,60);  // This invokes the play option
	Text t1(400,200,"PLAY");
	R1.setColor(COLOR("orange"));
	R1.setFill();
	
	Rectangle R2(400,500,200,60);  // This invokes the end game and it closes the windows i.e. Events canvas
	Text t2(400,500,"END");
	R2.setColor(COLOR("orange"));
	R2.setFill();
	
	Rectangle R3(400,300,200,60); // This displays the instructions
	Text t3(400,300,"INSTRUCTIONS");
	R3.setColor(COLOR("orange"));
	R3.setFill();
	
	Rectangle R9(400,400,200,60); // This invokes the credits
	Text t9(400,400,"CREDITS");
	R9.setColor(COLOR("orange"));
	R9.setFill();
	
	int click=getClick();
	int x=click/65536,y=click%65536;   // Getting x-coordinate and y-coordinate of mouse click

	if (abs(x-400.0)<=100 && abs(y-500.0)<=30) {
		closeCanvas();
	} else if (abs(x-400.0)<=100 && abs(y-200.0)<=30) {
		closeCanvas();
		play();
	} else if (abs(x-400.0)<=100 && abs(y-300.0)<=30) {
		closeCanvas();
		instructions();
	} else if (abs(x-400.0)<=100 && abs(y-400.0)<=30) {
		closeCanvas();
		credits();
	} else {
		closeCanvas();
		mainmenu();
	}
}  // End of mainmenu

void play()
{
	// Opens the Copter canvas which starts the copter game
	initCanvas("Copter",800,600);
	
	// Setting the background
	Line bac(0,0,0,600);
	int bacc=0;
	
	beginFrame();
	repeat(800) {
		bacc++;
		bac.setColor(COLOR(255,bacc*0.2,bacc*0.2));
		bac.move(1,0);
		bac.imprint();
	}
	endFrame();
	
	// Setting the canvas with 3 obstacles
	Rectangle r1(810,90,20,80);
	r1.setColor(COLOR("black"));
	r1.setFill(); // Top obstacle
	
	Rectangle r2(810,300,20,80);
	r2.setColor(COLOR("black"));
	r2.setFill(); // Middle obstacle
	
	Rectangle r3(810,510,20,80);
	r3.setColor(COLOR("black"));
	r3.setFill(); // Bottom obstacle
	
	// Setting the top and bottom margins
	Rectangle r4(400,25,800,50); // Border on top of the canvas
	Rectangle r5(400,575,800,50); // Border on bottom of canvas
	r4.setColor(COLOR("green"));
	r4.setFill(); // setting color
	r5.setColor(COLOR("yellow"));
	r5.setFill(); // setting color
	r4.imprint();
	r5.imprint();
	
	int score = 0;
	double r1x=300,r2x=600,r3x=900,r1y=100,r2y=randuv(50.0,550.0),r3y=randuv(50.0,550.0);
	double decrease_factor=0.5;
	int level=0;
	Circle  smoke[5];
	int smx[5],smy[5];
	
	// Array for coordinates of helicopter in two different positions.
	double ycor = 300;
	double a[19][2]={{0,-50},{-30,-45},{-30,-55},{30,-45},{30,-55},{0,-50},{0,-30},{25,-30},{50,0},{25,30},{-25,30},{-50,5},{-80,5},{-90,20},{-90,-20},{-80,-5},{-50,-5},{-25,-30},{0,-30}};
	double b[19][2]={{0,-50},{5,-35},{-5,-35},{5,-65},{-5,-65},{0,-50},{0,-30},{25,-30},{50,0},{25,30},{-25,30},{-50,5},{-80,5},{-90,20},{-90,-20},{-80,-5},{-50,-5},{-25,-30},{0,-30}};
	
	Polygon heli(200,ycor,a,19); // Helicopter is drawn
	srand(time(NULL));

	// smoke is initialized
	for (int loop=0; loop<5; loop++) {
		smx[loop]=20+40*loop;
		smy[loop]=ycor;
		smoke[loop].reset(smx[loop],smy[loop],10);
		smoke[loop].setFill(1);
		smoke[loop].setColor(COLOR("grey"));
	}

	XEvent event;

	while (true) {
		for (int loop=0; loop<5; loop++) {
			smx[loop]--;
			smoke[loop].reset(smx[loop],smy[loop],(180-smx[loop])*(1.0/12.0)+5);

			if (smx[loop]<-10) {
				smx[loop]=180;
				smy[loop]=ycor;
			}
		}

		level++;

		if (level>100) {
			decrease_factor+=0.05;
			level=0;
		}

		r1x-=decrease_factor;
		r2x-=decrease_factor;
		r3x-=decrease_factor;

		if (r1x<=0) {
			r1x=900;
			r1y=randuv(100.0,500.0);
		}

		if (r2x<=0) {
			r2x=900;
			r2y=randuv(100.0,500.0);
		}

		if (r3x<=0) {
			r3x=900;
			r3y=randuv(100.0,500.0);
		}

		beginFrame();
		r1.reset(r1x,r1y,20,100);
		r2.reset(r2x,r2y,20,100);
		r3.reset(r3x,r3y,20,100);
		endFrame();
		
		beginFrame();
		heli.reset(200,ycor,a,19);
		heli.setColor(COLOR(130,0,100));
		heli.setFill();
		endFrame();
		
		usleep(1000);
		
		beginFrame();
		heli.reset(200,ycor,b,19);
		heli.setColor(COLOR(130,0,100));
		heli.setFill();
		endFrame();
		
		score++;
		usleep(1000);
		// Moving the obstacles from right to left in the canvas
		//need some random number from (0,1,2)

		// Setting the motion of the helicopter with input
		if (checkEvent(&event)) { // wait for an event.
			if (keyPressEvent(&event)) {
				char c = charFromEvent(&event);

				if ((int)c == 32)
					ycor = ycor - 20;
				else
					ycor += 0.6;
			}
		} else
			ycor = ycor + 0.6 ;

		//TO CHECK COLLISION

			if (ycor>=520 || ycor<=105 || ((200<r1x+100 && 200>r1x-60) && (ycor<r1y+95 && ycor>r1y-70))||((200<r2x+100 && 200>r2x-60) && (ycor<r2y+95 && ycor>r2y-70)) || ((200<r3x+100 && 200>r3x-60) && (ycor<r3y+95 && ycor>r3y-70))) {
			wait(1);
			closeCanvas();
			result(score); // Sending score of player to result function
		}
	} // end of while
} // end of play

void result(int s)
{
	initCanvas("RESULTS",800,600);
	Text(400,50,"!!!                 BOOM !!!     BOOM  !!!    BOOM  !!!             !!!").imprint();
	Text(400,100,"!!!       THE HELICOPTER COLLIDED       !!!").imprint();
	Text t9(400,200,"Your score is :");
	t9.imprint();
	Text t19(600,200,s);
	t19.imprint();
	
	Rectangle R7(600,500,150,60);
	Text t7(600,500," MAIN MENU ");
	R7.setColor(COLOR("orange"));
	R7.setFill();
	
	Rectangle R8(200,500,150,60);
	Text t8(200,500," QUIT ");
	R8.setColor(COLOR("orange"));
	R8.setFill();
	
	int click=getClick();
	int x=click/65536,y=click%65536;   // Getting x-coordinate and y-coordinate of mouse click

	if (abs(x-200.0)<=50 && abs(y-500.0)<=30) {
		closeCanvas();
	} else if (abs(x-600.0)<=50 && abs(y-500.0)<=30) {
		closeCanvas();
		mainmenu();
	} else {
		closeCanvas();
		result(s);
	}
} // End of result

void instructions()
{
	// Opens the INSTRUCTIONS
	initCanvas("INSTRUCTIONS",800,600);
	Text t4(400,100,"Press space to go up and leave to go down.");
	t4.imprint();
	
	Rectangle R4(400,400,200,60);
	Text t5(400,400,"BACK");
	R4.setColor(COLOR("orange"));
	R4.setFill();
	
	int click=getClick();
	int x=click/65536,y=click%65536;   // Getting x-coordinate and y-coordinate of mouse click

	if (abs(x-400.0)<=100 && abs(y-400.0)<=30) {
		closeCanvas();
		mainmenu();
	} else {
		closeCanvas();
		instructions();
	}
} // end of instructions

void credits()
{
	// Opens the CREDITS
	initCanvas("CREDITS",800,600);
	Text t10(400,200,"1. Ayush Deothia");
	t10.imprint();
	Text t11(400,300,"2. Avinash Malviya");
	t11.imprint();
	Text t12(400,400,"3. Syamantak Naskar");
	t12.imprint();
	
	Rectangle R50(400,500,200,60);
	Text t50(400,500,"BACK");
	R50.setColor(COLOR("orange"));
	R50.setFill();
	
	int click=getClick();
	int x=click/65536,y=click%65536;   // Getting x-coordinate and y-coordinate of mouse click

	if (abs(x-400.0)<=100 && abs(y-500.0)<=30) {
		closeCanvas();
		mainmenu();
	} else {
		closeCanvas();
		credits();
	}
} // End of credits
