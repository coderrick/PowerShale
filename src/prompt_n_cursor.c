#include "prompt_n_cursor.h"

static Window *s_window;
static TextLayer *s_text_layer;

static AppTimer *s_timer;

//static void animate();

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  s_text_layer = text_layer_create(GRect(0, (bounds.size.h / 2) - 24, bounds.size.w, bounds.size.h));
  text_layer_set_text(s_text_layer, "Example text.");
  text_layer_set_text_color(s_text_layer, GColorWhite);
  text_layer_set_background_color(s_text_layer, GColorClear);
  text_layer_set_font(s_text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
  //text_layer_set_text_alignment(s_text_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(s_text_layer));
}

static void window_unload(Window *window) {
  text_layer_destroy(s_text_layer);
  window_destroy(s_window);
  s_window = NULL;
}

static void window_disappear(Window *window) {
  if(s_timer) {
    app_timer_cancel(s_timer);
    s_timer = NULL;
  }
}

void prompt_animation_window_push() {
  //snprintf(s_text[0], sizeof(s_text[0]), "Some example text");
  //snprintf(s_text[1], sizeof(s_text[1]), "Some more example text");
  //s_current_text = 0;

  if(!s_window) {
    s_window = window_create();
    window_set_background_color(s_window, GColorBlueMoon);
    window_set_window_handlers(s_window, (WindowHandlers) {
      .load = window_load,
      .unload = window_unload,
      .disappear = window_disappear
    });
  }
  window_stack_push(s_window, true);

  //animate();
}



