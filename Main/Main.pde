Thing mario, hundred;
Animate mario_a, hundred_a;
int feels;


void setup() {
  size(800, 600);

  // LOAD IMAGE THINGS
  mario = new Thing("./res/Mario-Kart8.png");
  hundred = new Thing("./res/100.png");


  // SET IMAGE THING PROPERTIES
  mario.resize(0.15, 0.15);
  hundred.resize(0.15, 0.15);


  // CONFIGURE ANIMATIONS
  mario_a = new Animate(mario);
  hundred_a = new Animate(hundred);
  
  
  // SETUP VARIABLES
  // feels = 5;
  feels = 10;  // DEBUG: Working through feels
}


/**
 * Display 10/10 Rating State
 */
void display10() {
  // DRAW IMAGES
  mario_a.update();
  hundred_a.update();

  

}

/**
 * Display the Rating XX/10
 */
void displayFeelsRating() {
  // DRAW FEELS VALUE
  fill(255);
  textSize(40);
  text("Rating: " + feels, (width/2) - 95, height/2);
}

/** 
 * Handle/Display Background based on State
 */
void displayBackground() {
  switch (feels) {
    case 1:         // DANGER!!
      background(139, 0, 0);
      break;

    case 2:         // SEMI-DANGER!
      background(178, 34, 34);
      break;

    case 3:         // BIT-DANGER
      background(220, 20, 60);
      break;
    
    case 4:         // NOT ALRIGHT
      background(220, 20, 60);
      break;
    
    case 5:         // OK?
      background(255, 69, 0);
      break;

    case 6:         // ALRIGHT
      background(255, 165, 0);
      break;

    case 7:         // MEH
      background(255, 0, 255);
      break;

    case 8:         // GOOD
      background(0, 191, 255);
      break;

    case 9:         // VERY GOOD!
      background(0, 255, 0);
      break;

    case 10:        // AMAZING!!!!
      background(0, 255, 255);
      break;

    default:
      background(0);
    break;	
  }
}


void draw() {
  // DEBUG: Cycle Through FEELS
  // if(frameCount % 50 == 0) {
  //   feels = (feels % 10) + 1;
  // }
  
  
  // BACKGROUND STATE
  displayBackground();

  // FEELS STATE
  display10();

  // RATING
  displayFeelsRating();
}
