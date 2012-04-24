<?php
/**
 * AT's liteweight plugin sub-system.
 */
global $theme_key;
$theme_name = $theme_key;

/**
 * Find and return all plugins.
 *
 * This will search all base themes and the active theme for "plugins" in their
 * info files, and return all plugins directories. Info file entries must
 * follow the Panels plugin structure i.e.:
 * - "plugins[plugin_type][type] = path/to/plugins"
 * For example for AT page layouts we use:
 * - "plugins[page_layout][layout] = layouts/core"
 *
 * @param $theme_name, usually the active theme.
 */
function at_get_plugins($theme_name) {

  $plugins = drupal_static(__FUNCTION__, array());
  if (empty($plugins)) {
    if ($plugins_cache = cache_get('at_get_plugins_plugins')) {
      $plugins = $plugins_cache->data;
    }
    else {
      $themes_info = at_get_info_trail($theme_name);
      // Look for and get all the plugins
      if (!empty($themes_info)) {
        foreach ($themes_info as $this_theme => $theme_info) {
          foreach ($theme_info as $info) {
            if (array_key_exists('plugins', $info)) {
              foreach ($info['plugins'] as $plugin_type => $types) {
                $plugins_list[$this_theme][$plugin_type] = $types;
              }
            }
          }
        }
        array_unique($plugins_list);
        $plugins = $plugins_list;
      }
    }
    cache_set('at_get_plugins_plugins', $plugins, 'cache');
  }

  return $plugins;
}

/**
 * Return the paths to all plugin providers plugin directories, this usually
 * means themes - both base themes and sub-themes that include plugin directory
 * declarations in their info files.
 *
 * @param $theme_name, ususally the active theme.
 */
function at_get_plugins_paths($theme_name) {
  $provider_paths = array();
  $plugins_list = at_get_plugins($theme_name);

  foreach ($plugins_list as $plugin_provider => $provider) {
    foreach ($provider as $plugin_type => $types) {
      foreach ($types as $type => $path) {
        $provider_path = drupal_get_path('theme', $plugin_provider) . '/' . $path;
        $provider_paths[$plugin_provider][$plugin_type][$type] = $provider_path;
      }
    }
  }

  return $provider_paths;
}

/**
 * Returns all files for plugins of a particular type.
 * This is called from at_load_plugins(), cannot be cached else it will return
 * stale data at some point.
 *
 * @param $theme_name
 */
function at_get_plugins_files($theme_name) {
  $plugins_files = array();
  $plugins_list = at_get_plugins($theme_name);

  $extension = 'inc';
  foreach ($plugins_list as $plugin_provider => $provider) {
    foreach ($provider as $plugin_type => $types) {
      foreach ($types as $type => $path) {
        $provider_path = drupal_get_path('theme', $plugin_provider) . '/' . $path;
        $plugins_files[$plugin_provider][$plugin_type][$type] = file_scan_directory($provider_path, '/\.' . $extension . '$/', array('key' => 'name'));
      }
    }
  }

  return $plugins_files;
}

/**
 * Extract plugin data structures.
 *
 * In essence what this does is return the data strutures (arrays) for all
 * plugins of a particular type. As of now only two types are used by AT, being
 * "panels" and "page_layout". This is hard to cache because it takes the
 * $plugin_type parameter, so everything else that calls this is heavily cached
 * instead. It does support an "everything else" plugin type, whatever that is.
 *
 * @param $theme_name, usually the active theme.
 * @param $plugin_type, the plugin type you need to return, usually one of
 * "panels" or "page_layout".
 */
function at_load_plugins($theme_name, $plugin_type) {

  $plugin_data_structures = array();
  $plugins_list = at_get_plugins_files($theme_name);

  foreach ($plugins_list as $plugin_provider => $plugin_types) {
    $plugin_providers[] = $plugin_provider;
    foreach ($plugin_types as $type => $plugins) {
      if ($type === $plugin_type) {
        foreach ($plugins as $ptypes => $plugin) {
          $plugins_array[$plugin_provider][$type] = $plugin;
        }
      }
    }
  }
  $plugin_files = array();
  foreach ($plugins_array as $provider => $types) {
    foreach ($types as $key => $value) {
      $plugin_files = array_merge_recursive($plugin_files, $value);
    }
  }

  foreach ($plugin_files as $file_data) {

    include_once(DRUPAL_ROOT . '/' . $file_data->uri);

    // panels
    if ($plugin_type === 'panels') {
      foreach ($plugin_providers as $provider) {
        $identifiers[$provider] = $provider . '_' . $file_data->name . '_panels_layouts';
      }
      foreach ($identifiers as $identifier) {
        $panels_function = $identifier;
        if (function_exists($panels_function)) {
          $plugin_data_structures[] = $panels_function();
        }
      }
    }
    // page_layout
    if ($plugin_type === 'page_layout') {
      $identifier = $file_data->name;
      $page_layout_function = $identifier;
      if (function_exists($page_layout_function)) {
        $plugin_data_structures[] = $page_layout_function();
      }
    }

    // everything else
    else if ($plugin_type !== 'panels' && $plugin_type !== 'page_layout') {
      $identifier = $file_data->name;
      $function = $identifier;
      if (function_exists($function)) {
        $plugin_data_structures[] = $function();
      }
      else {
        drupal_set_message(t('You defined an existing plugin type but no functions exists that match. If you are using Panels then you must use the "function method" in your plugins, see AT Cores panel layout plugins for examples.'), 'error');
      }
    }
  }

  if (empty($plugin_data_structures)) {
    return;
  }

  return $plugin_data_structures;
}

/**
 * Return Page layout data structures.
 * This returns the full data structures for all page layout plugins. Because
 * this can be a lot of data and appears to be computationally expensive to get
 * it is cached in the cache table.
 */
function responsive_page_layouts_data_structure() {
  global $theme_name;

  $page_data_structure = drupal_static(__FUNCTION__, array());
  if (empty($page_data_structure)) {
    if ($cache = cache_get('at_page_layouts_data_structure')) {
      $page_data_structure = $cache->data;
    }
    else {

      $data_structure = at_load_plugins($theme_name, $plugin_type = 'page_layout');

      foreach ($data_structure as $plugin => $datum) {
        foreach ($datum as $method => $layout) {
          $page_data_structure[$method] = $layout;
        }
      }
      cache_set('at_page_layouts_data_structure', $page_data_structure, 'cache');
    }
  }

  return $page_data_structure;
}

/**
 * Return Panels layout data structures.
 * This returns the full data structures for all Panels layout plugins. Because
 * this can be a lot of data and appears to be computationally expensive to get
 * it is cached in the cache table.
 */
function responsive_panels_data_structure() {
  global $theme_name;

  $panels_data_structure = drupal_static(__FUNCTION__, array());
  if (empty($panels_data_structure)) {
    if ($cache = cache_get('at_panels_data_structure')) {
      $panels_data_structure = $cache->data;
    }
    else {

      $data_structure = at_load_plugins($theme_name, $plugin_type = 'panels');

      foreach ($data_structure as $plugin => $datum) {
        foreach ($datum as $key => $value) {
          $type = $value['type'];
          $panels_data_structure[$type][] = $datum;
        }
      }
      if (empty($panels_data_structure)) {
        return; // fail silently
      }
      cache_set('at_panels_data_structure', $panels_data_structure, 'cache');
    }
  }

  return $panels_data_structure;
}

/**
 * Return just the plugin names.
 * This is used primarily in one place - adaptivetheme_process_node() so we can
 * search for matches against Display Suite template suggestions, sounds weird
 * buts a work-around for a bug in Display Suite.
 *
 * @see adaptivetheme_process_node()
 * @see http://drupal.org/node/1514216
 * TODO: marked for removal due to new features in Display Suite.
 */
function responsive_panels_plugin_names() {
  $plugin_names = drupal_static(__FUNCTION__, array());
  if (empty($plugin_names)) {
    $data_structure = responsive_panels_data_structure();
    foreach ($data_structure as $key => $value) {
      foreach ($value as $type => $sub_types) {
        foreach ($sub_types as $k => $v) {
          $plugin_names[] = $k;
        }
      }
    }
  }

  return $plugin_names;
}

/**
 * Return option arrays for forms.
 * Returns the options for radio lists in the page layout settings in the
 * appearance theme settings.
 *
 * @param $theme_name
 */
function responsive_page_layouts_device_group_options($theme_name) {
  $device_group_options = drupal_static(__FUNCTION__, array());
  if (empty($device_group_options)) {
    $layout_methods = responsive_page_layouts_data_structure();
    foreach ($layout_methods as $method => $values) {
      foreach ($values as $key => $value) {
        if ($key == 'device_groups') {
          $method_values[$method] = $value;
        }
      }
    }
    foreach ($method_values as $this_method => $these_values) {
      foreach ($these_values as $k => $dv) {
        $device_group_options[$dv][] = $this_method;
      }
    }
  }

  return $device_group_options;
}

/**
 * Return all the admin css files for a plugin type.
 * Used primarly to theme the icons for each layout method. The icons are in
 * sprites.
 *
 * @param $theme_name
 * @param $plugin_type
 * TODO: add options for other plugin types, e.g. an "everything else" option.
 */
function responsive_plugins_admin_css($theme_name, $plugin_type) {
  $admin_css_files = array();
  $plugin_paths = at_get_plugins_paths($theme_name);

  foreach ($plugin_paths as $providers => $provided_types) {
    foreach ($provided_types as $provider => $type_path) {
      if ($provider === $plugin_type) {
        $admin_css_paths[$providers] = $type_path;
      }
    }
  }

  if ($plugin_type === 'panels') {
    $rpl = responsive_panels_data_structure();
    foreach ($rpl as $group => $layouts) {
      foreach ($layouts as $layout) {
        foreach ($layout as $layout_key => $value) {
          if (isset($value['admin css'])) {
            $css_files[$layout_key] = $value['admin css'];
          }
        }
      }
    }
  }

  // I have been lazy here, in fact only the three_col_grail layout sets
  // an admin css file and returns all the CSS for all page layouts.
  if ($plugin_type === 'page_layout') {
    $rpl = responsive_page_layouts_data_structure();
    foreach ($rpl as $layout_method => $value) {
      if (isset($value['admin css'])) {
        $css_files[$layout_method] = $value['admin css'];
      }
    }
  }

  foreach ($admin_css_paths as $admin_css => $paths) {
    foreach ($paths as $path) {
      foreach ($css_files as $method_key => $file_name) {
        if($method_key !== 'one') {
          $admin_css_files[] = $path . '/' . $method_key . '/' . $file_name;
        }
      }
    }
  }

  if (!isset($rpl)) {
    return; // fail quietly
  }

  return $admin_css_files;
}

/**
 * Base config for page layout builder.
 * This is used in at_core.submit.responsive.inc to help retrieve the form
 * values for each device groups layout.
 */
function page_layout() {
  $variables_array = array(
    'layout',
    'media_query',
    'page_width',
    'page_unit',
    'sidebar_first',
    'sidebar_second',
    'sidebar_unit',
  );
  return $variables_array;
}
