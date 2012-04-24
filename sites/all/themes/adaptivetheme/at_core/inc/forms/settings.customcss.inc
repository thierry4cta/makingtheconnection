<?php

  // Custom CSS
  $form['at']['custom-styles'] = array(
    '#type' => 'fieldset',
    '#title' => t('Custom CSS'),
    '#weight' => 100,
  );
  $form['at']['custom-styles']['custom_css'] = array(
    '#type' => 'textarea',
    '#title' => t('Custom CSS'),
    '#rows' => 15,
    '#default_value' => at_get_setting('custom_css') ? at_get_setting('custom_css') : '/* Add any valid CSS declarations */',
    '#description' => t("The styles you enter here will be saved to the public file system in <code>themename.custom.css</code> and are not affected by upgrades. Consider using a sub-theme if you need to make major changes."),
  );
