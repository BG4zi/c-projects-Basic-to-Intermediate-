#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>

#include <iostream>
#include <SDL2/SDL.h>
#include <stdio.h>

#define SCREEN_WIDTH  600
#define SCREEN_HEIGHT 600
#define SIZE 600
#define FPS 60
#define RADIUS SIZE / 6
#define INNER_RADIUS 99

SDL_Color color_from_hex(Uint32 hex)
{
  SDL_Color color;
  color.r = (hex >> 16) & 0xFF;
  color.g = (hex >> 8) & 0xFF;
  color.b = hex & 0xFF;
  color.a = (hex >> 24) & 0xFF;
  return color;
}

void set_board(SDL_Renderer *renderer, SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLine(renderer, SCREEN_WIDTH / 3, 0, SCREEN_WIDTH / 3, SCREEN_HEIGHT);
    SDL_RenderDrawLine(renderer, SCREEN_WIDTH / 3 * 2, 0, SCREEN_WIDTH / 3 * 2, SCREEN_HEIGHT);
    SDL_RenderDrawLine(renderer, 0, SCREEN_HEIGHT / 3, SCREEN_WIDTH, SCREEN_HEIGHT / 3);
    SDL_RenderDrawLine(renderer, 0, SCREEN_HEIGHT / 3 * 2, SCREEN_WIDTH, SCREEN_HEIGHT / 3 * 2);
  
}

void draw_x(SDL_Renderer *renderer, int r, int c)
{
  SDL_RenderDrawLine(renderer,
		     SCREEN_WIDTH / 3 * c,
		     SCREEN_HEIGHT / 3 * r,
		     SCREEN_WIDTH / 3 * (c + 1),
		     SCREEN_HEIGHT / 3 * (r + 1));
  SDL_RenderDrawLine(renderer,
		     SCREEN_WIDTH / 3 * (c + 1),
		     SCREEN_HEIGHT / 3 * r,
		     SCREEN_WIDTH / 3 * c,
		     SCREEN_HEIGHT / 3 * (r + 1));
}
void draw_o(SDL_Renderer *renderer, int r, int c)
{
  SDL_Point center{
    .x = SCREEN_WIDTH*(2*c+1)/6,
    .y = SCREEN_HEIGHT*(2*r+1)/6
  };

  for (int i = 0; i < RADIUS * 2; ++i) {
    for (int j = 0; j < RADIUS * 2; ++j) {
      int dx = RADIUS - i;
      int dy = RADIUS - j;
      
      if ((dx*dx + dy*dy) <= (RADIUS * RADIUS) &&
	  (dx*dx + dy*dy)  >= (INNER_RADIUS * INNER_RADIUS)) {
	SDL_RenderDrawPoint(renderer, center.x + dx, center.y + dy);
      }
    } 
  }
}

void SDL_Destroy(SDL_Renderer *renderer, SDL_Window *window)
{
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();  
}

int main(int argc, char **argv)
{
  int WINNER = 0;
  (void) argc;
  (void) argv;
  SDL_Event ev;

  bool valid_key;
  SDL_Color BG_COLOR    = color_from_hex(0xFF1E1E2E); // Soft dark purple background (Dracula-style)
  SDL_Color LINE_COLOR  = color_from_hex(0xFFBD93F9); // Light violet for grid lines
  SDL_Color ICON_X_COLOR = color_from_hex(0xFFFF5555); // Red/pinkish for X
  SDL_Color ICON_O_COLOR = color_from_hex(0xFF50FA7B); // Green for O
  
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
    std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
    return 1;
  }
  SDL_Window *window = SDL_CreateWindow("Tic Tac Toe",
					SDL_WINDOWPOS_UNDEFINED,
					SDL_WINDOWPOS_UNDEFINED,
					SCREEN_WIDTH, SCREEN_HEIGHT,
					SDL_WINDOW_SHOWN);
  if (!window) {
    std::cerr << "ERROR: Could not initialize window: " << SDL_GetError() << "\n";
  }
	
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer) {
    std::cerr << "ERROR: " << SDL_GetError() << "\n";
    return 1;
  }

  bool quit = false;

  int board[3][3] = {0};
  int move[2] ;
  int count = 0;

  while (!quit) {

    SDL_SetRenderDrawColor(renderer, BG_COLOR.r, BG_COLOR.g, BG_COLOR.b, BG_COLOR.a);
    SDL_RenderClear(renderer);

    if (WINNER == 0) {

      set_board(renderer, LINE_COLOR);

      for (int i = 0; i < 3; ++i) {
	for (int j = 0; j < 3; ++j) {
	  if (board[i][j] == 1){
	    SDL_SetRenderDrawColor(renderer,
				   ICON_X_COLOR.r, ICON_X_COLOR.g,
				   ICON_X_COLOR.b, ICON_X_COLOR.a);
	    draw_x(renderer, i, j);
	  }
	  if (board[i][j] == 9){
	    SDL_SetRenderDrawColor(renderer,
				   ICON_O_COLOR.r, ICON_O_COLOR.g,
				   ICON_O_COLOR.b, ICON_O_COLOR.a);
	    draw_o(renderer, i, j);
	  }
	}
      }
    } else {
      if (WINNER == 1){
	SDL_SetRenderDrawColor(renderer,
			       ICON_X_COLOR.r, ICON_X_COLOR.g,
			       ICON_X_COLOR.b, ICON_X_COLOR.a);
	draw_x(renderer, 1, 1);
      }
      if (WINNER == 9) {
	SDL_SetRenderDrawColor(renderer,
			       ICON_O_COLOR.r, ICON_O_COLOR.g,
			       ICON_O_COLOR.b, ICON_O_COLOR.a);
	draw_o(renderer, 1, 1);
      }
    }

    SDL_RenderPresent(renderer);

    printf("{%d} {%d} {%d}\n", board[0][0], board[0][1], board[0][2]);
    printf("{%d} {%d} {%d}\n", board[1][0], board[1][1], board[1][2]);
    printf("{%d} {%d} {%d}\n", board[2][0], board[2][1], board[2][2]);
    printf("--------------------------------------\n");
      for (int x = 0; x < 3; ++x) {
        if (board[x][0]+ board[x][1] + board[x][2] == 3)
	    WINNER = 1;
	if(board[x][0]+ board[x][1] + board[x][2]==27)
	    WINNER = 9;	
	if (board[0][x]+ board[1][x] + board[2][x] == 3)
	    WINNER = 1;
	if(board[0][x]+ board[1][x] + board[2][x]==27)
	    WINNER = 9;	
      }
      if(board[0][0]+ board[1][1] + board[2][2]==3)
	  WINNER = 1;
      if(board[0][0]+ board[1][1] + board[2][2]==27)
	  WINNER = 9;
      if(board[0][2]+ board[1][1] + board[2][0]==3)
	  WINNER = 1;
      if(board[0][2]+ board[1][1] + board[2][0]==27)
	  WINNER = 9;
    valid_key = false;
    while (!valid_key && SDL_WaitEvent(&ev)) {    
      if (ev.type == SDL_QUIT) {
	quit = true;
	valid_key = true;
      } else if (ev.type == SDL_KEYDOWN) {
	switch (ev.key.keysym.sym) {
	case SDLK_KP_1: move[0] = 2; move[1] = 0; valid_key = true; break;
	case SDLK_KP_2: move[0] = 2; move[1] = 1; valid_key = true; break;
	case SDLK_KP_3: move[0] = 2; move[1] = 2; valid_key = true; break;
	case SDLK_KP_4: move[0] = 1; move[1] = 0; valid_key = true; break;
	case SDLK_KP_5: move[0] = 1; move[1] = 1; valid_key = true; break;
	case SDLK_KP_6: move[0] = 1; move[1] = 2; valid_key = true; break;
	case SDLK_KP_7: move[0] = 0; move[1] = 0; valid_key = true; break;
	case SDLK_KP_8: move[0] = 0; move[1] = 1; valid_key = true; break;
	case SDLK_KP_9: move[0] = 0; move[1] = 2; valid_key = true; break;
	default: continue;
	}
	if (WINNER == 0 && board[move[0]][move[1]] == 0 && count < 9) {
	  board[move[0]][move[1]] = (count % 2 == 0) ? 1 : 9;
	  count++;
	}
      }
    }
  }
  SDL_Destroy(renderer, window);
  return 0;
}


