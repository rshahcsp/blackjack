/*******************************************************************************/
// * CS 103 PR1 Twenty-One (Blackjack) Project
/******************************************************************************/

// Add other #includes if you need
#include <iostream>
#include <cstdlib>
using namespace std;

// Prototypes
void shuffle(int cards[]);
void printCard(int id);
int cardValue(int id);
void printHand(int hand[], int numCards);
int getBestScore(int hand[], int numCards);

const int NUM_CARDS = 52;

/**Global arrays to be used as look-up tables. You */// ♥, ♠, ♦, ♣
const char* suit[4] = {"\U00002665","\U00002660","\U00002666","\U00002663"}; // H, S, D, C
const char* type[13] = 
  {"2","3","4","5","6","7",
   "8","9","10","J","Q","K","A"};
const int value[13] = {2,3,4,5,6,7,8,9,10,10,10,10,11};

// shuffle using Fisher-Yates / Durstenfeld 
void shuffle(int cards[])
{
  for(int i= NUM_CARDS-1; i>0; i--){
    int j = rand() % (i + 1);
    int temp = cards[i];
    cards[i] = cards[j];
    cards[j] = temp;
  }
}

// print card in type-suit format
void printCard(int id)
{
  cout << type[id%13] << suit[id/13];
}

// return numeric value of card 
int cardValue(int id)
{
  int digit = id%13;
  return (value[digit]);
}

// print each card in hand
void printHand(int hand[], int numCards)
{
  for(int i=0; i< numCards; i++){
    printCard(hand[i]);
    cout << " ";
  }
}

// return best score of provided hand, account for aces
int getBestScore(int hand[], int numCards)
{
  int score = 0;
  int numAces = 0;
  for (int i=0; i < numCards; i++){
    int cardVal = cardValue(hand[i]);
    score += cardVal;
    if (cardVal == 11){
      numAces++;
    }
  }
  
  // reduce if score > 21 and aces present
  while (score > 21 && numAces>0){
    score -= 10;
    numAces--;
  }
  return score;
}

// main program
int main(int argc, char* argv[])
{
  //---------------------------------------
  // Do not change this code -- Begin
  //---------------------------------------
  if(argc < 2){
    cout << "Error - Please provide the seed value." << endl;
    return 1;
  }
  int seed = atoi(argv[1]);
  srand(seed);

  int cards[52];
  int dhand[9];
  int phand[9];
  //---------------------------------------
  // Do not change this code -- End
  //---------------------------------------

  char playAgain = 'y';

  // set conditions to keep playing game
  while (playAgain == 'y'){
    for (int i=0; i< NUM_CARDS; i++){
    cards[i] = i;
    }
   
    // declare variables
    int topCard = 0;
    int dNumCards = 2;
    int pNumCards = 2;

    // shuffle cards and set up game
    shuffle(cards);
    for(int i=0; i<2; i++){
      phand[i] = cards[topCard];
      topCard++;
      dhand[i] = cards[topCard];
      topCard++;
    }

    // output initial hands
    cout << "Dealer: ? "; // hide dealer's first card
    printCard(dhand[1]);
    cout << endl;
    cout << "Player: ";
    printHand(phand, pNumCards);
    cout << endl;
  
    // create variables
    char input;
    int pScore = getBestScore(phand, pNumCards);
    int dScore = getBestScore(dhand, dNumCards);

    // start game, set conditions
    while(pNumCards < 9 && pScore != 21){
      cout << "Type 'h' to hit and 's' to stay:" << endl;
      cin >> input;
    
      // check for valid input
      if (input != 'h' && input != 's'){
        return 0;
      }

      // break out if player chooses stay
      if(input == 's'){
        break;
      }

      // update player hand as they hit
      phand[pNumCards] = cards[topCard];
      topCard++;
      pNumCards++;
      pScore = getBestScore(phand, pNumCards);

      // print player hand
      cout << "Player: ";
      printHand(phand, pNumCards);
      cout << endl;

      // check if player bust
      if (pScore > 21){
      cout << "Player busts" << endl;
      cout << "Lose " <<  pScore << " " << dScore << endl;
      break;
      } 
    } 

    // dealer's turn after player stays
    if (pScore <= 21){
      dScore = getBestScore(dhand, dNumCards);
      while (dScore < 17 && dNumCards < 9){
        dhand[dNumCards] = cards[topCard];
        topCard++;
        dNumCards++;
        dScore = getBestScore(dhand, dNumCards);
      }
      cout << "Dealer: ";
      printHand(dhand, dNumCards);
      cout << endl;

      // check dealer bust
      if (dScore > 21){
        cout << "Dealer busts" << endl;
      }
    }

    // determine win/lose/tie outcome of game
    if ((pScore > dScore && pScore <= 21)|| dScore > 21){
      cout << "Win " << pScore << " " << dScore << endl;
    } else if (pScore < dScore){
      cout << "Lose " << pScore << " " << dScore << endl;
    } else if (pScore == dScore){
      cout << "Tie " << pScore << " " << dScore << endl;
    }

    // prompt player to play again
    cout << endl;
    cout << "Play again? [y/n]" << endl;
    cin >> playAgain;

    // check for valid input
    if (playAgain != 'y' && playAgain != 'n'){
      return 0;
    }

  }
  return 0;
}
