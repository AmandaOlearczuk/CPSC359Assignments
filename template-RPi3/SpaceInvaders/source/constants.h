/** Global vars/Constants declarations
 */
#define START_POS_BACKGROUND_x 0
#define START_POS_BACKGROUND_y 0

#define END_POS_BACKGROUND_x 500
#define END_POS_BACKGROUND_y 500

#define START_POS_SHIP_x 235 // (((backgroundWidth/2)- (shipwidth/2)))
#define START_POS_SHIP_y 460 // (((backgroundWidth/2)- (shipwidth/2))) + shipWidth

#define PAWN_START_POS_y 250
#define PAWN_1_START_POS_x 80
#define PAWN_2_START_POS_x 115
#define PAWN_3_START_POS_x 150
#define PAWN_4_START_POS_x 185
#define PAWN_5_START_POS_x 220
#define PAWN_6_START_POS_x 255
#define PAWN_7_START_POS_x 290
#define PAWN_8_START_POS_x 325
#define PAWN_9_START_POS_x 360
#define PAWN_10_START_POS_x 395

#define KNIGHT_START_POS_y 210
#define KNIGHT1_START_POS_x 110
#define KNIGHT2_START_POS_x 175
#define KNIGHT3_START_POS_x 233
#define KNIGHT4_START_POS_x 295
#define KNIGHT5_START_POS_x 355

#define QUEEN_START_POS_x 211
#define QUEEN1_START_POS_y 50
#define QUEEN2_START_POS_y 120

#define BRICK_START_POS_y 400
#define BRICK1_START_POS_x 80
#define BRICK2_START_POS_x 220
#define BRICK3_START_POS_x 360

#define HEART_START_POS_y 3

#define HEART1_START_POS_x 380
#define HEART2_START_POS_x 420
#define HEART3_START_POS_x 460


//The speeds are just a STEP # for example move by 1 pixel or by 5pixels
#define monstersMoveSpeed 6
#define bulletMoveSpeed 1
#define playerMoveSpeed 10

//The delays indicate how long to wait before next move will happen eg. wait 1second for bullet to move 1 milisecond up
#define playerBulletDelay 6
#define monstersBulletDelay 10
#define bulletFrequencyDelay 1000 //How much time between one bullet from any monster, and the next
