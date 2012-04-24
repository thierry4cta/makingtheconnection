<?php
// Automagical Info file builder
// This is the theme info backed up to a file. Its formatted and holds all
// current values - useful for migration or simply capturing the current
// theme settings as defaults, which is why I built it.
$theme_settings = $values;
if ($theme_settings) {
  $dynamic_settings_info = array();
  $static_settings_info = array();
  $lt = list_themes();
  foreach ($lt as $key => $value) {
    if ($theme_name == $key) {
      $this_themes_info = $lt[$theme_name]->info;
      foreach ($this_themes_info as $k => $v) {
        if ($k == 'name') {
          $static_settings_info[] = 'name = ' . $v;
        }
        if ($k == 'description') {
          $v = $v ? $v : $theme_name. ' is rocking the hardest!';
          $static_settings_info[] = 'description = ' . $v;
        }
        if ($k == 'base theme') {
          $static_settings_info[] = 'base theme = ' . $v;
        }
        if ($k == 'release') {
          $static_settings_info[] = 'release = ' . $v;
        }
        if ($k == 'core') {
          $static_settings_info[] = 'core = 7.x';
        }
        if ($k == 'engine') {
          $static_settings_info[] = 'engine = phptemplate';
        }
        if ($k == 'screenshot') {
          $static_settings_info[] = 'screenshot = screenshot.png';
        }
        if ($k == 'stylesheets' && !empty($k)) {
          foreach ($v as $media_target => $stylesheet_file) {
            foreach ($stylesheet_file as $stylesheet_file_name => $stylesheet_file_path) {
              $static_settings_info[] = 'stylesheets[' . $media_target . '][] = ' . $stylesheet_file_name;
            }
          }
        }
        if ($k == 'scripts' && !empty($k)) {
          foreach ($v as $script => $file) {
            $static_settings_info[] = 'scripts[] = ' . $script;
          }
        }
        if ($k == 'regions') {
          foreach ($v as $name => $label) {
            $static_settings_info[] = 'regions[' . $name . '] = ' . $label;
          }
        }
        if ($k == 'features') {
          foreach ($v as $feature_key => $feature) {
            $static_settings_info[] = 'features[] = ' . $feature;
          }
        }
      }
    }
  }
  if (!empty($static_settings_info)) {
    $static_settings = implode("\n", $static_settings_info);
  }
  // Might need to check this and add some more exclusions
  $exclusions = array(
    'var',
    'default_logo',
    'logo_path',
    'logo_upload',
    'default_favicon',
    'favicon_path',
    'favicon_upload',
    'submit',
    'form_build_id',
    'form_token',
    'form_id',
    'check',
    'output',
    'op',
    'scheme',
    'palette',
    'theme',
    'info',
    'at-layout__active_tab',
  );
  foreach ($theme_settings as $setting_name => $setting_value) {
    if (isset($setting_name) && !in_array($setting_name, $exclusions)) {
      $setting_value = $setting_value ? $setting_value : "''";
      $dynamic_settings_info[] = 'settings['. $setting_name .'] = ' . $setting_value;
    }
  }
  if (!empty($dynamic_settings_info)) {
    // Interesting trivial fact about info files, if the line ends with an equals operator (=) then the line
    // is not ended and the content of the next line will be assigned, therefor we can never leave an empty
    // setting with a hanging equals, so we set an empty string. I still need to test this properly because
    // it might be better, or even required to set it to a 0.
    $dynamic_settings_info = $dynamic_settings_info ? $dynamic_settings_info : "''";
    $dynamic_settings = implode("\n", $dynamic_settings_info);
  }
  if (!empty($static_settings_info) && !empty($dynamic_settings_info)) {
    $sanitized_values = filter_xss_admin($static_settings . "\n" . $dynamic_settings); // run a final sanity check
    $filepath = $path . '/' . $theme_name . '_settings.info';
    file_save_data($sanitized_values, $filepath, FILE_EXISTS_REPLACE);
  }
}
