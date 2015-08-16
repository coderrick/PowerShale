#include <pebble.h>
#include "text_window.h"
#include "menu_window.h"
  
static Window *text_window;
static TextLayer *g_text_layer;
static AppTimer *s_timer;
static char s_text[1];
static bool visible = true;
static char s_cmd[32];


void set_cmd(char* cmd){
  snprintf(s_cmd , sizeof(s_cmd), "%s", cmd);
}
char* get_cmd(){
 return s_cmd; 
}

//static void animate();
void toggle_callback(void *data){
  char* prompt = "PS C:\\...>";
  char* cmd = get_cmd();//"ls";//get_cmd_from_menu_item;
  APP_LOG(APP_LOG_LEVEL_DEBUG, "App started, %s", cmd);
  char* cursor = "_";
  char* commandline = (char *) malloc(1 + strlen(prompt)+strlen(cmd)+strlen(cursor));
  
  if(visible){
    //cursor[0]=' ';
    //graphics_text_layout_get_content_size(const char * text, GFont const font, const GRect box, const GTextOverflowMode overflow_mode, const GTextAlignment alignment)
    visible = false;
  }else{
    visible = true;
  }
  strcpy(commandline,prompt);
  strcat(commandline, cmd);
  strcat(commandline, cursor);
  text_layer_set_text(g_text_layer, commandline);
  layer_mark_dirty(text_layer_get_layer(g_text_layer));
  //app_timer_reschedule(s_timer, PROMPT_ANIMATION_WINDOW_INTERVAL);
  s_timer = app_timer_register(PROMPT_ANIMATION_WINDOW_INTERVAL , toggle_callback, NULL);
}
static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  //text_layer_set_text(text_layer, "Select");
  menu_window_push();
}

static void long_select_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(g_text_layer, "COMMAND SENT!");
  //menu_window_push();
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_long_click_subscribe(BUTTON_ID_SELECT,1000, long_select_click_handler,NULL);
}

static void window_load(Window *window){
  Layer *window_layer = window_get_root_layer(text_window);
  GRect bounds = layer_get_frame(window_layer);
  
  g_text_layer = text_layer_create(GRect(0,0,144,168));
  text_layer_set_background_color(g_text_layer, GColorBlue);//Set background for the frame that the TextLayer is contained in
  text_layer_set_text_color(g_text_layer, GColorWhite);//Set text color to white;
  layer_add_child(window_get_root_layer(window),text_layer_get_layer(g_text_layer));//Adds textlayer's root layer as a child of window layer so that the text can be seen
  //code was here
  s_timer = app_timer_register(PROMPT_ANIMATION_WINDOW_INTERVAL , toggle_callback, NULL);
 
  layer_add_child(window_layer, text_layer_get_layer(g_text_layer));
}

static void window_unload(Window *window){
  //We will safely destroy the Window's elements here!
  text_layer_destroy(g_text_layer);//deallocates memory for the textlayer since we don't need to see it anymore
}

void text_window_push(){
  APP_LOG(APP_LOG_LEVEL_DEBUG, "App started, %s", "***********************Program made it here***************************");
  text_window = window_create();
  window_set_click_config_provider(text_window, click_config_provider);
  window_set_window_handlers(text_window, (WindowHandlers) {
	  .load = window_load,
    .unload = window_unload,
  });
  const bool animated = true;
  window_stack_push(text_window, animated);
}

void text_window_pop(){
  window_stack_pop(true);
}