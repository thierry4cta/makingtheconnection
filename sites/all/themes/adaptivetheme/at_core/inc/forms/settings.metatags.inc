<?php

  // Metatags for Mobile
  $form['at']['meta'] = array(
    '#type' => 'fieldset',
    '#title' => t('Metatags'),
    '#description' => t('<h3>Metatags</h3><p>Configure meta tags for mobile devices.'),
    '#weight' => -40,
  );
  $form['at']['meta']['mobile'] = array(
    '#type' => 'fieldset',
    '#title' => t('Metatags'),
  );

  // Viewport
  $form['at']['meta']['mobile']['adaptivetheme_meta_viewport'] = array(
    '#type' => 'textfield',
    '#title' => t('viewport'),
    '#default_value' => at_get_setting('adaptivetheme_meta_viewport'),
  );

  // MobileOptimized
  $form['at']['meta']['mobile']['adaptivetheme_meta_mobileoptimized'] = array(
    '#type' => 'textfield',
    '#title' => t('MobileOptimized'),
    '#default_value' => at_get_setting('adaptivetheme_meta_mobileoptimized'),
  );

  // HandheldFriendly
  $form['at']['meta']['mobile']['adaptivetheme_meta_handheldfriendly'] = array(
    '#type' => 'textfield',
    '#title' => t('HandheldFriendly'),
    '#default_value' => at_get_setting('adaptivetheme_meta_handheldfriendly'),
  );

  // apple-mobile-web-app-capable
  $form['at']['meta']['mobile']['adaptivetheme_meta_apple_mobile_web_app_capable'] = array(
    '#type' => 'textfield',
    '#title' => t('apple-mobile-web-app-capable'),
    '#default_value' => at_get_setting('adaptivetheme_meta_apple_mobile_web_app_capable'),
  );

  // Chrome Edge
  $form['at']['meta']['mobile']['chrome_edge'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable Chrome Edge support for IE'),
    '#default_value' => at_get_setting('chrome_edge'),
  );

  // Clear type
  $form['at']['meta']['mobile']['clear_type'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable Cleartype in IE Mobile devices'),
    '#default_value' => at_get_setting('clear_type'),
  );
