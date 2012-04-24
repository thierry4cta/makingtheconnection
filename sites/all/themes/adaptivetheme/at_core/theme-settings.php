<?php

// Get our plugin system functions.
require_once(drupal_get_path('theme', 'adaptivetheme') . '/inc/plugins.inc');

// We need some getters.
require_once(drupal_get_path('theme', 'adaptivetheme') . '/inc/get.inc');

/**
 * Implements hook_form_system_theme_settings_alter().
 */
function adaptivetheme_form_system_theme_settings_alter(&$form, &$form_state, $form_id = NULL) {
  $path_to_at_core = drupal_get_path('theme', 'adaptivetheme');

  // General "alters" use a form id. Settings should not be set here. The only
  // thing useful about this is if you need to alter the form for the running
  // theme and *not* the theme setting.
  // @see http://drupal.org/node/943212
  if (isset($form_id)) {
    return;
  }

  // Get the active theme name, we need it at some stage.
  $theme_name = $form_state['build_info']['args'][0];

  // Version messages
  if (at_get_setting('atcore_version_test', $theme_name) === 1) {
    $legacy_info = at_get_info($theme_name);
    // Nag users of legacy sub-themes...
    if (!isset($legacy_info['release']) || $legacy_info['release'] === '7.x-2.x') {
      $version_message = t('<p>The version of your theme is not designed to run on <a href="!link_project" target="_blank">Adaptivetheme 7.x.3.x</a>. It will probably run, but your experience will not be optimal. You have three courses of action to choose from:</p>', array('!link_project' => 'http://drupal.org/project/adaptivetheme'));
      $version_message .= t('<ol><li>Downgrade Adaptivetheme to 7.x-2.x</li><li>Upgrade your theme to the 7.x-3.x branch&thinsp;&mdash;&thinsp;you will need to check if an upgrade exists.</li><li>Add the line <code>"release = 7.x-3.x"</code> (less quotes) to your sub-themes info file and clear the cache to make this message go away.</li></ol>');
      $version_message .= t('<p>You can turn off this message in the Debug settings, look for "Sub-theme compatibility test".</p>');
      drupal_set_message($version_message, 'warning');
    }
    // Celebrate the nouveau intelligentsia...
    if (isset($legacy_info['release']) && $legacy_info['release'] === '7.x-3.x') {
      $version_message = t('<p>This theme is compatible with <a href="!link_project" target="_blank">Adaptivetheme 7.x.3.x</a>. You are good to go! You can turn off this message in the Debug settings, look for "Sub-theme compatibility test".</p>', array('!link_project' => 'http://drupal.org/project/adaptivetheme'));
      drupal_set_message($version_message, 'status');
    }
  }

  // Get the admin theme so we can set a class for styling this form,
  // variable_get() returns 0 if the admin theme is the default theme.
  $admin_theme = variable_get('admin_theme') ? variable_get('admin_theme') : $theme_name;
  $admin_theme_class = 'admin-theme-'. drupal_html_class($admin_theme);

  // LAYOUT SETTINGS
  // Build a custom header for the layout settings form.
  $logo = file_create_url(drupal_get_path('theme', 'adaptivetheme') . '/logo.png');
  $layout_header  = '<div class="at-settings-form layout-settings-form ' . $admin_theme_class . '"><div class="layout-header theme-settings-header clearfix">';
  $layout_header .= '<h1>' . t('Layout, Global Settings &amp; Polyfills') . '</h1>';
  $layout_header .= '<a href="http://adaptivethemes.com" title="Adaptivethemes.com - Rocking the hardest since 2006" target="_blank"><img class="at-logo" src="' . $logo . '" /></a>';
  $layout_header .= '</div>';

  $form['at-layout'] = array(
    '#type' => 'vertical_tabs',
    '#description' => t('Layout'),
    '#prefix' => $layout_header,
    '#suffix' => '</div>',
    '#weight' => -10,
    '#attached' => array(
      'css' => array(drupal_get_path('theme', 'adaptivetheme') . '/css/at.settings.form.css'),
    ),
  );
  // Include layout forms, global settings and debug.
  require_once($path_to_at_core . '/inc/forms/settings.pagelayout.inc');
  require_once($path_to_at_core . '/inc/forms/settings.responsivepanels.inc');
  require_once($path_to_at_core . '/inc/forms/settings.global.inc');
  require_once($path_to_at_core . '/inc/forms/settings.polyfills.inc');
  require_once($path_to_at_core . '/inc/forms/settings.debug.inc');

  // EXTENSIONS
  if (at_get_setting('enable_extensions') === 1) {

    // Build a custom header for the Extensions settings form.
    $styles_header  = '<div class="at-settings-form style-settings-form ' . $admin_theme_class . '"><div class="styles-header theme-settings-header clearfix">';
    $styles_header .= '<h1>' . t('Extensions') . '</h1>';
    $styles_header .= '</div>';

    $form['at'] = array(
      '#type' => 'vertical_tabs',
      '#weight' => -9,
      '#prefix' => $styles_header,
      '#suffix' => '</div>',
      '#states' => array(
        'visible' => array(':input[name="enable_extensions"]' => array('checked' => TRUE)),
      ),
    );

    // Include the font functions if the Fonts or Headings extensions are active.
    if (at_get_setting('enable_font_settings') === 1 || at_get_setting('enable_heading_settings') === 1) {
      include_once($path_to_at_core . '/inc/fonts.inc');
    }

    // Heading styles
    if(at_get_setting('enable_heading_settings') === 1) {
      require_once($path_to_at_core . '/inc/forms/settings.headings.inc');
    }

    // Fonts
    if(at_get_setting('enable_font_settings') === 1) {
      require_once($path_to_at_core . '/inc/forms/settings.fonts.inc');
    }

    // Heading styles
    if(at_get_setting('enable_heading_settings') === 1) {
      require_once($path_to_at_core . '/inc/forms/settings.headings.inc');
    }

    // Breadcrumbs
    if (at_get_setting('enable_breadcrumb_settings') === 1) {
      require_once($path_to_at_core . '/inc/forms/settings.breadcrumbs.inc');
    }

    // Images
    if(at_get_setting('enable_image_settings') === 1) {
      require_once($path_to_at_core . '/inc/forms/settings.images.inc');
    }

    // Horizonatal login block
    if (at_get_setting('horizontal_login_block_enable') === 'on') {
      if (at_get_setting('enable_loginblock_settings') === 1) {
        require_once($path_to_at_core . '/inc/forms/settings.loginblock.inc');
      }
    }

    // Modify output
    if (at_get_setting('enable_markup_overides') === 1) {
      require_once($path_to_at_core . '/inc/forms/settings.modifyoutput.inc');
    }

    // Exclude CSS
    if (at_get_setting('enable_exclude_css') === 1) {
      require_once($path_to_at_core . '/inc/forms/settings.cssexclude.inc');
    }

    // Metatags
    if (at_get_setting('enable_mobile_metatags') === 1) {
      require_once($path_to_at_core . '/inc/forms/settings.metatags.inc');
    }

    // Touch icons
    if (at_get_setting('enable_apple_touch_icons') === 1) {
      require_once($path_to_at_core . '/inc/forms/settings.touchicons.inc');
    }

    // Custom CSS
    if (at_get_setting('enable_custom_css') === 1) {
      require_once($path_to_at_core . '/inc/forms/settings.customcss.inc');
    }

    // Always include tweaks (extension settings)
    require_once($path_to_at_core . '/inc/forms/settings.tweaks.inc');

  }

  // Include a hidden form field with the current release information
  $form['at-release']['at_core'] = array(
    '#type' => 'hidden',
    '#default_value' => '7.x-3.x',
  );

  // Collapse annoying forms
  $form['theme_settings']['#collapsible'] = TRUE;
  $form['theme_settings']['#collapsed'] = TRUE;
  $form['logo']['#collapsible'] = TRUE;
  $form['logo']['#collapsed'] = TRUE;
  $form['favicon']['#collapsible'] = TRUE;
  $form['favicon']['#collapsed'] = TRUE;

  /**
   * Originally posted by dvessel (http://drupal.org/user/56782).
   * The following will be processed even if the theme is inactive.
   * If you are on a theme specific settings page but it is not an active
   * theme (example.com/admin/apearance/settings/THEME_NAME), it will
   * still be processed.
   *
   * Build a list of themes related to the theme specific form. If the form
   * is specific to a sub-theme, all parent themes leading to it will have
   * hook_form_theme_settings invoked. For example, if a theme named
   * 'grandchild' has its settings form in focus, the following will be invoked.
   * - parent_form_theme_settings()
   * - child_form_theme_settings()
   * - grandchild_form_theme_settings()
   *
   * If 'child' was in focus it will invoke:
   * - parent_form_theme_settings()
   * - child_form_theme_settings()
   *
   *  @see http://drupal.org/node/943212
   */
  $form_themes = array();
  $themes = list_themes();
  $_theme = $GLOBALS['theme_key'];
  while (isset($_theme)) {
    $form_themes[$_theme] = $_theme;
    $_theme = isset($themes[$_theme]->base_theme) ? $themes[$_theme]->base_theme : NULL;
  }
  $form_themes = array_reverse($form_themes);

  foreach ($form_themes as $theme_key) {
    if (function_exists($form_settings = "{$theme_key}_form_theme_settings")) {
      $form_settings($form, $form_state);
    }
  }

  // Custom validate and submit functions
  $form['#validate'][] = 'at_core_settings_validate';
  $form['#submit'][] = 'at_core_settings_submit';
}

// Include custom form validation and submit functions
require_once(drupal_get_path('theme', 'adaptivetheme') . '/inc/forms/at_core.validate.inc');
require_once(drupal_get_path('theme', 'adaptivetheme') . '/inc/forms/at_core.submit.inc');
