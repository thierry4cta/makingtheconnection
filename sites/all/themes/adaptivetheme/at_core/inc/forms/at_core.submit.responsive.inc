<?php

  // Responsive Layouts and Styles
  $layout_variables = page_layout(); // Get the page layout config array
  $layouts = array(); // $layouts will hold all the page level layouts

  $is_default_layout = $values['global_default_layout']; // Initialize the $is_default_layout variable, we use this to test against

  $rpl = responsive_panels_data_structure(); //responsive_panels(); // Get the panels config array
  $float = ".at-panel .region {display:inline;float:left}"; // Some layouts generate their Panels CSS, we need to add a float delcaration for them

  $responsive_styles = array(); // Holds all the styles from the responsive stylesheets, wrapped in media queries

  // Get the values for the panels layouts
  unset($rpl['one']); // unset panels layout one, it has no layout data and we never use it
  foreach ($rpl as $grouped => $panels_layout_groups) {
    foreach ($panels_layout_groups as $panel_layout_group) {
      foreach ($panel_layout_group as $group_items => $item_value) {
        $panel_subtypes[] = $item_value['theme'];
        if (array_key_exists('styles', $item_value)) {
          $panel_styles[] = $item_value['styles'];
        }
      }
    }
  }

  // If the Cascading media queries CSS file is enabled, load these styles first
  if ($values['enable_cascading_media_queries'] === 1) {
    $responsive_css = drupal_load_stylesheet($path_to_responsive_css . 'responsive.cascade.css', FALSE);
    $responsive_styles[] = $responsive_css . "\n";
  }

  // Gutter width
  $gutters = "/* Gutters are not currently overridden in theme settings, but may be in theme CSS */";
  if(isset($values['enable_extensions']) && $values['enable_extensions'] === 1) {
    if (isset($values['enable_markup_overides']) && $values['enable_markup_overides'] === 1) {
      if (isset($values['global_gutter_width'])) {
        $gutter = $values['global_gutter_width'] . 'px';
        $gutters = "/* Gutters */" . "\n" .  "#main-content,.block-inner,.pane-inner,.menu-wrapper,.branding-elements,.breadcrumb-wrapper,.attribution,.at-panel .rounded-corner,div.messages {margin-left:$gutter;margin-right:$gutter;}"; // #content .at-panel {margin-left:-$gutter;margin-right:-$gutter;}
      }
    }
  }

  // Smartphone Portrait
  if ($values['smartphone_portrait_media_query']) {

    $device = 'smartphone_portrait';

    // Build an array of page layout settings values
    foreach ($layout_variables as $key => $value) {
      if (isset($values["$device" . '_' . "$value"])) {
        $smartphone_portrait_layout_data[$value] = $values["$device" . '_' . "$value"];
      }
    }
    $layout = at_build_page_layout($smartphone_portrait_layout_data['layout'], $smartphone_portrait_layout_data['sidebar_first'], $smartphone_portrait_layout_data['sidebar_second'], $smartphone_portrait_layout_data['sidebar_unit']);

    $method = $smartphone_portrait_layout_data['layout'];
    $comment = "/* $device $method */\n";
    $width = "\n" . '.container {width:' . $smartphone_portrait_layout_data['page_width'] . $smartphone_portrait_layout_data['page_unit'] . '}';
    $media_query = $smartphone_portrait_layout_data['media_query'];

    // If mobile first then smartphone portrait needs to do nothing, else its
    // problematic to set the layout later due to the cascade and inheritance
    if ($is_default_layout === 'smartphone-portrait') {
      $css = "/* smartphone_portrait is default, mobile first dude - you rock the hardest! */";
    }
    else {
      // Smartphone portrait panels are all 100% width and stacked, we need to overpower the default layouts when in desktop first mode
      $smartphone_portrait_panels_layout = '.at-panel .region,.at-panel .panel-row,.at-panel .panel-row .region,.at-panel .inset-wrapper{float:none;display:block;width:100%}';
      $styles = $width . "\n" . $layout . "\n" . $smartphone_portrait_panels_layout;
      $css = $comment . '@media ' . $media_query . ' {' . $styles . "\n" . '}';
    }

    // Get and wrap the responsive CSS styles in the relative media query
    $responsive_css = drupal_load_stylesheet($path_to_responsive_css . 'responsive.smartphone.portrait.css', FALSE);
    $responsive_styles[] = '@media ' . $media_query . ' {' . "\n" . $responsive_css . "\n" . '}';

    $layouts[] = $css;
  }

  // Smartphone Landscape
  if ($values['smartphone_landscape_layout']) {

    $device = 'smartphone_landscape';

    // Build an array of page layout settings values
    foreach ($layout_variables as $key => $value) {
      if (isset($values["$device" . '_' . "$value"])) {
        $smartphone_landscape_layout_data[$value] = $values["$device" . '_' . "$value"];
      }
    }
    $layout = at_build_page_layout($smartphone_landscape_layout_data['layout'], $smartphone_landscape_layout_data['sidebar_first'], $smartphone_landscape_layout_data['sidebar_second'], $smartphone_landscape_layout_data['sidebar_unit']);

    $method = $smartphone_landscape_layout_data['layout'];
    $comment = "/* $device $method */\n";
    $width = "\n" . '.container {width:' . $smartphone_landscape_layout_data['page_width'] . $smartphone_landscape_layout_data['page_unit'] . '}';
    $media_query = $smartphone_landscape_layout_data['media_query'];

    // Get the panel layout settings
    foreach ($panel_subtypes as $subtype) {
      $smartphone_landscape_panel_settings[] = $device . '_' . $subtype;
    }
    foreach ($smartphone_landscape_panel_settings as $setting) {
      $option = $values[$setting];
      $smartphone_landscape_panels_data[] = $option;
    }
    // Generate the panels layouts
    $smartphone_landscape_panels_css = at_build_panels_layout_css($panel_styles, $smartphone_landscape_panels_data);

    $panels_layouts = $float . $smartphone_landscape_panels_css;
    $styles = $width . "\n" . $layout . "\n" . $panels_layouts;
    $css = $comment . '@media ' . $media_query . ' {' . $styles . "\n" . '}';

    // Get and wrap the responsive CSS styles in the relative media query
    $responsive_css = drupal_load_stylesheet($path_to_responsive_css . 'responsive.smartphone.landscape.css', FALSE);
    $responsive_styles[] = '@media ' . $media_query . ' {' . "\n" . $responsive_css . "\n" . '}';

    $layouts[] = $css;
  }

  // Tablet Portrait
  if ($values['tablet_portrait_layout']) {

    $device = 'tablet_portrait';

    // Build an array of page layout settings values
    foreach ($layout_variables as $key => $value) {
      if (isset($values["$device" . '_' . "$value"])) {
        $tablet_portrait_layout_data[$value] = $values["$device" . '_' . "$value"];
      }
    }
    $layout = at_build_page_layout($tablet_portrait_layout_data['layout'], $tablet_portrait_layout_data['sidebar_first'], $tablet_portrait_layout_data['sidebar_second'], $tablet_portrait_layout_data['sidebar_unit']);

    $method = $tablet_portrait_layout_data['layout'];
    $comment = "/* $device $method */\n";
    $width = "\n" . '.container {width:' . $tablet_portrait_layout_data['page_width'] . $tablet_portrait_layout_data['page_unit'] . '}';
    $media_query = $tablet_portrait_layout_data['media_query'];

    // Get the panel layout settings and CSS for these layouts
    foreach ($panel_subtypes as $subtype) {
      $tablet_portrait_panel_settings[] = $device . '_' . $subtype;
    }

    foreach ($tablet_portrait_panel_settings as $setting) {
      $option = $values[$setting];
      $tablet_portrait_panels_data[] = $option;
    }

    // Generate the panels layouts
    $tablet_portrait_panels_css = at_build_panels_layout_css($panel_styles, $tablet_portrait_panels_data);

    $panels_layouts = $float . $tablet_portrait_panels_css;
    $styles = $width . "\n" . $layout . "\n" . $panels_layouts;
    $css = $comment . '@media ' . $media_query . ' {' . $styles . "\n" . '}';

     // Get and wrap the responsive CSS styles in the relative media query
    $responsive_css = drupal_load_stylesheet($path_to_responsive_css . 'responsive.tablet.portrait.css', FALSE);
    $responsive_styles[] = '@media ' . $media_query . ' {' . "\n" . $responsive_css . "\n" . '}';

    $layouts[] = $css;
  }

  // Tablet Landscape
  if ($values['tablet_landscape_layout']) {

    $device = 'tablet_landscape';

    // Build an array of page layout settings values
    foreach ($layout_variables as $key => $value) {
      if (isset($values["$device" . '_' . "$value"])) {
        $tablet_landscape_layout_data[$value] = $values["$device" . '_' . "$value"];
      }
    }
    $layout = at_build_page_layout($tablet_landscape_layout_data['layout'], $tablet_landscape_layout_data['sidebar_first'], $tablet_landscape_layout_data['sidebar_second'], $tablet_landscape_layout_data['sidebar_unit']);

    $method = $tablet_landscape_layout_data['layout'];
    $comment = "/* $device $method */\n";
    $width = "\n" . '.container {width:' . $tablet_landscape_layout_data['page_width'] . $tablet_landscape_layout_data['page_unit'] . '}';
    $media_query = $tablet_landscape_layout_data['media_query'];

    // Get the panel layout settings
    foreach ($panel_subtypes as $subtype) {
      $tablet_landscape_panel_settings[] = $device . '_' . $subtype;
    }
    foreach ($tablet_landscape_panel_settings as $setting) {
      $option = $values[$setting];
      $tablet_landscape_panels_data[] = $option;
    }
    // Generate the panels layouts
    $tablet_landscape_panels_css = at_build_panels_layout_css($panel_styles, $tablet_landscape_panels_data);

    $panels_layouts = $float . $tablet_landscape_panels_css;
    $styles = $width . "\n" . $layout . "\n" . $panels_layouts;
    $css = $comment . '@media ' . $media_query . ' {' . $styles . "\n" . '}';

     // Get and wrap the responsive CSS styles in the relative media query
    $responsive_css = drupal_load_stylesheet($path_to_responsive_css . 'responsive.tablet.landscape.css', FALSE);
    $responsive_styles[] = '@media ' . $media_query . ' {' . "\n" . $responsive_css . "\n" . '}';

    $layouts[] = $css;
  }

  // Standard Layout (bigscreen)
  if ($values['bigscreen_layout']) {

    $device = 'bigscreen';

    // Build an array of page layout settings values
    foreach ($layout_variables as $key => $value) {
      if (isset($values["$device" . '_' . "$value"])) {
        $bigscreen_layout_data[$value] = $values["$device" . '_' . "$value"];
      }
    }
    $layout = at_build_page_layout($bigscreen_layout_data['layout'], $bigscreen_layout_data['sidebar_first'], $bigscreen_layout_data['sidebar_second'], $bigscreen_layout_data['sidebar_unit']);

    $method = $bigscreen_layout_data['layout'];
    $comment = "/* $device $method */";
    $width = "\n" . '.container {width:' . $bigscreen_layout_data['page_width'] . $bigscreen_layout_data['page_unit'] . '}';
    $media_query = $bigscreen_layout_data['media_query'];

    // Standard layout can have a max-width
    if ($values['bigscreen_set_max_width'] === 1 && $bigscreen_layout_data['page_unit'] === '%') {
      if (!empty($values['bigscreen_max_width'])) {
        $width = "\n" . '.container {width:' . $bigscreen_layout_data['page_width'] . $bigscreen_layout_data['page_unit'] . ';max-width:' . $values['bigscreen_max_width'] . $values['bigscreen_max_width_unit'] . '}';
      }
      else {
        $width = "\n" . '.container {width:' . $bigscreen_layout_data['page_width'] . $bigscreen_layout_data['page_unit'] . ';max-width:' . $values['bigscreen_max_width'] . $values['bigscreen_max_width_unit'] . '}';
      }
    }

    // Load the default panels layouts
    $panels_layouts = drupal_load_stylesheet($path_to_panels_css . 'default.css', FALSE);

    // Build a $styles variable with the layout, width and default panels layouts
    $styles = $width . "\n" . $layout . "\n" . $panels_layouts;


    // We need to do some conditional checks to account for AT's "Settings", namely:
    // - is this mobile first or desktop first?
    // - is the responsive capability disabled?


    // Mobile first or Desktop first?
    if ($is_default_layout === 'standard-layout') {

      // DESKTOP FIRST

      // $css gets a comment that bigscreen is beign used as the "default layout"
      $css = '/* The standard layout is the default layout - this is a desktop first design */';

      // Prepare a "default layout" for output to file, we must load this when desktop first is being used
      $desktop_first_layout = $gutters . "\n" . $comment . $styles . "\n";

    }
    else {

      // MOIBLE FIRST
      $css = $comment . "\n" . '@media ' . $media_query . ' {' . $styles . "\n" . '}';
      $desktop_first_layout = '/* Not likely, this is mobile first - this themer is rocking the hardest! */';
    }


    // Responsive capability OFF?
    if ($values['disable_responsive_styles'] === 1) {

      // If its off we have to load something, so we choose to use the bigscreen layout and load that
      $desktop_first_layout = $gutters . "\n" . $comment . $styles;
    }

    // add $css to the layouts array
    $layouts[] = $css;
  }
  //****** END bigscreen layout ******//

  // Internet Exploder
  // We only want to load what is absolutely required for IE, depending on the theme settings and what version we are targeting,
  // remember, this only takes care of generating the stylesheets so what you see here are lots of messages being set for the
  // themer to get a handle on what is going on, adaptivetheme_preprocess_html() is actually loading the right files under the
  // right conditions.

  // $lt_ie9_css's assigned values all come from the bigscreen layout, since its the last layout to assign values to those variables
  $lt_ie9_css = $comment . $width . "\n" . $layout . "\n" . $panels_layouts;

  // Get the lt ie8 panels layouts if enabled
  $lt_ie8_css = '/* IE6/7 percentage rounding error fixes are OFF */';
  if ($values['load_ltie8css'] === 1) {
    $ie_panels_layouts = drupal_load_stylesheet($path_to_panels_css . 'ie_defaults.css', FALSE);
    $lt_ie8_css = $ie_panels_layouts;
  }

  // Respond.js is OFF
  if ($values['load_respondjs'] === 0) {

    // should we load the IE6/7 rounding error fixes?
    if ($values['load_ltie8css'] === 1) {

      // add the E6/7 rounding error fixes to $lt_ie9_css, set a message in $lt_ie8_css
      $lt_ie9_css = $comment . $width . "\n" . $layout . "\n" . $panels_layouts . "\n" . $ie_panels_layouts;
      $lt_ie8_css = '/* The IE6/7 panels layouts are loading in the lt IE9 CSS, to save an HTTP request hit on your server */';

      // Desktop first?
      if ($is_default_layout === 'standard-layout') {
        // repopulate $lt_ie8_css
        $lt_ie8_css = $ie_panels_layouts;
      }
    }
  }

  // Respond.js is ON
  if ($values['load_respondjs'] === 1) {
    $lt_ie9_css = '/* respond.js is loading so we dont load this file. IE6, 7 and 8 will rely on respond.js to work its magic */';
  }

  // Desktop first?
  if ($is_default_layout === 'standard-layout') {
    $lt_ie9_css = '/* The standard layout is the default layout, IE styles are not required because you are doing desktop first design */';
  }

  // Responsive capability OFF?
  if ($values['disable_responsive_styles'] === 1) {
    $lt_ie9_css = '/* Responsive capabilites are disabled, we no longer need to load an IE specific layout */';
  }

  // Get and wrap the responsive CSS styles in the relative media query
  $responsive_css = drupal_load_stylesheet($path_to_responsive_css . 'responsive.desktop.css', FALSE);
  $responsive_styles[] = '@media ' . $media_query . ' {' . "\n" . $responsive_css . "\n" . '}';

  // Generate the layout and responsive styles stylesheets
  // Here we generate five files:
  // 1. $theme_name.default.layout
  // 2. $theme_name.responsive.layout
  // 3. $theme_name.lt-ie9.layout
  // 4. $theme_name.lt-ie8.layout
  // 5. $theme_name.responsive.styles
  // adaptivetheme_preprocess_html() will take care of loading the right ones when they are needed.

  // responsive layout
  $responsive_layout_data = implode("\n", $layouts);

  // Prepend the gutters to the responsive layout if we're doing mobile first
  if ($is_default_layout !== 'standard-layout') {
    $responsive_layout = $gutters . "\n" . $responsive_layout_data;
  }
  else {
    $responsive_layout = $responsive_layout_data;
  }

  // Nuke $responsive_layout if we really don't need it
  if ($values['disable_responsive_styles'] == 1) {
    $responsive_layout = '/* Responsive capabilites are disabled, only the standard layout is loaded in themename.default.layout.css */';
  }

  // IE assignments, not sure why I am doing this, could be that I meant to do something at this stage and have forgotton for now...
  $lt_ie9_layout = $lt_ie9_css;
  $lt_ie8_layout = $lt_ie8_css;

  // Aggregate the design stylesheets
  $responsive_css = implode("\n", $responsive_styles);

  // Build a keyed array: file names as key, layout data as value
  $files = array(
    "$theme_name.default.layout" => $desktop_first_layout,
    "$theme_name.responsive.layout" => $responsive_layout,
    "$theme_name.lt-ie9.layout" => $lt_ie9_layout,
    "$theme_name.lt-ie8.layout" => $lt_ie8_layout,
    "$theme_name.responsive.styles" => $responsive_css,
  );

  // Loop over the array and save each file, and we're done!
  foreach ($files as $key => $value) {
    $sanitized_values = filter_xss_admin($value); // Can contain user entered data, run final sanity checks
    $filepath = "$path/$key.css";
    file_save_data($sanitized_values, $filepath, FILE_EXISTS_REPLACE);
  }
