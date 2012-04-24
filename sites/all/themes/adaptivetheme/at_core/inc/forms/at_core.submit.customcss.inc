<?php

  $custom_css = '';
  if (!empty($values['custom_css'])) {
    $custom_css = filter_xss($values['custom_css']); // sanitize user entered data, strip bad protocols
  }
  $file_name = $theme_name . '.custom.css';
  $filepath = $path . '/' . $file_name;
  file_save_data($custom_css, $filepath, FILE_EXISTS_REPLACE);
