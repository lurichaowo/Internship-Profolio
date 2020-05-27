import { Component } from '@angular/core';
import { MatSnackBar } from '@angular/material';
import { Player } from './player';
import { Block } from './Block';
import { GameService } from './game.service';


@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.scss'],
  providers: [GameService]
})

export class AppComponent {
  lock = false; // locks control of gameboard when it is computers turn or draw

  constructor(public gs: GameService, public snackbar: MatSnackBar){

  }

  newGame(){
    this.gs.freeBlocksRemaining = 9;
    this.gs.initBlocks();
    this.lock = false;
    this.gs.turn = 0;
  }

  resetGame(event){
    location.reload();
    event.preventDefault();
  }

  playerClick(i){
    if (this.gs.blocks[i].free == false || this.lock == true){
      //if block is filled, dont do anything
      return;
    }

    this.gs.freeBlocksRemaining -= 1; 
    // reduce # of free blocks per player action

    if (this.gs.freeBlocksRemaining <= 0){
      // if game ends in a draw
      this.gs.draw +=1;
      this.lock = true;
      this.snackbar.open("Game: ", "Draw ",{ duration: 4000, });
      this.newGame();
      return;
    }

    // make this not free 
    this.gs.blocks[i].free = false;

    if (this.gs.turn == 0){
      //p1 turn
      this.gs.blocks[i].setValue("tick");
    }
    else {
      // bot turn
      this.gs.blocks[i].setValue("cross");
    }

    // which block will complete a set of 3
    var complete = this.gs.blockSetComplete();

    if (complete == false){
      // if not done change turn
      this.changeTurn();
      return;
    }

    else{
      // if completed: lock board, +1 score to whos turn it is
      //announce winner
      // start a new game
      this.lock = true;
      this.gs.players[this.gs.turn].score += 1;
      this.snackbar.open("Winner:", "Player " + (this.gs.turn +1), { duration: 4000, });
      this.newGame();
      return;
    }
  }

  botTurn(){
    if (this.gs.freeBlocksRemaining <= 0){
      return;
    }

    var bot_selected = this.gs.figureBotMove()-1;

    if (this.gs.blocks[bot_selected].free == true){
      this.playerClick(bot_selected);
    }
    else{
      this.botTurn();
      return;
    }
  }

  changeTurn(){
    var player = this.gs.changeTurn();
    if (player ==1){
      //bot turn
      this.botTurn();
    }
  }

  title = 'TicTacToe';
}
