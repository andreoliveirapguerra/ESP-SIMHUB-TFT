// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.2
// LVGL version: 8.3.11
// Project name: DEMO

#include "ui.h"


// COMPONENT dashImage

lv_obj_t * ui_ImagedashImage_create(lv_obj_t * comp_parent)
{

    lv_obj_t * cui_ImagedashImage;
    cui_ImagedashImage = lv_img_create(comp_parent);
    lv_img_set_src(cui_ImagedashImage, &ui_img_akemi_smile_png);
    lv_obj_set_width(cui_ImagedashImage, LV_SIZE_CONTENT);   /// 100
    lv_obj_set_height(cui_ImagedashImage, LV_SIZE_CONTENT);    /// 100
    lv_obj_set_align(cui_ImagedashImage, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(cui_ImagedashImage, LV_FLEX_FLOW_ROW_WRAP);
    lv_obj_set_flex_align(cui_ImagedashImage, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_add_flag(cui_ImagedashImage, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(cui_ImagedashImage,
                      LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
    lv_obj_set_scrollbar_mode(cui_ImagedashImage, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_shadow_color(cui_ImagedashImage, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(cui_ImagedashImage, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(cui_ImagedashImage, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(cui_ImagedashImage, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(cui_ImagedashImage, -2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(cui_ImagedashImage, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t ** children = lv_mem_alloc(sizeof(lv_obj_t *) * _UI_COMP_IMAGEDASHIMAGE_NUM);
    children[UI_COMP_IMAGEDASHIMAGE_IMAGEDASHIMAGE] = cui_ImagedashImage;
    lv_obj_add_event_cb(cui_ImagedashImage, get_component_child_event_cb, LV_EVENT_GET_COMP_CHILD, children);
    lv_obj_add_event_cb(cui_ImagedashImage, del_component_child_event_cb, LV_EVENT_DELETE, children);
    lv_obj_add_event_cb(cui_ImagedashImage, ui_event_comp_ImagedashImage_ImagedashImage, LV_EVENT_ALL, children);
    ui_comp_ImagedashImage_create_hook(cui_ImagedashImage);
    return cui_ImagedashImage;
}

