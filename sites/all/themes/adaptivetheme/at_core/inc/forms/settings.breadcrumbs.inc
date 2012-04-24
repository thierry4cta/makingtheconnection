<?php

  // Breadcrumb settings
  $form['at']['breadcrumb'] = array(
    '#type' => 'fieldset',
    '#title' => t('Breadcrumbs'),
    '#description' => t('<h3>Breadcrumb Settings</h3>'),
    '#weight' => -70,
  );
  $form['at']['breadcrumb']['bd'] = array(
    '#type' => 'fieldset',
    '#title' => t('Breadcrumbs'),
  );

  // Display?
  $form['at']['breadcrumb']['bd']['breadcrumb_display'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show breadcrumbs'),
    '#default_value' => at_get_setting('breadcrumb_display'),
  );

  // Home link?
  $form['at']['breadcrumb']['bd']['breadcrumb_home'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show the homepage link'),
    '#default_value' => at_get_setting('breadcrumb_home'),
    '#states' => array(
      'visible' => array('input[name="breadcrumb_display"]' => array('checked' => TRUE)),
    ),
  );

  // Seperator
  $form['at']['breadcrumb']['bd']['breadcrumb_separator'] = array(
    '#type'  => 'textfield',
    '#title' => t('Separator'),
    '#description' => t('Text only. Dont forget to include spaces.'),
    '#default_value' => at_get_setting('breadcrumb_separator'),
    '#size' => 8,
    '#maxlength' => 10,
    '#states' => array(
      'visible' => array('input[name="breadcrumb_display"]' => array('checked' => TRUE)),
    ),
  );
