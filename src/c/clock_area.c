﻿#include <pebble.h>
#include "fctx.h"
#include "ffont.h"
#include "clock_area.h"
#include "settings.h"
#include "time_date.h"

static Layer* clock_area_layer;

// just allocate all the fonts at startup because i don't feel like
// dealing with allocating and deallocating things
static FFont* hours_font;
static FFont* minutes_font;
static FFont* colon_font;

static GFont date_font;

static uint8_t prev_clockFontId;

// "private" functions
static void update_original_clock_area_layer(Layer *l, GContext* ctx, FContext* fctx) {
  // check layer bounds
  GRect bounds = layer_get_unobstructed_bounds(l);

  // calculate font size
  int font_size = 4 * bounds.size.h / 7;

  // avenir + avenir bold metrics
  int v_padding = bounds.size.h / 16;
  int h_adjust = 0;
  int v_adjust = 0;

  // alternate metrics for LECO
  if(globalSettings.clockFontId == FONT_SETTING_LECO) {
    font_size += 6;
    v_padding = bounds.size.h / 20;
    h_adjust = -4;
    v_adjust = 0;
  }

  // for rectangular watches, adjust X position based on sidebar position
  if(globalSettings.sidebarLocation == RIGHT) {
    h_adjust -= ACTION_BAR_WIDTH / 2 + 1;
  } else if(globalSettings.sidebarLocation == LEFT) {
    h_adjust += ACTION_BAR_WIDTH / 2;
  }

  FPoint time_pos;

  // draw hours
  time_pos.x = INT_TO_FIXED(bounds.size.w / 2 + h_adjust);
  time_pos.y = INT_TO_FIXED(v_padding + v_adjust);
  fctx_begin_fill(fctx);
  fctx_set_offset(fctx, time_pos);
  fctx_set_text_em_height(fctx, hours_font, font_size);
  fctx_draw_string(fctx, time_date_hours, hours_font, GTextAlignmentCenter, FTextAnchorTop);
  fctx_end_fill(fctx);

  //draw minutes
  time_pos.y = INT_TO_FIXED(bounds.size.h - v_padding + v_adjust);
  fctx_begin_fill(fctx);
  fctx_set_offset(fctx, time_pos);
  fctx_set_text_em_height(fctx, minutes_font, font_size);
  fctx_draw_string(fctx, time_date_minutes, minutes_font, GTextAlignmentCenter, FTextAnchorBaseline);
  fctx_end_fill(fctx);
}

static void update_clock_and_date_area_layer(Layer *l, GContext* ctx, FContext* fctx) {
  // check layer bounds
  GRect fullscreen_bounds = layer_get_bounds(l);

  // calculate font size
  int font_size = fullscreen_bounds.size.h / 3;

  // avenir + avenir bold metrics
  int v_padding = fullscreen_bounds.size.h / 16;
  int h_adjust = -2;
  int v_adjust = 0;

  // alternate metrics for LECO
  if(globalSettings.clockFontId == FONT_SETTING_LECO) {
    v_padding = fullscreen_bounds.size.h / 20;
    h_adjust = -3;
  }

  // for rectangular watches, adjust X position based on sidebar position
  if(globalSettings.sidebarLocation == TOP) {
    v_adjust += FIXED_WIDGET_HEIGHT;
  }

  int h_middle = fullscreen_bounds.size.w / 2;
  int h_colon_margin = 7;

  FPoint time_pos;

  if(globalSettings.centerTime == false || globalSettings.clockFontId == FONT_SETTING_BOLD_H || globalSettings.clockFontId == FONT_SETTING_BOLD_M) {
    // draw hours
    time_pos.x = INT_TO_FIXED(h_middle - h_colon_margin + h_adjust);
    time_pos.y = INT_TO_FIXED(3 * v_padding + v_adjust);
    fctx_begin_fill(fctx);
    fctx_set_offset(fctx, time_pos);
    fctx_set_text_em_height(fctx, hours_font, font_size);
    fctx_draw_string(fctx, time_date_hours, hours_font, GTextAlignmentRight, FTextAnchorTop);
    fctx_end_fill(fctx);

    //draw ":"
    time_pos.x = INT_TO_FIXED(h_middle - 1);
    fctx_begin_fill(fctx);
    fctx_set_offset(fctx, time_pos);
    fctx_set_text_em_height(fctx, colon_font, font_size);
    fctx_draw_string(fctx, ":", colon_font, GTextAlignmentCenter, FTextAnchorTop);
    fctx_end_fill(fctx);

    //draw minutes
    time_pos.x = INT_TO_FIXED(h_middle + h_colon_margin + h_adjust);
    fctx_begin_fill(fctx);
    fctx_set_offset(fctx, time_pos);
    fctx_set_text_em_height(fctx, minutes_font, font_size);
    fctx_draw_string(fctx, time_date_minutes, minutes_font, GTextAlignmentLeft, FTextAnchorTop);
    fctx_end_fill(fctx);
  } else {
    // if only one font center all
    char time[6];

    strncpy(time, time_date_hours, sizeof(time_date_hours));
    strncat(time, ":" , 2);
    strncat(time, time_date_minutes, sizeof(time_date_minutes));

    time_pos.x = INT_TO_FIXED(h_middle - 2);
    time_pos.y = INT_TO_FIXED(3 * v_padding + v_adjust);
    fctx_begin_fill(fctx);
    fctx_set_offset(fctx, time_pos);
    fctx_set_text_em_height(fctx, colon_font, font_size);
    fctx_draw_string(fctx, time, colon_font, GTextAlignmentCenter, FTextAnchorTop);
    fctx_end_fill(fctx);
  }

  // draw date
  graphics_context_set_text_color(ctx, globalSettings.timeColor);
  graphics_draw_text(ctx,
                     time_date_currentDate,
                     date_font,
                     GRect(0, fullscreen_bounds.size.h / 2 - 11 + v_adjust, fullscreen_bounds.size.w, 30),
                     GTextOverflowModeFill,
                     GTextAlignmentCenter,
                     NULL);
}


static void update_clock_area_layer(Layer *l, GContext* ctx) {
  // initialize FCTX, the fancy 3rd party drawing library that all the cool kids use
  FContext fctx;

  fctx_init_context(&fctx, ctx);
  fctx_set_fill_color(&fctx, globalSettings.timeColor);

  if(globalSettings.sidebarLocation == BOTTOM || globalSettings.sidebarLocation == TOP) {
      update_clock_and_date_area_layer(l, ctx, &fctx);
  } else {
      update_original_clock_area_layer(l, ctx, &fctx);
  }
  fctx_deinit_context(&fctx);
}

void ClockArea_init(Window* window) {
  // record the screen size, since we NEVER GET IT AGAIN
  GRect screen_rect = layer_get_bounds(window_get_root_layer(window));
  GRect bounds = GRect(0, 0, screen_rect.size.w, screen_rect.size.h);

  // init the clock area layer
  clock_area_layer = layer_create(bounds);
  layer_add_child(window_get_root_layer(window), clock_area_layer);
  layer_set_update_proc(clock_area_layer, update_clock_area_layer);
}

void ClockArea_ffont_destroy(void) {
  ffont_destroy(hours_font);
  if(prev_clockFontId == FONT_SETTING_BOLD_H || prev_clockFontId == FONT_SETTING_BOLD_M) {
    ffont_destroy(minutes_font);
  }
}

void ClockArea_deinit(void) {
  layer_destroy(clock_area_layer);

  ClockArea_ffont_destroy();
}

void ClockArea_redraw(void) {
  layer_mark_dirty(clock_area_layer);
}

void ClockArea_update_fonts(void) {
  if(globalSettings.sidebarLocation == BOTTOM || globalSettings.sidebarLocation == TOP) {
    date_font = fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD);
  }

  if(prev_clockFontId != globalSettings.clockFontId) {
    if(prev_clockFontId != FONT_SETTING_UNSET) {
      ClockArea_ffont_destroy();
    }

    FFont* avenir;
    FFont* avenir_bold;
    FFont* leco;

    switch(globalSettings.clockFontId) {
      case FONT_SETTING_DEFAULT:
          avenir = ffont_create_from_resource(RESOURCE_ID_AVENIR_REGULAR_FFONT);

          hours_font = avenir;
          minutes_font = avenir;
          colon_font = avenir;
        break;
      case FONT_SETTING_BOLD:
          avenir_bold = ffont_create_from_resource(RESOURCE_ID_AVENIR_BOLD_FFONT);

          hours_font = avenir_bold;
          minutes_font = avenir_bold;
          colon_font = avenir_bold;
        break;
      case FONT_SETTING_BOLD_H:
          avenir =      ffont_create_from_resource(RESOURCE_ID_AVENIR_REGULAR_FFONT);
          avenir_bold = ffont_create_from_resource(RESOURCE_ID_AVENIR_BOLD_FFONT);

          hours_font = avenir_bold;
          minutes_font = avenir;
          colon_font = avenir;
        break;
      case FONT_SETTING_BOLD_M:
          avenir =      ffont_create_from_resource(RESOURCE_ID_AVENIR_REGULAR_FFONT);
          avenir_bold = ffont_create_from_resource(RESOURCE_ID_AVENIR_BOLD_FFONT);

          hours_font = avenir;
          minutes_font = avenir_bold;
          colon_font = avenir;
        break;
      case FONT_SETTING_LECO:
          leco = ffont_create_from_resource(RESOURCE_ID_LECO_REGULAR_FFONT);

          hours_font = leco;
          minutes_font = leco;
          colon_font = leco;
        break;
    }
    prev_clockFontId = globalSettings.clockFontId;
  }
}
