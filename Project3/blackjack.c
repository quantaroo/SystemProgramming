/*
   CENG 231 Assignment 2 Part 2
   Blackjack
   author: Jaccob Mau
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*function to denote value for cards*/
int valuefunct(int c){
        int value;
	if(c==1){
	        value = 11;
	}
        else if(c==2){ 
                value = 2;
	}
        else if(c==3){ 
                value = 3;
	}
	else if(c==4){ 
                value = 4;
	}
	else if(c==5){ 
                value = 5;
	}
	else if(c==6){ 
                value = 6;
	}
	else if(c==7){ 
                value = 7;
	}
	else if(c==8){ 
                value = 8;
	}
	else if(c==9){ 
                value = 9;
	}
	else{ 
                value = 10;
	}
        return value;
}

int main(){
    /* initialize the random number generator with the current time */
    srand((unsigned) time(NULL));
    /*Variables*/
    int runPlayer,runDealer,player, card, pCount, dCount, decide, count, val, choice;
    /*Initial Values for boolean while and if statemenets*/
    player = 0;
    runPlayer = 0;
    runDealer = 0;
    count = 0;
    pCount= 0;

    printf("*********************************\n");
    printf("**Welcome to CENG 231 BlackJack**\n");
    printf("*********************************\n");

    /*Player round*/
    while(runPlayer==0){
      /*First round*/
        if(count==0){
            
	  /*Initiate card*/
            card = rand() % 13 +1;
            printf("Your first card is : %d\n", card);
            val = valuefunct(card);
	    if(val == 11){
	       printf("You got an Ace!\nEnter 0 for 1\n OR Enter 1 for 11 : \n");
                  scanf("%d", &choice);
                if(choice == 0){
                    val = 1;
                }
                else{
                    val = 11;
                }
	    }
	    pCount = val;
	    
            /*Give option to continue playing*/
            printf("Do you want another card?\n");
            printf("Type 1 for Yes, 0 for No:\n");
            scanf("%d", &decide);
            if(decide==0){
                runPlayer=1;
            }
            else{
                count=1;
            }
            
        }
        
        /*Not first round*/
        else{
	  /*Check if player has lost*/
            if(player==0){

	      /*Initiate card*/
                card = rand() % 13 +1;
                printf("Your next card is : %d\n", card);
                val = valuefunct(card);
		if(val == 11){
		  printf("You got an Ace!\nEnter 0 for 1\n OR Enter 1 for 11 : \n");
                  scanf("%d", &choice);
		  if(choice == 0){
                    val = 1;
		  }
		  else{
                    val = 11;
		  }
		}
		printf("value : %d\n", val);
		pCount = pCount + val;
		printf("value : %d\n", pCount);
                printf("Your combined value is:%d\n", pCount);

                /*Check if pCount is above 21*/
                if(pCount<=21){
		  /*Give option to continue playing*/
                    printf("Do you want another card?\n");
                    printf("Type 1 for Yes, 0 for No:\n");
                    scanf("%d", &decide);
                    if(decide==0){
                      runPlayer=1;
                    }
                }
                else{
                    player=1;
                }
            }
            else{
                printf("Sorry. You lose!\n");
                runDealer = 1;
		runPlayer=1;
            }
        }
    }


    /*Dealer round*/
    while(runDealer==0){
      /*Initial Dealer*/
        printf("Dealer draws another card.\n");
        card = rand() % 13 +1;
        printf("Dealer's card is: %d\n", card);

        /*Card Value*/
        if(card<10){
            val = card;
        }
        else{
            val = 10;
        }
        dCount += val;

        /*Check if conditions have been met*/
        printf("Dealer's value is %d, you have %d\n", dCount, pCount);
        if((pCount<=dCount)&&(dCount<=21)){
            printf("Sorry. You lose!\n");
            runDealer =1; 
        }
        if(dCount>21){
            printf("Dealer loses. You win!\n");
            runDealer =1;
        }
    }
    return 0;
}
