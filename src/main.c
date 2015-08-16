#include <pebble.h>
  
#define NUM_MENU_SECTIONS 2
#define NUM_FIRST_MENU_ITEMS 3
#define NUM_SECOND_MENU_ITEMS 1
/*Global variables*/
  Window *g_window;//Global variable for window so that is accessible throughout the app.
  TextLayer *g_text_layer;//Global variable for TextLayer so that is accessible throughout the app.
/*******END********/



void window_load(Window *window)
{
  //We will add the creation of the Window's elements here soon!
  g_text_layer = text_layer_create(GRect(0,0,144,168));
  text_layer_set_background_color(g_text_layer, GColorOxfordBlue);//Set background for the frame that the TextLayer is contained in
  text_layer_set_text_color(g_text_layer, GColorWhite);//Set text color to white;
  layer_add_child(window_get_root_layer(window),text_layer_get_layer(g_text_layer));//Adds textlayer's root layer as a child of window layer so that the text can be seen
  //Adding menu as child of WIndow as well
  text_layer_set_text(g_text_layer, "PS C:\\...>");
  //Pseudo Code
  //set_remote_ps_command_from_menu() i.e "ls"
  //blink_text_cursor(character_to_blink) i.e "_"
  //ex: "PS C:\\...>" + "ls" + "_"
  
}

void window_unload(Window *window)
{
  //We will safely destroy the Window's elements here!
  text_layer_destroy(g_text_layer);//deallocates memory for the textlayer since we don't need to see it anymore
}
void init()
{
  //Create app elements here Window...etc
  g_window = window_create();//Initializing the Global variable as a window element in memory
  window_set_window_handlers(g_window, (WindowHandlers){//This handler will manage memory for properties of this windows
    .load = window_load,
    .unload = window_unload,
  });
  window_set_background_color(g_window, GColorClear);
  window_stack_push(g_window, true);//Make the app actually appear when chosen from menu.
}

void deinit()
{
  //Destroy app elements here
  window_destroy(g_window);//deallocate memory used by memory
  
}

int main()
{
  APP_LOG(APP_LOG_LEVEL_DEBUG, "App started, %d", 5);
  /*Used to create (or initialize) our app*/
  init();
  /*Handles all events that happen from the start of the app to the end*/
  app_event_loop();
  /*Deallocate memory*/
  deinit();
}