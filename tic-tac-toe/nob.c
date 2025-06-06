#define NOB_IMPLEMENTATION
#include "nob.h"

int main(int argc, char **argv)
{
  NOB_GO_REBUILD_URSELF(argc, argv);
  Nob_Cmd cmd = {0};

  nob_cmd_append(&cmd, "g++", "-Wall", "-Wextra", "-lSDL2", "-o", "tic-tac-toe", "main.cpp");
  
  if (!nob_cmd_run_sync(cmd)) return 1;  
  return 0;
}
