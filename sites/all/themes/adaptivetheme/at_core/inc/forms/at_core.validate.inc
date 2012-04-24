<?php

/**
 * Validatation for theme settings.
 *
 * @param $form
 * @param $form_state
 */
function at_core_settings_validate($form, &$form_state) {

  $values = $form_state['values'];
  $theme_name = $form_state['build_info']['args'][0];

  // Remove some stuff we never use or need
  if (isset($values['at__active_tab']) || isset($values['at-layout__active_tab'])) {
    unset($values['at__active_tab']);
    unset($values['at-layout__active_tab']);
  }

  // Validate our form #state required fields, #states are UI only.
  if ($values['bigscreen_set_max_width'] === 1) {
    if (empty($values['bigscreen_max_width'])) {
      form_set_error('bigscreen_max_width', t('Standard layout max-width is empty - enter a value or deselect "Set a max width".'));
    }
  }
  if ($values['smartphone_landscape_layout'] === 'one-col-vert') {
    if (empty($values['smartphone_landscape_sidebar_first'])) {
      form_set_error('smartphone_landscape_sidebar_first', t('Smartphone First Sidebar width is empty - enter a value or choose another layout.'));
    }
    if (empty($values['smartphone_landscape_sidebar_second'])) {
      form_set_error('smartphone_landscape_sidebar_second', t('Smartphone Second Sidebar width is empty - enter a value or choose another layout.'));
    }
  }

  // Apple touch icons
  if(at_get_setting('enable_extensions') === 1) {
    if ($values['enable_apple_touch_icons'] === 1) {
      // low
      // if (empty($values['apple_touch_icon_path_l'])) {
        // form_set_error('apple_touch_icon_path_l', t('Ops! The Apple touch 57x57 icon path is missing, you must enter a path or disable touch icons.'));
      // }
      if (!empty($values['apple_touch_icon_path_l'])) {
        $l = drupal_get_path('theme', $theme_name) .'/'. $values['apple_touch_icon_path_l'];
        if (!file_exists($l)) {
          form_set_error('apple_touch_icon_path_l', t('Ops! The Apple touch 57x57 icon path is not right, check the file exists or the path to the file is correct.'));
        }
      }
      // medium
      if (!empty($values['apple_touch_icon_path_m'])) {
        $m = drupal_get_path('theme', $theme_name) .'/'. $values['apple_touch_icon_path_m'];
        if (!file_exists($m)) {
          form_set_error('apple_touch_icon_path_m', t('Ops! The Apple touch 72x72 icon path is not right, check the file exists or the path to the file is correct.'));
        }
      }
      // high
      if (!empty($values['apple_touch_icon_path_h'])) {
        $h = drupal_get_path('theme', $theme_name) .'/'. $values['apple_touch_icon_path_h'];
        if (!file_exists($h)) {
          form_set_error('apple_touch_icon_path_h', t('Ops! The Apple touch 114x114 icon path is not right, check the file exists or the path to the file is correct.'));
        }
      }
    }
  }
}
