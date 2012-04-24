<?php
/**
 * General alters.
 */
global $theme_key, $theme_name;
$theme_name = $theme_key;
$path_to_at_core = drupal_get_path('theme', 'adaptivetheme');

/**
 * hook_html_head_alter()
 */
function adaptivetheme_html_head_alter(&$head_elements) {
  global $theme_name, $path_to_at_core;

  // charset utf-8
  $head_elements['system_meta_content_type']['#attributes'] = array('charset' => 'utf-8');

  // This injects new meta tags for mobile, it uses all user entered data so
  // we do heavy sanity checking.

  // Viewport
  if (at_get_setting('disable_responsive_styles', $theme_name) === 0) {
    if (at_get_setting('enable_mobile_metatags', $theme_name) === 1) {
      // Viewport
      $adaptivetheme_meta_viewport = filter_xss_admin(at_get_setting('adaptivetheme_meta_viewport', $theme_name));
      $head_elements['adaptivetheme_meta_viewport'] = array(
        '#type' => 'html_tag',
        '#tag' => 'meta',
        '#attributes' => array(
          'name' => 'viewport',
          'content' => $adaptivetheme_meta_viewport,
        ),
        '#weight' => 1,
      );
      // MobileOptimized
      $adaptivetheme_meta_mobileoptimized = filter_xss_admin(at_get_setting('adaptivetheme_meta_mobileoptimized', $theme_name));
      $head_elements['adaptivetheme_meta_mobileoptimized'] = array(
        '#type' => 'html_tag',
        '#tag' => 'meta',
        '#attributes' => array(
          'name' => "MobileOptimized",
          'content' => $adaptivetheme_meta_mobileoptimized,
        ),
        '#weight' => 2,
      );
      // HandheldFriendly
      $adaptivetheme_meta_handheldfriendly = filter_xss_admin(at_get_setting('adaptivetheme_meta_handheldfriendly', $theme_name));
      $head_elements['adaptivetheme_meta_handheldfriendly'] = array(
        '#type' => 'html_tag',
        '#tag' => 'meta',
        '#attributes' => array(
          'name' => "HandheldFriendly",
          'content' => $adaptivetheme_meta_handheldfriendly,
        ),
        '#weight' => 3,
      );
      // apple-mobile-web-app-capable
      $adaptivetheme_meta_apple_mobile_web_app_capable = filter_xss_admin(at_get_setting('adaptivetheme_meta_apple_mobile_web_app_capable', $theme_name));
      $head_elements['adaptivetheme_meta_apple_mobile_web_app_capable'] = array(
        '#type' => 'html_tag',
        '#tag' => 'meta',
        '#attributes' => array(
          'name' => "apple-mobile-web-app-capable",
          'content' => $adaptivetheme_meta_apple_mobile_web_app_capable,
        ),
        '#weight' => 4,
      );
    }
  }
  if (at_get_setting('chrome_edge', $theme_name) === 1) {
    // cleartype
    $head_elements['adaptivetheme_meta_cleartype'] = array(
      '#type' => 'html_tag',
      '#tag' => 'meta',
      '#attributes' => array(
        'http-equiv' => "cleartype",
        'content' => "on",
      ),
      '#weight' => 5,
    );
    // X-UA-Compatible
    $head_elements['adaptivetheme_meta_x_ua_compatible'] = array(
      '#type' => 'html_tag',
      '#tag' => 'meta',
      '#attributes' => array(
        'http-equiv' => "X-UA-Compatible",
        'content' => "IE=edge, chrome=1",
      ),
      '#weight' => 6,
    );
  }
  // Apple touch icons
  if (at_get_setting('enable_apple_touch_icons') === 1) {
    // low
    $apple_touch_icon_path_l = filter_xss_admin(at_get_setting('apple_touch_icon_path_l', $theme_name));
    if (!empty($apple_touch_icon_path_l)) {
      $l = drupal_get_path('theme', $theme_name) .'/'. $apple_touch_icon_path_l;
      $touch_icon_l = file_create_url($l);
      $head_elements['adaptivetheme_touch_icon_nokia'] = array(
        '#type' => 'html_tag',
        '#tag' => 'link',
        '#weight' => -97,
        '#attributes' => array(
          'href' => $touch_icon_l,
          'rel' => "shortcut icon",
        ),
      );
      $head_elements['adaptivetheme_touch_icon_low'] = array(
        '#type' => 'html_tag',
        '#tag' => 'link',
        '#weight' => -98,
        '#attributes' => array(
          'href' => $touch_icon_l,
          'rel' => "apple-touch-icon-processed",
        ),
      );
    }
    // medium
    $apple_touch_icon_path_m = filter_xss_admin(at_get_setting('apple_touch_icon_path_m', $theme_name));
    if (!empty($apple_touch_icon_path_m)) {
      $m = drupal_get_path('theme', $theme_name) .'/'. $apple_touch_icon_path_m;
      $touch_icon_m = file_create_url($m);
      $head_elements['adaptivetheme_touch_icon_medium'] = array(
        '#type' => 'html_tag',
        '#tag' => 'link',
        '#weight' => -99,
        '#attributes' => array(
          'href' => $touch_icon_m,
          'rel' => "apple-touch-icon-processed",
          'sizes' => "72x72",
        ),
      );
    }
    // high
    $apple_touch_icon_path_h = filter_xss_admin(at_get_setting('apple_touch_icon_path_h', $theme_name));
    if (!empty($apple_touch_icon_path_h)) {
      $h = drupal_get_path('theme', $theme_name) .'/'. $apple_touch_icon_path_h;
      $touch_icon_h = file_create_url($h);
      $head_elements['adaptivetheme_touch_icon_high'] = array(
        '#type' => 'html_tag',
        '#tag' => 'link',
        '#weight' => -100,
        '#attributes' => array(
          'href' => $touch_icon_h,
          'rel' => "apple-touch-icon-processed",
          'sizes' => "114x114",
        ),
      );
    }
  }
}

/**
 * hook_js_alter()
 */
function adaptivetheme_js_alter(&$javascript) {
  // Use our own vesion of vertical-tabs.js for better error handling
  // @see http://drupal.org/node/607752
  if (isset($javascript['misc/vertical-tabs.js'])) {
    $file = drupal_get_path('theme', 'adaptivetheme') . '/scripts/vertical-tabs.js';
    $javascript['misc/vertical-tabs.js'] = drupal_js_defaults($file);
  }
}

/**
 * hook_css_alter()
 */
function adaptivetheme_css_alter(&$css) {
  global $theme_key, $language;

  // Never allow this to run in our admin theme and only if the extension is enabled.
  if (at_get_setting('enable_exclude_css') === 1 && $theme_key !== 'adaptivetheme_admin') {
    // Get $css_data from the cache
    if ($cache = cache_get('at_get_css_files')) {
      $css_data = $cache->data;
    }
    else {
      $css_data = at_get_css_files($theme_key);
    }
    // We need the right theme name to get the theme settings
    $_get_active_theme_data = array_pop($css_data);
    if ($_get_active_theme_data['type'] == 'theme') {
      $theme_name = $_get_active_theme_data['source'];
    }
    else {
      $theme_name = $theme_key;
    }
    foreach ($css_data as $key => $value) {
      $setting = 'unset_css_' . drupal_html_class($key);
      if (theme_get_setting($setting, $theme_name) === 1) {
        if (isset($css[$key])) {
          unset($css[$key]);
        }
      }
    }
    // Unset -rtl.css files if language dir is RTL
    if ($language->dir === 'rtl') {
      foreach ($css_data as $key => $value) {
        $setting = 'unset_css_' . drupal_html_class($key);
        if (theme_get_setting($setting, $theme_name) === 1) {
          $key = str_replace('.css', '-rtl.css', $key);
          if (isset($css[$key])) {
            unset($css[$key]);
          }
        }
      }
    }
  }
}

/**
 * hook_page_alter()
 */
function adaptivetheme_page_alter(&$page) {
  // Look in each visible region for blocks.
  foreach (system_region_list($GLOBALS['theme'], REGIONS_VISIBLE) as $region => $name) {
    if (!empty($page[$region])) {
      // Find the last block in the region.
      $blocks = array_reverse(element_children($page[$region]));
      while ($blocks && !isset($page[$region][$blocks[0]]['#block'])) {
        array_shift($blocks);
      }
      if ($blocks) {
        $page[$region][$blocks[0]]['#block']->last_in_region = TRUE;
      }
    }
  }
}

/**
 * hook_form_FORM_alter()
 */
function adaptivetheme_form_alter(&$form, &$form_state, $form_id) {
  // Collapse Noggin fieldset by default
  if ($form_id == 'system_theme_settings') {
    if (module_exists('noggin')) {
      $form['noggin']['#collapsible'] = TRUE;
      $form['noggin']['#collapsed'] = TRUE;
    }
  }
}

/**
 * hook_form_FORM_ID_alter()
 */
function adaptivetheme_form_search_form_alter(&$form, $form_state) {

  // The problem with Drupals standard Advanced search form is that each
  // criterion group is wrapped in a DIV, whereas it should be a fieldset with
  // a legend, this is better semantics and improves accessibility by
  // logically grouping field items.
  if (at_get_setting('adv_search_extra_fieldsets') === 1) {
    if (isset($form['module']) && $form['module']['#value'] == 'node' && user_access('use advanced search')) {
      // Keyword boxes:
      $form['advanced'] = array(
        '#type' => 'fieldset',
        '#title' => t('Advanced search'),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
        '#attributes' => array('class' => array('search-advanced')),
      );
      $form['advanced']['keywords-fieldset'] = array(
        '#type' => 'fieldset',
        '#title' => t('Keywords'),
        '#collapsible' => FALSE,
      );
      $form['advanced']['keywords-fieldset']['keywords'] = array(
        '#prefix' => '<div class="criterion">',
        '#suffix' => '</div>',
      );
      $form['advanced']['keywords-fieldset']['keywords']['or'] = array(
        '#type' => 'textfield',
        '#title' => t('Containing any of the words'),
        '#size' => 30,
        '#maxlength' => 255,
      );
      $form['advanced']['keywords-fieldset']['keywords']['phrase'] = array(
        '#type' => 'textfield',
        '#title' => t('Containing the phrase'),
        '#size' => 30,
        '#maxlength' => 255,
      );
      $form['advanced']['keywords-fieldset']['keywords']['negative'] = array(
        '#type' => 'textfield',
        '#title' => t('Containing none of the words'),
        '#size' => 30,
        '#maxlength' => 255,
      );
      // Node types:
      $types = array_map('check_plain', node_type_get_names());
      $form['advanced']['types-fieldset'] = array(
        '#type' => 'fieldset',
        '#title' => t('Types'),
        '#collapsible' => FALSE,
      );
      $form['advanced']['types-fieldset']['type'] = array(
        '#type' => 'checkboxes',
        '#prefix' => '<div class="criterion">',
        '#suffix' => '</div>',
        '#options' => $types,
      );
      $form['advanced']['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Advanced search'),
        '#prefix' => '<div class="action advanced-search-submit">',
        '#suffix' => '</div>',
        '#weight' => 99,
      );
      // Languages:
      $language_options = array();
      foreach (language_list('language') as $key => $entity) {
        $language_options[$key] = $entity->name;
      }
      if (count($language_options) > 1) {
        $form['advanced']['lang-fieldset'] = array(
          '#type' => 'fieldset',
          '#title' => t('Languages'),
          '#collapsible' => FALSE,
          '#collapsed' => FALSE,
        );
        $form['advanced']['lang-fieldset']['language'] = array(
          '#type' => 'checkboxes',
          '#prefix' => '<div class="criterion">',
          '#suffix' => '</div>',
          '#options' => $language_options,
        );
      }
      $form['#validate'][] = 'node_search_validate';
    }
  }
}

/**
 * hook_form_BASE_FORM_ID_alter()
 */
function adaptivetheme_form_node_form_alter(&$form, &$form_state, $form_id) {
  // Remove if #1245218 is backported to D7 core.
  foreach (array_keys($form) as $item) {
    if (strpos($item, 'field_') === 0) {
      if (!empty($form[$item]['#attributes']['class'])) {
        foreach ($form[$item]['#attributes']['class'] as &$class) {
          if (strpos($class, 'field-type-') === 0 || strpos($class, 'field-name-') === 0) {
            // Make the class different from that used in theme_field().
            $class = $class . '-form';
          }
        }
      }
    }
  }
}

/**
 * Set a class on the iframe body element for WYSIWYG editors. This allows you
 * to easily override the background for the iframe body element.
 * This only works for the WYSIWYG module: http://drupal.org/project/wysiwyg
 */
function adaptivetheme_wysiwyg_editor_settings_alter(&$settings, &$context) {
  $settings['bodyClass'] = 'wysiwygeditor';
}

/* debug
function adaptivetheme_block_view_alter(&$data, $block) {
  dsm($data);
  dsm($block);
}
*/
