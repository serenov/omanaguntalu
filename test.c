short conclusion(short turn, short gunta[], short *score){
        for(short i = 0; i < 7; i++){
                if(gunta[7 * turn + i] != 0){
			for(short i = 0; i < 7; i++){
				if(gunta[7 * (!turn) + i] != 0) return 0;
			}	
			turn = !turn;
			break;
		}
        }
        for(short i = 0; i < 7; i++) *(score + !turn) += gunta[7 * (!turn) + i];
	if(*score > *(score + 1)) return 1;
	if(*score == *(score + 1)) return 2;
        return -1;
}
short t(short turn){ if (turn == 0) return 1; return -1;}
short minmax(short gunta[], int long depth, short turn, short *score){
	if(depth > 1){
		if(*score > *(score + 1)) return 1;
		if(*score == *(score + 1)) return 0;
		return -1;
	}
	short tgunta[14], r = -100 * t(turn), rtemp, conclude, tscore[] = {*score, *(score + 1)};
	for(short i = 0; i < 14; i++) tgunta[i] = gunta[i];
	if(conclude = conclusion(turn, tgunta, score)){
		if(conclude == 2) return 0;
		return conclude;
	}
	for(short i = 0; i < 7; i++){
		if(tgunta[7 * turn + i] != 0){
			distribute(tgunta, 7 * turn + i, tscore, turn);
			printf("At the depth: %ld, score: %hd %hd, pos: %hd, turn %d", depth, *tscore, *(tscore + 1), 7 * turn + i, turn);
			display(tgunta);
			rtemp = minmax(tgunta, depth + 1,  !turn, tscore);
			if(rtemp * t(turn) > r * t(turn)){
				if(depth == 0) r = 7 * turn + i;
				else r = rtemp;
			}
			for(short i = 0; i < 14; i++) tgunta[i] = gunta[i];
			tscore[0] = *score; 
			tscore[1] = *(score + 1);
		}
	}	
	return r;
}
