#pragma once
#define PROMPT_ANIMATION_WINDOW_DURATION 40   // Duration of each half of the animation
#define PROMPT_ANIMATION_WINDOW_INTERVAL 500 // Interval between timers


void text_window_push();
void text_window_pop();
char* get_cmd();
void set_cmd(char* cmd);