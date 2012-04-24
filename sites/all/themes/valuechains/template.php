<?php
/**
 * Preprocess and Process Functions SEE: http://drupal.org/node/254940#variables-processor
 * 1. Rename each function and instance of "splash" to match
 *    your subthemes name, e.g. if your theme name is "footheme" then the function
 *    name will be "footheme_preprocess_hook". Tip - you can search/replace
 *    on "splash".
 * 2. Uncomment the required function to use.
 */


/**
 * Preprocess variables for the html template.
 */

function valuechains_preprocess_html(&$vars) {
  global $theme_key;

  // Add a body class for the active theme name.
$vars['classes_array'][] = drupal_html_class($theme_key);

  // Browser/platform sniff - adds body classes such as ipad, webkit, chrome etc.
$vars['classes_array'][] = css_browser_selector();
drupal_add_css('http://fonts.googleapis.com/css?family=Frutiger+condensed', array('type' => 'external'));
}



/**
 * Process variables for the html template.
 */

function valuechains_process_html(&$vars) {
}
// */


/**
 * Preprocess variables for the page templates.
 */

function valuechains_preprocess_page(&$vars) {
}
function valuechains_process_page(&$vars) {
}
// */


/**
 * Override or insert variables into the node templates.
 */
/* -- Delete this line if you want to use these functions
function valuechains_preprocess_node(&$vars) {
}
function valuechains_process_node(&$vars) {
}
// */


/**
 * Override or insert variables into the comment templates.
 */
/* -- Delete this line if you want to use these functions
function valuechains_preprocess_comment(&$vars) {
}
function valuechains_process_comment(&$vars) {
}
// */


/**
 * Override or insert variables into the block templates.
 */
/* -- Delete this line if you want to use these functions
function valuechains_preprocess_block(&$vars) {
}
function valuechains_process_block(&$vars) {
}
// */