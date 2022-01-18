#include<stdio.h>
/*void display(short board[], char flag){
	printf("___________________________________\n");
	printf("|    |    |    |    |    |    |    |\n");
	printf("|    |    |    |    |    |    |    |\n");
	printf("___________________________________\n");
	printf("|    |    |    |    |    |    |    |\n");
	printf("|    |    |    |    |    |    |    |\n");
	printf("___________________________________\n");
}*/
void display(short board[]){
	printf("\n");
	printf("\n");
	for(short i = 6; i >= 0; i--) printf("%d\t", board[i]);
	printf("\n");
	for(short i = 7; i < 14; i++) printf("%d\t", board[i]);
	printf("\n");
	printf("\n");
	printf("\n");
}
void distribute(short gunta[], short pos, short *score, short turn){
	short j = 1, ginja;
	while(1){
		ginja = gunta[pos];
		gunta[pos] = 0;
		for(; ginja > 0; ginja--, j++){
			gunta[(pos + j) % 14]++;
			if(gunta[(pos + j) % 14] == 4){ if(((pos + j) % 14) / 7 == turn) *(score + turn) += 4; else *(score + !turn) += 4; gunta[(pos + j) % 14] = 0;}
		//	printf("at the pos %d, from the pos %d, remaining %d\n", (pos + j) % 14, (pos) % 14, ginja - 1); 
			//printf("o's score %d, 1's score %d", *score, *(score + 1));
			//display(gunta);	
		}
		if(gunta[(pos + j) % 14] == 0){ *(score + turn) += gunta[(pos + j + 1) % 14]; gunta[(pos + j + 1) % 14] = 0; break;}
		pos = (pos + j) % 14;
		j = 1;
	}
}
short input(short turn){
	short gunta;
	if(scanf("%hd", &gunta))if(gunta < 15 && gunta > 0)if((gunta - 1) / 7 == turn) return gunta;
        return 0;	
}
short monitor(short turn){
	short gunta;
	printf("select a gunta: ");
	while(!(gunta = input(turn))){
		printf("INVALID INPUT.\nselect a gunta: ");
	}
	return gunta - 1;
}
short turn(short mov){return mov % 2;}
short is_over(short turn, short gunta[], short *score){
	for(short i = 0; i < 7; i++){
		if(gunta[7 * turn + i] != 0) return 0;
	}
	for(short i = 0; i < 7; i++) *(score + !turn) += gunta[7 * (!turn) + i];
	return 1;
}
void win(short *score){
	printf("final scores... 0: %d, 1: %d", *score, *(score + 1));
	if(*score > *(score + 1)) printf("0 won..\n");
	else printf("1 won\n");
}
#include"minmax.c"
void game(){
	short gunta[14], in, score[] = {0, 0};
	for(short i = 0; i < 14; i++) gunta[i] = 5;
	//gunta[3] = 1;
	//gunta[8] = 1;
	//gunta[12] = 1;
	for(short mov = 0; !is_over(turn(mov), gunta, score); mov++){
		if(mov % 2 == 0){
			printf("Score of 0 is %d\t\t", score[0]);
			printf("Score of 1 is %d\n", score[1]);
			display(gunta);
			in = monitor(turn(mov));
			distribute(gunta, in, score, turn(mov));
		}
		else{
			display(gunta);
			printf("\n\n\n\n\\n\n\n\n");
			in = minmax(gunta, 0, turn(mov), score);
			if(gunta[in] == 0){printf("glitchy\n"); break;}
			distribute(gunta, in, score, turn(mov));
			printf("%d\n", in);
		}
	}
	win(score);
}
int main(){
	game();
	return 0;
}
