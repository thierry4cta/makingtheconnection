<?php
/**
 * Override or insert variables into the html template
 */
function at_panels_everywhere_preproces_html(&$vars) {

  global $theme_key;
  
  // Load the media queries styles
  $media_queries_css = array(
    'responsive.style.css',
  );
  load_subtheme_media_queries($media_queries_css, $theme_key);

 /**
  * Load IE Stylesheets
  *
  * AT automates adding IE stylesheets, simply add to the array using
  * the conditional comment as the key and the stylesheet name as the value.
  *
  * See our online help: http://adaptivethemes.com/documentation/working-with-internet-explorer
  *
  * For example to add a stylesheet for IE8 only use:
  *
  *  'IE 8' => 'ie-8.css',
  *
  * Your IE CSS file must be in the /css/ directory in your subtheme.
  */
  /* -- Delete this line to add a conditional stylesheet for IE 7 or less.
  $ie_files = array(
    'lte IE 7' => 'ie-lte-7.css',
  );
  load_subtheme_ie_styles($ie_files, $theme_key);
  // */
  
  // Add class for the active theme name
  $vars['classes_array'][] = drupal_html_class($theme_key);

  // Browser/platform sniff - adds body classes such as ipad, webkit, chrome etc.
  /* -- Delete this line to add a classes for the browser and platform.
  $vars['classes_array'][] = css_browser_selector();
  // */

  // Remove body classes added by Drupal core
  $classes_to_remove = array('two-sidebars', 'one-sidebar sidebar-first', 'one-sidebar sidebar-second', 'no-sidebars');
  foreach ($vars['classes_array'] as $key => $css_class) {
    if (in_array($css_class, $classes_to_remove)) {
      unset($vars['classes_array'][$key]);
    }
  }
}

// Preprocess vars for the site template
function at_panels_everywhere_preprocess_atpe_site_template(&$vars) {
  // Add information about the number of sidebars.
  $content = $vars['content'];
  $vars['sidebar_classes'] = '';
  
  $sidebars = array();
  if (!empty($content['sidebar_first']) && !empty($content['sidebar_second'])) {
    $sidebars[] = 'two-sidebars';
  }
  elseif (!empty($content['sidebar_first'])) {
    $sidebars[] = 'one-sidebar sidebar-first';
  }
  elseif (!empty($content['sidebar_second'])) {
    $sidebars[] = 'one-sidebar sidebar-second';
  }
  else {
    $sidebars[] = 'no-sidebars';
  }
  $vars['sidebar_classes'] = implode(' ', $sidebars);
}

// Preprocess pane header vars
function at_panels_everywhere_preprocess_pane_header(&$vars) {
  $vars['logo_alt_text'] = check_plain(variable_get('site_name', '')) . ' ' . t('logo');
  $vars['logo_img'] = $vars['logo'] ? '<img src="' . check_url($vars['logo']) . '" alt="' . $vars['logo_alt_text'] . '"/>' : '';
  $vars['linked_site_logo'] = $vars['logo_img'] ? l($vars['logo_img'], '<front>', array(
    'attributes' => array(
      'title' => t('Home page')
    ),
    'html' => TRUE,
    )
  ) : '';
  if (theme_get_setting('toggle_name') == FALSE) {
    $vars['visibility'] = 'element-invisible';
    $vars['hide_site_name'] = TRUE;
  }
  else {
    $vars['visibility'] = '';
    $vars['hide_site_name'] = FALSE;
  }
  $sitename = filter_xss_admin(variable_get('site_name', 'Drupal'));
  $vars['site_name'] = $sitename ? l($sitename, '<front>', array(
    'attributes' => array(
      'title' => t('Home page')),
    )
  ) : '';
}

// Preprocess pane navigation vars
function at_panels_everywhere_preprocess_pane_navigation(&$vars) {
  if (isset($vars['main_menu'])) {

    $text = block_get_blocks_by_region('menu_bar') ? t('Navigation') : t('Main menu');

    $vars['primary_navigation'] = theme('links', array(
      'links' => $vars['main_menu'],
      'attributes' => array(
        'class' => array('menu', 'primary-menu', 'clearfix'),
       ),
      'heading' => array(
        'text' => $text,
        'level' => 'h2',
        'class' => array('element-invisible'),
      )
    ));
  }
  if (!empty($vars['primary_navigation'])) {
    $vars['primary_navigation'] = _theme_menu_variables($vars['primary_navigation'], 'primary');
  }
  if (isset($vars['secondary_menu'])) {
    $vars['secondary_navigation'] = theme('links', array(
      'links' => $vars['secondary_menu'],
      'attributes' => array(
        'class' => array('menu', 'secondary-menu', 'clearfix'),
      ),
      'heading' => array(
        'text' => t('Secondary navigation'),
        'level' => 'h2',
        'class' => array('element-invisible'),
      )
    ));
  }
  if (!empty($vars['secondary_navigation'])) {
    $vars['secondary_navigation'] = _theme_menu_variables($vars['secondary_navigation'], 'secondary');
  }
}

// Preprocess pane messages vars
function at_panels_everywhere_preprocess_pane_messages(&$vars) {
  $vars['primary_local_tasks'] = menu_primary_local_tasks();
  $vars['secondary_local_tasks'] = menu_secondary_local_tasks();
}
