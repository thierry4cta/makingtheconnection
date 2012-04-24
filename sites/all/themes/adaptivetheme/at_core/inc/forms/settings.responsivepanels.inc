<?php

  // Panel and Gpanel Reponsive Layout Settings
  // Build the settings form for responsive panels. This gets its data
  // via responsive_panels_data_structure() in config.inc, which pulls
  // its data from each Panels layout plugin.

  // Supported devices
  $devices = array(
    'tablet_landscape',
    'tablet_portrait',
    'smartphone_landscape',
  );

  // Get the configuration array for panel layouts
  $rpl = responsive_panels_data_structure();

  // This is pretty ugly and will not be sustaintable, what I need is a function
  // that sorts the layouts properly, alphabetical is no good, it needs to be in
  // a very precise order to make sense in the UI.
  if (isset($rpl['one'])) {
    unset($rpl['one']);
  }
  if (isset($rpl['six'])) {
    $six = $rpl['six']; unset($rpl['six']); $rpl['six'] = $six;
  }
  if (isset($rpl['inset'])) {
    $inset = $rpl['inset']; unset($rpl['inset']); $rpl['inset'] = $inset;
  }

  // We need the admin_css files for each plugin
  $panels_admin_css_files = responsive_plugins_admin_css($theme_name, $plugin_type = 'panels');
  foreach ($panels_admin_css_files as $filepath) {
    if (file_exists($filepath)) {
      $panels_css_files['css'][] = array('type' => 'file', 'data' => $filepath, 'weight' => 100);
    }
  }

  // Gpanels and Panels
  $form['at-layout']['panels'] = array(
    '#type' => 'fieldset',
    '#title' => t('Gpanels &amp; Panels'),
    '#description' => t('<h3>Gpanels &amp; Panels</h3><p>These settings apply to both <a href="!gpanels_link" target="_blank">Gpanels</a> and <a href="!panels_link" target="_blank">Panels module</a> layouts.</p><p><strong>Usage:</strong> select layout options for each mobile device orientation.</p>', array('!panels_link' => 'http://drupal.org/project/panels', '!gpanels_link' => 'http://adaptivethemes.com/documentation/using-gpanels')),
    '#attached' => $panels_css_files,
  );

  // Disabled message
  $panels_disable_message = t('<p>The responsive layout is disabled, only the default layout for each Gpanel and Panel layout will be used.</p><p>To re-enable uncheck the "Disable responsive layout and styles" checkbox under the "Settings" tab.</p>');
  if(at_get_setting('disable_responsive_styles') === 1) {
    $form['at-layout']['panels']['disabled'] = array(
      '#markup' => '<div class="messages warning">'. $panels_disable_message .'</div>',
    );
  }

  $form['at-layout']['panels']['panels-wrapper'] = array(
    '#type' => 'fieldset',
    '#attributes' => array('class' => array('panel-option-lists')),
    '#states' => array(
      'disabled' => array('input[name="disable_responsive_styles"]' => array('checked' => TRUE)),
    ),
  );

  // Build the forms
  foreach ($devices as $device) {
    $title = str_replace('_', ' ', drupal_ucfirst($device));
    $form['at-layout']['panels']['panels-wrapper'][$device] = array(
      '#type' => 'fieldset',
      '#title' => t($title),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    if (isset($rpl)) {
      foreach ($rpl as $group => $layouts) {
        $form['at-layout']['panels']['panels-wrapper'][$device][$group] = array(
          '#type' => 'fieldset',
          '#title' => t($group),
          '#collapsible' => TRUE,
          '#collapsed' => TRUE,
        );
        foreach ($layouts as $layout) {
          foreach ($layout as $key => $value) {
            $form['at-layout']['panels']['panels-wrapper'][$device][$group][$device .'_'. $value['theme']] = array(
              '#type' => 'radios',
              '#title' => t($value['title']),
              '#default_value' => theme_get_setting($device .'_'. $value['theme']),
              '#options' => $value['options'],
            );
          }
        }
      }
    }
  }
