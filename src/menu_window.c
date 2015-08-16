#include <pebble.h>
#include "text_window.h"
#include "menu_window.h"
char *LS = "ls";
char *GET_DATE = "Get-Date";
char *GET_WMIOBJECT = "Get-WmiObject –class Win32_processor | select *";

static Window *menu_window;
static MenuLayer *s_menu_layer;

static uint16_t menu_get_num_sections_callback(MenuLayer *menu_layer, void *data) {
  return NUM_MENU_SECTIONS;
}

static uint16_t menu_get_num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *data) {
  switch (section_index) {
    case 0:
      return NUM_FIRST_MENU_ITEMS;
    case 1:
      return NUM_SECOND_MENU_ITEMS;
    default:
      return 0;
  }
}

static int16_t menu_get_header_height_callback(MenuLayer *menu_layer, uint16_t section_index, void *data) {
  return MENU_CELL_BASIC_HEADER_HEIGHT;
}

static void menu_draw_header_callback(GContext* ctx, const Layer *cell_layer, uint16_t section_index, void *data) {
  // Determine which section we're working with
  switch (section_index) {
    case 0:
      // Draw title text in the section header
      menu_cell_basic_header_draw(ctx, cell_layer, "PowerShale cmds");
      break;
    case 1:
      menu_cell_basic_header_draw(ctx, cell_layer, "EOL");
      break;
  }
}

static void menu_draw_row_callback(GContext* ctx, const Layer *cell_layer, MenuIndex *cell_index, void *data) {
  // Determine which section we're going to draw in
  switch (cell_index->section) {
    case 0:
      // Use the row to specify which item we'll draw
      switch (cell_index->row) {
        case 0:
          // This is a basic menu item with a title and subtitle
          menu_cell_basic_draw(ctx, cell_layer, "ls", "Cmdlet", NULL);
          break;
        case 1:
          
           menu_cell_basic_draw(ctx, cell_layer, "Get-Date", "Cmdlet", NULL);
          break;
        case 2: 
             menu_cell_basic_draw(ctx, cell_layer, "Get-WmiObject –class Win32_processor | select *", "Cmdlet", NULL);      
          break;
      }
      break;
    case 1:
      switch (cell_index->row) {
        case 0:
          // There is title draw for something more simple than a basic menu item
          //menu_cell_title_draw(ctx, cell_layer, "More commands coming soon!");
          break;
      }
  }
}

static void menu_select_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *data) {
  // Use the row to specify which item will receive the select action
  switch (cell_index->row) {
    // This is the menu item with the cycling icon
    case 0:
      set_cmd(LS);
      // Cycle the icon
      //s_current_icon = (s_current_icon + 1) % NUM_MENU_ICONS;
      // After changing the icon, mark the layer to have it updated
      //layer_mark_dirty(menu_layer_get_layer(menu_layer));
      break;
    case 1:
      set_cmd(GET_DATE);
      break;
    case 2:
      set_cmd(GET_WMIOBJECT);
      break;  
  }

}
/*End*/
static void window_load(Window *window){
  Layer *window_layer = window_get_root_layer(menu_window);
  GRect bounds = layer_get_frame(window_layer);
  
   s_menu_layer = menu_layer_create(bounds);
   menu_layer_set_normal_colors(s_menu_layer, GColorBlue, GColorClear);
   menu_layer_set_highlight_colors(s_menu_layer, GColorLightGray, GColorWhite);
   menu_layer_set_callbacks(s_menu_layer, NULL, (MenuLayerCallbacks){
    .get_num_sections = menu_get_num_sections_callback,
    .get_num_rows = menu_get_num_rows_callback,
    .get_header_height = menu_get_header_height_callback,
    .draw_header = menu_draw_header_callback,
    .draw_row = menu_draw_row_callback,
    .select_click = menu_select_callback,
  });
  menu_layer_set_click_config_onto_window(s_menu_layer, window);
  layer_add_child(window_layer, menu_layer_get_layer(s_menu_layer));
}

static void window_unload(Window *window){
  //We will safely destroy the Window's elements here!
  menu_layer_destroy(s_menu_layer);//deallocates memory for the textlayer since we don't need to see it anymore
  APP_LOG(APP_LOG_LEVEL_DEBUG, "App started, %s", "***********************Program made it here MENU***************************");
}

void menu_window_push(){
  
  menu_window = window_create();
  //window_set_click_config_provider(menu_window, click_config_provider);
  window_set_window_handlers(menu_window, (WindowHandlers) {
	  .load = window_load,
    .unload = window_unload,
  });
  const bool animated = true;
  window_stack_push(menu_window, animated);
}
