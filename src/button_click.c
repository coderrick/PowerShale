#include <pebble.h>
#include "text_window.h"
#include "menu_window.h"
  

  
//    static Window *window;
// static TextLayer *text_layer;
// static MenuLayer *s_menu_layer;


// static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
//   //text_layer_set_text(text_layer, "Select");
//   menu_window_push();
// }


// static void click_config_provider(void *context) {
//   window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
// }

static void window_load(Window *window) {
  //Layer *window_layer = window_get_root_layer(window);
  //GRect bounds = layer_get_bounds(window_layer);
  /*
  s_menu_layer = menu_layer_create(bounds);
  menu_layer_set_callbacks(s_menu_layer, NULL, (MenuLayerCallbacks){
    .get_num_sections = menu_get_num_sections_callback,
    .get_num_rows = menu_get_num_rows_callback,
    .get_header_height = menu_get_header_height_callback,
    .draw_header = menu_draw_header_callback,
    .draw_row = menu_draw_row_callback,
    .select_click = menu_select_callback,
  });
  menu_layer_set_click_config_onto_window(s_menu_layer, window);

  text_layer = text_layer_create((GRect) { .origin = { 0, 72 }, .size = { bounds.size.w, 20 } });
  text_layer_set_text(text_layer, "Press a button");
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(text_layer));
  layer_add_child(window_layer, menu_layer_get_layer(s_menu_layer));
  */
}

// static void window_unload(Window *window) {
//   text_layer_destroy(text_layer);
//   menu_layer_destroy(s_menu_layer);
// }

static void init(void) {
  
//   window = window_create();
//   window_set_click_config_provider(window, click_config_provider);
//   window = window_create();
//   window_set_click_config_provider(window, click_config_provider);
//   window_set_window_handlers(window, (WindowHandlers) {
// 	  .load = window_load,
//     .unload = window_unload,
//   });
//   const bool animated = true;
//   window_stack_push(window, animated);
  text_window_push();
  //menu_window_push();
}

static void deinit(void) {
//   window_destroy(window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}