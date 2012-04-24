<?php

global $path_to_at_core;
$path_to_at_core = drupal_get_path('theme', 'adaptivetheme');

// Helper functions for processing the page layout and font families.
require_once($path_to_at_core . '/inc/forms/at_core.submit.builders.inc');

/**
 * Custom submit function - this mostly builds and saves stylesheets for
 * various features such as the responsive layout and font styles.
 *
 * @param $form
 * @param $form_state
 */
function at_core_settings_submit($form, &$form_state) {
  global $path_to_at_core;

  //dsm($form_state);

  // Set form_state values into one variable
  $values = $form_state['values'];

  // Get the active theme name, $theme_key will return the admin theme
  $theme_name = $form_state['build_info']['args'][0];

  // Set up some paths we use to get and save files
  $path_to_panels_css = $path_to_at_core . '/layouts/css/';
  $path_to_responsive_css = drupal_get_path('theme', $theme_name) . '/css/';

  // Set up our files directory for the generated files. Files are never
  // overwritten, however the files are really small - total around 25kb
  // depending, of which around 8kb is never loaded - the theme info
  // config file, which is just a backup.
  $id = $theme_name . '_files_' . substr(hash('sha256', serialize($theme_name) . microtime()), 0, 8);
  $path  = 'public://adaptivetheme/' . $id;
  file_prepare_directory($path, FILE_CREATE_DIRECTORY);
  variable_set('theme_' . $theme_name . '_files_directory', $path);

  // Include processing for automagical info builder
  require_once($path_to_at_core . '/inc/forms/at_core.submit.info.inc');

  // Include processing for page & panels layouts, and responsive styles
  require_once($path_to_at_core . '/inc/forms/at_core.submit.responsive.inc');

  if($values['enable_extensions'] === 1) {
    // Include processing for fonts
    if (isset($values['enable_font_settings']) && $values['enable_font_settings'] === 1) {
      require_once($path_to_at_core . '/inc/fonts.inc');
      require_once($path_to_at_core . '/inc/forms/at_core.submit.fonts.inc');
    }
    // Include processing for Custom CSS
    if (isset($values['enable_custom_css']) && $values['enable_custom_css'] === 1) {
      require_once($path_to_at_core . '/inc/forms/at_core.submit.customcss.inc');
    }
  }
  
  // Color inc save
  if(module_exists('color')) {
    if (isset($values['at-color']) && $values['at-color'] == TRUE) {
      require_once($path_to_at_core . '/inc/forms/at_core.submit.color.inc');
    }
  }
}
