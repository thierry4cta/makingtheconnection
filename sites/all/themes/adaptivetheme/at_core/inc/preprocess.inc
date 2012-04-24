<?php
/**
 * All Preprocess functions for templates and theme fucntions.
 * If you need to add or modify preprocess functions do it in your sub-theme.
 */

/**
 * Preprocess variables for html.tpl.php
 */
function adaptivetheme_preprocess_html(&$vars, $hook) {
  global $theme_key, $language;
  $theme_name = $theme_key;

  // Set some paths
  $path_to_at_core = drupal_get_path('theme', 'adaptivetheme');
  $vars['base_path'] = base_path();

  // Get the info file data
  $info = at_get_info($theme_name);

  // DOCTYPE
  // AT no longer uses doctype switching or $rdf_profile, these maintain
  // backwards compatibility with pre 7.x-2.1 versions of html.tpl.php
  $vars['doctype'] = '<!DOCTYPE html>' . "\n";
  $vars['rdf_profile'] = '';

  // Clean up the lang attributes.
  $vars['html_attributes'] = 'lang="' . $language->language . '" dir="' . $language->dir . '"';

  // Set the path to the directory where our CSS files are saved
  $path = variable_get('theme_' . $theme_name . '_files_directory');

  // Load Layout
  load_layout_css($path, $theme_name);

  // Load Responsive Styles.
  if (at_get_setting('disable_responsive_styles', $theme_name) === 0) {
    load_responsive_css($path, $theme_name);
  }

  // Load fonts and/or Custom CSS
  if(at_get_setting('enable_extensions', $theme_name) === 1) {

    if (at_get_setting('enable_font_settings', $theme_name) === 1) {
      load_fonts($path, $theme_name);
    }

    if (at_get_setting('enable_custom_css', $theme_name) === 1) {
      load_custom_css($path, $theme_name);
    }
  }

  // Load Extension Settings CSS
  load_extensions_css($theme_name);

  // Build an array of polyfilling scripts
  $vars['polyfills_array'] = '';
  $vars['polyfills_array'] = load_polyfills($theme_name, $vars);

  // Set the skip link target id
  $vars['skip_link_target'] = '#main-content';
  if (at_get_setting('skip_link_target', $theme_name)) {
    $skip_link_target = at_get_setting('skip_link_target', $theme_name);
    $vars['skip_link_target'] = check_plain($skip_link_target);
  }

  // Generate body classes
  if ($html_classes = generate_html_classes($vars, $theme_name)) {
    foreach ($html_classes as $class_name) {
      $vars['classes_array'][] = $class_name;
    }
  }

  // Do some legacy stuff for 7.x-2.x themes that have google webfonts running
  // on the old system. Scan for the existence of a "release" key and
  // conditionally load google.web.fonts.inc
  if (!isset($info['release']) || $info['release'] === '7.x-2.x') {
    include_once($path_to_at_core . '/inc/google.web.fonts.inc');
  }

  // Load debuggers if enabled.
  if (
    at_get_setting('expose_regions', $theme_name) === 1 ||
    at_get_setting('load_all_panels', $theme_name) === 1 ||
    at_get_setting('show_window_size', $theme_name) === 1) {
    load_debuggers($theme_name);
  }
}

/**
 * Preprocess variables for page.tpl.php
 */
function adaptivetheme_preprocess_page(&$vars, $hook) {
  global $theme_key;
  $theme_name = $theme_key;

  // Set up logo element
  if (at_get_setting('toggle_logo', $theme_name) === 1) {
    $vars['site_logo'] = drupal_static('adaptivetheme_preprocess_page_site_logo');
    if (empty($vars['site_logo'])) {
      $logo_path = check_url($vars['logo']);
      $logo_alt = check_plain(variable_get('site_name', t('Site logo')));
      $logo_vars = array('path' => $logo_path, 'alt' => $logo_alt, 'attributes' => array('class' => 'site-logo'));
      $logo_img = theme('image', $logo_vars);
      $vars['site_logo'] = $logo_img ? l($logo_img, '<front>', array('attributes' => array('title' => t('Home page')), 'html' => TRUE)) : '';
    }
    // Maintain backwards compatibility with 7.x-2.x sub-themes
    $vars['logo_img'] = isset($logo_img) ? $logo_img : '';
    $vars['linked_site_logo'] = $vars['site_logo'];
  }
  else {
    $vars['site_logo'] = '';
  }

  // Site name
  $vars['site_name'] = &drupal_static('adaptivetheme_preprocess_page_site_name');
  if (empty($vars['site_name'])) {
    $sitename = variable_get('site_name', 'Drupal');
    $vars['site_name'] = l($sitename, '<front>', array('attributes' => array('title' => t('Home page'))));
  }

  // Hide the site name if toggled off, don't remove it
  if (at_get_setting('toggle_name', $theme_name) === 0) {
    $vars['visibility'] = 'element-invisible';
    $vars['hide_site_name'] = TRUE;
  }
  else {
    $vars['visibility'] = '';
    $vars['hide_site_name'] = FALSE;
  }

  // Site Name and Slogan classes
  if(at_get_setting('enable_heading_settings', $theme_name) === 1) {
    $heading_settings_array = &drupal_static('adaptivetheme_preprocess_page_heading_settings');
    $sitename_classes = array();
    $slogan_classes = array();
    if (empty($heading_settings_array)) {
      if ($vars['hide_site_name'] == FALSE) {
        $sitename_classes = array('site_name_case', 'site_name_weight', 'site_name_alignment', 'site_name_shadow');
        $heading_settings_array = $sitename_classes;
      }
      if ($vars['site_slogan']) {
        $slogan_classes = array('site_slogan_case', 'site_slogan_weight', 'site_slogan_alignment', 'site_slogan_shadow');
        $heading_settings_array = array_merge($sitename_classes, $slogan_classes);
      }
    }
    if (!empty($heading_settings_array)) {
      foreach ($heading_settings_array as $setting) {
        if ($heading_setting = at_get_setting($setting, $theme_name)) {
          $vars['classes_array'][] = $heading_setting;
        }
      }
    }
  }

  // Build a variable for the main menu
  if (isset($vars['main_menu'])) {
    $vars['primary_navigation'] = theme('links', array(
      'links' => $vars['main_menu'],
      'attributes' => array(
        'class' => array('menu', 'primary-menu', 'clearfix'),
       ),
      'heading' => array(
        'text' => t('Main menu'),
        'level' => 'h2',
        'class' => array('element-invisible'),
      )
    ));
  }

  // Build a variable for the secondary menu
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

  // Build variables for Primary and Secondary local tasks
  $vars['primary_local_tasks'] = menu_primary_local_tasks();
  $vars['secondary_local_tasks'] = menu_secondary_local_tasks();

  // Add back the $search_box var to D7
  if (module_exists('search')) {
    $search_box = drupal_get_form('search_form');
    $vars['search_box'] = '<div id="search-box">' . drupal_render($search_box) . '</div>';
  }

  // Remove the infernal feed icons
  if (at_get_setting('feed_icons_hide', $theme_name) === 1) {
    $vars['feed_icons'] = '';
  }

  // Remove block system main, just from the front page
  if (drupal_is_front_page()) {
    if (at_get_setting('unset_block_system_main_front', $theme_name) === 1) {
      $vars['page']['content']['system_main'] = ''; // Brutal but effective
    }
  }

  // Attribution variable used in admin theme and some others
  $vars['attribution'] = "<small class=\"attribution\"><a href=\"http://adaptivethemes.com\">Premium Drupal Themes</a></small>";

  // Work around a perculier bug/feature(?) in Drupal 7 which incorrectly sets
  // the page title to "User account" for all three of these pages.
  if (arg(0) === 'user') {
    if (arg(1) === 'login' || arg(1) == '') {
      drupal_set_title(t('User login'));
    }
    if (arg(1) === 'password') {
      drupal_set_title(t('Request new password'));
    }
    if (arg(1) === 'register') {
      drupal_set_title(t('Create new account'));
    }
  }
}

/**
 * Preprocess variables for region.tpl.php
 */
function adaptivetheme_preprocess_region(&$vars, $hook) {

  // Add a "sidebar" class to sidebar regions
  if (strpos($vars['region'], 'sidebar_') === 0) {
    $vars['classes_array'][] = 'sidebar';
  }

  // Add classes to conditional stack regions in Gpanel regions, in the Panels layout plugins these are hard coded.
  $conditional_stack_regions = &drupal_static(__FUNCTION__, array());
  if (empty($conditional_stack_regions)) {
    $conditional_stack_regions = array(
      'three_25_25_50_top',
      'three_25_25_50_bottom',
      'three_25_50_25_top',
      'three_25_50_25_bottom',
      'three_50_25_25_top',
      'three_50_25_25_bottom',
      'three_33_top',
      'three_33_bottom',
      'two_50_top',
      'two_50_bottom',
      'two_33_66_top',
      'two_33_66_bottom',
      'two_66_33_top',
      'two_66_33_bottom',
      'two_brick_top',
      'two_brick_middle',
      'two_brick_bottom',
      'threecol_inset_left_top',
      'threecol_inset_left_bottom',
      'threecol_inset_right_top',
      'threecol_inset_right_bottom',
    );
  }
  if (in_array($vars['region'], $conditional_stack_regions)) {
    $vars['classes_array'][] = 'region-conditional-stack';
  }
}

/**
 * Preprocess variables for block.tpl.php
 */
function adaptivetheme_preprocess_block(&$vars, $hook) {
  global $theme_key;
  $theme_name = $theme_key;

  // The menu bar region gets special treatment for the block template
  if ($vars['block']->region === 'menu_bar') {
    // Hide titles, very unlikey to want it show, ever
    $vars['title_attributes_array']['class'][] = 'element-invisible';
    $vars['classes_array'][] = 'menu-wrapper menu-bar-wrapper clearfix';
  }

  // Add extra classes if required
  if (at_get_setting('extra_block_classes', $theme_name) === 1) {

    // Zebra
    $vars['classes_array'][] = $vars['block_zebra'];

    // Position?
    if ($vars['block_id'] === 1) {
      $vars['classes_array'][] = 'first';
    }
    if (isset($vars['block']->last_in_region)) {
      $vars['classes_array'][] = 'last';
    }

    // Count
    $vars['classes_array'][] = 'block-count-' . $vars['id'];

    // Region
    $vars['classes_array'][] = drupal_html_class('block-region-' . $vars['block']->region);

    // Delta
    $vars['classes_array'][] = drupal_html_class('block-' . $vars['block']->delta);
  }

  // Add title style classes, these are loaded via the classes_array and not
  // title_attributes_array so we can style the whole block depending on the
  // title styles.
  if (isset($vars['block']->subject)) {
    if(at_get_setting('enable_heading_settings', $theme_name) === 1) {
      $settings_array = &drupal_static('adaptivetheme_preprocess_block_heading_settings');
      if (empty($settings_array)) {
        $settings_array = array('block_title_case', 'block_title_weight', 'block_title_alignment', 'block_title_shadow');
      }
      foreach ($settings_array as $setting) {
        if ($heading_setting = at_get_setting($setting, $theme_name)) {
          $vars['classes_array'][] = $heading_setting;
        }
      }
    }
  }

  // Add classes to theme the horizontal block option
  if (at_get_setting('horizontal_login_block', $theme_name) === 1 &&
    $vars['block']->module === 'user' &&
    $vars['block']->delta === 'login')
    {
    $vars['classes_array'][] = 'lb-h';
  }
  if (at_get_setting('slider_login_block', $theme_name) === 1 &&
    $vars['block']->module === 'user' &&
    $vars['block']->delta === 'login')
    {
    $vars['classes_array'][] = 'lb-s';
  }

  // Give our block titles and content some additional class
  $vars['title_attributes_array']['class'][] = 'block-title';
  $vars['content_attributes_array']['class'][] = 'block-content';
  $vars['content_attributes_array']['class'][] = 'content';

  // Add Aria Roles via attributes
  switch ($vars['block']->module) {
    case 'system':
      switch ($vars['block']->delta) {
        case 'main':
          // Note: the "main" role goes in the page.tpl, not here.
          break;
        case 'help':
        case 'powered-by':
          $vars['attributes_array']['role'] = 'complementary';
          break;
        default:
          // Any other "system" block is a menu block.
          $vars['attributes_array']['role'] = 'navigation';
          break;
      }
      break;
    case 'menu':
    case 'menu_block':
    case 'blog':
    case 'book':
    case 'comment':
    case 'forum':
    case 'shortcut':
    case 'statistics':
      $vars['attributes_array']['role'] = 'navigation';
      break;
    case 'search':
      $vars['attributes_array']['role'] = 'search';
      break;
    case 'help':
    case 'aggregator':
    case 'locale':
    case 'poll':
    case 'profile':
      $vars['attributes_array']['role'] = 'complementary';
      break;
    case 'node':
      switch ($vars['block']->delta) {
        case 'syndicate':
          $vars['attributes_array']['role'] = 'complementary';
          break;
        case 'recent':
          $vars['attributes_array']['role'] = 'navigation';
          break;
      }
      break;
    case 'user':
      switch ($vars['block']->delta) {
        case 'login':
          $vars['attributes_array']['role'] = 'form';
          break;
        case 'new':
        case 'online':
          $vars['attributes_array']['role'] = 'complementary';
          break;
      }
      break;
  }
}

/**
 * Preprocess variables for node.tpl.php
 */
function adaptivetheme_preprocess_node(&$vars, $hook) {
  global $theme_key;
  $theme_name = $theme_key;

  // article class to attempt backwards compatibility
  $vars['classes_array'][] = 'article';

  // Extra classes if required
  if (at_get_setting('extra_article_classes', $theme_name) === 1) {

    // Zebra
    $vars['classes_array'][] = $vars['zebra'];

    // Langauge
    if (module_exists('translation')) {
      if ($vars['node']->language) {
        $vars['classes_array'][] = 'node-lang-' . $vars['node']->language;
      }
    }

    // User picture?
    if ($vars['display_submitted'] && !empty($vars['picture'])) {
      $vars['classes_array'][] = 'node-with-picture';
    }

    // Class for each view mode, core assumes we only need to target teasers but neglects custom view modes or full
    if ($vars['view_mode'] !== 'teaser') {
      $vars['classes_array'][] = drupal_html_class('node-' . $vars['view_mode']);
    }
  }

  // Add title style classes, as per blocks these are added to classes_array not title_attraibutes_array
  // so we can style the entire node based on how the title wants to be handled (such as alignmment)
  if (isset($vars['title'])) {
    if(at_get_setting('enable_heading_settings', $theme_name) === 1) {
      $settings_array = &drupal_static('adaptivetheme_preprocess_node_heading_settings');
      if (empty($settings_array)) {
        $settings_array = array('node_title_case', 'node_title_weight', 'node_title_alignment', 'node_title_shadow');
      }
      foreach ($settings_array as $setting) {
        if ($heading_setting = at_get_setting($setting, $theme_name)) {
          $vars['classes_array'][] = $heading_setting;
        }
      }
    }
  }

  // ARIA Role
  $vars['attributes_array']['role'][] = 'article';

  // Title and content classes
  $vars['title_attributes_array']['class'][] = 'node-title';
  $vars['content_attributes_array']['class'][] = 'node-content';

  // Build the submitted by and time elements
  $vars['datetime'] = format_date($vars['created'], 'custom', 'Y-m-d\TH:i:s\Z'); // PHP 'c' format is not proper ISO8601!
  if (variable_get('node_submitted_' . $vars['node']->type, TRUE)) {
    $vars['submitted'] = t('Submitted by !username on !datetime',
      array(
        '!username' => $vars['name'],
        '!datetime' => '<time datetime="' . $vars['datetime'] . '" pubdate="pubdate">' . $vars['date'] . '</time>',
      )
    );
  }
  else {
    $vars['submitted'] = '';
  }

  // Unpublised?
  $vars['unpublished'] = '';
  if (!$vars['status']) {
    $vars['unpublished'] = '<p class="unpublished">' . t('Unpublished') . '</p>';
  }
}

/**
 * Preprocess variables for comment.tpl.php
 */
function adaptivetheme_preprocess_comment(&$vars, $hook) {
  global $theme_key;
  $theme_name = $theme_key;

  // Extra comment classes if required
  if (at_get_setting('extra_comment_classes', $theme_name) === 1) {

    // Zebra
    $vars['classes_array'][] = $vars['zebra'];

    // Position?
    if ($vars['id'] === 1) {
      $vars['classes_array'][] = 'first';
    }
    if ($vars['id'] === $vars['node']->comment_count) {
      $vars['classes_array'][] = 'last';
    }

    // Title hidden?
    if (at_get_setting('comments_hide_title', $theme_name) === 1) {
      $vars['classes_array'][] = 'comment-title-hidden';
    }

    // User picture?
    if (isset($vars['picture'])) {
      $vars['classes_array'][] = 'comment-with-picture';
    }

    // Signature?
    if (isset($vars['signature'])) {
      $vars['classes_array'][] = 'comment-with-signature';
    }
  }

  // Classes for comment title
  $vars['title_attributes_array']['class'][] = 'comment-title';

  // Title hidden?
  if (at_get_setting('comments_hide_title', $theme_name) === 1) {
    $vars['title_attributes_array']['class'][] = 'element-invisible';
  }

  // Add title style classes
  if (at_get_setting('comments_hide_title', $theme_name) !== 1) {
    if(at_get_setting('enable_heading_settings', $theme_name) === 1) {
      $settings_array = &drupal_static('adaptivetheme_preprocess_comment_heading_settings');
      if (empty($settings_array)) {
        $settings_array = array('comment_title_case', 'comment_title_weight', 'comment_title_alignment', 'comment_title_shadow');
      }
      foreach ($settings_array as $setting) {
        if ($heading_setting = at_get_setting($setting, $theme_name)) {
          $vars['classes_array'][] = $heading_setting;
        }
      }
    }
  }

  // Classes for comment content
  $vars['content_attributes_array']['class'][] = 'comment-content';

  // Build the submitted by and time elements
  $uri = entity_uri('comment', $vars['comment']);
  $uri['options'] += array('attributes' => array('rel' => 'bookmark'));
  $vars['title'] = l($vars['comment']->subject, $uri['path'], $uri['options']);
  $vars['permalink'] = l(t('Permalink'), $uri['path'], $uri['options']); // Permalinks are embedded in the time element, aka Wordpress
  $vars['created'] = '<span class="date-time permalink">' . l($vars['created'], $uri['path'], $uri['options']) . '</span>';
  $vars['datetime'] = format_date($vars['comment']->created, 'custom', 'Y-m-d\TH:i:s\Z'); // Generate the timestamp, PHP "c" format is wrong
  $vars['submitted'] = t('Submitted by !username on !datetime',
    array(
      '!username' => $vars['author'],
      '!datetime' => '<time datetime="' . $vars['datetime'] . '" pubdate="pubdate">' . $vars['created'] . '</time>',
    )
  );

  // Unpublished?
  $vars['unpublished'] = '';
  if ($vars['status'] === 'comment-unpublished') {
    $vars['unpublished'] = '<p class="unpublished">' . t('Unpublished') . '</p>';
  }
}

/**
 * Preprocess variables for the search block form.
 */
function adaptivetheme_preprocess_search_block_form(&$vars, $hook) {
  // Changes the search form to use the "search" input element attribute (HTML5)
  // We have to replace the string because FAPI don't know what type=search is, i.e.
  // no way we can do this in a form alter hook.
  $vars['search_form'] = str_replace('type="text"', 'type="search"', $vars['search_form']);
}

/**
 * Preprocess variables for field.tpl.php
 */
function adaptivetheme_preprocess_field(&$vars) {
  global $theme_key;
  $theme_name = $theme_key;

  $element = $vars['element'];

  // add a view mode class to fields
  $vars['classes_array'][] = 'view-mode-' . $element['#view_mode'];

  // provide an variable we can use to test the view mode inside templates, I found
  // $element['#view_mode'] impossible to get to inside the template, which may be a
  // lack of understanding of render arrays and how we can access variables, or that
  // Drupal theme layer is so horribly inconsistant it drives me insane.
  $vars['field_view_mode'] = $element['#view_mode'] ? $element['#view_mode'] : '';

  // enable captioning capability for image fields
  if ($element['#field_type'] === 'image') {
    $vars['image_caption_teaser'] = FALSE;
    $vars['image_caption_full'] = FALSE;
    if (at_get_setting('image_caption_teaser', $theme_name) === 1) {
      $vars['image_caption_teaser'] = TRUE;
    }
    if (at_get_setting('image_caption_full', $theme_name) === 1) {
      $vars['image_caption_full'] = TRUE;
    }
  }
}

/**
 * Preprocess variables for aggregator-item.tpl.php
 */
function adaptivetheme_preprocess_aggregator_item(&$vars, $hook) {
  $item = $vars['item'];
  // We want the same highly accurate time stamp feature as nodes and comments
  $vars['datetime'] = format_date($item->timestamp, 'custom', 'Y-m-d\TH:i:s\Z');

  // Give our aggregator items some class
  $vars['classes_array'][] = 'feed-item clearfix';
  $vars['title_attributes_array']['class'][] = 'title feed-item-title';
  $vars['content_attributes_array']['class'][] = 'content feed-item-content';
}

/**
 * Preprocess variables for maintenance-page.tpl.php
 */
function adaptivetheme_preprocess_maintenance_page(&$vars, $hook) {
  $vars['attribution'] = "<small id=\"attribution\"><a href=\"http://adaptivethemes.com\">Premium Drupal Themes</a></small>";
}

/**
 * Preprocess variables for adaptivtheme_menubar()
 */
function adaptivetheme_preprocess_menubar(&$vars, $hook) {
  $type = $vars['type'];
  $vars['menubar_id'] = $type . '-menu-bar';
  $vars['classes_array'][] = 'nav clearfix';
  $vars['content_attributes_array']['role'][] = 'navigation';
  $vars['content_attributes_array']['class'][] = $type .'-menu-wrapper menu-wrapper clearfix';
  $vars['theme_hook_suggestions'][] = 'menubar__' . $type;
}
