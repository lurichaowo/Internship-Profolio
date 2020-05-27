import { Injectable } from '@angular/core';
import { Player } from './player';
import { Block } from './Block';

@Injectable({
  providedIn: 'root'
})

export class GameService {
  players = []
  turn: number = 0; // default frist player turn is first 
  draw: number = 0;

  blocks = []; // where the symbols go
  freeBlocksRemaining = 9; //empty blocks left

  constructor() { 
    this.initBlocks(); // initialize blocks
    this.initPlayers(); // initialize players
  }

  initBlocks() {
    this.blocks = [];
    for (var i = 1; i <= 9; ++i){
      var block = new Block(); // create 9 blocks

      // set block values to vanilla
      block.free = true;
      block.value = "";
      block.symbol = "";

      this.blocks.push(block);
    }
  }

  initPlayers() {
    // Player 1
    var p1 = new Player();
    p1.bot = false; //human player

    // bot 
    var p2 = new Player();

    this.players.push(p1);
    this.players.push(p2);
  }

  changeTurn() {
    // 0 = player | 1 = bot 
    // switch btwn them if not the other
    if (this.turn == 1){ 
      this.turn = 0;
    }
    else {
      this.turn = 1;
    }
    return this.turn;
  }

  blockSetComplete() {
    //setting block vars
    var b1 = this.blocks[0];
    var b2 = this.blocks[1];
    var b3 = this.blocks[2];

    var b4 = this.blocks[3];
    var b5 = this.blocks[4];
    var b6 = this.blocks[5];

    var b7 = this.blocks[6];
    var b8 = this.blocks[7];
    var b9 = this.blocks[8];
    
    if (
      (b1.free == false && b2.free == false && b3.free == false && (b1.value == b2.value) && (b1.value == b3.value))||
      (b4.free == false && b5.free == false && b6.free == false && (b4.value == b5.value) && (b4.value == b6.value))||
      (b7.free == false && b8.free == false && b9.free == false && (b7.value == b8.value) && (b7.value == b9.value))||
      (b1.free == false && b4.free == false && b7.free == false && (b1.value == b4.value) && (b1.value == b7.value))||
      (b2.free == false && b5.free == false && b8.free == false && (b2.value == b5.value) && (b2.value == b8.value))||
      (b3.free == false && b6.free == false && b9.free == false && (b3.value == b6.value) && (b3.value == b9.value))||
      (b1.free == false && b5.free == false && b9.free == false && (b1.value == b5.value) && (b1.value == b9.value))||
      (b3.free == false && b5.free == false && b7.free == false && (b3.value == b5.value) && (b3.value == b7.value))) {
        return true; // if matches 3 in row win
      }
      return false; // else not win
    }

  figureBotMove() { // ai to move bot
    // Prioritize by checking set that can complete
    var bot_move = this.GetCompletingSet();  

    if (bot_move > 0){
      return bot_move;
    }

    //2nd priority block enemy from completing set 
    var bot_move = this.blockEnemyAttemptCompleteSet();

    if ( bot_move > 0){
      return bot_move;
    }

    // else return random block
    return Math.floor(Math.random() * 8) + 1;
  }

  GetCompletingSet(){ // return block to complete the set
    var b1 = this.blocks[0];
    var b2 = this.blocks[1];
    var b3 = this.blocks[2];

    var b4 = this.blocks[3];
    var b5 = this.blocks[4];
    var b6 = this.blocks[5];

    var b7 = this.blocks[6];
    var b8 = this.blocks[7];
    var b9 = this.blocks[8];
      
    //b1 
    if (b1.free == false && b1.value == 'cross'){
        if (b2.free == true && b3.free == false && (b1.value == b3.value)){
          return 2; // row 1 w/ 2 free
        }
        else if (b2.free == false && b3.free == true && (b1.value == b2.value)){
          return 3; // row 1 w/ 3 free
        }
        else if (b4.free == true && b7.free == false && (b1.value == b7.value)){
          return 4; // col 1 w/ 4 free
        }
        else if (b4.free == false && b7.free == true && (b1.value == b4.value)){
          return 7; // col 1 w/ 7 free
        }
        else if (b5.free == true && b9.free == false && (b1.value == b9.value)){
          return 5; // diag 1 w/ 5 free
        }
        else if (b5.free == false && b9.free == true && (b1.value == b5.value)){
          return 9; // daig 1 w/ 9 free
        }
    }

    // b2
    else if (b2.free == false && b2.value == 'cross'){
        if (b1.free == true && b3.free == false && (b2.value == b3.value)){
          return 1; // row 1 w/ 2 free
        }
        else if (b5.free == true && b8.free == false && (b2.value == b8.value)){
          return 5; // col 2 w/ 5 free
        }
        else if (b5.free == false && b8.free == true && (b2.value == b5.value)){
          return 8; // col 2 w/ 8 free
        }
    }

    //b3
    else if (b3.free == false && b3.value == 'cross'){
        if (b6.free == true && b9.free == false && (b3.value == b9.value)){
          return 6; // col 3 w/ 6 free
        }
        else if (b6.free == false && b9.free == true && (b3.value == b6.value)){
          return 9; // col 3 w/ 9 free
        }
        else if (b5.free == true && b7.free == false && (b3.value == b7.value)){
          return 5; // diag 2 w/ 5 free
        }
        else if (b5.free == false && b7.free == true && (b3.value == b5.value)){
          return 7; // daig 2 w/ 7 free
        }
    }

    //b4
    else if (b4.free == false && b4.value == 'cross'){
        if (b1.free == true && b7.free == false && (b4.value == b7.value)){
          return 1; // col 1 w/ 1 free
        }
        else if (b5.free == false && b6.free == true && (b5.value == b4.value)){
          return 6; // row 2 w/ 6 free
        }
        else if (b5.free == true && b6.free == false && (b4.value == b6.value)){
          return 5; // col 2 w/ 5 free
        }
    }

    //b5
    else if (b5.free == false && b5.value == 'cross'){
        if (b1.free == true && b9.free == false && (b5.value == b9.value)){
          return 1; // diag 1 w/ 1 free
        }
        else if (b7.free == false && b3.free == true && (b5.value == b7.value)){
          return 3; // diag 2 w/ 3 free
        }
        else if (b2.free == true && b8.free == false && (b5.value == b8.value)){
          return 2; // col 2 w/ 2 free
        }
        else if (b6.free == false && b4.free == true && (b5.value == b6.value)){
          return 4; // row 2 w/ 4 free
        }
    }

    //b6
    else if (b6.free == false && b6.value == 'cross'){
        if (b3.free == true && b9.free == false && (b6.value == b9.value)){
          return 3; // col 3 w/ 3 free
        }
    }

    //b7
    else if (b7.free == false && b7.value == 'cross'){
        if (b8.free == true && b9.free == false && (b7.value == b9.value)){
          return 8; // row 3 w/ 8 free
        }
        else if (b8.free == false && b9.free == true && (b7.value == b8.value)){
          return 9; // row 3 w/ 9 free
      }

      //b8
      if (b8.free == false && b8.value == 'cross'){
        if (b7.free == true && b9.free == false && (b8.value == b9.value)){
          return 7; // row 3 w/ 7 free
        }
      }
    }

    //b8
    else if (b8.free == false){
        if (b7.free == true && b9.free == false && (b8.value == b9.value)){
          return 7; // row 3 w/ 7 free
        }
    }

    else {
      return 0;
    }
  }

  blockEnemyAttemptCompleteSet(){ // bot will block player from winning
                                  // basically almost the same as get completing set
    var b1 = this.blocks[0];
    var b2 = this.blocks[1];
    var b3 = this.blocks[2];

    var b4 = this.blocks[3];
    var b5 = this.blocks[4];
    var b6 = this.blocks[5];

    var b7 = this.blocks[6];
    var b8 = this.blocks[7];
    var b9 = this.blocks[8];

    //b1 
    if (b1.free == false){
            if (b2.free == true && b3.free == false && (b1.value == b3.value)){
              return 2; // row 1 w/ 2 free
            }
            else if (b2.free == false && b3.free == true && (b1.value == b2.value)){
              return 3; // row 1 w/ 3 free
            }
            else if (b4.free == true && b7.free == false && (b1.value == b7.value)){
              return 4; // col 1 w/ 4 free
            }
            else if (b4.free == false && b7.free == true && (b1.value == b4.value)){
              return 7; // col 1 w/ 7 free
            }
            else if (b5.free == true && b9.free == false && (b1.value == b9.value)){
              return 5; // diag 1 w/ 5 free
            }
            else if (b5.free == false && b9.free == true && (b1.value == b5.value)){
              return 9; // daig 1 w/ 9 free
            }
    }
    
    // b2
    else if (b2.free == false){
            if (b1.free == true && b3.free == false && (b2.value == b3.value)){
              return 1; // row 1 w/ 2 free
            }
            else if (b5.free == true && b8.free == false && (b2.value == b8.value)){
              return 5; // col 2 w/ 5 free
            }
            else if (b5.free == false && b8.free == true && (b2.value == b5.value)){
              return 8; // col 2 w/ 8 free
            }
    }
    
    //b3
    else if (b3.free == false){
            if (b6.free == true && b9.free == false && (b3.value == b9.value)){
              return 6; // col 3 w/ 6 free
            }
            else if (b6.free == false && b9.free == true && (b3.value == b6.value)){
              return 9; // col 3 w/ 9 free
            }
            else if (b5.free == true && b7.free == false && (b3.value == b7.value)){
              return 5; // diag 2 w/ 5 free
            }
            else if (b5.free == false && b7.free == true && (b3.value == b5.value)){
              return 7; // daig 2 w/ 7 free
            }
    }
    
    //b4
    else if (b4.free == false){
            if (b1.free == true && b7.free == false && (b4.value == b7.value)){
              return 1; // col 1 w/ 1 free
            }
            else if (b5.free == false && b6.free == true && (b5.value == b4.value)){
              return 6; // row 2 w/ 6 free
            }
            else if (b5.free == true && b6.free == false && (b4.value == b6.value)){
              return 5; // col 2 w/ 5 free
            }
    }
    
    //b5
    else if (b5.free == false){
            if (b1.free == true && b9.free == false && (b5.value == b9.value)){
              return 1; // diag 1 w/ 1 free
            }
            else if (b7.free == false && b3.free == true && (b5.value == b7.value)){
              return 3; // diag 2 w/ 3 free
            }
            else if (b2.free == true && b8.free == false && (b5.value == b8.value)){
              return 2; // col 2 w/ 2 free
            }
            else if (b6.free == false && b4.free == true && (b5.value == b6.value)){
              return 4; // row 2 w/ 4 free
            }
    }
    
    //b6
    else if (b6.free == false){
            if (b3.free == true && b9.free == false && (b6.value == b9.value)){
              return 3; // col 3 w/ 3 free
            }
    }
    
    //b7
    else if (b7.free == false){
            if (b8.free == true && b9.free == false && (b7.value == b9.value)){
              return 8; // row 3 w/ 8 free
            }
            else if (b8.free == false && b9.free == true && (b7.value == b8.value)){
              return 9; // row 3 w/ 9 free
          }
    }
    
    //b8
    else if (b8.free == false){
      if (b7.free == true && b9.free == false && (b8.value == b9.value)){
        return 7; // row 3 w/ 7 free
      }
    }
    else {
      return 0;
    }
  }
}