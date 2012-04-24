<?php
/**
 * IMPORTANT WARNING: DO NOT MODIFY THIS FILE OR ANY OF THE INCLUDED FILES.
 */

// Set globals for often used stuff.
global $theme_key, $path_to_at_core;
$theme_key = $GLOBALS['theme_key'];
$path_to_at_core = drupal_get_path('theme', 'adaptivetheme');

// Let this bird fly...
require_once($path_to_at_core . '/inc/get.inc');        // get theme info, settings, css etc
require_once($path_to_at_core . '/inc/plugins.inc');    // the plugin system with wrapper and helper functions
require_once($path_to_at_core . '/inc/generate.inc');    // misc infrequently used functions
require_once($path_to_at_core . '/inc/load.inc');       // drupal_add_css() wrappers
require_once($path_to_at_core . '/inc/alter.inc');      // hook_alters
require_once($path_to_at_core . '/inc/preprocess.inc'); // all preprocess functions
require_once($path_to_at_core . '/inc/process.inc');    // all process functions
require_once($path_to_at_core . '/inc/theme.inc');      // theme function overrides
