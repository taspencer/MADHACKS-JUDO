#include <stdio.h>
#include <stdlib.h>

typedef struct player{
	
	int computer;
	int grip;
	int x;
	int y;
	int power;
	int tall;
	int dominance;
	int throwVuln;
	int nextThrowVuln;
	int sweepVuln;
	int attack;
	int thrown;
}player;

typedef struct fight{
	
	int round;
	int x;
	int y;
	
}fight;

int done;
int ippon;

int main(){
	player player1;
	player player2;
	fight fight1;
	char choice;
	
	srand ( time(NULL) );
	
	while(!done){
		
		done = 0;
		ippon = 0;
		fight1.round = 1;
		fight1.x = 0;
		fight1.y = 0;
		choice = 0;
		playerSelect(&player1, &player2);
		characterSelect(&player1, &player2);
		
		while(!ippon && fight1.round < 15){
			printf("ROUND %d\n", fight1.round);
			gripfight(&player1, &player2);
			move(&player1, &player2, &fight1);
			attack(&player1, &player2, &fight1);
			//debug(&player1, &player2, &fight1);
			displayResults(&player1, &player2, &fight1);
			fight1.round = fight1.round + 1;
		}
		if(fight1.round == 15){
			printf("TIME OUT\n");
		}

		printf("PLAY AGAIN?\n1. YES\n2. NO\n");
		scanf(" %c", &choice);
		if(choice == 'n'){
			done = 1;
		}
	}
}

int playerSelect(player * player1, player * player2){
	int choice;
	printf("0, 1, OR 2 PLAYERS?\n");
	scanf("%d", &choice);
	
	if(choice == 0){
		player1->computer = 1;
		player2->computer = 1;
	}else if(choice == 1){
		player1->computer = 0;
		player2->computer = 1;
	}else{
		player1->computer = 0;
		player2->computer = 0;
	}
}

int debug(player * player1, player * player2, fight * fight1){

	printf("PLAYER1\n");
	printf("grip: %d\n", player1->grip);
	printf("x: %d\n", player1->x);
	printf("y: %d\n", player1->y);
	printf("power: %d\n", player1->power);
	printf("tall: %d\n", player1->tall);
	printf("dominance: %d\n", player1->dominance);
	printf("sweep vulnerability: %d\n", player1->sweepVuln);
	printf("throw vulnerability: %d\n", player1->throwVuln);
	printf("next throw vulnerability: %d\n", player1->nextThrowVuln);
	printf("thrown: %d\n", player1->thrown);
	
	printf("PLAYER2\n");
	printf("grip: %d\n", player2->grip);
	printf("x: %d\n", player2->x);
	printf("y: %d\n", player2->y);
	printf("power: %d\n", player2->power);
	printf("tall: %d\n", player2->tall);
	printf("dominance: %d\n", player2->dominance);
	printf("sweep vulnerability: %d\n", player2->sweepVuln);
	printf("throw vulnerability: %d\n", player2->throwVuln);
	printf("next throw vulnerability: %d\n", player2->nextThrowVuln);
	printf("thrown: %d\n", player1->thrown);
	
	printf("FIGHT\n");
	printf("round: %d\n", fight1->round);
	printf("x: %d\n", fight1->x);
	printf("y: %d\n", fight1->y);
	
	
}

int displayResults(player * player1, player * player2, fight * fight1){
	
	if(player1->thrown && !player2->thrown){
		printf("IPPON FOR PLAYER 2\n");
		ippon = 1;
	}else if(!player1->thrown && player2->thrown){
		printf("IPPON FOR PLAYER 1\n");
		ippon = 1;
	}else{
	
		switch(player1->nextThrowVuln){
			case 0: break;
			case 1: printf("PLAYER 1 OFF BALANCE\n");
					break;
			case 2: printf("PLAYER 1 IN DANGER\n");
					break;
			default:printf("PLAYER 1 IN GRAVE DANGER\n");
		}
		
		switch(player2->nextThrowVuln){
			case 0: break;
			case 1: printf("PLAYER 2 OFF BALANCE\n");
					break;
			case 2: printf("PLAYER 2 IN DANGER\n");
					break;
			default: printf("PLAYER 2 IN GRAVE DANGER\n");
		}
	}
}

int attack(player * player1, player * player2, fight * fight1){
	
	int power1;
	int power2;
	int p1AddThrowVuln = player1->nextThrowVuln;
	int p2AddThrowVuln = player2->nextThrowVuln;
	
	player1->nextThrowVuln = 0;
	player2->nextThrowVuln = 0;
	
	if(!player1->computer){
		printf("PRESS 1 TO SWEEP, 2 TO THROW, OR 3 TO COUNTER THROW\n");
		scanf("%d", &player1->attack);
		
		
		if(player1->attack != 3){
			if(player1->power != 0){
				printf("PRESS 1 FOR NORMAL ATTACK OR 2 FOR POWER ATTACK\n");
				scanf("%d", &power1);
			}else{
				printf("PLAYER 1 WEAKENED, CANNOT USE POWER ATTACKS\n");
				power1 = 1;
			}
		}else{
			player1->sweepVuln += player1->throwVuln;
			player1->throwVuln = 0;
		}
	}else{
		player1->attack = rand() % 3 + 1;
		if(player1->attack != 3){
			if(player1->power != 0){
				power1 = rand() % 2 + 1;
			}else{
				power1 = 1;
			}
		}else{
			player1->sweepVuln += player1->throwVuln;
			player1->throwVuln = 0;
		}
		printf("COMP1 ATTACK: %d\n", player1->attack);
		if(player1->attack != 3){
			printf("COMP1 POWER: %d\n", power1);
		}
	}
	
	if(!player2->computer){
		printf("PRESS 1 TO SWEEP, 2 TO THROW, OR 3 TO COUNTER THROW\n");
		scanf("%d", &player2->attack);
		
		
		if(player2->attack != 3){
			
			if(player2->power != 0){
				printf("PRESS 1 FOR NORMAL ATTACK OR 2 FOR POWER ATTACK\n");
				scanf("%d", &power2);
			}else{
				printf("PLAYER 1 WEAKENED, CANNOT USE POWER ATTACKS\n");
				power2 = 1;
			}
		}else{
			player2->sweepVuln += player2->throwVuln;
			player2->throwVuln = -4;
		}
	}else{
		player2->attack = rand() % 3 + 1;
		if(player2->attack != 3){
			if(player2->power != 0){
				power2 = rand() % 2 + 1;
			}else{
				power2 = 1;
			}
		}else{
			player2->sweepVuln += player2->throwVuln;
			player2->throwVuln = -4;
		}
		printf("COMP2 ATTACK: %d\n", player2->attack);
		if(player2->attack != 3){
			printf("COMP2 POWER: %d\n", power2);
		}
	}
	
	if(power1 > 2){
		power1 == 2;
	}
	
	if(power2 > 2){
		power2 == 2;
	}
	
	switch(player1->attack){
		
		case 1: 
			if(player2->sweepVuln + power1 > 4){
				player2->thrown = 1;
			}else if(player2->sweepVuln + power1 > 2){
				player2->nextThrowVuln += power1;
			}
			break;
		case 2:
			if(player2->throwVuln + p2AddThrowVuln + power1 > 4){
				player2->thrown = 1;
			}else{
				player1->nextThrowVuln += power2;
			}break;
		default: break;
		
	}
	
	switch(player2->attack){
		
		case 1: 
			if(player1->sweepVuln + power2 > 4){
				player1->thrown = 1;
			}else if(player1->sweepVuln + power2 > 2){
				player1->nextThrowVuln++;
			}
			break;
		case 2:
			if(player1->throwVuln + p1AddThrowVuln + power2 > 4){
				player1->thrown = 1;
			}else{
				player2->nextThrowVuln++;
			}break;
			
		default: break;
		
	}
	player1->power = player1->power - power1 + 1;
	player2->power = player2->power - power2 + 1;
}

int move(player * player1, player * player2, fight * fight1){
	
	char choice1;
	char choice2;
	int compChoice1;
	int compChoice2;
	
	if(!player1->computer){
		printf("PLAYER1: USE WASD TO CHOOSE A DIRECTION\n");
		scanf(" %c", &choice1);
	}else{
		compChoice1 = rand() % 4 + 1;
		switch(compChoice1){
			case 1: choice1 = 'w';
					break;
			case 2: choice1 = 'a';
					break;
			case 3: choice1 = 's';
					break;
			case 4: choice1 = 'd';
					break;
		}
		printf("COMP1 MOVE: %c\n", choice1);
	}
	
	
	
	switch(choice1){
		case 'w': 
				player1->x = 0;
				player1->y = 1;
				break;
		case 'a': 
				player1->x = -1;
				player1->y = 0;
				break;
		case 's': 
				player1->x = 0;
				player1->y = -1;
				break;
		case 'd': 
				player1->x = 1;
				player1->y = 0;
				break;
		default: break;
	}
	
	if(!player2->computer){
		printf("PLAYER2: USE WASD TO CHOOSE A DIRECTION\n");
		scanf(" %c", &choice2);
	}else{
		compChoice2= rand() % 4+ 1;
		switch(compChoice2){
			case 1: choice2 = 'w';
					break;
			case 2: choice2 = 'a';
					break;
			case 3: choice2 = 's';
					break;
			case 4: choice2 = 'd';
					break;
		}
		printf("COMP2 MOVE: %c\n", choice2);
	}
	
	switch(choice2){
		case 'w': 
				player2->x = 0;
				player2->y = 1;
				break;
		case 'a': 
				player2->x = -1;
				player2->y = 0;
				break;
		case 's': 
				player2->x = 0;
				player2->y = -1;
				break;
		case 'd': 
				player2->x = 1;
				player2->y = 0;
				break;
		default: break;
	}
	
	fight1->x = player1->dominance*player1->x + player2->dominance*player2->x;
	fight1->y = player1->dominance*player1->y + player2->dominance*player2->y;
	player1->sweepVuln = (abs(fight1->x*fight1->y) + 1)/player1->dominance;
	player2->sweepVuln = (abs(fight1->x*fight1->y) + 1)/player2->dominance;
	player1->throwVuln = abs(fight1->x - player1->x) + abs(fight1->y - player1->y);
	player2->throwVuln = abs(fight1->x - player2->x) + abs(fight1->y - player2->y);

	
}

int characterSelect(player * player1, player * player2){
	
	
	
	int choice1;
	int choice2;
	
	player1->x = 0;
	player1->y = 0;
	player2->x = 0;
	player2->y = 0;
	player1->dominance = 0;
	player2->dominance = 0;
	player1->throwVuln = 0;
	player2->throwVuln = 0;
	player1->nextThrowVuln = 0;
	player2->nextThrowVuln = 0;
	player1->sweepVuln = 0;
	player2->sweepVuln = 0;
	player1->attack = 0;
	player1->attack = 0;
	player1->thrown = 0;
	player2->thrown = 0;
	
	if(!player1->computer){
		printf("PLAYER1: CHARACTER SELECT\n");
		printf("1 for short and strong\n2 for tall and safe\n");
		
		scanf("%d", &choice1);
	}else{
		choice1 = rand() % 2 + 1;
		printf("COMP1 CHAR: %d\n", choice1);
	}
	switch(choice1){
		
		
		case 1: player1->power = 5;
				player1->tall = 0;
				break;
		case 2: player1->power = 2;
				player1->tall = 1;
				break;
		default: printf("wat");
	}
	
	if(!player2->computer){
		printf("PLAYER2: CHARACTER SELECT\n");
		printf("1 for short and strong\n2 for tall and safe\n");
		
		scanf("%d", &choice2);
	}else{
		choice2 = rand() % 2 + 1;
		printf("COMP2 CHAR: %d\n", choice2);
	}
	
	switch(choice2){
		
		case 1: player2->power = 5;
				player2->tall = 0;
				break;
		case 2: player2->power = 2;
				player2->tall = 1;
				break;
		default: printf("wat");
	}
	return 0;
}

int gripfight(player * player1, player * player2){
	
	if(!player1->computer){
		printf("PLAYER1: choose grip\n");
		printf("1 for HIP\n");
		printf("2 for LAPEL\n");
		printf("3 for COLLAR\n");
		
		scanf("%d", &player1->grip);
	}else{
		player1->grip = rand() % 3 + 1;
		printf("COMP1 GRIP: %d\n", player1->grip);
	}
	
	if(!player2->computer){
		printf("PLAYER2: choose grip\n");
		printf("1 for HIP\n");
		printf("2 for LAPEL\n");
		printf("3 for COLLAR\n");
		
		scanf("%d", &player2->grip);
	}else{
		player2->grip = rand() % 3 + 1;
		printf("COMP2 GRIP: %d\n", player2->grip);
	}
	if(player1->tall == player2->tall){
		
	
		if(player1->grip == player2->grip)
		{
			printf("TIE\n");
			player1->dominance = 1;
			player2->dominance = 1;
			
		}else if(player1->grip == 1 && player2->grip == 3 ||
				player1->grip == 2 && player2->grip == 1 ||
				player1->grip == 3 && player2->grip == 2)
		{
			printf("PLAYER1 ADVANTAGE\n")	;
			player1->dominance = 2;
			player2->dominance = 1;
				
		}else if(player2->grip == 1 && player1->grip == 3 ||
				player2->grip == 2 && player1->grip == 1 ||
				player2->grip == 3 && player1->grip == 2)
		{
			printf("PLAYER2 ADVANTAGE\n")	;
			player1->dominance = 1;
			player2->dominance = 2;
			
		}
	}else if(player1->tall && !player2->tall){
		if(player1->grip == player2->grip)
		{
			printf("PLAYER1 ADVANTAGE\n");
			player1->dominance = 2;
			player2->dominance = 1;
			
		}else if(player1->grip == 1 && player2->grip == 3 ||
				player1->grip == 2 && player2->grip == 1 ||
				player1->grip == 3 && player2->grip == 2)
		{
			printf("PLAYER1 ADVANTAGE\n")	;
			player1->dominance = 2;
			player2->dominance = 1;
				
		}else if(player2->grip == 1 && player1->grip == 3 ||
				player2->grip == 2 && player1->grip == 1 ||
				player2->grip == 3 && player1->grip == 2)
		{
			printf("PLAYER2 ADVANTAGE\n")	;
			player1->dominance = 1;
			player2->dominance = 3;
			
		}
	}else if(!player1->tall && player2->tall){
		if(player1->grip == player2->grip){
			
			printf("PLAYER2 ADVANTAGE\n");
			player1->dominance = 1;
			player2->dominance = 2;
			
		}else if(player1->grip == 1 && player2->grip == 3 ||
				player1->grip == 2 && player2->grip == 1 ||
				player1->grip == 3 && player2->grip == 2)
		{
			printf("PLAYER1 ADVANTAGE\n")	;
			player1->dominance = 3;
			player2->dominance = 1;
				
		}else if(player2->grip == 1 && player1->grip == 3 ||
				player2->grip == 2 && player1->grip == 1 ||
				player2->grip == 3 && player1->grip == 2)
		{
			printf("PLAYER2 ADVANTAGE\n")	;
			player1->dominance = 1;
			player2->dominance = 2;
			
		}
	}
}